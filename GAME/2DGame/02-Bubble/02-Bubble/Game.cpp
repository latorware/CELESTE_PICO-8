#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	//AllocConsole(); //consola per debuguejar
	//freopen("CONOUT$", "w", stdout); //consola per debuguejar
	//cout << "a" << endl; 
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	scene.init();				//inicializa shaders que se usan en las subclases 
	scene.initObjects();		//inicializa los objetos en una funci�n diferente para evitar un uso excesivo de la memoria
	menu.init();
	MScene.init(1);
	actualScene = 0; //0 = menu		1 = game	2 = guide		3 = credits
	credits.init(); 
}

bool Game::update(int deltaTime)
{

	scene.update(deltaTime);

	if (actualScene == 0) {
		menu.update(deltaTime);
	}
	else if (actualScene == 1) {	//solo actualiza el juego si estamos en un nivel, para que los clics del teclado anteriores no afecten al Player
		MScene.update(deltaTime); 
	}
	else if (actualScene == 3)
	{
		credits.update(deltaTime); 
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (actualScene == 0) {
		menu.render();
	}
	else if (actualScene == 1) {
		scene.renderClouds(); //solo renderiza las nubes si estamos en un nivel
		MScene.render();
	}
	else if (actualScene == 3)
	{
		credits.render(); 
	}

	scene.renderSnow(); //renderiza la nieve en todo el juego
}

void Game::keyPressed(int key)
{
	if (key == 13) // Enter code
	{
		actualScene = 1;
		if (menu.getOption() == 0)
		{
			actualScene = 1;
		}
		else if (menu.getOption() == 2)
		{
			actualScene = 3;
		}
		else if (menu.getOption() == 3)
		{
			bPlay = false;
		}
	}

	if (key == 27) // Escape code
	{
		if (actualScene == 0) // Si estamos en una pantalla que no es el men� principal, volvemos a el
			bPlay = false;
		else actualScene = 0; // Si estamos en el men� principal, cerramos el juego
	}

	if (actualScene == 1) {		//Solo se inicializan los mapas una vez pulsamos jugar (mejor gestion de memoria)
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
		if (key == 55) // Number 7 code
			MScene.init(7);
		if (key == 56) // Number 8 code
			MScene.init(8);
		if (key == 57) // Number 9 code
			MScene.init(9);
		if (key == 48) // Number 0 code
			MScene.init(10);
	}
	
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





