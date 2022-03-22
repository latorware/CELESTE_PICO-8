#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	//scene.init();
	menu.init();
	actualScene = 0; 
}

bool Game::update(int deltaTime)
{
	//scene.update(deltaTime);
	menu.update(deltaTime); 


	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//scene.render();
	menu.render(); 
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_DOWN && actualScene== 0) { //scroll menu down
		menu.setOptionArrowDown(); 
	}
	if (key == GLUT_KEY_UP && actualScene == 0) { //scroll menu down
		menu.setOptionArrowUp();
	}
	if (key == GLUT_KEY_RIGHT && actualScene == 0) { //scroll menu down
		menu.setOptionArrowRight();
	}
	if (key == GLUT_KEY_LEFT && actualScene == 0) { //scroll menu down
		menu.setOptionArrowLeft();
	}
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





