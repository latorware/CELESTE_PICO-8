#pragma once

#include "Scene.h"
#include <vector>
#include "TileMap.h"
#include "Player.h"
#include "Sprite.h"
#include "AudioManager.h"

#define SCREEN_X 16
#define SCREEN_Y 16


class MapScene : public Scene
{
public:
	MapScene();
	~MapScene();

	void init(int level);
	void update(int deltaTime);
	void render();
	void comensaJoc(AudioManager* audioManagerr);
	void canviaNivell(int level); 


private:
	void inicialitzaNivellActual(); 

private:
	TileMap* map, * background;
	Player* player;
	vector<Sprite*> sprites;
	vector<Texture> textures;
	vector<pair<bool, float>> spritesClicats; //si sa clicat sprite (jugador a passat per sobre) i en quin instant
	vector<bool> spriteShouldBeRendered;
	int currentLevel, movementAngle;
	int contador; 
	struct Transicio {
		bool fentTransicio; 
		int desdeLevel; 
		int aLevel; 
		float startTime; 
		bool canviTileMapFet; 
	} transicio;
	glm::vec2 displacement;
	bool inincialitzatNivellPrimeraVegada; //per evitar bug en que no es mostren les textures perque no san carregat encars
	AudioManager* audioManager; 
};