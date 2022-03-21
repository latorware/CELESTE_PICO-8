#ifndef _MAINMENU_INCLUDE
#define _MAINMENU_INCLUDE


#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


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


private:
	void initShaders();


private: 
	Sprite* selector; 
	Sprite* MenuGui; 
	float currentTime;
	Texture spritesheet, menuGuiTexture; 
	glm::mat4 projection;
	ShaderProgram texProgram;

	const glm::vec2 textureCoordinates = glm::vec2(float(9.f / 16.f), float(15.f / 16.f)); 
	const glm::vec2 startButtonPosition = glm::vec2(float(10), float(10)); 
	const glm::vec2 guideButtonPosition= glm::vec2(float(20), float(10)); 
	const glm::vec2 creditsButtonPosition = glm::vec2(float(30), float(10)); 
	const glm::vec2 exitButtonPosition = glm::vec2(float(40), float(10)); 
	
	enum Positions {
		START, GUIDE, CREDITS, EXIT
	};

	Positions actualPosition; 


};


#endif
