#include "pch.h"
#include "CameraManager.h"
#include "Camera.h"
#include "OrientationManager.h"

#include "utils.h"

CameraManager::CameraManager(const Window& window)
	:CameraManager(window.width,window.height)
{
}

CameraManager::CameraManager(float width, float height)
	:m_WindowWidth{width}
	,m_WindowHeight{height}
	,m_CamMovementspeed{700}
	,m_pCamera{new Camera{width,height}}
	,m_pTrackingPoint{nullptr}
	,m_UnlockedPoint{0,0}
	,m_IsUnlocked{true}
{
}

CameraManager::~CameraManager()
{
	delete m_pCamera;
	m_pCamera = nullptr;
}

void CameraManager::Transform() const
{
	if (m_IsUnlocked || m_pTrackingPoint == nullptr)
	{
		m_pCamera->Transform(m_UnlockedPoint);
	}
	else if (m_pTrackingPoint)
	{
		m_pCamera->Transform(*m_pTrackingPoint);
	}
}

void CameraManager::Update(float elapsedSec, const Uint8* pStates, const Point2f& mousePos)
{
	if (pStates[SDL_SCANCODE_UP])
	{
		m_UnlockedPoint.y += m_CamMovementspeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_DOWN])
	{
		m_UnlockedPoint.y -= m_CamMovementspeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_UnlockedPoint.x -= m_CamMovementspeed * elapsedSec;
	}
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_UnlockedPoint.x += m_CamMovementspeed * elapsedSec;
	}

	if (m_IsUnlocked || m_pTrackingPoint == nullptr)
	{
		MouseMoveCam(mousePos);
		OrientationManager::UpdateCameraLoc(m_pCamera->GetCameraPosition(m_UnlockedPoint));
	}
	else if (m_pTrackingPoint)
	{
		OrientationManager::UpdateCameraLoc(m_pCamera->GetCameraPosition(*m_pTrackingPoint));
	}
}

void CameraManager::MouseMoveCam(const Point2f& mousePos)
{
	using namespace utils;

	float borderX{ 100 },borderY{100};
	Rectf safeRect{borderX,borderY,m_WindowWidth - borderX * 2,m_WindowHeight - borderY * 2};
	
	if (IsPointInRect(mousePos, safeRect))
	{

	}
	else
	{
		Vector2f direction{mousePos - Point2f{m_WindowWidth / 2,m_WindowHeight / 2} };
		if (abs(direction.y) > abs(direction.x))
		{
			direction.x = 0;
		}
		else
		{
			direction.y = 0;
		}
		direction = direction.Normalized();
		m_UnlockedPoint += direction * m_CamMovementspeed * 0.02f;
	}
}

void CameraManager::Track(const Point2f& point)
{
	m_pTrackingPoint = &point;
	m_UnlockedPoint = point;
	m_IsUnlocked = false;
}

void CameraManager::Unlock()
{
	m_IsUnlocked = true;
	if (m_pTrackingPoint)
	{
		m_UnlockedPoint = *m_pTrackingPoint;
	}
}

void CameraManager::Lock()
{
	m_IsUnlocked = false;
}

void CameraManager::ToggleLock()
{
	if (m_IsUnlocked)
	{
		Lock();
	}
	else
	{
		Unlock();
	}
}

void CameraManager::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_pCamera->SetLevelBoundaries(levelBoundaries);
}

bool CameraManager::IsUnlocked() const
{
	return m_IsUnlocked;
}
