////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ctime>
#include <iostream>
#include <sstream>

#include "Chrono.h"

#define APP_VERSION 0.2

#define DAYINSEC 86400
//#define WIN_H 75
#define WIN_H 300
#define WIN_W 400

//-------------------------------------------------------//
// Entry point of application
//
// \return Application exit code
//
//-------------------------------------------------------//

sf::Color f(float);
int getCumulativeTime(int step, std::vector<ChronoDuration> & sched);

std::ostringstream app_title;

int main(int argc, char** argv)
{
	app_title << "Combo Chrono ! - v" << APP_VERSION;
	// Create main window
	sf::RenderWindow App(sf::VideoMode(WIN_W, WIN_H), app_title.str());
	
	float startTime, previousTime, currentTime, elapsedTime, deltaTime;
	startTime = previousTime = currentTime = elapsedTime = deltaTime = 0;
	bool paused, counting;
	paused = true; counting = false;

	sf::SoundBuffer buftest;
	sf::Sound soundtest;

	buftest.LoadFromFile("sound/sw_vaderyes.wav");
	soundtest.SetBuffer(buftest);

	std::vector<ChronoDuration> schedule;
	int scheduleState =0;
	// Default program :
	ChronoDuration time1(10, "None", "mphg_ni.wav", "1 - Push-ups");
	ChronoDuration time2(7, "None", "ut_doublekill.wav", "2 - Crunch");
	ChronoDuration time3(9, "None", "sw_vaderyes.wav", "3 - Power Jacks");
	//ChronoDuration time3(9,"ut_godlike.wav", "sw_vaderyes.wav");
	ChronoDuration time4(5, "None", "ut_unstoppable.wav", "4 - Mountain Climbers");

	schedule.push_back(time1);
	schedule.push_back(time2);
	schedule.push_back(time3);
	schedule.push_back(time4);


//	Chrono krono;
	//krono.loadSchedule("defaultsched.txt");
    
	std::cout << "Debug menu : " << std::endl
	<< "---------------------------------- " << std::endl
	<< "Press R to initialize time counting ; " << std::endl
	<< "Press Space to pause/resume ;" << std::endl
	<< "Press Escape to quit ;" << std::endl
	<< "---------------------------------- " << std::endl
	<< "That's all folks !!!" << std::endl;

	// Start game loop
	while (App.IsOpened())
	{
		// -------------------------------------------------------------
		// Get current time and date
		time_t t = time(0); // time now
		struct tm * now = localtime( &t );
		std::ostringstream datess;
		std::ostringstream eltimess;
		datess << "Current time : " <<  now->tm_hour / 10 << now->tm_hour % 10 << ":"
		<< now->tm_min / 10 << now->tm_min % 10 << ":"
		<< now->tm_sec / 10 << now->tm_sec % 10 << std::endl;
		//<< now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec << "/" << 3600*23+60*59+59+1 << " - st : " << startTime << " pt : " << previousTime << " ct : " << currentTime 
		eltimess << "Elapsed time : " <<  elapsedTime;
		//<< now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec << "/" << 3600*23+60*59+59+1 << " - " << krono.getElapsedTime();


		// -------------------------------------------------------------
		// Count time :
		//krono.runChrono();
		//krono.countTime();
		// -------------------------------------------------------------

		// Process events
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			// Close window : exit
			if(Event.Type == sf::Event::Closed){ std::cout << "close ..." << std::endl; App.Close(); }
			if(Event.Type == sf::Event::KeyPressed)
			{
				if( Event.Key.Code == sf::Key::Escape){ App.Close(); }
				if(App.GetInput().IsKeyDown(sf::Key::R))
				{
					// Initialize and Start Chrono :
					startTime = float(now->tm_hour)*3600 + float(now->tm_min) * 60 + float(now->tm_sec);
					currentTime = previousTime = startTime; 
					deltaTime = elapsedTime = 0;
					scheduleState = 0;
					paused = false;
					counting = true;
					std::cout << "play start ! schedule state : " << scheduleState << std::endl;
					schedule[scheduleState].playStartSound();
				}
				if(App.GetInput().IsKeyDown(sf::Key::Space)){ paused = !paused; }
				if(App.GetInput().IsKeyDown(sf::Key::T)){ soundtest.Play();sleep(buftest.GetDuration()+1); }
			}
		}
		
		// Update time variables =======================================
		if(startTime > 0 && counting)
		{
			//std::cout << "." << std::flush;
			currentTime = float(now->tm_hour)*3600 + float(now->tm_min) * 60 + float(now->tm_sec);
			deltaTime = currentTime - previousTime;
			if(!paused)
			{
				elapsedTime += deltaTime; 

				if( (elapsedTime == getCumulativeTime(scheduleState, schedule)) )
				{
					std::cout << "play end ! schedule state : " << scheduleState << std::endl;
					schedule[scheduleState].playEndSound();
					scheduleState++;
					if( scheduleState < schedule.size())
					{
						schedule[scheduleState].playStartSound();
						std::cout << "play start ! schedule state : " << scheduleState << std::endl;
					}
					else{ std::cout << "Finished ! schedule state : " << scheduleState  << std::endl; counting=false;  }
				}
			}
			previousTime = currentTime;
		}

		// Graphics ====================================================
		// Clear screen
		App.Clear(sf::Color(f(now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec)));

		//Draw date and time
		sf::String Texte;
		Texte.SetText(datess.str());
		Texte.SetSize(25);
//		Texte.SetPosition(WIN_W / 12, WIN_H / 2 - 12);
		Texte.SetPosition(5, 5);
		App.Draw(Texte);
		
		Texte.SetText(eltimess.str());
		Texte.SetPosition(5, 5+30);
		App.Draw(Texte);

		// Exercices list :
		for(int i=0 ; i < schedule.size() ; i++){ schedule[i].displayInfo(App, 5, 60+25*i, (( (i == scheduleState) && counting)? sf::Color::Red : sf::Color::Black)); }
		//

		// Menu :

		// Finally, display the rendered frame on screen
		App.Display();
	}

    return EXIT_SUCCESS;
}

sf::Color f(float timeInSec)
{
	sf::Color correspondingColor(63+64*(1+sin(3600*M_PI*timeInSec/DAYINSEC)), 63+64*(1+sin(M_PI*timeInSec/DAYINSEC)), 63+64*(1+sin(60*M_PI*timeInSec/DAYINSEC)));
	return correspondingColor;
}

int getCumulativeTime(int step, std::vector<ChronoDuration> & sched)
{
        int cumTime=0;
        for(int it=0 ; it<=step ; it++)
        {
                cumTime += sched[it].getDuration();
        }
	//std::cout << "step /time : " << step << "/" << cumTime << std::endl;
        return cumTime;
}

