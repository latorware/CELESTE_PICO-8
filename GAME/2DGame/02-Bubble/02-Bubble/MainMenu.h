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
	int getOption(); 


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
	const glm::vec2 startButtonPosition = glm::vec2(float(20), float(290)); 
	const glm::vec2 guideButtonPosition= glm::vec2(float(470), float(290)); 
	const glm::vec2 creditsButtonPosition = glm::vec2(float(20), float(380)); 
	const glm::vec2 exitButtonPosition = glm::vec2(float(470), float(380)); 
	
	enum Positions {
		START, GUIDE, CREDITS, EXIT
	};

	Positions actualPosition; 

};

#endif
