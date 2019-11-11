#ifndef _MATRIXFUNCTION_H_
#define _MATRIXFUNCTION_H_

//Matrix transpose b=a' where a[m][n] b[n][m]
void MatrixTrans(int m, int n, const double *a, double *b);

//Matrix multiplication c=a*b where a[m][p] b[p][n] c[m][n]
void MatrixMultiply(int m,  int p,int n,const double *a, const double *b, double *c);

//Matrix addition c=a+b where a[m][n] b[m][n] c[m][n]
void MatrixAdd(int m,int n,const double *a, const double *b, double *c);

//Matrix norm where a[m][n] b(scalar)
void MatrixNorm(int m,int n,const double *a, double & b);

//Scalar multiplication of matrix c=b*a where a[m][n] b(scalar) c[m][n]
void MatrixScalarMultiply(int m,int n,const double *a, const double b, double *c);

#endif 