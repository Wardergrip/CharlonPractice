#pragma once
class OrientationManager final
{
public:
	OrientationManager() = delete;

	static Point2f GetCameraLoc();
	static void UpdateCameraLoc(const Point2f& camPos);
	static Point2f GetWorldLocation(const Point2f& mousePos);
	static Point2f GetWorldLocation(const SDL_MouseButtonEvent& e);

private:
	static Point2f m_CameraLocation;
};

