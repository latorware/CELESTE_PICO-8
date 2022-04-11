#include "Credits.h"
#include "Game.h"


Credits::Credits()
{
	Creditsgui = NULL;
}

Credits::~Credits() {
	if (Creditsgui != NULL) delete Creditsgui;
}



void Credits::update(int deltaTime) {
	currentTime += deltaTime;
}


void Credits::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	Creditsgui->render();
}



void Credits::init() {
	initShaders();
	currentTime = 0.0f;

	textureCredits.setWrapS(GL_CLAMP_TO_EDGE);
	textureCredits.setWrapT(GL_CLAMP_TO_EDGE);
	textureCredits.setMinFilter(GL_NEAREST);
	textureCredits.setMagFilter(GL_NEAREST);

	textureCredits.loadFromFile("images/Credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Creditsgui = Sprite::createSprite(glm::ivec2(512, 512), glm::vec2(float(1.f), float(1.f)), &textureCredits, &texProgram);
	Creditsgui->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));




	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

}








void Credits::initShaders()
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