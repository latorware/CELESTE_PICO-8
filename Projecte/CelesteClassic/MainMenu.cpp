#include "MainMenu.h"
#include "Game.h"

MainMenu::MainMenu()
{
	selector = NULL;
	MenuGui = NULL;
}

MainMenu::~MainMenu() {
	if (selector != NULL) delete selector;
	if (MenuGui != NULL) delete MenuGui;
}

void MainMenu::init() {
	initShaders();
	currentTime = 0.0f;

	menuGuiTexture.setWrapS(GL_CLAMP_TO_EDGE);
	menuGuiTexture.setWrapT(GL_CLAMP_TO_EDGE);
	menuGuiTexture.setMinFilter(GL_NEAREST);
	menuGuiTexture.setMagFilter(GL_NEAREST);

	spritesheet.setWrapS(GL_CLAMP_TO_EDGE);
	spritesheet.setWrapT(GL_CLAMP_TO_EDGE);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	menuGuiTexture.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	MenuGui = Sprite::createSprite(glm::ivec2(512, 512), glm::vec2(float(1.f), float(1.f)), &menuGuiTexture, &texProgram);
	MenuGui->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	MenuGui->setPosition(glm::vec2(SCREEN_X, SCREEN_Y));

	spritesheet.loadFromFile("images/repaired_sheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	selector = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(float(1.f / 16.f), float(1.f / 16.f)), &spritesheet, &texProgram);
	selector->setNumberAnimations(1);
	selector->setAnimationSpeed(0, 1);
	selector->addKeyframe(0, textureCoordinates);
	selector->changeAnimation(0);
	selector->setPosition(startButtonPosition);
	actualPosition = START;
	selector->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));


	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

}


void MainMenu::update(int deltaTime) {
	currentTime += deltaTime;
	selector->update(deltaTime);
}

void MainMenu::setOptionArrowRight() {
	if (actualPosition == START) {
		selector->setPosition(guideButtonPosition);
		actualPosition = GUIDE;
	}
	else if (actualPosition == CREDITS) {
		selector->setPosition(exitButtonPosition);
		actualPosition = EXIT;
	}
}

void MainMenu::setOptionArrowUp() {
	if (actualPosition == CREDITS) {
		selector->setPosition(startButtonPosition);
		actualPosition = START;
	}
	else if (actualPosition == EXIT) {
		selector->setPosition(guideButtonPosition);
		actualPosition = GUIDE;
	}
}

void MainMenu::setOptionArrowDown() {
	if (actualPosition == START) {
		selector->setPosition(creditsButtonPosition);
		actualPosition = CREDITS;
	}
	else if (actualPosition == GUIDE) {
		selector->setPosition(exitButtonPosition);
		actualPosition = EXIT;
	}
}

void MainMenu::setOptionArrowLeft() {
	if (actualPosition == GUIDE) {
		selector->setPosition(startButtonPosition);
		actualPosition = START;
	}
	else if (actualPosition == EXIT) {
		selector->setPosition(creditsButtonPosition);
		actualPosition = CREDITS;
	}
}

void MainMenu::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	MenuGui->render();
	selector->render();
}

void MainMenu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



int MainMenu::getOption()
{
	return actualPosition;
}



void MainMenu::setGris()
{
	texProgram.use();
	texProgram.setUniformInt("gris", 1);
}

void MainMenu::treuGris()
{
	texProgram.use();
	texProgram.setUniformInt("gris", 0);
}