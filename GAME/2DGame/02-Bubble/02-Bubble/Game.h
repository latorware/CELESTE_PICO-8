#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "MainMenu.h"
#include "MapScene.h"
#include "Credits.h"
#include "Guide.h"
#include "AudioManager.h"

#define SCREEN_X 16
#define SCREEN_Y 16

#define SCREEN_WIDTH 546
#define SCREEN_HEIGHT 546


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}

public:
	static Game& instance()
	{
		static Game G;

		return G;
	}

	void init();
	bool update(int deltaTime);
	void render();

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	bool checkSlowMode(); 

private:
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	MainMenu menu;						//Escena del menú principal
	Credits credits;
	Guide guide;						//Escena de les instruccions
	MapScene MScene;					// Escena de los niveles del juego
	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time
	int actualScene;
	AudioManager audioManager; 
	bool slowMode; 

};


#endif // _GAME_INCLUDE

