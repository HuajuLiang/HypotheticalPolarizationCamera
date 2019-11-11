/*
"CameraParametersInit()" and "CameraSimulation()" functions of Hypothetical Polarization Camera

==========================================================================

Copyright (c) 2019 - 2020, Huaju Liang and Hongyang Bai
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * None of the names of the contributors may be used to endorse or promote 
      products derived from this software without specific prior written 
      permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
==========================================================================


This file is part of an implementation of Hypothetical Polarization Camera
which is the code of our manuscript


     "Limitation of Rayleigh Sky Model for Bio-inspired Polarized Skylight Navigation in Three-dimensional Attitude Determination"
                                    
                                   by 

                       Huaju Liang and Hongyang Bai
              Nanjing University of Science and Technology in Nanjing, China


                        Version: 1.1, October 23, 2019
=========================================================================



This code is written for simulating polarization camera based on Rayleigh sky model.
And this code is written in Microsoft Visual Studio 2010 C++.

Usage information:
Using the code to simulate DOP (degree of polarization) and AOP (angle of polarization) based on Rayleigh sky model.
--------------------------

Function 1: "CameraParametersInit()" 
	
	//Initialize the hypothetical polarization camera parameters.
	CameraParameters * CameraParametersInit(
		const double  D_x,
		const double  D_z,
		const int     n_x,
		const int     n_z,
		const double  f,
		const int     PixelInterval
    );
	--------------input----------------
	const double  D_x,           //Unit cell size of CCD or COMS (unit is micrometer)
	const double  D_z,           //Unit cell size of CCD or COMS (unit is micrometer)
	const int     n_x,           //Image pixel size (unit is pixel)
	const int     n_z,           //Image pixel size (unit is pixel)
	const double  f,             //Focus of the camera (unit is millimeter)
	const int     PixelInterval  //Convenient for debugging. Its value is 1 for practical application.(unit is pixel)
	-----------------------------------
	-------------output----------------
	CameraParameters *           //Record camera parameters
	-----------------------------------


Function 2: "CameraSimulation()" 

    //Hypothetical polarization camera simulation based on Rayleigh sky model.
	void CameraSimulation(
		const double  psa,
		const double  afa,
		const double  beta,
		CameraParameters *	parm 
	);
	--------------input----------------
	const double  psa,        //yaw angle (unit is radian)
	const double  afa,        //pitch angle (unit is radian)
    const double  beta,       //roll angle (unit is radian)
	CameraParameters *	parm  //camera parameters
	-----------------------------------
	-------------output----------------
	HypotheticalImages.txt          //Record DOP and AOP captured by polarization camera based on Rayleigh sky model.
	-----------------------------------

--------------------------
========================================================================== 
*/


#include<math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include"PolarizationCamera.h"
#include"MatrixFunction.h"

#ifndef ALLOC
#define ALLOC(_struct)              ((_struct *)malloc(sizeof(_struct)))
#endif
const double pi = 3.141592653589793;

using namespace std;

ofstream HypotheticalImages("output\\HypotheticalImages.txt");

//Initialize the hypothetical polarization camera parameters.
CameraParameters * CameraParametersInit(
	const double  D_x,           //Unit cell size of CCD or COMS (unit is micrometer)
	const double  D_z,           //Unit cell size of CCD or COMS (unit is micrometer)
	const int     n_x,           //Image pixel size (unit is pixel)
	const int     n_z,           //Image pixel size (unit is pixel)
	const double  f,             //Focus of the camera (unit is millimeter)
	const int     PixelInterval  //Convenient for debugging. Its value is 1 for practical application.(unit is pixel)
        ){
			CameraParameters  * parm = ALLOC(CameraParameters);

			parm->f = f;
			parm->D_x = D_x/1000.0;
			parm->D_z = D_z/1000.0;
			parm->n_x = n_x;
			parm->n_z = n_z;

			parm->PixelInterval = PixelInterval;

			return parm;
}



