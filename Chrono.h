#ifndef CHRONO_H
#define CHRONO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "ChronoDuration.h"
#include <SFML/Graphics.hpp>

class Chrono
{
	private :
		bool paused; // counting or pause ?
		bool counting; // we may be counting a schedule or waiting for user to set things up
		
		// May be deprecated very soon
		int startTime;
		int pauseTime;
		
		// Tracking time
		int currentTime;
		int previousTime;
		int elapsedTime; // Count of time actually spent counting
		
		//datastructureToDefine schedule;
		std::vector<ChronoDuration> schedule;
		int state;
		//std::vector<ChronoDuration>::iterator state;
		//datastructureToDefine remainingSchedule;
		// current state in the schedule

		// For playing welcome sound :
		sf::SoundBuffer buf;
		sf::Sound snd;
	
	public :
		Chrono();
		~Chrono();

		// Sound related methods (may be removed from Chrono and be in gui only) :
		void loadSoundDB(const char *); // takes file name as argument

		void runChrono(); // Handle Chrono states
		// time related methods :
		void loadSchedule(const char *); // takes file name as argument
		void startChrono(); // start counting time from beginning of schedule
		//void stopChrono(); // stop the chrono and reset to beginning
		void resetChrono(); // stop the chrono and reset to beginning
		void pauseChrono(); // pause/unpause counting time in keeping current state ; actually inverse value of "paused"
		void countTime(); // check time and manage sounds / steps

		// Access data for GUI wrapping
		int getElapsedTime(); // return time counted till then with pauses and resumes
		//int getCumulativeTime(std::vector<ChronoDuration>::iterator step); // return cumulative time from beginning to schedule step
		int getCumulativeTime(int step); // return cumulative time from beginning to schedule step
		
		void displaySchedule(sf::RenderWindow & app, int x, int y); // pause/unpause counting time in keeping current state ; actually inverse value of "paused"
		
		void displaySchedule(); // pause/unpause counting time in keeping current state ; actually inverse value of "paused"
//		void resumeChrono(); // re-start counting time from current state
};

#endif
