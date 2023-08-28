#include "pch.h"
#include "Game.h"

#include "Unit.h"
#include "InfoPlate.h"
#include "Champion.h"
#include "HooverChampion.h"
#include "ProjectileManager.h"
#include "Ability.h"

#include "TargetDummy.h"

#include "utils.h"

#include "SmartTextComponent.h"

#include "OrientationManager.h"
#include "HUD.h"
#include "CameraManager.h"

#include "ResourceManager.h"

#include "LockOnProjectile.h"
#include "SkillShotProjectile.h"

Game::Game(const Window& window)
	:BaseGame(window)
	,m_Window{ window }
{
	ResourceManager::Init("Resources.json");

	m_pCameraManager = new CameraManager{ window };
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	ProjectileManager::ChangeUnits(&m_Units);
	m_ProjectileManager = new ProjectileManager();
	Ability::InitProjManager(m_ProjectileManager);

	m_TestingChamp = new HooverChampion(m_Window, m_ProjectileManager);
	m_TestingChamp->TeleportTo(Point2f{ m_Window.width / 2,m_Window.height / 2 });

	m_Units.push_back(new TargetDummy(Point2f{ 70,50 }));

	m_Orientation = new SmartTextComponent("w");
	m_Orientation->ChangeTransform(Transform{ Point2f{0,m_Window.height - 25} });
	m_FPS = new SmartTextComponent("w", 16, Color4f{ 1,1,1,0.5f });
	m_FPS->ChangeTransform(Transform{ Point2f{0,m_Window.height - 50} });

	m_pCameraManager->SetLevelBoundaries(Rectf{ 0,0,400,400 });
	m_pCameraManager->Track(m_TestingChamp->GetTransform().location);

	m_pInGameHUD = new HUD(HUD::HUDName::ingame);
}

void Game::Cleanup()
{
	delete m_TestingChamp;
	m_TestingChamp = nullptr;
	delete m_ProjectileManager;
	m_ProjectileManager = nullptr;
	for (size_t i{ 0 }; i < m_Units.size(); ++i)
	{
		delete m_Units[i];
		m_Units[i] = nullptr;
	}

	delete m_pInGameHUD;
	m_pInGameHUD = nullptr;
	delete m_pCameraManager;
	m_pCameraManager = nullptr;

	ResourceManager::CleanUp();
}

void Game::Update(float elapsedSec)
{
	// Check keyboard state
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	m_TestingChamp->OnKeyHold(elapsedSec, pStates, m_LastMousePos);
	m_TestingChamp->Update(elapsedSec);
	m_ProjectileManager->UpdateAll(elapsedSec);
	for (size_t i{ 0 }; i < m_Units.size(); ++i)
	{
		m_Units[i]->Update(elapsedSec);
	}
	m_Orientation->UpdateText("Champ loc: " + std::to_string(int(m_TestingChamp->GetTransform().location.x)) + " " + std::to_string(int(m_TestingChamp->GetTransform().location.y)));
	m_FPS->UpdateText(std::to_string(int(1 / elapsedSec)) + " fps");
	m_pCameraManager->Update(elapsedSec, pStates, m_LastMousePos);
}

void Game::Draw() const
{
	ClearBackground();
	glPushMatrix();
	{
		m_pCameraManager->Transform();
		m_TestingChamp->Draw();

		m_ProjectileManager->DrawAll();
		for (Unit* unit : m_Units)
		{
			if (unit)
			{
				unit->Draw();
			}
		}
	}
	glPopMatrix();

	m_pInGameHUD->DrawAll();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_p:
		Unit::SwitchDrawingHitboxes();
		LockOnProjectile::SwitchDrawingHitboxes();
		SkillShotProjectile::SwitchDrawingHitboxes();
		std::cout << std::boolalpha << "[DEBUG] DrawingHitboxes: " << Unit::IsDrawingHitboxes() << std::endl;
		break;
	case SDLK_o:
		InfoPlate::SwitchDrawInfoPlates();
		std::cout << std::boolalpha << "[DEBUG] DrawingInfoPlates: " << InfoPlate::IsDrawingInfoPlates() << std::endl;
		break;
	case SDLK_y:
		m_pCameraManager->ToggleLock();
		break;
	}
	m_TestingChamp->OnKeyDown(e, m_LastMousePos);
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}

	m_TestingChamp->OnKeyUp(e, m_LastMousePos);
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_LastMousePos = Point2f{ float(e.x),float(e.y) };

	m_TestingChamp->OnMouseMotion(e);
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	m_TestingChamp->OnMouseDown(e);
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	m_TestingChamp->OnMouseUp(e);
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
