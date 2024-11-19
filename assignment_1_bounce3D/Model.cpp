#include "Model.h"

/*
Creates a box3D from two points, the bottom left and top right corners.
Creates an array of vertices and normals, and also an index array for drawing
the box.
*/
ElementBuffer create_box3D(const Vector3d& bottom_bl, const Vector3d& top_fr){
	/*
        3|---|2
        0|BAC|1
    |---|---|---|
	|LEF|BOT|RIG|
    |---|---|---|
        |FRO|
        |---|
        |TOP|
        |---|
  */
 	ElementBuffer _elementBuffer;
	Vector3d bottom_br = Vector3d(top_fr.x, bottom_bl.y, bottom_bl.z);
	Vector3d top_br = Vector3d(top_fr.x, top_fr.y, bottom_bl.z);
	Vector3d top_bl = Vector3d(bottom_bl.x, top_fr.y, bottom_bl.z);

	Vector3d bottom_fr = Vector3d(top_fr.x, bottom_bl.y, top_fr.z);
	Vector3d top_fl = Vector3d(bottom_bl.x, top_fr.y, top_fr.z);
	Vector3d bottom_fl = Vector3d(bottom_bl.x, bottom_bl.y, top_fr.z);

	_elementBuffer.vertices = {
		// back_face
		bottom_bl, bottom_br, top_br, top_bl,
		// front face
		bottom_fl, bottom_fr, top_fr, top_fl,
		// left face
		bottom_bl, bottom_fl, top_fl, top_bl,
		// right face
		bottom_br, bottom_fr, top_fr, top_br,
		// bottom face
		bottom_bl, bottom_br, bottom_fr, bottom_fl,
		// top face
		top_bl, top_br, top_fr, top_fl
	};
	Vector3d back_normal = Vector3d(0, 0, -1);
	Vector3d front_normal = Vector3d(0, 0, 1);
	Vector3d left_normal = Vector3d(-1, 0, 0);
	Vector3d right_normal = Vector3d(1, 0, 0);
	Vector3d bottom_normal = Vector3d(0, -1, 0);
	Vector3d top_normal = Vector3d(0, 1, 0);

	_elementBuffer.normals = {
		// back face
		back_normal, back_normal, back_normal, back_normal,
		// front face
		front_normal, front_normal, front_normal, front_normal,
		// left face
		left_normal, left_normal, left_normal, left_normal,
		// right face
		right_normal, right_normal, right_normal, right_normal,
		// bottom face
		bottom_normal, bottom_normal, bottom_normal, bottom_normal,
		// top face
		top_normal, top_normal, top_normal, top_normal
	};

	_elementBuffer.indices = {
		// back face
		0, 1, 2, 0, 2, 3,
		// front face
		4, 5, 6, 4, 6, 7,
		// left face
		8, 9, 10, 8, 10, 11,
		// right face
		12, 13, 14, 12, 14, 15,
		// bottom face
		16, 17, 18, 16, 18, 19,
		// top face
		20, 21, 22, 20, 22, 23
	};
	return _elementBuffer;
}