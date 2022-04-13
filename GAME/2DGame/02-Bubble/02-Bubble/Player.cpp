#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include <stdlib.h> 


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 80
#define FALL_STEP 4
#define DURACIOTREMOLAR 500
#define STRENGTHTREMOLAR 15
#define LIMITINFERIOR 479

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, LOOK_UP_LEFT, LOOK_UP_RIGHT, LOOK_DOWN_LEFT, LOOK_DOWN_RIGHT,
	DASH_LEFT, DASH_RIGHT
};


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, AudioManager* audioManagerr)
{
	audioManager = audioManagerr; 
	fentTremolar = make_pair(false, 0.f); 
	tremolarAlCaure = false; 
	displacement = glm::vec2(float(0.f), float(0.f));
	texProgram = shaderProgram; 
	spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
	spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	bJumping = false;
	dashCarregat = true;
	dashInfinit = false;
	deixatClicarSalt = true;
	deixatClicarDash = true;
	climbDretEnProces = false;
	climbEsquerreEnProces = false;
	spritesheet.loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);

	sprite->setAnimationSpeed(STAND_LEFT, 8);	//Quieta hacia la izquierda
	sprite->addKeyframe(STAND_LEFT, glm::vec2(float(15.f / 16.f), float(0.f / 16.f)));

	sprite->setAnimationSpeed(STAND_RIGHT, 8);	//Quieta hacia la derecha
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(float(10.f / 16.f), float(0.f / 16.f)));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);	//Animación corriendo hacia la izquierda
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(float(15.f / 16.f), float(0.f / 16.f)));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(float(14.f / 16.f), float(0.f / 16.f)));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(float(15.f / 16.f), float(1.f / 16.f)));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(float(13.f / 16.f), float(0.f / 16.f)));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);	//Animación corriendo hacia la derecha
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(float(10.f / 16.f), float(0.f / 16.f)));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(float(11.f / 16.f), float(0.f / 16.f)));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(float(10.f / 16.f), float(1.f / 16.f)));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(float(12.f / 16.f), float(0.f / 16.f)));

	sprite->setAnimationSpeed(DASH_LEFT, 8);	//Animación DASH izquierda
	sprite->addKeyframe(DASH_LEFT, glm::vec2(float(14.f / 16.f), float(1.f / 16.f)));

	sprite->setAnimationSpeed(DASH_RIGHT, 8);	//Animación DASH derecha
	sprite->addKeyframe(DASH_RIGHT, glm::vec2(float(11.f / 16.f), float(1.f / 16.f)));

	sprite->setAnimationSpeed(LOOK_UP_LEFT, 8);	//Mirando hacia arriba izquierda
	sprite->addKeyframe(LOOK_UP_LEFT, glm::vec2(float(14.f / 16.f), float(2.f / 16.f)));

	sprite->setAnimationSpeed(LOOK_UP_RIGHT, 8);	//Mirando hacia arriba derecha
	sprite->addKeyframe(LOOK_UP_RIGHT, glm::vec2(float(11.f / 16.f), float(2.f / 16.f)));

	sprite->setAnimationSpeed(LOOK_DOWN_LEFT, 8);	//Mirando hacia abajo izquierda
	sprite->addKeyframe(LOOK_DOWN_LEFT, glm::vec2(float(15.f / 16.f), float(2.f / 16.f)));

	sprite->setAnimationSpeed(LOOK_DOWN_RIGHT, 8);	//Mirando hacia abajo derecha
	sprite->addKeyframe(LOOK_DOWN_RIGHT, glm::vec2(float(10.f / 16.f), float(2.f / 16.f)));

	sprite->changeAnimation(0);
	sprite->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime, float currentTime)
{
	sprite->update(deltaTime);

	if (!(Game::instance().getKey(67) || Game::instance().getKey(99))) //per que no es produeixi loop de salts
	{
		deixatClicarSalt = true;
	}
	if (!(Game::instance().getKey(88) || Game::instance().getKey(120))) //Per que no es produeixi loop de DASH
	{
		deixatClicarDash = true;
	}

	if (deixatClicarSalt && (Game::instance().getKey(67) || Game::instance().getKey(99))) //comprovem si es vol fer salt de CLIMB. Codis: C=67 i c=99 
	{
		//comprovem si estem al costat de mur esquerre
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			//fem el climb
			posPlayer.x += 2;
			deixatClicarSalt = false;
			bJumping = true;
			jumpAngle = 0;
			startY = posPlayer.y;
			climbDretEnProces = true;
		}
		//altrament comprovem si estem al costat de mur dret
		else
		{
			posPlayer.x += 4;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)/*, &posPlayer.x*/))
			{
				//fem el climb
				posPlayer.x -= 2;
				deixatClicarSalt = false;
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
				climbEsquerreEnProces = true;
			}
			else
			{
				posPlayer.x -= 2;
			}
		}

	}

	if (climbEsquerreEnProces)
	{
		if (sprite->animation() != MOVE_LEFT && dashCarregat && !dashInfinit)
		{
			sprite->changeAnimation(MOVE_LEFT);
		}
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);

		}
	}
	else if (climbDretEnProces)
	{
		if (sprite->animation() != MOVE_RIGHT && dashCarregat && !dashInfinit)
		{
			sprite->changeAnimation(MOVE_RIGHT);
		}
		posPlayer.x += 2;	//Aumnetar el desplazameitno en x a 4 para conseguir más velocidad
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)/*, &posPlayer.x*/))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != MOVE_LEFT && dashCarregat && !dashInfinit)
		{
			sprite->changeAnimation(MOVE_LEFT);
		}
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);

		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != MOVE_RIGHT && dashCarregat && !dashInfinit)
		{
			sprite->changeAnimation(MOVE_RIGHT);
		}
		posPlayer.x += 2;	//Aumnetar el desplazameitno en x a 4 para conseguir más velocidad
		if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)/*, &posPlayer.x*/))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		/*
		if (sprite->animation() == STAND_LEFT)
			sprite->changeAnimation(LOOK_UP_LEFT);
		else if (sprite->animation() != LOOK_UP_RIGHT)
			sprite->changeAnimation(LOOK_UP_RIGHT);
		*/
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		/*
		if (sprite->animation() != LOOK_DOWN_LEFT)
			sprite->changeAnimation(LOOK_DOWN_LEFT);
		else if (sprite->animation() != LOOK_DOWN_RIGHT)
			sprite->changeAnimation(LOOK_DOWN_RIGHT);
		*/
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle >= 180)
		{
			bJumping = false;
			//posPlayer.y = startY;

		}
		else
		{
			int posicioAnterior = posPlayer.y; //la guardem en el cas que hi hagi collisinMoveUp
			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) //comprovar collisionMoveUp
			{
				posPlayer.y = posicioAnterior;
				//trobar angle
				jumpAngle = 90;
				startY = posPlayer.y + JUMP_HEIGHT;
				//bJumping = false; 
			}
			else
			{
				if (jumpAngle > 90)
				{
					bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
					if (climbDretEnProces)
					{
						climbDretEnProces = false;
					}
					if (climbEsquerreEnProces)
					{
						climbEsquerreEnProces = false;
					}
				}

			}
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;  //UN COP SACABA EL SALT, la caiguda es fa lineal ja que es va restant el fall_step
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			dashCarregat = true;
			if (tremolarAlCaure)
			{
				fentTremolar.first = true; 
				fentTremolar.second = currentTime;
				tremolarAlCaure = false; 
				//cout << "començant el tremolar" << endl; 
			}
			if ((Game::instance().getKey(67)|| Game::instance().getKey(99)) && deixatClicarSalt) //Codis: C=67 i c=99
			{
				deixatClicarSalt = false;
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}

	//Gestión del DASH
	if (deixatClicarDash && ((Game::instance().getKey(88) || Game::instance().getKey(120)) && dashCarregat)) //Codis: X=88 i x=120
	{
		if (!dashInfinit)
		{
			dashCarregat = false;
		}
		if (dashInfinit)
			deixatClicarDash = false;
		audioManager->dashSoundPlay();
		bJumping = true;
		jumpAngle = 0;
		startY = posPlayer.y;
		fentTremolar.first = true;
		fentTremolar.second = currentTime;

		if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
		{
			sprite->changeAnimation(DASH_LEFT);
		}
		else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
		{
			sprite->changeAnimation(DASH_RIGHT);
		}

	}

	//Gestió DASH infinit
	if (Game::instance().getKey(68) || Game::instance().getKey(100) && !dashInfinit) //Codis: D=68 i d=100
	{
			dashInfinit = true;       
	} 
	else if (Game::instance().getKey(68) || Game::instance().getKey(100) && dashInfinit)
	{
		dashInfinit = false;
	}


	if (fentTremolar.first)
	{
		cout << currentTime - fentTremolar.second << endl;
		if ((currentTime - fentTremolar.second) >= DURACIOTREMOLAR)
		{
			displacement = glm::vec2(float(0.f), float(0.f));
			fentTremolar.first = false;
			//cout << "acabant tremolar" << endl; 
		}
		else
		{
			float strength = (1.f - ((currentTime - fentTremolar.second) / DURACIOTREMOLAR * 1.f))*(STRENGTHTREMOLAR*1.f); 
			float desviacioy = strength * sin(currentTime); 
			float desviaciox = ((rand() % 10+1)*0.1f)*desviacioy;
			if ((rand() % 2) == 0)
			{
				desviaciox = -desviaciox; 
			}
			displacement = glm::vec2(float(desviaciox), float(desviacioy));
			//cout << "desviaciox " << desviaciox << "        desviacioy " << desviacioy << endl;
		}
	}

	/**
	if (posPlayer.y >= (LIMITINFERIOR*1.f))
	{
		cout << "a" << endl; 
		fentTremolar.first = true;
		fentTremolar.second = currentTime;
		tremolarAlCaure = false;
	}
	*/

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	texProgram.setUniform2f("displacement", displacement.x, displacement.y);
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPositionPlayer()
{
	return posPlayer;
}

void Player::setTremolar(bool tremolar)
{
	if (tremolar == true)
	{
		tremolarAlCaure = true; 
		fentTremolar.first = false; 
		displacement = glm::vec2(float(0.f), float(0.f));

	}
	else
	{
		tremolarAlCaure = false; 
		fentTremolar.first = false;
		displacement = glm::vec2(float(0.f), float(0.f));
	}
}

bool Player::encaraTremolant()
{
	return fentTremolar.first; 
}
