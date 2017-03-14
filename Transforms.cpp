#include "Transforms.h"

stack()
	: c()
{	// construct with empty container
}

mat4 Transforms::translate(const float &tx, const float &ty, const float &tz) {
	mat4 ret = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1);
	return ret;
}


mat3 Transforms::rotate(const vec3& axis, const float degrees) {
	mat3 IMatrix = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);

	vec3 axis1 = normalize(axis);

	mat3 aa = outerProduct(axis1, axis1);
	mat3 A = mat3(0, axis1.z, (-1)*axis1.y, (-1)*axis1.z, 0, axis1.x, axis1.y, (-1)*axis1.x, 0);

	mat3 rotationMatrix = (IMatrix * (float)cos(degrees)) + (aa*(1 - (float)cos(degrees))) + (A*(float)sin(degrees));

	return rotationMatrix;
}


mat4 Transforms::scale(const float &sx, const float &sy, const float &sz) {
	mat4 ret = mat4(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
	return ret;
}


void Transforms::pushTransform(const value_type& _Val) {
	// insert element at end
	c.push_back(_Val);
}


void popTransform() {
	// erase last element
	c.pop_back();
}