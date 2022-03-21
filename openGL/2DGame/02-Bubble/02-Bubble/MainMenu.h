#ifndef _MAINMENU_INCLUDE
#define _MAINMENU_INCLUDE


#include "Scene.h"



class MainMenu : public Scene {
public:
	MainMenu(); 
	~MainMenu();

	//virtual void init(); 
	virtual void render(); 
	virtual void update(int deltaTime);



private: 

};


#endif //
