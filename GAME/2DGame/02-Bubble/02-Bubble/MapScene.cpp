#include "MapScene.h"
#include "Game.h"

#define MOVEMENT_HEIGHT 5
#define ANGLE_STEP 5

#define POSXMADUIXALVL3 45
#define POSYMADUIXALVL3 200
#define POSXMOLLA1LVL3 175
#define POSYMOLLA1LVL3 463
#define POSXMOLLA2LVL3 430
#define POSYMOLLA2LVL3 463

#define POSXMADUIXALVL4 65
#define POSYMADUIXALVL4 165

#define POSXBLOC1LVL4 142
#define POSYBLOC1LVL4 495
#define POSXBLOC2LVL4 174
#define POSYBLOC2LVL4 495

#define POSXBLOC3LVL4 270
#define POSYBLOC3LVL4 463
#define POSXBLOC4LVL4 302
#define POSYBLOC4LVL4 463

#define POSXBLOC5LVL4 398
#define POSYBLOC5LVL4 431
#define POSXBLOC6LVL4 430
#define POSYBLOC6LVL4 431

#define POSXBLOC7LVL4 462
#define POSYBLOC7LVL4 367
#define POSXBLOC8LVL4 494
#define POSYBLOC8LVL4 367

#define POSXBLOC9LVL4 366
#define POSYBLOC9LVL4 303
#define POSXBLOC10LVL4 398
#define POSYBLOC10LVL4 303

#define POSXBLOC11LVL4 398
#define POSYBLOC11LVL4 207
#define POSXBLOC12LVL4 430
#define POSYBLOC12LVL4 207

#define POSXCLAULVL5 245
#define POSYCLAULVL5 460
#define POSXTRESORLVL5 470
#define POSYTRESORLVL5 400
#define POSXMADUIXALVL5 485
#define POSYMADUIXALVL5 380
#define POSXMADUIXALVL7 330
#define POSYMADUIXALVL7 120

#define POSXBLOC1LVL8 230
#define POSYBLOC1LVL8 460
#define POSXBLOC2LVL8 262
#define POSYBLOC2LVL8 460
#define POSXBLOC3LVL8 294
#define POSYBLOC3LVL8 460

#define POSXBLOC1LVL10 180
#define POSYBLOC1LVL10 460
#define POSXBLOC2LVL10 212
#define POSYBLOC2LVL10 460
#define POSXBLOC3LVL10 340
#define POSYBLOC3LVL10 460
#define POSXBLOC4LVL10 372
#define POSYBLOC4LVL10 460

#define OFFSET 20


#define INIT_PLAYER_X_TILESLVL1 1
#define INIT_PLAYER_Y_TILESLVL1 10

#define INIT_PLAYER_X_TILESLVL2 1
#define INIT_PLAYER_Y_TILESLVL2 12

#define INIT_PLAYER_X_TILESLVL3 1
#define INIT_PLAYER_Y_TILESLVL3 10

#define INIT_PLAYER_X_TILESLVL4 1
#define INIT_PLAYER_Y_TILESLVL4 9

#define INIT_PLAYER_X_TILESLVL5 1
#define INIT_PLAYER_Y_TILESLVL5 8

#define INIT_PLAYER_X_TILESLVL6 1
#define INIT_PLAYER_Y_TILESLVL6 8

#define INIT_PLAYER_X_TILESLVL7 1
#define INIT_PLAYER_Y_TILESLVL7 11

#define INIT_PLAYER_X_TILESLVL8 1
#define INIT_PLAYER_Y_TILESLVL8 11

#define INIT_PLAYER_X_TILESLVL9 2
#define INIT_PLAYER_Y_TILESLVL9 9

#define INIT_PLAYER_X_TILESLVL10 1
#define INIT_PLAYER_Y_TILESLVL10 10

#define EXPFACTORYDESVIATION 15

#define FIRSTNUMBERMETERSX 150
#define SECONDNUMBERMETERSX 200
#define THIRDNUMBERMETTERSX 250
#define LETTERMETTERSX 300
#define METERSY 240

#define LIMITINFERIOR 480
#define DURACIOTREMOLAR 500



MapScene::MapScene() {
	map = NULL;
	background = NULL;
	player = new Player();
	slowMode = false;
}

MapScene::~MapScene() {
	if (map != NULL) delete map;
	if (background != NULL) delete background;
	if (player != NULL) delete player;

}

void MapScene::init(int level) {
	//dividit en començaJoc(), canviaNivell(int level)
}

