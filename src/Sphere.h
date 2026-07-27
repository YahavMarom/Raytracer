#ifndef SPHERE_H
#define SPHERE_H

class Sphere {

private:
    int m_id;
    static int m_nextId; 

public:
    Sphere();
    int getID() const;


};


bool operator==(const Sphere& a, const Sphere& b);


#endif