#pragma once
#include "Transform.h"

class Timer;

class CircleProgression final
{
public:
	static void DrawCircleProgression(const Point2f& location, float radX, float radY, float percentage, bool isFilled);

public:
	CircleProgression(const Point2f& location, const float& percentage, bool isFilled = true);
	CircleProgression(const Point2f& location, const Timer& timer, bool isFilled = true);
	CircleProgression(const Point2f& location = {}, bool isFilled = true);
	CircleProgression(const CircleProgression& other) = default;
	CircleProgression& operator=(const CircleProgression& other) = default;
	CircleProgression(CircleProgression&& other) = default;
	CircleProgression& operator=(CircleProgression&& other) = default;
	~CircleProgression() = default;

	void Draw() const;

	void SetPercentage(float percentage);
	void SetIsFilled(bool isFilled);
	void SetLocation(const Point2f& location);
	void SetScale(const Vector2f& scale);
	void SetRotation(float angle);
	void SetRadX(float radX);
	void SetRadY(float radY);
	void SetRad(float radX, float radY = -1);

	void FlipY();
	void FlipX();

private:
	Transform m_Transform;
	bool m_IsFilled;
	const float& m_pPercentage;
	float m_Percentage;
	float m_RadX, m_RadY;
	const Timer* m_TimerRef;
};

