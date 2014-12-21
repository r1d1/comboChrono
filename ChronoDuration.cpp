#include "ChronoDuration.h"

ChronoDuration::ChronoDuration(){}

ChronoDuration::ChronoDuration(float dur, std::string startSnd, std::string endSnd)
{
	durationInSec = dur;
	startSound = startSnd;
	endSound = endSnd;
}

ChronoDuration::~ChronoDuration(){}

void ChronoDuration::displayInfo()
{
	sf::SoundBuffer bufStart, bufEnd;
	bufStart.LoadFromFile("sound/"+startSound);
	bufEnd.LoadFromFile("sound/"+endSound);

	sf::Sound sndStart, sndEnd;
	sndStart.SetBuffer(bufStart);
	sndEnd.SetBuffer(bufEnd);

	sndStart.Play();
	sleep(bufStart.GetDuration()+1);
	std::cout << "stsnd : " << startSound << " / dur: " << durationInSec << "s / endsnd : " << endSound << std::endl;
	sndEnd.Play();
	sleep(bufEnd.GetDuration()+1);

}
