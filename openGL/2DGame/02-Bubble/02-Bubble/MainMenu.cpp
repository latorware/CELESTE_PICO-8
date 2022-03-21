#include "MainMenu.h"

MainMenu::MainMenu(ShaderProgram &shaderProgram)
{
    currentTime = 0.0f;

    scene.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(512, 512), glm::vec2(float(1.f), float(1.f)), &scene, &shaderProgram);


}