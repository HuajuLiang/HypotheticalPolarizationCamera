#ifndef _POLARIZATIONCAMERA_H_
#define _POLARIZATIONCAMERA_H_

//polarization camera parameters struct
typedef struct CameraParameters
{

	double  D_x;            //Unit cell size of CCD or COMS (unit is micrometer)
	double  D_z;            //Unit cell size of CCD or COMS (unit is micrometer)
	int     n_x;            //Image pixel size (unit is pixel)
	int     n_z;            //Image pixel size (unit is pixel)
	double  f;              //Focus of the camera (unit is millimeter)

	int     PixelInterval;  //Convenient for debugging. Its value is 1 for practical application.(unit is pixel)

	double  psa;            //yaw angle (unit is degree)
	double  afa;            //pitch angle (unit is degree)
	double  beta;           //roll angle (unit is degree)
}
CameraParameters;


//Initialize the hypothetical polarization camera parameters.
CameraParameters * CameraParametersInit(
	const double  D_x,           //Unit cell size of CCD or COMS (unit is micrometer)
	const double  D_z,           //Unit cell size of CCD or COMS (unit is micrometer)
	const int     n_x,           //Image pixel size (unit is pixel)
	const int     n_z,           //Image pixel size (unit is pixel)
	const double  f,             //Focus of the camera (unit is millimeter)
	const int     PixelInterval  //Convenient for debugging. Its value is 1 for practical application.(unit is pixel)
        );

//Hypothetical polarization camera simulation based on Rayleigh sky model.
void CameraSimulation(
	const double  psa,        //yaw angle (unit is radian)
	const double  afa,        //pitch angle (unit is radian)
    const double  beta,       //roll angle (unit is radian)
	CameraParameters *	parm  //camera parameters
	);

#endif //