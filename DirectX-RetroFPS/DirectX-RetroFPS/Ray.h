#pragma once

#include "Vector.h"

struct Ray
{
	Ray()
	{
		Origin = Vector();
		Direction = Vector();
	}

	Ray(Vector origin, Vector direction)
	{
		Origin = origin;
		Direction = direction;
	}

	Vector ClosestPointOnRay(Vector point)
	{
		Vector normDir = Direction.GetNormalized();
		Vector rayVector = point - Origin;

		return Origin + normDir * Vector::DotProduct(rayVector, normDir);
	}

	bool IsValid()
	{
		return !Direction.IsZero();
	}

	Vector Origin;
	Vector Direction;
};