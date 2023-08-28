#pragma once

#include <vector>

class UserInterfaceElement;

class HUD final
{
// STATICS
public:
	enum class HUDName 
	{
		UNDEFINED = 0,
		ingame
	};
	static void QueueUI(const std::pair<HUDName, UserInterfaceElement*>& pair);

private:
	static std::vector<std::pair<HUDName, UserInterfaceElement*>> c_UIQueue;
	static void SwapQueueIdx(int a, int b);

// NON STATICS
public:
	HUD(HUDName name, bool readQueue = true);
	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& other) = delete;
	~HUD();

	void DrawAll() const;

	void Pushback(UserInterfaceElement* newElement);

	void ReadQueueAndPushback();
private:
	HUDName m_Name;
	std::vector<UserInterfaceElement*>  m_pUserInterfaceElements;
};