void MapScene::update(int deltaTime) {
	currentTime += deltaTime;
	//cout << "currentTime " << currentTime << "        deltaTime " << deltaTime << endl; 

	if (player->getPositionPlayer().y <= 1.f)
	{
		audioManager->levelUpSoundPlay();
		if (currentLevel == 10)
		{
			jocEnded = true; 
		}
		else
		{
			canviaNivell(currentLevel + 1); 
		}
	}
	
	if (!transicio.fentTransicio)
	{
		if (player->getPositionPlayer().y >= (LIMITINFERIOR * 1.f))
		{
			if ((!player->encaraTremolant()) && (!personatgeCaigut))
			{
				audioManager->deathSoundPlay();
				personatgeCaigut = true; 
				player->setTremolar(true);
				player->update(deltaTime, currentTime);
			}
			else if ((player->encaraTremolant()) && (personatgeCaigut))
			{
				player->update(deltaTime, currentTime);
			}
			else if ((!player->encaraTremolant()) && (personatgeCaigut))
			{
				personatgeCaigut = false;
				canviaNivell(currentLevel);
			}

		}
		else
		{
			if (currentLevel == 1 && enPosicioPunxesLevel1() && (!invulnerable))
			{
				if ((!personatgepunxat))
				{
					//cout << "a" << endl;
					audioManager->deathSoundPlay();
					personatgepunxat = true;
					punxatUltimaVegada = currentTime;
					player->setTremolar(true);
					player->update(deltaTime, currentTime);
				}
				else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
				{
					//cout << "b" << endl;
					player->update(deltaTime, currentTime);
				}
				else
				{
					//cout << "c" << endl;
					personatgepunxat = false;
					canviaNivell(currentLevel);
				}
			}

			else if (currentLevel == 2 && enPosicioPunxesLevel2() && (!invulnerable))
			{
				if ((!personatgepunxat))
				{
					//cout << "a" << endl;
					audioManager->deathSoundPlay();
					personatgepunxat = true;
					punxatUltimaVegada = currentTime;
					player->setTremolar(true);
					player->update(deltaTime, currentTime);
				}
				else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
				{
					//cout << "b" << endl;
					player->update(deltaTime, currentTime);
				}
				else
				{
					//cout << "c" << endl;
					personatgepunxat = false;
					canviaNivell(currentLevel);
				}
			}

			else if (currentLevel == 3 && enPosicioPunxesLevel3() && (!invulnerable))
			{
				if ((!personatgepunxat))
				{
					//cout << "a" << endl;
					audioManager->deathSoundPlay();
					personatgepunxat = true;
					punxatUltimaVegada = currentTime;
					player->setTremolar(true);
					player->update(deltaTime, currentTime);
				}
				else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
				{
					//cout << "b" << endl;
					player->update(deltaTime, currentTime);
				}
				else
				{
					//cout << "c" << endl;
					personatgepunxat = false;
					canviaNivell(currentLevel);
				}
			}


			else if (currentLevel == 5 && enPosicioPunxesLevel5() && (!invulnerable))
			{
				if ((!personatgepunxat))
				{
					//cout << "a" << endl;
					audioManager->deathSoundPlay();
					personatgepunxat = true;
					punxatUltimaVegada = currentTime;
					player->setTremolar(true);
					player->update(deltaTime, currentTime);
				}
				else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
				{
					//cout << "b" << endl;
					player->update(deltaTime, currentTime);
				}
				else
				{
					//cout << "c" << endl;
					personatgepunxat = false;
					canviaNivell(currentLevel);
				}
			}


			else if (currentLevel == 6 && enPosicioPunxesLevel6() && (!invulnerable))
			{
				if ((!personatgepunxat))
				{
					//cout << "a" << endl;
					audioManager->deathSoundPlay();
					personatgepunxat = true;
					punxatUltimaVegada = currentTime;
					player->setTremolar(true);
					player->update(deltaTime, currentTime);
				}
				else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
				{
					//cout << "b" << endl;
					player->update(deltaTime, currentTime);
				}
				else
				{
					//cout << "c" << endl;
					personatgepunxat = false;
					canviaNivell(currentLevel);
				}
			}

			else if (currentLevel == 7 && enPosicioPunxesLevel7() && (!invulnerable))
			{
			if ((!personatgepunxat))
			{
				//cout << "a" << endl;
				audioManager->deathSoundPlay();
				personatgepunxat = true;
				punxatUltimaVegada = currentTime;
				player->setTremolar(true);
				player->update(deltaTime, currentTime);
			}
			else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
			{
				//cout << "b" << endl;
				player->update(deltaTime, currentTime);
			}
			else
			{
				//cout << "c" << endl;
				personatgepunxat = false;
				canviaNivell(currentLevel);
			}
			}

			else if (currentLevel == 8 && enPosicioPunxesLevel8() && (!invulnerable))
			{
			if ((!personatgepunxat))
			{
				//cout << "a" << endl;
				audioManager->deathSoundPlay();
				personatgepunxat = true;
				punxatUltimaVegada = currentTime;
				player->setTremolar(true);
				player->update(deltaTime, currentTime);
			}
			else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
			{
				//cout << "b" << endl;
				player->update(deltaTime, currentTime);
			}
			else
			{
				//cout << "c" << endl;
				personatgepunxat = false;
				canviaNivell(currentLevel);
			}
			}

			else if (currentLevel == 9 && enPosicioPunxesLevel9() && (!invulnerable))
			{
			if ((!personatgepunxat))
			{
				//cout << "a" << endl;
				audioManager->deathSoundPlay();
				personatgepunxat = true;
				punxatUltimaVegada = currentTime; 
				player->setTremolar(true);
				player->update(deltaTime, currentTime);
			}
			else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
			{
				//cout << "b" << endl;
				player->update(deltaTime, currentTime);
			}
			else
			{
				//cout << "c" << endl;
				personatgepunxat = false;
				canviaNivell(currentLevel);
			}
			}

			else if (currentLevel == 10 && enPosicioPunxesLevel10() && (!invulnerable))
			{
			if ((!personatgepunxat))
			{
				//cout << "a" << endl;
				audioManager->deathSoundPlay();
				personatgepunxat = true;
				punxatUltimaVegada = currentTime;
				player->setTremolar(true);
				player->update(deltaTime, currentTime);
			}
			else if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
			{
				//cout << "b" << endl;
				player->update(deltaTime, currentTime);
			}
			else
			{
				//cout << "c" << endl;
				personatgepunxat = false;
				canviaNivell(currentLevel);
			}
			}
			else if (personatgepunxat && (!invulnerable))
			{
				if (((currentTime - punxatUltimaVegada) < DURACIOTREMOLAR) && personatgepunxat)
					{
					cout << "d" << endl;
					player->update(deltaTime, currentTime);
					}
				else
					{
					cout << "e" << endl;
					personatgepunxat = false;
					canviaNivell(currentLevel);
					}
			}

			else 
			{
				player->update(deltaTime, currentTime);
			}
			
		}
	}
	else
	{
		float duracio = currentTime - transicio.startTime; 
		//cout << "duracio " << duracio << endl; 
		if (duracio >= 1000)
		{
			displacement = glm::vec2(float(0.f), float(0.f));
			texProgram.setUniform2f("displacement", displacement.x, displacement.y);
			transicio.fentTransicio = false; 

		}
		else
		{
			float ydesviation;
			if (duracio < 500)
			{
				
				if (transicio.desdeLevel < transicio.aLevel)
				{
					ydesviation = -exp((EXPFACTORYDESVIATION * 1.f) * (duracio / 1000.f));
				}
				else
				{
					ydesviation = exp((EXPFACTORYDESVIATION * 1.f) * (duracio / 1000.f));
				}
			}
			else
			{
				if (!transicio.canviTileMapFet)
				{
					inincialitzatNivellPrimeraVegada = false; 
					transicio.canviTileMapFet = true; 
					currentLevel = transicio.aLevel; 

					movementAngle = 0;
					for (auto p : sprites)
					{
						delete p;
					}
					sprites.clear();
					textures.clear();
					spritesClicats.clear();
					spriteShouldBeRendered.clear();
					map = TileMap::createTileMap("levels/level_" + to_string(currentLevel) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, currentLevel, &spriteShouldBeRendered);
					background = TileMap::createTileMap("levels/background_" + to_string(currentLevel) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 90, &spriteShouldBeRendered);
					player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, audioManager);
					player->setTremolar(true);
					player->setTileMap(map);
					inicialitzaNivellActual(); 
					//cout << "b" << endl; 


				}
			
				if (transicio.desdeLevel < transicio.aLevel)
				{
					ydesviation = exp((EXPFACTORYDESVIATION * 1.f) * ((500 - (int(duracio) % 500))/1000.f));
				}
				else
				{
					ydesviation = -exp((EXPFACTORYDESVIATION * 1.f) * ((500 - (int(duracio) % 500))/1000.f));
				}
			}


			displacement = glm::vec2(float(0.f), float(ydesviation));
			//cout << "factor " << ydesviation << endl;
		}
	}


	if (currentLevel == 3)
	{
		if (!spritesClicats[0].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			//cout << "x " << x << "     y " << y << endl; 
			if (((y >= (POSYMADUIXALVL3 - OFFSET)) && (y <= (POSYMADUIXALVL3 + OFFSET))) && ((x >= (POSXMADUIXALVL3 - OFFSET)) && (x <= (POSXMADUIXALVL3 + OFFSET))))
			{
				//el sprite de maduixa passa a ser nombre 1000 durant temps limitat
				spritesClicats[0].first = true;
				spritesClicats[0].second = currentTime;
				audioManager->maduixaSoundPlay();
				delete sprites[0];
				sprites[0] = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(float(2.f / 16.f), float(1.f / 16.f)), &textures[3], &texProgram);
				sprites[0]->setNumberAnimations(1);
				sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
				sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(1.f / 16.f)));
				sprites[0]->setAnimationSpeed(0, 100);
				sprites[0]->changeAnimation(0);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL3), float(POSYMADUIXALVL3)));
				sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
			}
			else
			{
				movementAngle += ANGLE_STEP;
				sprites[0]->update(deltaTime);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL3), float(POSYMADUIXALVL3 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f))));
				//cout << float(200 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f)) << endl; 
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[0].second;
			//cout << currentTime - spritesClicats[0].second << endl; 
			if ((difference) > 1000)
			{
				//sprites[0]->setColor(glm::vec4(0.f, 0.f, 0.f, 0.f));
				//no s'imprimira ja que no el rendejarem
				spriteShouldBeRendered[0] = false;
				sprites[0]->setAnimationSpeed(0, 1);
			}
			else
			{
				sprites[0]->update(deltaTime);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL3), float(POSYMADUIXALVL3 - (difference * 0.05f))));
			}
		}



	}
	else if (currentLevel == 4)
	{
		if (!spritesClicats[0].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			//cout << "x " << x << "     y " << y << endl; 
			if (((y >= (POSYMADUIXALVL4 - OFFSET)) && (y <= (POSYMADUIXALVL4 + OFFSET))) && ((x >= (POSXMADUIXALVL4 - OFFSET)) && (x <= (POSXMADUIXALVL4 + OFFSET))))
			{
				//el sprite de maduixa passa a ser nombre 1000 durant temps limitat
				spritesClicats[0].first = true;
				spritesClicats[0].second = currentTime;
				audioManager->maduixaSoundPlay();
				delete sprites[0];
				sprites[0] = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(float(2.f / 16.f), float(1.f / 16.f)), &textures[3], &texProgram);
				sprites[0]->setNumberAnimations(1);
				sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
				sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(1.f / 16.f)));
				sprites[0]->setAnimationSpeed(0, 100);
				sprites[0]->changeAnimation(0);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL4), float(POSYMADUIXALVL4)));
				sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
				//sprites ales ja no es renderejen mes
				spriteShouldBeRendered[1] = false;
				spriteShouldBeRendered[2] = false;
			}
			else
			{
				movementAngle += ANGLE_STEP;
				float newPosy = POSYMADUIXALVL4 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL4), float(newPosy)));
				sprites[1]->setPosition(glm::vec2(float(POSXMADUIXALVL4 - 28), float(newPosy)));
				sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL4 + 28), float(newPosy)));
				//cout << float(200 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f)) << endl; 
				//cout << movementAngle % 360 << endl; 
				if (((movementAngle % 360) > 180))
				{
					if (sprites[1]->animation() == 0)
					{
						sprites[1]->changeAnimation(1);
						sprites[2]->changeAnimation(1);
					}
				}
				else if (sprites[1]->animation() == 1)
				{
					sprites[1]->changeAnimation(0);
					sprites[2]->changeAnimation(0);
				}

				sprites[0]->update(deltaTime);
				sprites[1]->update(deltaTime);
				sprites[2]->update(deltaTime);
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[0].second;
			//cout << currentTime - spritesClicats[0].second << endl; 
			if ((difference) > 1000)
			{
				//sprites[0]->setColor(glm::vec4(0.f, 0.f, 0.f, 0.f));
				//no s'imprimira ja que no el rendejarem
				spriteShouldBeRendered[0] = false;
				sprites[0]->setAnimationSpeed(0, 1);
			}
			else
			{
				sprites[0]->update(deltaTime);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL4), float(POSYMADUIXALVL4 - (difference * 0.05f))));
			}
		}


		//tractem bloc 1
		if (!spritesClicats[1].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC1LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC1LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC1LVL4 - OFFSET)) && (x <= (POSXBLOC1LVL4 + OFFSET)))))
			{
				spritesClicats[1].first = true;
				spritesClicats[1].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[1].second;
			if (difference >= 1500)
			{
				spritesClicats[1].first = false;
				spriteShouldBeRendered[3] = true;
				sprites[3]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[3]->changeAnimation(1);
					}
					else
					{
						sprites[3]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[3] = false;
				}
			}
		}



		//tractem bloc 2
		if (!spritesClicats[2].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC2LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC2LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC2LVL4 - OFFSET)) && (x <= (POSXBLOC2LVL4 + OFFSET)))))
			{
				spritesClicats[2].first = true;
				spritesClicats[2].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[2].second;
			if (difference >= 1500)
			{
				spritesClicats[2].first = false;
				spriteShouldBeRendered[4] = true;
				sprites[4]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[4]->changeAnimation(1);
					}
					else
					{
						sprites[4]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[4] = false;
				}
			}
		}
		//tractem bloc 3
		if (!spritesClicats[3].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC3LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC3LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC3LVL4 - OFFSET)) && (x <= (POSXBLOC3LVL4 + OFFSET)))))
			{
				spritesClicats[3].first = true;
				spritesClicats[3].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[3].second;
			if (difference >= 1500)
			{
				spritesClicats[3].first = false;
				spriteShouldBeRendered[5] = true;
				sprites[5]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[5]->changeAnimation(1);
					}
					else
					{
						sprites[5]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[5] = false;
				}
			}
		}
		//tractem bloc 4
		if (!spritesClicats[4].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC4LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC4LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC4LVL4 - OFFSET)) && (x <= (POSXBLOC4LVL4 + OFFSET)))))
			{
				spritesClicats[4].first = true;
				spritesClicats[4].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[4].second;
			if (difference >= 1500)
			{
				spritesClicats[4].first = false;
				spriteShouldBeRendered[6] = true;
				sprites[6]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[6]->changeAnimation(1);
					}
					else
					{
						sprites[6]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[6] = false;
				}
			}
		}
		//tractem bloc 5
		if (!spritesClicats[5].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC5LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC5LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC5LVL4 - OFFSET)) && (x <= (POSXBLOC5LVL4 + OFFSET)))))
			{
				spritesClicats[5].first = true;
				spritesClicats[5].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[5].second;
			if (difference >= 1500)
			{
				spritesClicats[5].first = false;
				spriteShouldBeRendered[7] = true;
				sprites[7]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[7]->changeAnimation(1);
					}
					else
					{
						sprites[7]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[7] = false;
				}
			}
		}
		//tractem bloc 6
		if (!spritesClicats[6].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC6LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC6LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC6LVL4 - OFFSET)) && (x <= (POSXBLOC6LVL4 + OFFSET)))))
			{
				spritesClicats[6].first = true;
				spritesClicats[6].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[6].second;
			if (difference >= 1500)
			{
				spritesClicats[6].first = false;
				spriteShouldBeRendered[8] = true;
				sprites[8]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[8]->changeAnimation(1);
					}
					else
					{
						sprites[8]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[8] = false;
				}
			}
		}
		//tractem bloc 7
		if (!spritesClicats[7].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC7LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC7LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC7LVL4 - OFFSET)) && (x <= (POSXBLOC7LVL4 + OFFSET)))))
			{
				spritesClicats[7].first = true;
				spritesClicats[7].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[7].second;
			if (difference >= 1500)
			{
				spritesClicats[7].first = false;
				spriteShouldBeRendered[9] = true;
				sprites[9]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[9]->changeAnimation(1);
					}
					else
					{
						sprites[9]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[9] = false;
				}
			}
		}
		//tractem bloc 8
		if (!spritesClicats[8].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC8LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC8LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC8LVL4 - OFFSET)) && (x <= (POSXBLOC8LVL4 + OFFSET)))))
			{
				spritesClicats[8].first = true;
				spritesClicats[8].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[8].second;
			if (difference >= 1500)
			{
				spritesClicats[8].first = false;
				spriteShouldBeRendered[10] = true;
				sprites[10]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[10]->changeAnimation(1);
					}
					else
					{
						sprites[10]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[10] = false;
				}
			}
		}
		//tractem bloc 9
		if (!spritesClicats[9].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC9LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC9LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC9LVL4 - OFFSET)) && (x <= (POSXBLOC9LVL4 + OFFSET)))))
			{
				spritesClicats[9].first = true;
				spritesClicats[9].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[9].second;
			if (difference >= 1500)
			{
				spritesClicats[9].first = false;
				spriteShouldBeRendered[11] = true;
				sprites[11]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[11]->changeAnimation(1);
					}
					else
					{
						sprites[11]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[11] = false;
				}
			}
		}
		//tractem bloc 10
		if (!spritesClicats[10].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC10LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC10LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC10LVL4 - OFFSET)) && (x <= (POSXBLOC10LVL4 + OFFSET)))))
			{
				spritesClicats[10].first = true;
				spritesClicats[10].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[10].second;
			if (difference >= 1500)
			{
				spritesClicats[10].first = false;
				spriteShouldBeRendered[12] = true;
				sprites[12]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[12]->changeAnimation(1);
					}
					else
					{
						sprites[12]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[12] = false;
				}
			}
		}
		//tractem bloc 11
		if (!spritesClicats[11].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC11LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC11LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC11LVL4 - OFFSET)) && (x <= (POSXBLOC11LVL4 + OFFSET)))))
			{
				spritesClicats[11].first = true;
				spritesClicats[11].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[11].second;
			if (difference >= 1500)
			{
				spritesClicats[11].first = false;
				spriteShouldBeRendered[13] = true;
				sprites[13]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[13]->changeAnimation(1);
					}
					else
					{
						sprites[13]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[13] = false;
				}
			}
		}
		//tractem bloc 12
		if (!spritesClicats[12].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC12LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC12LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC12LVL4 - OFFSET)) && (x <= (POSXBLOC12LVL4 + OFFSET)))))
			{
				spritesClicats[12].first = true;
				spritesClicats[12].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[12].second;
			if (difference >= 1500)
			{
				spritesClicats[12].first = false;
				spriteShouldBeRendered[14] = true;
				sprites[14]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[14]->changeAnimation(1);
					}
					else
					{
						sprites[14]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[14] = false;
				}
			}
		}
	}
	else if (currentLevel == 5)
	{
		if (!spritesClicats[0].first) //clau no clicada
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if (((y >= (POSYCLAULVL5 - 3)) && (y <= (POSYCLAULVL5 + OFFSET))) && ((x >= (POSXCLAULVL5 - OFFSET)) && (x <= (POSXCLAULVL5 + OFFSET))))
			{
				spritesClicats[0].first = true;
				spritesClicats[0].second = currentTime;
				audioManager->maduixaSoundPlay();
				//clau ja desapareix
				spriteShouldBeRendered[0] = false;
			}
			else
			{
				sprites[0]->update(deltaTime);
			}
		}
		else
		{
			//comprovem si encara a de tremolar tresor
			float difference = currentTime - spritesClicats[0].second;
			if ((difference) < 1000)
			{
				float x_vella = sprites[1]->getPosition().x;
				if (x_vella < POSXTRESORLVL5)
				{
					sprites[1]->setPosition(glm::vec2(float(POSXTRESORLVL5 + 10), float(POSYTRESORLVL5)));
				}
				else
				{
					sprites[1]->setPosition(glm::vec2(float(POSXTRESORLVL5 - 10), float(POSYTRESORLVL5)));
				}
			}
			else
			{
				//desactivem tresor si estava activat
				if (spriteShouldBeRendered[1])
				{
					spriteShouldBeRendered[1] = false;
				}
				//tractem lo de la maduixa
				if (!spritesClicats[1].first)
				{
					//activem maduixa si no estava
					if (!spriteShouldBeRendered[2])
					{
						spriteShouldBeRendered[2] = true;
					}

					int y = player->getPositionPlayer().y + 14;
					int x = player->getPositionPlayer().x + 14;
					if (((y >= (POSYMADUIXALVL5 - OFFSET)) && (y <= (POSYMADUIXALVL5 + OFFSET))) && ((x >= (POSXMADUIXALVL5 - OFFSET)) && (x <= (POSXMADUIXALVL5 + OFFSET))))
					{
						//el sprite de maduixa passa a ser nombre 1000 durant temps limitat
						spritesClicats[1].first = true;
						spritesClicats[1].second = currentTime;
						audioManager->maduixaSoundPlay();
						delete sprites[2];
						sprites[2] = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(float(2.f / 16.f), float(1.f / 16.f)), &textures[3], &texProgram);
						sprites[2]->setNumberAnimations(1);
						sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
						sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(1.f / 16.f)));
						sprites[2]->setAnimationSpeed(0, 100);
						sprites[2]->changeAnimation(0);
						sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL5), float(POSYMADUIXALVL5)));
						sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
					}
					else
					{
						movementAngle += ANGLE_STEP;
						sprites[2]->update(deltaTime);
						sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL5), float(POSYMADUIXALVL5 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f))));
					}
				}
				else
				{
					float difference = currentTime - spritesClicats[1].second;
					if ((difference) > 1000)
					{
						//no s'imprimira ja que no el rendejarem
						spriteShouldBeRendered[2] = false;
						sprites[2]->setAnimationSpeed(0, 1);
					}
					else
					{
						sprites[2]->update(deltaTime);
						sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL5), float(POSYMADUIXALVL5 - (difference * 0.05f))));
					}
				}
			}
		}

	}
	else if (currentLevel == 7)
	{
		if (!spritesClicats[0].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			//cout << "x " << x << "     y " << y << endl; 
			if (((y >= (POSYMADUIXALVL7 - OFFSET)) && (y <= (POSYMADUIXALVL7 + OFFSET))) && ((x >= (POSXMADUIXALVL7 - OFFSET)) && (x <= (POSXMADUIXALVL7 + OFFSET))))
			{
				//el sprite de maduixa passa a ser nombre 1000 durant temps limitat
				spritesClicats[0].first = true;
				spritesClicats[0].second = currentTime;
				
				audioManager->maduixaSoundPlay();
				delete sprites[0];
				sprites[0] = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(float(2.f / 16.f), float(1.f / 16.f)), &textures[3], &texProgram);
				sprites[0]->setNumberAnimations(1);
				sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
				sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(1.f / 16.f)));
				sprites[0]->setAnimationSpeed(0, 100);
				sprites[0]->changeAnimation(0);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL7), float(POSYMADUIXALVL7)));
				sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
				//sprites ales ja no es renderejen mes
				spriteShouldBeRendered[1] = false;
				spriteShouldBeRendered[2] = false;
			}
			else
			{
				movementAngle += ANGLE_STEP;
				float newPosy = POSYMADUIXALVL7 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL7), float(newPosy)));
				sprites[1]->setPosition(glm::vec2(float(POSXMADUIXALVL7 - 28), float(newPosy)));
				sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL7 + 28), float(newPosy)));
				//cout << float(200 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f)) << endl; 
				//cout << movementAngle % 360 << endl; 
				if (((movementAngle % 360) > 180))
				{
					if (sprites[1]->animation() == 0)
					{
						sprites[1]->changeAnimation(1);
						sprites[2]->changeAnimation(1);
					}
				}
				else if (sprites[1]->animation() == 1)
				{
					sprites[1]->changeAnimation(0);
					sprites[2]->changeAnimation(0);
				}

				sprites[0]->update(deltaTime);
				sprites[1]->update(deltaTime);
				sprites[2]->update(deltaTime);
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[0].second;
			//cout << currentTime - spritesClicats[0].second << endl; 
			if ((difference) > 1000)
			{
				//sprites[0]->setColor(glm::vec4(0.f, 0.f, 0.f, 0.f));
				//no s'imprimira ja que no el rendejarem
				spriteShouldBeRendered[0] = false;
				sprites[0]->setAnimationSpeed(0, 1);
			}
			else
			{
				sprites[0]->update(deltaTime);
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL7), float(POSYMADUIXALVL7 - (difference * 0.05f))));
			}
		}
	}
	else if (currentLevel == 8)
	{
		//tractem bloc 1
		if (!spritesClicats[0].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC1LVL8 - 16) - OFFSET)) && (y <= ((POSYBLOC1LVL8 - 16) + OFFSET))) && ((x >= (POSXBLOC1LVL8 - OFFSET)) && (x <= (POSXBLOC1LVL8 + OFFSET)))))
			{
				spritesClicats[0].first = true;
				spritesClicats[0].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[0].second;
			if (difference >= 1500)
			{
				spritesClicats[0].first = false;
				spriteShouldBeRendered[0] = true;
				sprites[5]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[5]->changeAnimation(1);
					}
					else
					{
						sprites[5]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[0] = false;
				}
			}
		}



		//tractem bloc 2
		if (!spritesClicats[1].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC2LVL8 - 16) - OFFSET)) && (y <= ((POSYBLOC2LVL8 - 16) + OFFSET))) && ((x >= (POSXBLOC2LVL8 - OFFSET)) && (x <= (POSXBLOC2LVL8 + OFFSET)))))
			{
				spritesClicats[1].first = true;
				spritesClicats[1].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[1].second;
			if (difference >= 1500)
			{
				spritesClicats[1].first = false;
				spriteShouldBeRendered[1] = true;
				sprites[6]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[6]->changeAnimation(1);
					}
					else
					{
						sprites[6]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[1] = false;
				}
			}
		}
		//tractem bloc 3
		if (!spritesClicats[2].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC3LVL8 - 16) - OFFSET)) && (y <= ((POSYBLOC3LVL8 - 16) + OFFSET))) && ((x >= (POSXBLOC3LVL8 - OFFSET)) && (x <= (POSXBLOC3LVL8 + OFFSET)))))
			{
				spritesClicats[2].first = true;
				spritesClicats[2].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[2].second;
			if (difference >= 1500)
			{
				spritesClicats[2].first = false;
				spriteShouldBeRendered[2] = true;
				sprites[7]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[7]->changeAnimation(1);
					}
					else
					{
						sprites[7]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[2] = false;
				}
			}
		}
	}
	else if (currentLevel == 10)
	{
		//tractem bloc 1
		if (!spritesClicats[0].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC1LVL10 - 16) - OFFSET)) && (y <= ((POSYBLOC1LVL10 - 16) + OFFSET))) && ((x >= (POSXBLOC1LVL10 - OFFSET)) && (x <= (POSXBLOC1LVL10 + OFFSET)))))
			{
				spritesClicats[0].first = true;
				spritesClicats[0].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[0].second;
			if (difference >= 1500)
			{
				spritesClicats[0].first = false;
				spriteShouldBeRendered[0] = true;
				sprites[6]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[6]->changeAnimation(1);
					}
					else
					{
						sprites[6]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[0] = false;
				}
			}
		}



		//tractem bloc 2
		if (!spritesClicats[1].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC2LVL10 - 16) - OFFSET)) && (y <= ((POSYBLOC2LVL10 - 16) + OFFSET))) && ((x >= (POSXBLOC2LVL10 - OFFSET)) && (x <= (POSXBLOC2LVL10 + OFFSET)))))
			{
				spritesClicats[1].first = true;
				spritesClicats[1].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[1].second;
			if (difference >= 1500)
			{
				spritesClicats[1].first = false;
				spriteShouldBeRendered[1] = true;
				sprites[7]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[7]->changeAnimation(1);
					}
					else
					{
						sprites[7]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[1] = false;
				}
			}
		}
		//tractem bloc 3
		if (!spritesClicats[2].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC3LVL10 - 16) - OFFSET)) && (y <= ((POSYBLOC3LVL10 - 16) + OFFSET))) && ((x >= (POSXBLOC3LVL10 - OFFSET)) && (x <= (POSXBLOC3LVL10 + OFFSET)))))
			{
				spritesClicats[2].first = true;
				spritesClicats[2].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[2].second;
			if (difference >= 1500)
			{
				spritesClicats[2].first = false;
				spriteShouldBeRendered[2] = true;
				sprites[8]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[8]->changeAnimation(1);
					}
					else
					{
						sprites[8]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[2] = false;
				}
			}
		}
		//tractem bloc 4
		if (!spritesClicats[3].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= ((POSYBLOC4LVL10 - 16) - OFFSET)) && (y <= ((POSYBLOC4LVL10 - 16) + OFFSET))) && ((x >= (POSXBLOC4LVL10 - OFFSET)) && (x <= (POSXBLOC4LVL10 + OFFSET)))))
			{
				spritesClicats[3].first = true;
				spritesClicats[3].second = currentTime;
			}
		}
		else
		{
			float difference = currentTime - spritesClicats[3].second;
			if (difference >= 1500)
			{
				spritesClicats[3].first = false;
				spriteShouldBeRendered[3] = true;
				sprites[9]->changeAnimation(0);
			}
			else
			{
				if (difference < 500)
				{
					if (difference <= 250)
					{
						sprites[9]->changeAnimation(1);
					}
					else
					{
						sprites[9]->changeAnimation(2);
					}
				}

				else
				{
					spriteShouldBeRendered[3] = false;
				}
			}
		}
	}
}

