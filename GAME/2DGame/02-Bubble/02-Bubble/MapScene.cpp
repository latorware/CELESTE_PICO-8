#include "MapScene.h"
#include "Game.h"

#define MOVEMENT_HEIGHT 5
#define ANGLE_STEP 5
#define POSXMADUIXALVL3 45
#define POSYMADUIXALVL3 200
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
#define OFFSET 20

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


		//tractem bloc 1
		if (!spritesClicats[1].first)
		{
			int y = player->getPositionPlayer().y + 14;
			int x = player->getPositionPlayer().x + 14;
			if ((((y >= (POSYBLOC1LVL4 - OFFSET)) && (y <= (POSYBLOC1LVL4 + OFFSET))) && ((x >= (POSXBLOC1LVL4 - OFFSET)) && (x <= (POSXBLOC1LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC2LVL4 - OFFSET)) && (y <= (POSYBLOC2LVL4 + OFFSET))) && ((x >= (POSXBLOC2LVL4 - OFFSET)) && (x <= (POSXBLOC2LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC3LVL4 - OFFSET)) && (y <= (POSYBLOC3LVL4 + OFFSET))) && ((x >= (POSXBLOC3LVL4 - OFFSET)) && (x <= (POSXBLOC3LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC4LVL4 - OFFSET)) && (y <= (POSYBLOC4LVL4 + OFFSET))) && ((x >= (POSXBLOC4LVL4 - OFFSET)) && (x <= (POSXBLOC4LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC5LVL4 - OFFSET)) && (y <= (POSYBLOC5LVL4 + OFFSET))) && ((x >= (POSXBLOC5LVL4 - OFFSET)) && (x <= (POSXBLOC5LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC6LVL4 - OFFSET)) && (y <= (POSYBLOC6LVL4 + OFFSET))) && ((x >= (POSXBLOC6LVL4 - OFFSET)) && (x <= (POSXBLOC6LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC7LVL4 - OFFSET)) && (y <= (POSYBLOC7LVL4 + OFFSET))) && ((x >= (POSXBLOC7LVL4 - OFFSET)) && (x <= (POSXBLOC7LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC8LVL4 - OFFSET)) && (y <= (POSYBLOC8LVL4 + OFFSET))) && ((x >= (POSXBLOC8LVL4 - OFFSET)) && (x <= (POSXBLOC8LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC9LVL4 - OFFSET)) && (y <= (POSYBLOC9LVL4 + OFFSET))) && ((x >= (POSXBLOC9LVL4 - OFFSET)) && (x <= (POSXBLOC9LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC10LVL4 - OFFSET)) && (y <= (POSYBLOC10LVL4 + OFFSET))) && ((x >= (POSXBLOC10LVL4 - OFFSET)) && (x <= (POSXBLOC10LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC11LVL4 - OFFSET)) && (y <= (POSYBLOC11LVL4 + OFFSET))) && ((x >= (POSXBLOC11LVL4 - OFFSET)) && (x <= (POSXBLOC11LVL4 + OFFSET)))))
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
			if ((((y >= (POSYBLOC12LVL4 - OFFSET)) && (y <= (POSYBLOC12LVL4 + OFFSET))) && ((x >= (POSXBLOC12LVL4 - OFFSET)) && (x <= (POSXBLOC12LVL4 + OFFSET)))))
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