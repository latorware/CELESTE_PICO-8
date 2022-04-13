#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 12

void Scene::init()
{
	initShaders();
	currentTime = 0.0f;

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
}

void Scene::initObjects() 
{
	for (int i = 0; i < 20; ++i) {
		int random = 15 + rand() % (41 - 15);
		randomSnow.push_back(random);
		randomClouds.push_back(random);
	}

	spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
	spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	spritesheet.loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	for (int i = 0; i < randomSnow.size(); ++i) {
		snowFlakes.push_back(Sprite::createSprite(glm::ivec2(4 + 4 * (i % 2), 4 + 4 * (i % 2)), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &spritesheet, &texProgram));
		snowFlakes[i]->setNumberAnimations(1);
		snowFlakes[i]->setAnimationSpeed(0, 1);
		snowFlakes[i]->addKeyframe(0, glm::vec2(float(3.f / 16.f), float(0.f / 16.f)));
		snowFlakes[i]->changeAnimation(0);
		snowFlakes[i]->setPosition(glm::vec2(10, 10));
		snowFlakes[i]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	}
	for (int i = 0; i < randomClouds.size(); ++i) {
		clouds.push_back(Sprite::createSprite(glm::ivec2(128, 32 + 12 * (i % 2)), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &spritesheet, &texProgram));
		clouds[i]->setNumberAnimations(1);
		clouds[i]->setAnimationSpeed(0, 1);
		clouds[i]->addKeyframe(0, glm::vec2(float(4.f / 16.f), float(0.f / 16.f)));
		clouds[i]->changeAnimation(0);
		clouds[i]->setPosition(glm::vec2(10, 10));
		clouds[i]->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	}
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime*6;

	for (int i = 0; i < randomSnow.size(); ++i) {
		float oscilation = (sin(((currentTime / 1000.f) + randomSnow[i]) + 1.0f) / 2.0f); //calcula el movimiento vertical de cada SnowFlake
		int desplazamiento = ((int)currentTime / randomSnow[i]) + i*20; //calcula el desplazamiento horizontal de cada SnowFlake
		snowFlakes[i]->setPosition(glm::vec2(desplazamiento % 546, (randomSnow[i] * 4 * oscilation) + (546/20) * i));
	}

	for (int i = 0; i < randomClouds.size(); ++i) {
		//float oscilation = (sin(((currentTime / 1000.f) + randomSnow[i]) + 1.0f) / 2.0f); //calcula el movimiento vertical de cada SnowFlake
		int desplazamiento = ((int)currentTime / randomSnow[i]) + i * 20; //calcula el desplazamiento horizontal de cada SnowFlake
		clouds[i]->setPosition(glm::vec2(desplazamiento % 546, (randomSnow[i] * 4 /* * oscilation*/) + (546 / 20) * i));
	}

}

void Scene::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
}

void Scene::renderClouds() {
	render();

	for (int i = 0; i < clouds.size(); ++i)
	{
		clouds[i]->render();
	}
}

void Scene::renderSnow()
{
	render();

	for (int i = 0; i < snowFlakes.size(); ++i) {
		snowFlakes[i]->render();
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



