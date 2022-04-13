#ifndef _MAINMENU_INCLUDE
#define _MAINMENU_INCLUDE


#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "MapScene.h"


class MainMenu {
public:
	MainMenu();
	~MainMenu();

	void init();
	void render();
	void update(int deltaTime);
	void setOptionArrowLeft();
	void setOptionArrowRight();
	void setOptionArrowUp();
	void setOptionArrowDown();
	int getOption();
	void setGris();
	void treuGris();


private:
	void initShaders();


private:
	Sprite* selector;
	Sprite* MenuGui;
	float currentTime;
	Texture spritesheet, menuGuiTexture;
	glm::mat4 projection;
	ShaderProgram texProgram;

	const glm::vec2 textureCoordinates = glm::vec2(float(10.f / 16.f), float(0.f / 16.f));
	const glm::vec2 startButtonPosition = glm::vec2(float(20+ SCREEN_X), float(290 + SCREEN_Y));
	const glm::vec2 guideButtonPosition = glm::vec2(float(470 + SCREEN_X), float(290 + SCREEN_Y));
	const glm::vec2 creditsButtonPosition = glm::vec2(float(20 + SCREEN_X), float(380 + SCREEN_Y));
	const glm::vec2 exitButtonPosition = glm::vec2(float(470 + SCREEN_X), float(380 + SCREEN_Y));

	enum Positions {
		START, GUIDE, CREDITS, EXIT
	};

	Positions actualPosition;

};

#endif