void MapScene::render() {


	if (!inincialitzatNivellPrimeraVegada)
	{
		//cout << "b" << endl;  
		inicialitzaNivellActual(); 
		inincialitzatNivellPrimeraVegada = true;
	}
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if (transicio.fentTransicio)
	{
		texProgram.setUniform2f("displacement", displacement.x, displacement.y);
	}



	if (!(((currentTime - transicio.startTime) < 500) && (transicio.fentTransicio == true) && (transicio.desdeLevel == 0)))
	{
		background->render();
		map->render();

	}
	else
	{
		return;
	}

	if (!transicio.fentTransicio)
	{
		player->render();
	}

	if (currentLevel == 1)
	{
		if (currentTime < 3000)
		{
			sprites[0]->render();
			sprites[1]->render();
			sprites[2]->render();
			sprites[3]->render();
			sprites[4]->render();

		}

	}
	else if (currentLevel == 2)
	{
		if (currentTime < 3000)
		{
			sprites[0]->render();
			sprites[1]->render();
			sprites[2]->render();
			sprites[3]->render();
			sprites[4]->render();

		}
	}

	else if (currentLevel == 3)
	{
		if (spriteShouldBeRendered[0])
		{
			sprites[0]->render();
		}
		sprites[6]->render(); //Molla 1 nivel 3
		sprites[7]->render(); //Molla 2 nivel 3 

		if (currentTime < 3000)
		{
			sprites[1]->render();
			sprites[2]->render();
			sprites[3]->render();
			sprites[4]->render();
			sprites[5]->render();
		}
	}
	else if (currentLevel == 4)
	{
		if (spriteShouldBeRendered[0])
		{
			sprites[0]->render();
		}
		if (spriteShouldBeRendered[1])
		{
			sprites[1]->render();
		}
		if (spriteShouldBeRendered[2])
		{
			sprites[2]->render();
		}
		if (spriteShouldBeRendered[3])
		{
			sprites[3]->render();
		}
		if (spriteShouldBeRendered[4])
		{
			sprites[4]->render();
		}
		if (spriteShouldBeRendered[5])
		{
			sprites[5]->render();
		}
		if (spriteShouldBeRendered[6])
		{
			sprites[6]->render();
		}
		if (spriteShouldBeRendered[7])
		{
			sprites[7]->render();
		}
		if (spriteShouldBeRendered[8])
		{
			sprites[8]->render();
		}
		if (spriteShouldBeRendered[9])
		{
			sprites[9]->render();
		}
		if (spriteShouldBeRendered[10])
		{
			sprites[10]->render();
		}
		if (spriteShouldBeRendered[11])
		{
			sprites[11]->render();
		}
		if (spriteShouldBeRendered[12])
		{
			sprites[12]->render();
		}
		if (spriteShouldBeRendered[13])
		{
			sprites[13]->render();
		}
		if (spriteShouldBeRendered[14])
		{
			sprites[14]->render();
		}

		if (currentTime < 3000)
		{
			sprites[15]->render();
			sprites[16]->render();
			sprites[17]->render();
			sprites[18]->render();
			sprites[19]->render();

		}
	}
	else if (currentLevel == 5)
	{
		if (spriteShouldBeRendered[0])
		{
			sprites[0]->render();
		}
		if (spriteShouldBeRendered[1])
		{
			sprites[1]->render();
		}
		if (spriteShouldBeRendered[2])
		{
			sprites[2]->render();
		}


		if (currentTime < 3000)
		{
			sprites[3]->render();
			sprites[4]->render();
			sprites[5]->render();
			sprites[6]->render();
			sprites[7]->render();

		}
	}
	else if (currentLevel == 6)
	{
		if (currentTime < 3000)
		{
			sprites[0]->render();
			sprites[1]->render();
			sprites[2]->render();
			sprites[3]->render();
			sprites[4]->render();

		}
	}
	else if (currentLevel == 7)
	{
		if (spriteShouldBeRendered[0])
		{
			sprites[0]->render();
		}
		if (spriteShouldBeRendered[1])
		{
			sprites[1]->render();
		}
		if (spriteShouldBeRendered[2])
		{
			sprites[2]->render();
		}


		if (currentTime < 3000)
		{
			sprites[3]->render();
			sprites[4]->render();
			sprites[5]->render();
			sprites[6]->render();
			sprites[7]->render();

		}
	}
	else if (currentLevel == 8)
	{
		if (currentTime < 3000)
		{
			sprites[0]->render();
			sprites[1]->render();
			sprites[2]->render();
			sprites[3]->render();
			sprites[4]->render();

		}

		if (spriteShouldBeRendered[0])
		{
			sprites[5]->render();
		}
		if (spriteShouldBeRendered[1])
		{
			sprites[6]->render();
		}
		if (spriteShouldBeRendered[2])
		{
			sprites[7]->render();
		}
	}
	else if (currentLevel == 9)
	{
	if (currentTime < 3000)
	{
		sprites[0]->render();
		sprites[1]->render();
		sprites[2]->render();
		sprites[3]->render();
		sprites[4]->render();

	}
	}
	else if (currentLevel == 10)
	{
	if (currentTime < 3000)
	{
		sprites[0]->render();
		sprites[1]->render();
		sprites[2]->render();
		sprites[3]->render();
		sprites[4]->render();
		sprites[5]->render();




	}

	if (spriteShouldBeRendered[0])
	{
		sprites[6]->render();
	}
	if (spriteShouldBeRendered[1])
	{
		sprites[7]->render();
	}
	if (spriteShouldBeRendered[2])
	{
		sprites[8]->render();
	}
	if (spriteShouldBeRendered[3])
	{
		sprites[9]->render();
	}
	}
}

