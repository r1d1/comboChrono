#ifndef CHRONODURATION_H
#define CHRONODURATION_H

// representing durations
#include <iostream>
#include <string>
#include <typeinfo>
#include <SFML/Audio.hpp>

const std::string soundPath="sound/";

class ChronoDuration
{
	private :
		float durationInSec; // Duration to count

		// Sounds data :
		std::string startSoundName;
		sf::SoundBuffer startSoundBuf;
		sf::Sound startSound;
		
		std::string endSoundName;
		sf::SoundBuffer endSoundBuf;
		sf::Sound endSound;

	public :
	//	ChronoDuration();
//		ChronoDuration(float dur, sf::SoundBuffer startSnd, sf::SoundBuffer endSnd);
		//ChronoDuration(float dur, std::string startSnd="ut_headshot.wav", std::string endSnd="ut_headshot.wav");
		ChronoDuration(float dur, std::string startSnd="None", std::string endSnd="None");
		~ChronoDuration();

		void playStartSound();
		void playEndSound();

		float getDuration();
		std::string getStartSoundName();
		std::string getEndSoundName();

		void displayInfo();
};

#endif
