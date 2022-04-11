#ifndef _GUIDE_INCLUDE
#define _GUIDE_INCLUDE

#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Guide : public Scene 
{
public:

	Guide();
	~Guide();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:

	Texture textureGuide;
	Sprite* Guidegui;
	float currentTime;
	glm::mat4 projection;
	ShaderProgram texProgram;
		 
};

#endif