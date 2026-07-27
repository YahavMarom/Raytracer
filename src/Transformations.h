#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H


#include "Matrix.h"
#include "Ray.h"

Matrix translation(double x, double y, double z);
Matrix scaling(double x, double y, double z);
Matrix rotation_x(double radians);
Matrix rotation_y(double radians);
Matrix rotation_z(double radians);
Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);


Ray transform(const Ray& r, const Matrix& m);


#endif