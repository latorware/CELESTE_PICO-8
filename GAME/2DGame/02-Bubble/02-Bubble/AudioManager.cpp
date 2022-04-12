#include "AudioManager.h"
using namespace std;

AudioManager::AudioManager()
{
	engine = irrklang::createIrrKlangDevice();
	menuMusic = engine->play2D("music/menu.mp3", true, true, true);
	gameMusic = engine->play2D("music/game.mp3", true, true, true);
	deathSound = engine->play2D("music/death.mp3", false, true, true);
	jumpSound = engine->play2D("music/jump.mp3", false, true, true);
	levelUpSound = engine->play2D("music/levelUp.mp3", false, true, true);
	maduixaSound = engine->play2D("music/maduixa.mp3", false, true, true);
	selectSound = engine->play2D("music/select.mp3", false, true, true);
	dashSound = engine->play2D("music/dash.mp3", false, true, true);
}

void AudioManager::menuMusicPlay()
{
	if (menuMusic->getIsPaused())
	{
		bool paused = false; 
		menuMusic->setPlayPosition(0.f);
		menuMusic->setIsPaused(paused); 
	}
	
}

void AudioManager::menuMusicStop()
{
	if (!menuMusic->getIsPaused())
	{
		bool paused = true; ;
		menuMusic->setIsPaused(paused);
		
	}
}

void AudioManager::gameMusicPlay()
{
	if (gameMusic->getIsPaused())
	{
		bool paused = false;
		gameMusic->setPlayPosition(0.f);
		gameMusic->setIsPaused(paused);
	}
}

void AudioManager::gameMusicStop()
{
	if (!gameMusic->getIsPaused())
	{
		bool paused = true; ;
		gameMusic->setIsPaused(paused);

	}
}

void AudioManager::deathSoundPlay()
{
	if (deathSound->getIsPaused())
	{
		bool paused = false;
		deathSound->setIsPaused(paused);
	}
	else
	{
		deathSound->drop();
		deathSound = engine->play2D("music/death.mp3", false, false, true);
	}
}

void AudioManager::jumpSoundPlay()
{
	if (jumpSound->getIsPaused())
	{
		bool paused = false;
		jumpSound->setIsPaused(paused);
	}
	else
	{
		jumpSound->drop();
		jumpSound = engine->play2D("music/jump.mp3", false, false, true);
	}
}

void AudioManager::levelUpSoundPlay()
{
	if (levelUpSound->getIsPaused())
	{
		bool paused = false;
		levelUpSound->setIsPaused(paused);
	}
	else
	{
		levelUpSound->drop();
		levelUpSound = engine->play2D("music/levelUp.mp3", false, false, true);
	}
}

void AudioManager::maduixaSoundPlay()
{
	if (maduixaSound->getIsPaused())
	{
		bool paused = false;
		maduixaSound->setIsPaused(paused);
	}
	else
	{
		maduixaSound->drop();
		selectSound = engine->play2D("music/maduixa.mp3", false, false, true);
	}
}

void AudioManager::selectSoundPlay()
{
	if (selectSound->getIsPaused())
	{
		bool paused = false;
		selectSound->setIsPaused(paused);
	}
	else
	{
		selectSound->drop();
		selectSound = engine->play2D("music/select.mp3", false, false, true);
	}
}

void AudioManager::dashSoundPlay()
{
	if (dashSound->getIsPaused())
	{
		bool paused = false;
		dashSound->setIsPaused(paused);
	}
	else
	{
		dashSound->drop();
		dashSound = engine->play2D("music/dash.mp3", false, false, true);
	}
}
