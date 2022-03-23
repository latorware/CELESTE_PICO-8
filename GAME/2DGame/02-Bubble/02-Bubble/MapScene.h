#pragma once

#include "Scene.h"

#include "TileMap.h"

#define SCREEN_X 16
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 12


class MapScene : public Scene
{
	public: 
		MapScene();
		~MapScene();

		void init(int level);
		void update();
		void render();

	private:
		TileMap *map, *background;
};