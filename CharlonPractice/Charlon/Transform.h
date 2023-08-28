#pragma once
#include "Vector2f.h"

struct Transform
{
	Transform();
	explicit Transform(const Point2f& location);
	explicit Transform(const Point2f& location, const Vector2f& scale, float angle = 0);

	// PushMatrix
	void Push() const;
	// Apply translate, rotate and scale. Insert true to apply scale, rotate, translate
	void Apply(bool inverseConvention = false) const;
	// PopMatrix
	void Pop() const;

	// scale.x = -scale.x
	void FlipX();
	// scale.y = -scale.y
	void FlipY();

	void SetAngleInRad(float rad);
	float GetAngleInRad() const;

	void RotateTowards(const Point2f& target);

	Point2f location;
	Vector2f scale;
	float angle;
};

