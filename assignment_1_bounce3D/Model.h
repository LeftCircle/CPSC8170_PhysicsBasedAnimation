#ifndef MODEL_H
#define MODEL_H

#include "Vector.h"

class Transform{
public:
	Transform();
	Transform(Vector3d position, Vector3d rotation, Vector3d scale);
	~Transform();
	
	Vector3d position;
	Vector3d rotation;
	Vector3d scale;
}

class Model{

}


#endif