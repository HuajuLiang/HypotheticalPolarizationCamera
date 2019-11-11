# Hypothetical Polarization Camera
 A Visual Studio (VS) 2010 C++ implementation of Hypothetical Polarization Camera is the code of our manuscript 
 "Limitation of Rayleigh Sky Model for Bio-inspired Polarized Skylight Navigation in Three-dimensional Attitude Determination" 
 by Huaju Liang, Hongyang Bai, Ning Liu and Kai Shen.


Table of Contents
--------------------------
Installation

Capture polarization images

Draw polarization images


Installation
--------------------------
Install Visual Studio 2010 and Matlab R2016b.


Capture poalrization images
--------------------------
Open project "HypotheticalPolarizationCamera" with Visual Studio 2010.
Using the code to call the functions "CameraParametersInit()" and "CameraSimulation()".

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

After running the project, the polarization image information is saved to "./output/HypotheticalImages.txt"


Draw polarization images
--------------------------
Place the "ImageDarwing.m" file in the "./output" folder of the "HypotheticalPolarizationCamera" program. 
Then, run "ImageDarwing.m" with MATLAB R2016b after running the "HypotheticalPolarizationCamera" program. 
Above all, "DOP.png" and "AOP.png" can be obtained.
