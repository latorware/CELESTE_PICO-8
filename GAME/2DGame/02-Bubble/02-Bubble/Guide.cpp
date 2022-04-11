#include "Guide.h"

Guide::Guide()
{
	Guidegui = NULL;
}

Guide::~Guide() {
	if (Guidegui != NULL) delete Guidegui;
}

void Guide::init() {

	initShaders();
	currentTime = 0.0f;

	textureGuide.setWrapS(GL_CLAMP_TO_EDGE);
	textureGuide.setWrapT(GL_CLAMP_TO_EDGE);
	textureGuide.setMinFilter(GL_NEAREST);
	textureGuide.setMagFilter(GL_NEAREST);

	textureGuide.loadFromFile("images/guide.png", TEXTURE_PIXEL_FORMAT_RGBA);
	Guidegui = Sprite::createSprite(glm::ivec2(512, 512), glm::vec2(float(1.f), float(1.f)), &textureGuide, &texProgram);
	Guidegui->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	Guidegui->setPosition(glm::vec2(SCREEN_X, SCREEN_Y));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

}

void Guide::update(int deltaTime) {
	currentTime += deltaTime;
}


void Guide::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	Guidegui->render();
}

void Guide::initShaders()
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