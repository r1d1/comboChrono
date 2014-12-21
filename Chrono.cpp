#include "Chrono.h"

Chrono::Chrono()
{
	paused = true;
	currentTime = startTime = 0;
}

Chrono::~Chrono(){}

void Chrono::loadSchedule(const char * schedFile)
{
	// Check schedFile name
	// open schedFile
	//std::ifstream filetoread;
	//filetoread.open(schedFile);

	std::cout << "CTOR chrono " << std::flush;

	ChronoDuration time1(5, "mphg_ni.wav");
	ChronoDuration time2(3, "double_kill.wav");
	ChronoDuration time3(8,"godlike.wav", "sw_vader03.wav");
	ChronoDuration time4(4, "unstoppable.wav");
	
	schedule.push_back(time1);
	schedule.push_back(time2);
	schedule.push_back(time3);
	schedule.push_back(time4);
	
	std::cout << "... done !" << std::endl;
}

void Chrono::resetChrono(){}

void Chrono::startChrono()
{
	time_t t = time(0);
	struct tm * now = localtime( &t );
	startTime = int(now->tm_hour)*3600 + int(now->tm_min) * 60 + int(now->tm_sec);
	previousTime = currentTime = startTime;
	elapsedTime=0;
	// reset state
	state = schedule.begin();
	
	paused = false;
	
	std::cout << "Started at " << startTime << std::endl;
}

void Chrono::pauseChrono()
{
	time_t t = time(0); // time now
	struct tm * now = localtime( &t );

	paused = !paused; 
	pauseTime = int(now->tm_hour)*3600 + int(now->tm_min) * 60 + int(now->tm_sec);
	std::cout << ( (paused) ? "Paused" : "Resumed" ) << " chrono at " << currentTime << "s time spent : " << elapsedTime << "s " << std::endl;
}

//void Chrono::resumeChrono(){ paused = true; }

void Chrono::countTime()
{
	 // Get current time and date
	time_t t = time(0); // time now
	struct tm * now = localtime( &t );
	int deltaTime;	
	// If we initialized chrono :
	if(startTime > 0)
	{
		// Get current time in sec currentTime-startTime
		currentTime = int(now->tm_hour)*3600 + int(now->tm_min) * 60 + int(now->tm_sec);
		deltaTime = currentTime - previousTime;
		// If not paused, we add the difference to elapsed time :
		if( !paused )
		{
			elapsedTime += deltaTime;	
//			std::cout << "Current time is " << currentTime << " time spent : " << elapsedTime << " - CT - ST : " << currentTime-startTime << std::endl;
		}
		// else, we only consider time from beginning to pauseTime
/*		else
		{
			std::cout << "chrono paused, saved time : " << elapsedTime << std::endl;
		}*/
//		std::cout << "deltatime : " <<deltaTime << std::endl;
		previousTime = currentTime;
	}
//	else{ std::cout << "Timer hasn't been initialized" << std::endl; }


}

// For debugging :
int Chrono::getElapsedTime(){ return elapsedTime; }

// For debugging :
void Chrono::displaySchedule()
{
	std::cout << "Schedule items : " << schedule.size() << std::endl;
	for(int i=0 ; i < schedule.size() ; i++)
	{
		schedule[i].displayInfo();
	}
}
