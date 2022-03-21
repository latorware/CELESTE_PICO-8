#ifndef _MAINMENU_INCLUDE
#define _MAINMENU_INCLUDE


#include "Scene.h"



class MainMenu : public Scene {
public:
	MainMenu(ShaderProgram &shaderProgram); 
	~MainMenu();

	//virtual void init(); 
	virtual void render(); 
	virtual void update(int deltaTime);
	void setOption(int option); 

private: 
	Sprite* selector;
	Sprite* background; 
	float currentTime;
	Texture spritesheet;
	glm::mat4 projection;
	Texture scene; 

};


#endif
