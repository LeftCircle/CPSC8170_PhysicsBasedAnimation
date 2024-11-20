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

#endif