void MapScene::comensaJoc(AudioManager* audioManagerr)
{
	jocEnded = false; 
	invulnerable = false; 
	personatgeCaigut = false; 
	personatgepunxat = false; 
	audioManager = audioManagerr; 
	audioManager->levelUpSoundPlay();
	inincialitzatNivellPrimeraVegada = false; 
	Scene::init();
	transicio.fentTransicio = false;
	currentLevel = 1;
	movementAngle = 0;
	displacement = glm::vec2(float(0.f), float(0.f));
	for (auto p : sprites)
	{
		delete p;
	}
	sprites.clear();
	textures.clear();
	spritesClicats.clear();
	spriteShouldBeRendered.clear();
	map = TileMap::createTileMap("levels/level_" + to_string(1) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 1, &spriteShouldBeRendered);
	background = TileMap::createTileMap("levels/background_" + to_string(1) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 90, &spriteShouldBeRendered);
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, audioManager);
	player->setTremolar(true);
	player->setTileMap(map);

	player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL1 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL1 * map->getTileSize()));
	contador = 0; 

	transicio.fentTransicio = true; 
	transicio.desdeLevel = 0; 
	transicio.aLevel = 1; 
	transicio.startTime = currentTime; 
	transicio.canviTileMapFet = false; 
	if (slowMode)
	{
		setGris();
	}
}

