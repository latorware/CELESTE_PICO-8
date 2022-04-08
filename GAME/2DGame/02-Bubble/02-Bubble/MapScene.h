#pragma once

#include "Scene.h"
#include <vector>
#include "TileMap.h"
#include "Player.h"
#include "Sprite.h"

#define SCREEN_X 16
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 10


class MapScene : public Scene
{
	public: 
		MapScene();
		~MapScene();

		void init(int level);
		void update(int deltaTime);
		void render();	

	private:
		TileMap *map, *background;
		Player* player;
		vector<Sprite *> sprites; 
		vector<Texture> textures; 
		vector<pair<bool, float>> spritesClicats; //si sa clicat sprite (jugador a passat per sobre) i en quin instant
		vector<bool> spriteShouldBeRendered; 
		int currentLevel, movementAngle; 
};