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
	scene.initObjects();		//inicializa los objetos en una función diferente para evitar un uso excesivo de la memoria
	menu.init();
	actualScene = 0; //0 = menu		1 = game	2 = guide		3 = credits
	audioManager.menuMusicPlay(); 
	credits.init();
	guide.init();
	slowMode = false; 
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);

	if (actualScene == 0) 
	{
		menu.update(deltaTime);
	}
	else if (actualScene == 1) //solo actualiza el juego si estamos en un nivel, para que los clics del teclado anteriores no afecten al Player
	{	
		if (MScene.jocAcabat())
		{
			actualScene = 3; 
		}
		else
		{
			MScene.update(deltaTime);
		}
	}
	else if (actualScene == 2)
	{
		guide.update(deltaTime);
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

	if (actualScene == 0) 
	{
		menu.render();
	}
	else if (actualScene == 1) 
	{
		//scene.renderClouds(); //solo renderiza las nubes si estamos en un nivel
		MScene.render();
	}
	else if (actualScene == 2) 
	{
		guide.render();
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
		if (menu.getOption() == 0)
		{
			audioManager.menuMusicStop();
			audioManager.gameMusicPlay();
			MScene.comensaJoc(&audioManager); 
			actualScene = 1;
		}
		else if (menu.getOption() == 1)
		{
			actualScene = 2;
			if (actualScene != 2)
			{
				audioManager.selectSoundPlay();
			}
		}
		else if (menu.getOption() == 2)
		{
			actualScene = 3;
			if (actualScene != 3)
			{
				audioManager.selectSoundPlay();
			}
		}
		else if (menu.getOption() == 3)
		{
			bPlay = false;
		}
	}

	if (key == 27) // Escape code
	{
		if (actualScene == 0) // Si estamos en una pantalla que no es el menú principal, volvemos a el
			bPlay = false;
		else
		{
			audioManager.gameMusicStop(); 
			audioManager.menuMusicPlay(); 
			audioManager.selectSoundPlay();
			actualScene = 0; // Si estamos en el menú principal, cerramos el juego
		}
	}

	if (actualScene == 1) {		//Solo se inicializan los mapas una vez pulsamos jugar (mejor gestion de memoria)
		if (key == 49) // Number 1 code
			MScene.canviaNivell(1); 
		if (key == 50) // Number 2 code
			MScene.canviaNivell(2);
		if (key == 51) // Number 3 code
			MScene.canviaNivell(3);
		if (key == 52) // Number 4 code
			MScene.canviaNivell(4);
		if (key == 53) // Number 5 code
			MScene.canviaNivell(5);
		if (key == 54) // Number 6 code
			MScene.canviaNivell(6);
		if (key == 55) // Number 7 code
			MScene.canviaNivell(7);
		if (key == 56) // Number 8 code
			MScene.canviaNivell(8);
		if (key == 57) // Number 9 code
			MScene.canviaNivell(9); ;
		if (key == 48) // Number 0 code
			MScene.canviaNivell(10);
	}

	if (key == 83 || key == 115) // s, toggle speed
	{
		if (slowMode)
		{
			slowMode = false; 
			audioManager.menuMusicNormalMode();
			audioManager.gameMusicNormalMode();
			MScene.treuGris();
			credits.treuGris();
			menu.treuGris();
			guide.treuGris();
		}
		else
		{
			slowMode = true; 
			audioManager.menuMusicSlowMode();
			audioManager.gameMusicSlowMode();
			credits.setGris();
			menu.setGris();
			guide.setGris();
			MScene.setGris();
		}
	}


	if (key == 71 || key == 103) //g, la invulnerabilitat
	{
		MScene.toggleInvulnerabilitat();
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
		audioManager.selectSoundPlay();
		menu.setOptionArrowDown();
	}
	if (key == GLUT_KEY_UP && actualScene == 0) { //scroll menu down
		audioManager.selectSoundPlay();
		menu.setOptionArrowUp();
	}
	if (key == GLUT_KEY_RIGHT && actualScene == 0) { //scroll menu down
		audioManager.selectSoundPlay();
		menu.setOptionArrowRight();
	}
	if (key == GLUT_KEY_LEFT && actualScene == 0) { //scroll menu down
		audioManager.selectSoundPlay();
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

bool Game::checkSlowMode()
{
	return slowMode; 
}


