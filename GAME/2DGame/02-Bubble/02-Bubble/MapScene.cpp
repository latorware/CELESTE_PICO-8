#include "MapScene.h"
#include "Game.h"

#define MOVEMENT_HEIGHT 5
#define ANGLE_STEP 5

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
		sprites[0]->setPosition(glm::vec2(float(45), float(200)));
		sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		spritesClicats.emplace_back(false, 0); 
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
			if (((y >= 197) && (y <= 203)) && ((x >= 42) && (x <= 48)))
			{
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
				sprites[0]->setPosition(glm::vec2(float(45), float(200)));
				sprites[0]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
			}
			else
			{
				movementAngle += ANGLE_STEP;
				sprites[0]->update(deltaTime);
				sprites[0]->setPosition(glm::vec2(float(45), float(200 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f))));
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
				sprites[0]->setPosition(glm::vec2(float(45), float(200 - (difference*0.05f))));
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
}