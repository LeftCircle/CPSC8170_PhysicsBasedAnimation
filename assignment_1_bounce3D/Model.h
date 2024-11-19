#ifndef MODEL_H
#define MODEL_H

#include "Vector.h"
#include "ECSCoordinator.h"

#include <vector>


struct Transform
{
	Vector3d position;
	Vector3d rotation;
	Vector3d scale;
};

struct RigidBody
{
	Vector3d velocity;
	Vector3d acceleration;
};

struct Collidable
{
	float CRestitution;
};

struct ElementBuffer{
	std::vector<int> indices;
	std::vector<Vector3d> vertices;
	std::vector<Vector3d> normals;
};

ElementBuffer create_box3D(const Vector3d& bottom_bl, const Vector3d& top_fr);

// class Box3D{
// 	// a box with the bottom drawn, and the other five sides drawn with wires
// 	// in opengl, the box is drawn centered at the origin, with sides of length 1
// public:
// 	Box3D(const Vector3d& blc, const Vector3d& trc);


// private:
// 	// One side is 
// 	// a -- b
// 	// |    |
// 	// c -- d
// 	// vertices = [a, b, c, d]
// 	// normals  = [na, nb, nc, nd]
// 	// indeces  = [0, 1, 2, 1, 2, 3]
// 	// x6 for each side
// 	ElementBuffer _elementBuffer;
// };


#endif