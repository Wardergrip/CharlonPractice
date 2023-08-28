#include "pch.h"
#include "OrientationManager.h"

Point2f OrientationManager::m_CameraLocation{0,0};

Point2f OrientationManager::GetCameraLoc()
{
    return m_CameraLocation;
}

void OrientationManager::UpdateCameraLoc(const Point2f& camPos)
{
    m_CameraLocation = camPos;
}

Point2f OrientationManager::GetWorldLocation(const Point2f& mousePos)
{
    return Point2f(-m_CameraLocation.x + mousePos.x, -m_CameraLocation.y + mousePos.y);
}

Point2f OrientationManager::GetWorldLocation(const SDL_MouseButtonEvent& e)
{
    return GetWorldLocation(Point2f{float(e.x),float(e.y)});
}
