#ifndef _AUDIOMANAGER_INCLUDE
#define _AUDIOMANAGER_INCLUDE


#include <irrKlang.h>
#include <iostream>


class AudioManager
{



public:
	AudioManager(); 

	void menuMusicPlay(); 
	void menuMusicStop(); 
	void menuMusicSlowMode();
	void menuMusicNormalMode();

	void gameMusicPlay(); 
	void gameMusicStop(); 
	void gameMusicSlowMode(); 
	void gameMusicNormalMode();

	void deathSoundPlay(); 
	void jumpSoundPlay(); 
	void levelUpSoundPlay(); 
	void maduixaSoundPlay();
	void selectSoundPlay();
	void dashSoundPlay();


	

private:


	irrklang::ISoundEngine* engine; 
	irrklang::ISound* menuMusic; 
	irrklang::ISound* gameMusic; 
	irrklang::ISound* deathSound; 
	irrklang::ISound* jumpSound; 
	irrklang::ISound* levelUpSound; 
	irrklang::ISound* maduixaSound; 
	irrklang::ISound* selectSound; 
	irrklang::ISound* dashSound;




};

#endif

