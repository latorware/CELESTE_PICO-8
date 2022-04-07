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
	}
}

void MapScene::update(int deltaTime) {
	currentTime += deltaTime;
	player->update(deltaTime);
	if (currentLevel == 3)
	{
		movementAngle += ANGLE_STEP; 
		sprites[0]->update(deltaTime);
		sprites[0]->setPosition(glm::vec2(float(45), float(200 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f))));
		//cout << float(200 - MOVEMENT_HEIGHT * sin(3.14159f * movementAngle / 180.f)) << endl; 
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
		sprites[0]->render();
	}
}