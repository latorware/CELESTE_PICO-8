#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"

#define SCREEN_X 16
#define SCREEN_Y 16

#define SCREEN_WIDTH 546
#define SCREEN_HEIGHT 546

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:

	void virtual init();
	void initObjects();
	void virtual update(int deltaTime);
	void virtual render();
	void renderClouds();
	void renderSnow();

protected:
	void initShaders();

protected:
	Texture spritesheet;
	vector<Sprite*> snowFlakes;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int snowPosition;
	vector<int> randomSnow;

};


#endif // _SCENE_INCLUDE

