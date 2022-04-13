#ifndef _Credits_INCLUDE
#define _Credits_INCLUDE


#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "TileMap.h"


class Credits {
public:
	Credits();
	~Credits();

	void init();
	void render();
	void update(int deltaTime);
	void setGris();
	void treuGris();


private:
	void initShaders();


private:
	Texture textureCredits;
	Sprite* Creditsgui;
	float currentTime;
	glm::mat4 projection;
	ShaderProgram texProgram;

};

#endif