void MapScene::canviaNivell(int level)
{
	inincialitzatNivellPrimeraVegada = false; 
	audioManager->levelUpSoundPlay();
	Scene::init();
	if (level == currentLevel)
	{
		transicio.fentTransicio = false; 
		sprites.clear();
		textures.clear();
		spritesClicats.clear();
		spriteShouldBeRendered.clear();
		map = TileMap::createTileMap("levels/level_" + to_string(currentLevel) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, currentLevel, &spriteShouldBeRendered);
		background = TileMap::createTileMap("levels/background_" + to_string(currentLevel) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, 90, &spriteShouldBeRendered);
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, audioManager);
		player->setTremolar(true);
		player->setTileMap(map);
		inicialitzaNivellActual(); 
	}
	else 
	{
		transicio.fentTransicio = true; 
	}
	displacement = glm::vec2(float(0.f), float(0.f));
	transicio.startTime = currentTime; 
	transicio.desdeLevel = currentLevel; 
	transicio.aLevel = level; 
	transicio.canviTileMapFet = false; 

}

bool MapScene::jocAcabat()
{
	return jocEnded; 
}

void MapScene::setGris()
{
	texProgram.use();
	texProgram.setUniformInt("gris", 1);
	slowMode = true; 
}

void MapScene::treuGris()
{
	texProgram.use();
	texProgram.setUniformInt("gris", 0);
	slowMode = false; 
}

