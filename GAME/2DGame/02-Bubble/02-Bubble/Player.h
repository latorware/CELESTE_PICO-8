#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "AudioManager.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, AudioManager* audioManagerr);
	void update(int deltaTime, float currentTimee);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPositionPlayer();
	void setTremolar(bool tremolar); 
	bool encaraTremolant(); 
	void saltMolla();
	void carregarDash();

private:
	bool bJumping;
	bool dashCarregat, dashInfinit;
	bool deixatClicarSalt, deixatClicarDash;
	bool climbDretEnProces, climbEsquerreEnProces;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	ShaderProgram texProgram;
	glm::vec2 displacement;
	bool tremolarAlCaure; 
	pair<bool, float> fentTremolar;
	AudioManager* audioManager;
	int alcadaSaltMolla;

};


#endif // _PLAYER_INCLUDE
