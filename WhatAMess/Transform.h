#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Vector3.h"

struct Transform
{
public:
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;
};

#endif
