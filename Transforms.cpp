#include "Transforms.h"

mat4 Transforms::translate(const float &tx, const float &ty, const float &tz) {
	mat4 ret = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1);
	return ret;
}


mat3 Transforms::rotate(const vec3& axis, const float degrees) {
  const float radians = degrees * pi / 180; // Convert to radians
	const vec3 norm = glm::normalize(axis); // Normalize axis of rotation

	const mat3 identity_cos = cosf(radians) * mat3(1,0,0,0,1,0,0,0,1);
	const mat3 astar_sin    = sinf(radians) * mat3(0, norm.z, -norm.y,
																							  -norm.z, 0, norm.x,
																							  norm.y, -norm.x, 0);
	const mat3 aat = (1 - cosf(radians)) *
		mat3 (pow(norm.x, 2), norm.x * norm.y, norm.x * norm.z,
	        norm.x * norm.y, pow(norm.y, 2), norm.y * norm.z,
				  norm.x * norm.z, norm.y * norm.z, pow(norm.z, 2));

	return identity_cos + aat + astar_sin;
}


mat4 Transforms::scale(const float &sx, const float &sy, const float &sz) {
	mat4 ret = mat4(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
	return ret;
}
