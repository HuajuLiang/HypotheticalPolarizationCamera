/*
"main()" function of Hypothetical Polarization Camera

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



This code is written for calling the functions of Hypothetical Polarization Camera.
And this code is written in Microsoft Visual Studio 2010 C++.

Usage information:
Using the code to call the functions "CameraParametersInit()" and "CameraSimulation()".
--------------------------

Step 1: Initialize the hypothetical polarization camera parameters.

	CameraParameters * Camera_paremeters;//Record camera parameters
	double Camera_D_x = 5.2;//Unit cell size of CCD or COMS (unit is micrometer)
	double Camera_D_z = 5.2;//Unit cell size of CCD or COMS (unit is micrometer)
	int Camera_n_x = 1024;//Image pixel size (unit is pixel)
	int Camera_n_z = 1280;//Image pixel size (unit is pixel)
	double Camera_f = 4.0;//Focus of the camera (unit is millimeter)

	int Camera_PixelInterval = 1;//Convenient for debugging. Its value is 1 for practical application.
	
	//call the function "CameraParametersInit()" to initialize the camera parameters.
	CameraParameters = CameraParametersInit(
				Camera_f,      
				Camera_D_x,  
				Camera_D_z,
				Camera_n_x, 
				Camera_n_z,
				Camera_PixelInterval
        );


Step 2: Hypothetical polarization camera simulation.

	//Three Euler angles of camera (from body to solar vector coordinate system)
	double  psa = 78.9;//yaw angle (unit is degree)
	double  afa = -65.2;//pitch angle (unit is degree)
    double  beta = 278.3;//roll angle (unit is degree)
		
	//Call the function "CameraSimulation()" to simulate polarization camera.
	CameraSimulation(psa*pi/180.0,afa*pi/180.0,beta*pi/180.0,camera_state);

--------------------------
========================================================================== 
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "PolarizationCamera.h"
#include "MatrixFunction.h"

using namespace std;
const double pi = 3.141592653589793;


int main(){


	CameraParameters * Camera_paremeters;//Record camera parameters

	//Camera parameters
	double Camera_D_x = 5.2;      //Unit cell size of CCD or COMS (unit is micrometer)
	double Camera_D_z = 5.2;      //Unit cell size of CCD or COMS (unit is micrometer)
	int    Camera_n_x = 1024;     //Image pixel size (unit is pixel)
	int    Camera_n_z = 1280;     //Image pixel size (unit is pixel)
	double Camera_f = 4.0;        //Focus of the camera (unit is millimeter)

	int Camera_PixelInterval = 1; //Convenient for debugging. Its value is 1 for practical application.(unit is pixel)
	
	//Call the function "CameraParametersInit()" to initialize the camera parameters.
	Camera_paremeters = CameraParametersInit(
				Camera_D_x,  
				Camera_D_z,
				Camera_n_x, 
				Camera_n_z,
				Camera_f,
				Camera_PixelInterval
        );

	//Three Euler angles of camera (from body to solar vector coordinate system)
	double  psa = 78.9;//yaw angle (unit is degree)
	double  afa = -65.2;//pitch angle (unit is degree)
    double  beta = 278.3;//roll angle (unit is degree)

	//Call the function "CameraSimulation()" to simulate polarization camera.		
	CameraSimulation(psa*pi/180.0,afa*pi/180.0,beta*pi/180.0,Camera_paremeters);

    return 0;
}

