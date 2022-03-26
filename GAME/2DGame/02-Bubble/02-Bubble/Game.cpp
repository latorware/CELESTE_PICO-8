#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	//scene.init();		Comentada para implentar la jerarquía
	menu.init();
	MScene.init(1);
	actualScene = 0; 
}

bool Game::update(int deltaTime)
{
	//scene.update(deltaTime);
	menu.update(deltaTime);
	MScene.update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//scene.render();

	if (actualScene == 0) {
		menu.render();
	}
	else if (actualScene == 1) {
		MScene.render();
	}
}

void Game::keyPressed(int key)
{
	if (key == 13) // Enter code
		actualScene = 1;
	if (key == 27) // Escape code
		bPlay = false;
	if (key == 49) // Number 1 code
		MScene.init(1);
	if (key == 50) // Number 2 code
		MScene.init(2);
	if (key == 51) // Number 3 code
		MScene.init(3);
	if (key == 52) // Number 4 code
		MScene.init(4);
	if (key == 53) // Number 5 code
		MScene.init(5);
	if (key == 54) // Number 6 code
		MScene.init(6);
	/*if (key == 55) // Number 7 code
		MScene.init(7);*/
	if (key == 56) // Number 8 code
		MScene.init(8);
	if (key == 57) // Number 9 code
		MScene.init(9);
	if (key == 48) // Number 0 code
		MScene.init(10);
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_DOWN && actualScene == 0) { //scroll menu down
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





