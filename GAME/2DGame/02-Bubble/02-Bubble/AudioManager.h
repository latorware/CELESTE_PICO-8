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

	void gameMusicPlay(); 
	void gameMusicStop(); 

	void deathSoundPlay(); 
	void jumpSoundPlay(); 
	void levelUpSoundPlay(); 
	void maduixaSoundPlay();
	void selectSoundPlay();


	

private:


	irrklang::ISoundEngine* engine; 
	irrklang::ISound* menuMusic; 
	irrklang::ISound* gameMusic; 
	irrklang::ISound* deathSound; 
	irrklang::ISound* jumpSound; 
	irrklang::ISound* levelUpSound; 
	irrklang::ISound* maduixaSound; 
	irrklang::ISound* selectSound; 




};

#endif

