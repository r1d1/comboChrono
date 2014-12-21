#ifndef CHRONODURATION_H
#define CHRONODURATION_H

// representing durations
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

class ChronoDuration
{
	private :
		float durationInSec; // Duration to count
		// Maybe we should define these as pointers to the sounds to play :
		std::string startSound;
		std::string endSound;

	public :
		ChronoDuration();
		ChronoDuration(float dur, std::string startSnd="headshot.wav", std::string endSnd="headshot.wav");
		~ChronoDuration();

		void displayInfo();
};

#endif
