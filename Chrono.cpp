#include "Chrono.h"

Chrono::Chrono()
{
	std::cout << "CTOR chrono " << std::flush;
	
	counting = false;
	paused = true;
	currentTime = startTime = 0;
	elapsedTime=0;
	state = 0;
	std::cout << "CTOR done" << std::endl;

	// Welcome sound
	buf.LoadFromFile("sound/cc_welcome.wav");
	snd.SetBuffer(buf);
	snd.Play();
	sleep(buf.GetDuration()+1);
}

Chrono::~Chrono(){ /*soundLib.clear();*/ }


void Chrono::runChrono()
{
	if( counting ){ countTime(); }
}

void Chrono::loadSchedule(const char * schedFile)
{
	// Check schedFile name
	// open schedFile
	//std::ifstream filetoread;
	//filetoread.open(schedFile);

	std::cout << "Chrono: loadSchedule : " << std::endl;
	// build fake schedule for testing :
	ChronoDuration time1(5,"mphg_ni.wav");
	ChronoDuration time2(3,"ut_doublekill.wav");
	ChronoDuration time3(2,"ut_godlike.wav", "sw_vaderyes.wav");
	ChronoDuration time4(4,"ut_unstoppable.wav");

	schedule.push_back(time1);
	schedule.push_back(time2);
	schedule.push_back(time3);
	schedule.push_back(time4);
	/* End of fake schedule */

	std::cout << "... done !" << std::endl;

	//schedule[0].playStartSound();
	std::cout << "Ni said !" << std::endl;
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
	//state = schedule.begin();
	state = 0;
	
	paused = false;
	counting = true;
	
	std::cout << "Started at " << startTime << " playing ... "  << schedule[state].getStartSoundName() << std::endl;
	schedule[state].playStartSound();
	
}

void Chrono::pauseChrono()
{
	time_t t = time(0); // time now
	struct tm * now = localtime( &t );

	paused = !paused; 
	pauseTime = int(now->tm_hour)*3600 + int(now->tm_min) * 60 + int(now->tm_sec);
	std::cout << ( (paused) ? "Paused" : "Resumed" ) << " chrono at " << currentTime << "s time spent : " << elapsedTime << "s " << std::endl;
}

void Chrono::countTime()
{
//	std::cout << "paf2" << std::endl;
	 // Get current time and date
	time_t t = time(0); // time now
	struct tm * now = localtime( &t );
	int deltaTime;	
	// If we initialized chrono :
	//if(startTime > 0 && counting) 
	if(startTime > 0) 
	{
		// Get current time in sec currentTime-startTime
		currentTime = int(now->tm_hour)*3600 + int(now->tm_min) * 60 + int(now->tm_sec);
		deltaTime = currentTime - previousTime;
		// If not paused, we add the difference to elapsed time :
		if( !paused )
		{
			elapsedTime += deltaTime;
			// We check elapsedTime with schedule :
			if(elapsedTime == getCumulativeTime(state) )
			{
				std::cout << "Playing " << schedule[state].getEndSoundName() << " " <<  schedule[state].getDuration() << std::endl;
				schedule[state].playEndSound();
				//std::cout << typeid(state->getEndSound()).name() << std::endl; //.Play();
				state++;
				if(state == schedule.size()){ paused = true; counting = false; std::cout << "finished" << std::endl; }
				else{ std::cout << "Playing " << schedule[state].getStartSoundName() << std::endl; }
			}


		}
		previousTime = currentTime;
	}
//	else{ std::cout << "Timer hasn't been initialized" << std::endl; }
//	std::cout << "paf" << std::endl;
}

int Chrono::getElapsedTime(){ return elapsedTime; }

int Chrono::getCumulativeTime(int step)
{
	int cumTime=0;
	for(int it=0 ; it<step ; it++)
	{
		cumTime += schedule[it].getDuration();
	}
	return cumTime;
}

// For debugging :
void Chrono::displaySchedule()
{
	std::cout << "Schedule items : " << schedule.size() << std::endl;
	for(int i=0 ; i < schedule.size() ; i++)
	{
		schedule[i].displayInfo();
	}
}