void MapScene::toggleInvulnerabilitat()
{
	if (!invulnerable)
	{
		invulnerable = true; 
	}
	else
	{
		invulnerable = false; 
	}
}

void MapScene::inicialitzaNivellActual()
{
	if (currentLevel == 1)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL1 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL1 * map->getTileSize()));
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(0+SCREEN_X), float(220+SCREEN_Y)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[1]->setNumberAnimations(1);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(3.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[2]->setNumberAnimations(1);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));


	}

	else if (currentLevel == 2)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL2 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL2 * map->getTileSize()));
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[1]->setNumberAnimations(1);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(4.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[2]->setNumberAnimations(1);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	}

	else if (currentLevel == 3)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL3 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL3 * map->getTileSize()));
		
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		//MADUIXA
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(5.f / 16.f), float(6.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL3), float(POSYMADUIXALVL3)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);

		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[1]->setNumberAnimations(1);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[2].setWrapS(GL_CLAMP_TO_EDGE);
		textures[2].setWrapT(GL_CLAMP_TO_EDGE);
		textures[2].setMinFilter(GL_NEAREST);
		textures[2].setMagFilter(GL_NEAREST);
		textures[2].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[2]->setNumberAnimations(1);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(5.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[5]->setNumberAnimations(1);
		sprites[5]->setAnimationSpeed(0, 1);
		sprites[5]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[5]->changeAnimation(0);
		sprites[5]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[5]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));

		//MOLLA1
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[6]->setNumberAnimations(2);
		sprites[6]->setAnimationSpeed(0, 1);
		sprites[6]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(8.f / 16.f)));
		sprites[6]->addKeyframe(0, glm::vec2(float(10.f / 10.f), float(8.f / 16.f)));
		sprites[6]->changeAnimation(0);
		sprites[6]->setPosition(glm::vec2(float(POSXMOLLA1LVL3), float(POSYMOLLA1LVL3)));
		sprites[6]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);

		//MOLLA2
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[7]->setNumberAnimations(2);
		sprites[7]->setAnimationSpeed(0, 1);
		sprites[7]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(8.f / 16.f)));
		sprites[7]->addKeyframe(0, glm::vec2(float(10.f / 10.f), float(8.f / 16.f)));
		sprites[7]->changeAnimation(0);
		sprites[7]->setPosition(glm::vec2(float(POSXMOLLA2LVL3), float(POSYMOLLA2LVL3)));
		sprites[7]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);


		textures.emplace_back();
		textures[3].setWrapS(GL_CLAMP_TO_EDGE);
		textures[3].setWrapT(GL_CLAMP_TO_EDGE);
		textures[3].setMinFilter(GL_NEAREST);
		textures[3].setMagFilter(GL_NEAREST);
		textures[3].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}

	else if (currentLevel == 4)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL4 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL4 * map->getTileSize()));
		//maduixa voladora (sprite maduixa, ala dreta, ala esquerra)
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		//maduixa
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(5.f / 16.f), float(6.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL4), float(POSYMADUIXALVL4)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//ala esquerra
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[1]->setNumberAnimations(2);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->setAnimationSpeed(1, 5);
		sprites[1]->addKeyframe(0, glm::vec2(float(6.f / 16.f), float(6.f / 16.f)));
		sprites[1]->addKeyframe(1, glm::vec2(float(7.f / 16.f), float(6.f / 16.f)));
		sprites[1]->addKeyframe(1, glm::vec2(float(8.f / 16.f), float(6.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(POSXMADUIXALVL4 - 28), float(POSYMADUIXALVL4)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		//spritesClicats.emplace_back(false, 0);  LES ALES NO ES CLIQUEN
		spriteShouldBeRendered.push_back(true);
		//ala dreta
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[2]->setNumberAnimations(2);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->setAnimationSpeed(1, 5);
		sprites[2]->addKeyframe(0, glm::vec2(float(13.f / 16.f), float(6.f / 16.f)));
		sprites[2]->addKeyframe(1, glm::vec2(float(12.f / 16.f), float(6.f / 16.f)));
		sprites[2]->addKeyframe(1, glm::vec2(float(11.f / 16.f), float(6.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL4 + 28), float(POSYMADUIXALVL4)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		//spritesClicats.emplace_back(false, 0);  LES ALES NO ES CLIQUEN
		spriteShouldBeRendered.push_back(true);

		//bloc 1
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[3]->setNumberAnimations(3);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->setAnimationSpeed(1, 1);
		sprites[3]->setAnimationSpeed(2, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[3]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[3]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(POSXBLOC1LVL4), float(POSYBLOC1LVL4)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 2
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[4]->setNumberAnimations(3);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->setAnimationSpeed(1, 1);
		sprites[4]->setAnimationSpeed(2, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[4]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[4]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(POSXBLOC2LVL4), float(POSYBLOC2LVL4)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 3
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[5]->setNumberAnimations(3);
		sprites[5]->setAnimationSpeed(0, 1);
		sprites[5]->setAnimationSpeed(1, 1);
		sprites[5]->setAnimationSpeed(2, 1);
		sprites[5]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[5]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[5]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[5]->changeAnimation(0);
		sprites[5]->setPosition(glm::vec2(float(POSXBLOC3LVL4), float(POSYBLOC3LVL4)));
		sprites[5]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 4
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[6]->setNumberAnimations(3);
		sprites[6]->setAnimationSpeed(0, 1);
		sprites[6]->setAnimationSpeed(1, 1);
		sprites[6]->setAnimationSpeed(2, 1);
		sprites[6]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[6]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[6]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[6]->changeAnimation(0);
		sprites[6]->setPosition(glm::vec2(float(POSXBLOC4LVL4), float(POSYBLOC4LVL4)));
		sprites[6]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 5
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[7]->setNumberAnimations(3);
		sprites[7]->setAnimationSpeed(0, 1);
		sprites[7]->setAnimationSpeed(1, 1);
		sprites[7]->setAnimationSpeed(2, 1);
		sprites[7]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[7]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[7]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[7]->changeAnimation(0);
		sprites[7]->setPosition(glm::vec2(float(POSXBLOC5LVL4), float(POSYBLOC5LVL4)));
		sprites[7]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 6
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[8]->setNumberAnimations(3);
		sprites[8]->setAnimationSpeed(0, 1);
		sprites[8]->setAnimationSpeed(1, 1);
		sprites[8]->setAnimationSpeed(2, 1);
		sprites[8]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[8]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[8]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[8]->changeAnimation(0);
		sprites[8]->setPosition(glm::vec2(float(POSXBLOC6LVL4), float(POSYBLOC6LVL4)));
		sprites[8]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 7
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[9]->setNumberAnimations(3);
		sprites[9]->setAnimationSpeed(0, 1);
		sprites[9]->setAnimationSpeed(1, 1);
		sprites[9]->setAnimationSpeed(2, 1);
		sprites[9]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[9]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[9]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[9]->changeAnimation(0);
		sprites[9]->setPosition(glm::vec2(float(POSXBLOC7LVL4), float(POSYBLOC7LVL4)));
		sprites[9]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 8
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[10]->setNumberAnimations(3);
		sprites[10]->setAnimationSpeed(0, 1);
		sprites[10]->setAnimationSpeed(1, 1);
		sprites[10]->setAnimationSpeed(2, 1);
		sprites[10]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[10]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[10]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[10]->changeAnimation(0);
		sprites[10]->setPosition(glm::vec2(float(POSXBLOC8LVL4), float(POSYBLOC8LVL4)));
		sprites[10]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 9
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[11]->setNumberAnimations(3);
		sprites[11]->setAnimationSpeed(0, 1);
		sprites[11]->setAnimationSpeed(1, 1);
		sprites[11]->setAnimationSpeed(2, 1);
		sprites[11]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[11]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[11]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[11]->changeAnimation(0);
		sprites[11]->setPosition(glm::vec2(float(POSXBLOC9LVL4), float(POSYBLOC9LVL4)));
		sprites[11]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 10
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[12]->setNumberAnimations(3);
		sprites[12]->setAnimationSpeed(0, 1);
		sprites[12]->setAnimationSpeed(1, 1);
		sprites[12]->setAnimationSpeed(2, 1);
		sprites[12]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[12]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[12]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[12]->changeAnimation(0);
		sprites[12]->setPosition(glm::vec2(float(POSXBLOC10LVL4), float(POSYBLOC10LVL4)));
		sprites[12]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 11
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[13]->setNumberAnimations(3);
		sprites[13]->setAnimationSpeed(0, 1);
		sprites[13]->setAnimationSpeed(1, 1);
		sprites[13]->setAnimationSpeed(2, 1);
		sprites[13]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[13]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[13]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[13]->changeAnimation(0);
		sprites[13]->setPosition(glm::vec2(float(POSXBLOC11LVL4), float(POSYBLOC11LVL4)));
		sprites[13]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 12
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[14]->setNumberAnimations(3);
		sprites[14]->setAnimationSpeed(0, 1);
		sprites[14]->setAnimationSpeed(1, 1);
		sprites[14]->setAnimationSpeed(2, 1);
		sprites[14]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[14]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[14]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[14]->changeAnimation(0);
		sprites[14]->setPosition(glm::vec2(float(POSXBLOC12LVL4), float(POSYBLOC12LVL4)));
		sprites[14]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);



		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[15]->setNumberAnimations(1);
		sprites[15]->setAnimationSpeed(0, 1);
		sprites[15]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[15]->changeAnimation(0);
		sprites[15]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[15]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[2].setWrapS(GL_CLAMP_TO_EDGE);
		textures[2].setWrapT(GL_CLAMP_TO_EDGE);
		textures[2].setMinFilter(GL_NEAREST);
		textures[2].setMagFilter(GL_NEAREST);
		textures[2].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[16]->setNumberAnimations(1);
		sprites[16]->setAnimationSpeed(0, 1);
		sprites[16]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(6.f / 16.f)));
		sprites[16]->changeAnimation(0);
		sprites[16]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[16]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[17]->setNumberAnimations(1);
		sprites[17]->setAnimationSpeed(0, 1);
		sprites[17]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[17]->changeAnimation(0);
		sprites[17]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[17]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[18]->setNumberAnimations(1);
		sprites[18]->setAnimationSpeed(0, 1);
		sprites[18]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[18]->changeAnimation(0);
		sprites[18]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[18]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[19]->setNumberAnimations(1);
		sprites[19]->setAnimationSpeed(0, 1);
		sprites[19]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[19]->changeAnimation(0);
		sprites[19]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[19]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));



		textures.emplace_back();
		textures[3].setWrapS(GL_CLAMP_TO_EDGE);
		textures[3].setWrapT(GL_CLAMP_TO_EDGE);
		textures[3].setMinFilter(GL_NEAREST);
		textures[3].setMagFilter(GL_NEAREST);
		textures[3].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);


	}

	else if (currentLevel == 5)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL5 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL5 * map->getTileSize()));
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		//clau
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 5);
		sprites[0]->addKeyframe(0, glm::vec2(float(5.f / 16.f), float(7.f / 16.f)));
		sprites[0]->addKeyframe(0, glm::vec2(float(6.f / 16.f), float(7.f / 16.f)));
		sprites[0]->addKeyframe(0, glm::vec2(float(7.f / 16.f), float(7.f / 16.f)));
		sprites[0]->addKeyframe(0, glm::vec2(float(7.f / 16.f), float(9.f / 16.f)));
		sprites[0]->addKeyframe(0, glm::vec2(float(6.f / 16.f), float(9.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(POSXCLAULVL5), float(POSYCLAULVL5)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//tresor
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[1]->setNumberAnimations(1);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->addKeyframe(0, glm::vec2(float(8.f / 16.f), float(7.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(POSXTRESORLVL5), float(POSYTRESORLVL5)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		//spritesClicats.emplace_back(false, 0); EL TRESOR NO ES CLICA
		spriteShouldBeRendered.push_back(true);
		//maduixa
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[2]->setNumberAnimations(1);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->addKeyframe(0, glm::vec2(float(5.f / 16.f), float(6.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL5), float(POSYMADUIXALVL5)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(false); //AL PRINCIPI NO ES MOSTRA LA MADUIXA


		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[2].setWrapS(GL_CLAMP_TO_EDGE);
		textures[2].setWrapT(GL_CLAMP_TO_EDGE);
		textures[2].setMinFilter(GL_NEAREST);
		textures[2].setMagFilter(GL_NEAREST);
		textures[2].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(7.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[5]->setNumberAnimations(1);
		sprites[5]->setAnimationSpeed(0, 1);
		sprites[5]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[5]->changeAnimation(0);
		sprites[5]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[5]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[6]->setNumberAnimations(1);
		sprites[6]->setAnimationSpeed(0, 1);
		sprites[6]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[6]->changeAnimation(0);
		sprites[6]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[6]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[7]->setNumberAnimations(1);
		sprites[7]->setAnimationSpeed(0, 1);
		sprites[7]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[7]->changeAnimation(0);
		sprites[7]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[7]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));


		textures.emplace_back();
		textures[3].setWrapS(GL_CLAMP_TO_EDGE);
		textures[3].setWrapT(GL_CLAMP_TO_EDGE);
		textures[3].setMinFilter(GL_NEAREST);
		textures[3].setMagFilter(GL_NEAREST);
		textures[3].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}

	else if (currentLevel == 6)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL6 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL6 * map->getTileSize()));
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[1]->setNumberAnimations(1);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(8.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[2]->setNumberAnimations(1);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	}

	else if (currentLevel == 7)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL7 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL7 * map->getTileSize()));
		//maduixa voladora (sprite maduixa, ala dreta, ala esquerra)
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		//maduixa
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(5.f / 16.f), float(6.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL7), float(POSYMADUIXALVL7)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//ala esquerra
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[1]->setNumberAnimations(2);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->setAnimationSpeed(1, 5);
		sprites[1]->addKeyframe(0, glm::vec2(float(6.f / 16.f), float(6.f / 16.f)));
		sprites[1]->addKeyframe(1, glm::vec2(float(7.f / 16.f), float(6.f / 16.f)));
		sprites[1]->addKeyframe(1, glm::vec2(float(8.f / 16.f), float(6.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(POSXMADUIXALVL7 - 28), float(POSYMADUIXALVL7)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		//spritesClicats.emplace_back(false, 0);  LES ALES NO ES CLIQUEN
		spriteShouldBeRendered.push_back(true);
		//ala dreta
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[2]->setNumberAnimations(2);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->setAnimationSpeed(1, 5);
		sprites[2]->addKeyframe(0, glm::vec2(float(13.f / 16.f), float(6.f / 16.f)));
		sprites[2]->addKeyframe(1, glm::vec2(float(12.f / 16.f), float(6.f / 16.f)));
		sprites[2]->addKeyframe(1, glm::vec2(float(11.f / 16.f), float(6.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL7 + 28), float(POSYMADUIXALVL7)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		//spritesClicats.emplace_back(false, 0);  LES ALES NO ES CLIQUEN
		spriteShouldBeRendered.push_back(true);



		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[2].setWrapS(GL_CLAMP_TO_EDGE);
		textures[2].setWrapT(GL_CLAMP_TO_EDGE);
		textures[2].setMinFilter(GL_NEAREST);
		textures[2].setMagFilter(GL_NEAREST);
		textures[2].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(9.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[5]->setNumberAnimations(1);
		sprites[5]->setAnimationSpeed(0, 1);
		sprites[5]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[5]->changeAnimation(0);
		sprites[5]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[5]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[6]->setNumberAnimations(1);
		sprites[6]->setAnimationSpeed(0, 1);
		sprites[6]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[6]->changeAnimation(0);
		sprites[6]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[6]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[7]->setNumberAnimations(1);
		sprites[7]->setAnimationSpeed(0, 1);
		sprites[7]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[7]->changeAnimation(0);
		sprites[7]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[7]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));


		textures.emplace_back();
		textures[3].setWrapS(GL_CLAMP_TO_EDGE);
		textures[3].setWrapT(GL_CLAMP_TO_EDGE);
		textures[3].setMinFilter(GL_NEAREST);
		textures[3].setMagFilter(GL_NEAREST);
		textures[3].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);

	}

	else if (currentLevel == 8)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL8 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL8 * map->getTileSize()));
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[1]->setNumberAnimations(1);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(10.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[2]->setNumberAnimations(1);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));


		textures.emplace_back();
		textures[2].setWrapS(GL_CLAMP_TO_EDGE);
		textures[2].setWrapT(GL_CLAMP_TO_EDGE);
		textures[2].setMinFilter(GL_NEAREST);
		textures[2].setMagFilter(GL_NEAREST);
		textures[2].loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		//bloc 1
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[5]->setNumberAnimations(3);
		sprites[5]->setAnimationSpeed(0, 1);
		sprites[5]->setAnimationSpeed(1, 1);
		sprites[5]->setAnimationSpeed(2, 1);
		sprites[5]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[5]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[5]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[5]->changeAnimation(0);
		sprites[5]->setPosition(glm::vec2(float(POSXBLOC1LVL8), float(POSYBLOC1LVL8)));
		sprites[5]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 2
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[6]->setNumberAnimations(3);
		sprites[6]->setAnimationSpeed(0, 1);
		sprites[6]->setAnimationSpeed(1, 1);
		sprites[6]->setAnimationSpeed(2, 1);
		sprites[6]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[6]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[6]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[6]->changeAnimation(0);
		sprites[6]->setPosition(glm::vec2(float(POSXBLOC2LVL8), float(POSYBLOC2LVL8)));
		sprites[6]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 3
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[7]->setNumberAnimations(3);
		sprites[7]->setAnimationSpeed(0, 1);
		sprites[7]->setAnimationSpeed(1, 1);
		sprites[7]->setAnimationSpeed(2, 1);
		sprites[7]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[7]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[7]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[7]->changeAnimation(0);
		sprites[7]->setPosition(glm::vec2(float(POSXBLOC3LVL8), float(POSYBLOC3LVL8)));
		sprites[7]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);


	}

	else if (currentLevel == 9)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL9 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL9 * map->getTileSize()));

		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[1]->setNumberAnimations(1);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(11.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[2]->setNumberAnimations(1);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	}

	else if (currentLevel == 10)
	{
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILESLVL10 * map->getTileSize(), INIT_PLAYER_Y_TILESLVL10 * map->getTileSize()));
		textures.emplace_back();
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/black.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(512, 64), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(0.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(0 + SCREEN_X), float(220 + SCREEN_Y)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		textures.emplace_back();
		textures[1].setWrapS(GL_CLAMP_TO_EDGE);
		textures[1].setWrapT(GL_CLAMP_TO_EDGE);
		textures[1].setMinFilter(GL_NEAREST);
		textures[1].setMagFilter(GL_NEAREST);
		textures[1].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[1]->setNumberAnimations(1);
		sprites[1]->setAnimationSpeed(0, 1);
		sprites[1]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(3.f / 16.f)));
		sprites[1]->changeAnimation(0);
		sprites[1]->setPosition(glm::vec2(float(FIRSTNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[1]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[2]->setNumberAnimations(1);
		sprites[2]->setAnimationSpeed(0, 1);
		sprites[2]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[2]->changeAnimation(0);
		sprites[2]->setPosition(glm::vec2(float(SECONDNUMBERMETERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[2]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[3]->setNumberAnimations(1);
		sprites[3]->setAnimationSpeed(0, 1);
		sprites[3]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[3]->changeAnimation(0);
		sprites[3]->setPosition(glm::vec2(float(THIRDNUMBERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[3]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[4]->setNumberAnimations(1);
		sprites[4]->setAnimationSpeed(0, 1);
		sprites[4]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(2.f / 16.f)));
		sprites[4]->changeAnimation(0);
		sprites[4]->setPosition(glm::vec2(float(LETTERMETTERSX + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[4]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[1], &texProgram));
		sprites[5]->setNumberAnimations(1);
		sprites[5]->setAnimationSpeed(0, 1);
		sprites[5]->addKeyframe(0, glm::vec2(float(0.f / 16.f), float(12.f / 16.f)));
		sprites[5]->changeAnimation(0);
		sprites[5]->setPosition(glm::vec2(float(LETTERMETTERSX+ 50.f + SCREEN_X), float(METERSY + SCREEN_Y)));
		sprites[5]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));



		textures.emplace_back();
		textures[2].setWrapS(GL_CLAMP_TO_EDGE);
		textures[2].setWrapT(GL_CLAMP_TO_EDGE);
		textures[2].setMinFilter(GL_NEAREST);
		textures[2].setMagFilter(GL_NEAREST);
		textures[2].loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		//bloc 1
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[6]->setNumberAnimations(3);
		sprites[6]->setAnimationSpeed(0, 1);
		sprites[6]->setAnimationSpeed(1, 1);
		sprites[6]->setAnimationSpeed(2, 1);
		sprites[6]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[6]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[6]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[6]->changeAnimation(0);
		sprites[6]->setPosition(glm::vec2(float(POSXBLOC1LVL10), float(POSYBLOC1LVL10)));
		sprites[6]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 2
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[7]->setNumberAnimations(3);
		sprites[7]->setAnimationSpeed(0, 1);
		sprites[7]->setAnimationSpeed(1, 1);
		sprites[7]->setAnimationSpeed(2, 1);
		sprites[7]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[7]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[7]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[7]->changeAnimation(0);
		sprites[7]->setPosition(glm::vec2(float(POSXBLOC2LVL10), float(POSYBLOC2LVL10)));
		sprites[7]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 3
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[8]->setNumberAnimations(3);
		sprites[8]->setAnimationSpeed(0, 1);
		sprites[8]->setAnimationSpeed(1, 1);
		sprites[8]->setAnimationSpeed(2, 1);
		sprites[8]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[8]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[8]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[8]->changeAnimation(0);
		sprites[8]->setPosition(glm::vec2(float(POSXBLOC3LVL10), float(POSYBLOC3LVL10)));
		sprites[8]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);
		//bloc 4
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[2], &texProgram));
		sprites[9]->setNumberAnimations(3);
		sprites[9]->setAnimationSpeed(0, 1);
		sprites[9]->setAnimationSpeed(1, 1);
		sprites[9]->setAnimationSpeed(2, 1);
		sprites[9]->addKeyframe(0, glm::vec2(float(9.f / 16.f), float(7.f / 16.f)));
		sprites[9]->addKeyframe(1, glm::vec2(float(10.f / 16.f), float(7.f / 16.f)));
		sprites[9]->addKeyframe(2, glm::vec2(float(11.f / 16.f), float(7.f / 16.f)));
		sprites[9]->changeAnimation(0);
		sprites[9]->setPosition(glm::vec2(float(POSXBLOC4LVL10), float(POSYBLOC4LVL10)));
		sprites[9]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0);
		spriteShouldBeRendered.push_back(true);



	}


	inincialitzatNivellPrimeraVegada = true; 
}

