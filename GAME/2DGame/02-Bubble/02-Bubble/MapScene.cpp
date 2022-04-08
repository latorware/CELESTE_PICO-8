#include "MapScene.h"
#include "Game.h"

#define MOVEMENT_HEIGHT 5
#define ANGLE_STEP 5
#define POSXMADUIXALVL3 45
#define POSYMADUIXALVL3 200
#define POSXMADUIXALVL4 65
#define POSYMADUIXALVL4 165
#define POSXCLAULVL5 245
#define POSYCLAULVL5 460
#define POSXTRESORLVL5 470
#define POSYTRESORLVL5 400
#define POSXMADUIXALVL5 485
#define POSYMADUIXALVL5 380
#define POSXMADUIXALVL7 330
#define POSYMADUIXALVL7 120
#define OFFSET 2

MapScene::MapScene() {
	map = NULL;
	background = NULL;
	player = new Player();
}

MapScene::~MapScene() {
	if (map != NULL) delete map;
}

void MapScene::init(int level) {
	Scene::init();
	currentLevel = level; 
	movementAngle = 0; 

	for (auto p : sprites)
	{
		delete p;
	}
	sprites.clear();


	textures.clear();

	spritesClicats.clear(); 

	spriteShouldBeRendered.clear(); 


	map = TileMap::createTileMap("levels/level_" + to_string(level) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	background = TileMap::createTileMap("levels/background_" + to_string(level) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	if (level == 3)
	{
		//sprite maduixa
		textures.emplace_back(); 
		textures[0].setWrapS(GL_CLAMP_TO_EDGE);
		textures[0].setWrapT(GL_CLAMP_TO_EDGE);
		textures[0].setMinFilter(GL_NEAREST);
		textures[0].setMagFilter(GL_NEAREST);
		textures[0].loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprites.push_back(Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram));
		sprites[0]->setNumberAnimations(1);
		sprites[0]->setAnimationSpeed(0, 1);
		sprites[0]->addKeyframe(0, glm::vec2(float(5.f / 16.f), float(6.f / 16.f)));
		sprites[0]->changeAnimation(0);
		sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL3), float(POSYMADUIXALVL3)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0); 
		spriteShouldBeRendered.push_back(true); 
	}

	else if (level == 4)
	{
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
		sprites[1]->setPosition(glm::vec2(float(POSXMADUIXALVL4 -28), float(POSYMADUIXALVL4)));
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

	}

	else if (level == 5)
	{
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
		
	}

	else if (level == 7)
	{
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

	}
}

void MapScene::update(int deltaTime) {
	currentTime += deltaTime;
	//cout << "currentTime " << currentTime << "        deltaTime " << deltaTime << endl; 
	player->update(deltaTime);
	if (currentLevel == 3)
	{
		if (!spritesClicats[0].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14; 
			//cout << "x " << x << "     y " << y << endl; 
			if (((y >= (POSYMADUIXALVL3-OFFSET)) && (y <= (POSYMADUIXALVL3 + OFFSET))) && ((x >= (POSXMADUIXALVL3 - OFFSET)) && (x <= (POSXMADUIXALVL3 + OFFSET))))
			{
				//el sprite de maduixa passa a ser nombre 1000 durant temps limitat
				spritesClicats[0].first = true; 
				spritesClicats[0].second = currentTime; 
				delete sprites[0]; 
				textures[0].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
				sprites[0] = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(float(2.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram);
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
				sprites[0]->setPosition(glm::vec2(float(POSXMADUIXALVL3), float(POSYMADUIXALVL3 - (difference*0.05f))));
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
			if (((y >= (POSYMADUIXALVL4-OFFSET)) && (y <= (POSYMADUIXALVL4+ OFFSET))) && ((x >= (POSXMADUIXALVL4- OFFSET)) && (x <= (POSXMADUIXALVL4+ OFFSET))))
			{
				//el sprite de maduixa passa a ser nombre 1000 durant temps limitat
				spritesClicats[0].first = true;
				spritesClicats[0].second = currentTime;
				delete sprites[0];
				textures[0].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
				sprites[0] = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(float(2.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram);
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
				sprites[1]->setPosition(glm::vec2(float(POSXMADUIXALVL4 -28), float(newPosy)));
				sprites[2]->setPosition(glm::vec2(float(POSXMADUIXALVL4 +28), float(newPosy)));
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
						delete sprites[2];
						textures[0].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
						sprites[2] = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(float(2.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram);
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
				delete sprites[0];
				textures[0].loadFromFile("images/numbers.png", TEXTURE_PIXEL_FORMAT_RGBA);
				sprites[0] = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(float(2.f / 16.f), float(1.f / 16.f)), &textures[0], &texProgram);
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
}

void MapScene::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	map->render();
	player->render();
	if (currentLevel == 3)
	{
		if (spriteShouldBeRendered[0])
		{
			sprites[0]->render();
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
	}
}