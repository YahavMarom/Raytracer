#include "Transformations.h"

// when doing translation * point, we add point_x + translation_x, same for all cords 
Matrix translation(double x, double y, double z) {
    return Matrix(
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    );
}

// multiply each coordinate
Matrix scaling(double x, double y, double z) {
    return Matrix(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
}

// rorate around the x axis by radions
Matrix rotation_x(double radians) {
    return Matrix(
        1, 0, 0, 0, 
        0, cos(radians), -sin(radians), 0,
        0, sin(radians), cos(radians), 0,
        0, 0, 0, 1
    );
}

Matrix rotation_y(double radians) {
    return Matrix(
        cos(radians), 0, sin(radians), 0,
        0, 1, 0, 0,
        -sin(radians), 0, cos(radians), 0,
        0, 0, 0, 1
    );
}

Matrix rotation_z(double radians) {
    return Matrix(
        cos(radians), -sin(radians), 0, 0,
        sin(radians), cos(radians), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}
/*
Scenario: A shearing transformation moves x in proportion to y
Given transform ← shearing(1, 0, 0, 0, 0, 0)
And p ← point(2, 3, 4)
Then transform * p = point(5, 3, 4)
*/
Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y){
    return Matrix(
        1, x_y, x_z, 0,
        y_x, 1, y_z, 0,
        z_x, z_y, 1, 0,
        0, 0, 0, 1

    );
}

Ray transform(const Ray& r, const Matrix& m) {
    return Ray (
        m * r.getOrigin(),
        m * r.getDirection() 
    );

}


Matrix viewTransform(const Tuple& from, const Tuple& to, const Tuple& up) {
    Tuple forward  { (to - from).normalize() };
    Tuple left { cross( forward, up.normalize() ) };
    Tuple trueUp {cross(left, forward)};

    Matrix OrientedMatrix (
        left.getX(), left.getY(), left.getZ(), 0,
        trueUp.getX(), trueUp.getY(), trueUp.getZ(), 0,
        -forward.getX(), -forward.getY(), -forward.getZ(), 0,
        0, 0, 0, 1
    );

    return OrientedMatrix * translation(-from.getX(), -from.getY(), -from.getZ());
}