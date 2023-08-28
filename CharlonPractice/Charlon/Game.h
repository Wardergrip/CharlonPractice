#pragma once
#include "BaseGame.h"
#include <vector>

class Unit;
class Champion;
class ProjectileManager;
class HUD;
class CameraManager;

class SmartTextComponent;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	const Window m_Window;

	Point2f m_LastMousePos;

	Champion* m_TestingChamp;
	ProjectileManager* m_ProjectileManager;
	std::vector<Unit*> m_Units;

	HUD* m_pInGameHUD;
	SmartTextComponent* m_Orientation;
	SmartTextComponent* m_FPS;
	CameraManager* m_pCameraManager;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};