#include "Transformations.h"


Matrix translation(double x, double y, double z) {
    return Matrix(
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    );
}

Matrix scaling(double x, double y, double z) {
    return Matrix(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
}


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

Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y){
    return Matrix(
        1, x_y, x_z, 0,
        y_x, 1, y_z, 0,
        z_x, z_y, 1, 0,
        0, 0, 0, 1

    );
}
