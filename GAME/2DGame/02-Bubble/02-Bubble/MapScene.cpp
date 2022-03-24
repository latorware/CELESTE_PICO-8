#include "MapScene.h"
#include "Game.h"

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

	map = TileMap::createTileMap("levels/level_" + to_string(level) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	background = TileMap::createTileMap("levels/background_" + to_string(level) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
}

void MapScene::update(int deltaTime) {
	currentTime += deltaTime;
	player->update(deltaTime);
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
}