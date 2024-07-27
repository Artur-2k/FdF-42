#include "fdf.h"

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

float	normalize_angle(float angle)
{
	return (fmod(angle, 360.0));
}