//Hypothetical polarization camera simulation based on Rayleigh sky model.
void CameraSimulation(
	const double  psa,        //yaw angle (unit is radian)
	const double  afa,        //pitch angle (unit is radian)
    const double  beta,       //roll angle (unit is radian)
	CameraParameters *	parm  //camera parameters
	){
	//three Euler angles
	parm->psa = psa;   //yaw angle (unit is radian)
	parm->afa = afa;   //pitch angle (unit is radian)
	parm->beta = beta; //roll angle (unit is radian)

	//rotation matrix
	double C_vTb[3][3] = {cos(parm->beta)*cos(parm->psa)+sin(parm->beta)*sin(parm->afa)*sin(parm->psa),     -cos(parm->beta)*sin(parm->psa)+sin(parm->beta)*sin(parm->afa)*cos(parm->psa),     -sin(parm->beta)*cos(parm->afa),
						  cos(parm->afa)*sin(parm->psa),														cos(parm->afa)*cos(parm->psa),                                                       sin(parm->afa),
						  sin(parm->beta)*cos(parm->psa)-cos(parm->beta)*sin(parm->afa)*sin(parm->psa),     -sin(parm->beta)*sin(parm->psa)-cos(parm->beta)*sin(parm->afa)*cos(parm->psa),     cos(parm->beta)*cos(parm->afa),
			};	//rotation matrix from solar vector to body coordinate system
	double C_bTv[3][3];//rotation matrix from body to solar vector coordinate system
	MatrixTrans(3, 3,C_vTb[0], C_bTv[0]);

	//Calculate DOP and AOP of each pixels.
	for(int i_x=1; i_x<=parm->n_x; i_x=i_x+parm->PixelInterval){
		for(int j_z=1; j_z<=parm->n_z; j_z=j_z+parm->PixelInterval){

			//location of a pixel P in pixel coordinate system
			double P_x = parm->D_x*(i_x-(parm->n_x+1)/2);
			double P_z = parm->D_z*(j_z-(parm->n_z+1)/2);
		    double Vector_b_P[3][1] = {P_x,0.0,P_z};	//location

			//shooting direction of pixel P in solar vector coordinate system
			double Vector_b_f[3][1] = {0.0,parm->f,0.0};
			double Vector_b_PaF[3][1] = {0.0,0,0.0};
			double Vector_v_P[3][1] = {0.0,0,0.0};		//shooting direction
			MatrixAdd(3,1,Vector_b_P[0],Vector_b_f[0],Vector_b_PaF[0]);
			MatrixMultiply(3,3,1,C_bTv[0],Vector_b_PaF[0],Vector_v_P[0]);

			//zenith angle and yaw angle of pixel P in solar vector coordinate system
			double Vector_v_P_Norm = 0.0;
			MatrixNorm(3,1,Vector_v_P[0],Vector_v_P_Norm);
			double sita_v_P = acos(Vector_v_P[2][0]/Vector_v_P_Norm);	//zenith angle
			double fi_v_P = 0.0;	//yaw angle
			if(Vector_v_P[0][0]>0 && Vector_v_P[1][0]>=0){	//quadrants judgement.
				fi_v_P = atan(Vector_v_P[1][0]/Vector_v_P[0][0]);
			}
			else if(Vector_v_P[0][0]<0 && Vector_v_P[1][0]>=0){
				fi_v_P = atan(Vector_v_P[1][0]/Vector_v_P[0][0])+pi;
			}
			else if(Vector_v_P[0][0]>0 && Vector_v_P[1][0]<=0){
				fi_v_P = atan(Vector_v_P[1][0]/Vector_v_P[0][0])+2*pi;
			}
			else if(Vector_v_P[0][0]<0 && Vector_v_P[1][0]<=0){
				fi_v_P = atan(Vector_v_P[1][0]/Vector_v_P[0][0])+pi;
			}
			else if(Vector_v_P[0][0]==0 && Vector_v_P[1][0]>0){
				fi_v_P = pi;
			}
			else if(Vector_v_P[0][0]==0 && Vector_v_P[1][0]<0){
				fi_v_P = -pi;
			}
			else if(Vector_v_P[0][0]==0 && Vector_v_P[1][0]==0){
				fi_v_P = 0.0;
			}

			//DOP of pixel P based on Rayleigh sky model
			double DOP_max = 1;	//maximum DOP in the sky
			double DOP = DOP_max*sin(sita_v_P)*sin(sita_v_P)/(1+cos(sita_v_P)*cos(sita_v_P));	//DOP

			//AOP of pixel P based on Rayleigh sky model
			double E_v_P[3][1] = {sin(fi_v_P),-cos(fi_v_P),0.0};	//polarization E-vector in solar vector coordinate system
			double E_b_P[3][1] = {0.0,0.0,0.0};						//polarization E-vector in body coordinate system
			MatrixMultiply(3,3,1,C_vTb[0],E_v_P[0],E_b_P[0]);
			double AOP = atan(E_b_P[0][0]/E_b_P[2][0]);				//AOP
			if(DOP==0.0){	//	Elimination of invalid solution
				AOP = 0.0;	
			}

			//Record DOP and AOP to HypotheticalImages.txt in output folder.
			HypotheticalImages<<setprecision(16)
			<<i_x<<setw(25)<<j_z<<setw(25)
			<<DOP<<setw(25)<<AOP*180/pi<<endl;
			//HypotheticalImages.txt
			//The first column is i_x (column coordinate in pixel coordinate system)
			//The second column is j_z (raw coordinate in pixel coordinate system)
			//The third column is DOP (degree of polarization)
			//The forth column is AOP (angle of polarization and the unit of AOP is degree )

		}
	}
}