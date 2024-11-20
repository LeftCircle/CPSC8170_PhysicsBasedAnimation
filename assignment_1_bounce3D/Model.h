#ifndef MODEL_H
#define MODEL_H

#include "Vector.h"
#include "ECSCoordinator.h"

#include <vector>

#define RED 1.0, 0.0, 0.0
#define GREEN 0.0, 1.0, 0.0
#define BLUE 0.0, 0.0, 1.0
#define YELLOW 1.0, 1.0, 0.0
#define CYAN 0.0, 1.0, 1.0
#define PURPLE 1.0, 0.0, 1.0

inline void set_color3(float (&color)[3], float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

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
	std::vector<Vector3d> colors;
};

ElementBuffer create_box3D(const Vector3d& bottom_bl, const Vector3d& top_fr);

void build_model();

#endif