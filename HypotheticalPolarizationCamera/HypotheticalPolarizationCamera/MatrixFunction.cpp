/*
Matrix functions of Hypothetical Polarization Camera

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



This code is written for matrix operations.
And this code is written in Microsoft Visual Studio 2010 C++.

Usage information:
Using the code to complete matrix operations in polarization camera simulation.
--------------------------

Function 1: "MatrixTrans()" 
	
	//Matrix transpose b=a' where a[m][n] b[n][m]
	void MatrixTrans(int m, int n, const double *a, double *b);
	--------------input----------------
    int m,              //The number of rows of the input matrix a
	int n,              //The number of columns of the input matrix a
	const double *a,    //Input matrix a
	-----------------------------------
	-------------output----------------
	double *b,          //The transpose of matrix a
	-----------------------------------

Function 2: "MatrixMultiply()" 
	
	//Matrix multiplication c=a*b where a[m][p] b[p][n] c[m][n]
	void MatrixMultiply(int m,  int p, int n, const double *a,const double *b, double *c);
	--------------input----------------
	int m,                 //The number of rows of the input matrix a
	int p,                 //The number of columns of the input matrix a and rows of the input matrix b
	int n,                 //The number of columns of the input matrix b
	const double *a,       //Input matrix a
	const double *b,       //Input matrix b
	-----------------------------------
	-------------output----------------
	double *c,          //The result of a*b
	-----------------------------------

Function 3: "MatrixAdd()" 
	
	//Matrix addition c=a+b where a[m][n] b[m][n] c[m][n]
	MatrixAdd(int m,int n,const double *a, const double *b, double *c);
	--------------input----------------
	int m,                 //The number of rows of the input matrices a and b
	int n,                 //The number of columns of the input matrices a and b
	const double *a,       //Input matrix a
	const double *b,       //Input matrix b
	-----------------------------------
	-------------output----------------
	double *c,          //The result of a+b
	-----------------------------------

Function 4: "MatrixNorm()" 
	
	//Matrix norm where a[m][n] b(scalar)
	void MatrixNorm(int m,int n,const double *a, double & b);
	--------------input----------------
    int m,                 //The number of rows of the input matrix a
	int n,				   //The number of columns of the input matrix a
	const double *a,       //Input matrix a
	-----------------------------------
	-------------output----------------
	double & b,        //The norm of matrix a
	-----------------------------------

Function 5: "MatrixScalarMultiply()" 
	
	//Scalar multiplication of matrix c=b*a where a[m][n] b(scalar) c[m][n]
	double	MatrixNorm(int m,int n,const double *a);
	--------------input----------------
    int m,                 //The number of rows of the input matrix a
	int n,				   //The number of columns of the input matrix a
	const double *a,       //Input matrix a
	const double b,        //Input Scalar b
	-----------------------------------
	-------------output----------------
	double *c,        //The result of b*a
	-----------------------------------

--------------------------
========================================================================== 
*/



#include "MatrixFunction.h"
#include<math.h>
#include<iostream>

using namespace std;


//Matrix transpose b=a' where a[m][n] b[n][m]
void MatrixTrans(int m, int n, const double *a, double *b)
{
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			b[j*m+i]=a[n*i+j];

}


//Matrix multiplication c=a*b where a[m][p] b[p][n] c[m][n]
void MatrixMultiply(int m,  int p, int n, const double *a,const double *b, double *c)
{
	double temp=0;
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
		{  
		    temp=0;
	    	for(int k=0; k<p; k++)
			    temp+=(a[p*i+k]) *  (b[k*n+j]);
			c[n*i+j]=temp;
		}


}


//Matrix addition c=a+b where a[m][n] b[m][n] c[m][n]
void MatrixAdd(int m,int n,const double *a, const double *b, double *c){
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
		{
			c[i*n+j]=a[i*n+j]+b[i*n+j];
		}
}


//Matrix norm where a[m][n] b(scalar)
void MatrixNorm(int m,int n,const double *a, double & b){
	b = 0.0;
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
		{
			b = b+a[i*n+j]*a[i*n+j];
		}
		b = sqrt(b);
}


//Scalar multiplication of matrix c=b*a where a[m][n] b(scalar) c[m][n]
void MatrixScalarMultiply(int m,int n,const double *a, const double b, double *c){
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
		{
			c[i*n+j]=b*a[i*n+j];
		}
}