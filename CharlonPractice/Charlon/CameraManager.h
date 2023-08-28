#pragma once

class Camera;

class CameraManager final
{
public:
	CameraManager(const Window& window);
	CameraManager(float width, float height);
	CameraManager(const CameraManager& other) = delete;
	CameraManager& operator=(const CameraManager& other) = delete;
	CameraManager(CameraManager&& other) = delete;
	CameraManager& operator=(CameraManager&& other) = delete;
	~CameraManager();

	void Transform() const;
	void Update(float elapsedSec, const Uint8* pStates, const Point2f& mousePos);

	void Track(const Point2f& point);

	void Unlock();
	void Lock();
	void ToggleLock();

	void SetLevelBoundaries(const Rectf& levelBoundaries);

	bool IsUnlocked() const;

private:
	const float m_WindowWidth;
	const float m_WindowHeight;
	float m_CamMovementspeed;
	const Point2f* m_pTrackingPoint;
	Point2f m_UnlockedPoint;
	Camera* m_pCamera;
	bool m_IsUnlocked;

	void MouseMoveCam(const Point2f& mousePos);
};