bool MapScene::enPosicioPunxesLevel1()
{
	if (player->getPositionPlayer().y == 416)
	{
		if ((player->getPositionPlayer().x >= 160) && (player->getPositionPlayer().x <= 192))
		{
			return true; 
		}
	}
	else if (player->getPositionPlayer().y == 384)
	{
		if ((player->getPositionPlayer().x >= 288) && (player->getPositionPlayer().x <= 320))
		{
			return true;
		}
	}
	else if (player->getPositionPlayer().y == 352)
	{
		if ((player->getPositionPlayer().x >= 289) && (player->getPositionPlayer().x <= 416))
		{
			return true;
		}
	}
	return false; 
}

bool MapScene::enPosicioPunxesLevel2()
{
	if (player->getPositionPlayer().y == 128)
	{
		if ((player->getPositionPlayer().x >= 193) && (player->getPositionPlayer().x <= 255))
		{
			return true;
		}
	}
	else if (player->getPositionPlayer().y == 384)
	{
		if ((player->getPositionPlayer().x >= 256) && (player->getPositionPlayer().x <= 351))
		{
			return true;
		}
	}


	return false;
}

bool MapScene::enPosicioPunxesLevel3()
{
	if (player->getPositionPlayer().y == 320)
	{
		if ((player->getPositionPlayer().x >= 197) && (player->getPositionPlayer().x <= 347))
		{
			return true;
		}
	}
	else if (player->getPositionPlayer().y == 160)
	{
		if ((player->getPositionPlayer().x >= 224) && (player->getPositionPlayer().x <= 347))
		{
			return true;
		}
	}

	return false; 
}

bool MapScene::enPosicioPunxesLevel5()
{
	if (player->getPositionPlayer().y == 160)
	{
		if ((player->getPositionPlayer().x >= 165) && (player->getPositionPlayer().x <= 251))
		{
			return true;
		}
	}
	else if (player->getPositionPlayer().y == 96)
	{
		if ((player->getPositionPlayer().x >= 293) && (player->getPositionPlayer().x <= 383))
		{
			return true;
		}
	}
	return false; 
}

bool MapScene::enPosicioPunxesLevel6()
{
	if (player->getPositionPlayer().y > 210 && player->getPositionPlayer().y < 224)
	{
		if ((player->getPositionPlayer().x >= 36) && (player->getPositionPlayer().x <= 152))
		{
			return true;
		}
	}
	return false; 

}

bool MapScene::enPosicioPunxesLevel7()
{
	return false;
}

bool MapScene::enPosicioPunxesLevel8()
{
	return false;
}

bool MapScene::enPosicioPunxesLevel9()
{
	return false;
}

bool MapScene::enPosicioPunxesLevel10()
{
	return false;
}
