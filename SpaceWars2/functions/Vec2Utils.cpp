#include "Vec2Utils.hpp"

/*template <typename T>
double Vec2Angle(const Vector2D<T>& v) {
	return Atan2(v.y, v.x);
}*/
double Vec2Angle(const Vec2& v) {
	return Atan2(v.y, v.x);
}

double AngleNormalize(double radians) {
	while (radians < 0) radians += 2 * Pi;
	radians = fmod(radians, 2 * Pi);
	if (radians > Pi) radians -= 2 * Pi;
	return radians;
}
