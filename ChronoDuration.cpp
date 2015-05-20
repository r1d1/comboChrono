#include "ChronoDuration.h"

//ChronoDuration::ChronoDuration(){}

ChronoDuration::ChronoDuration(float dur, std::string startSnd, std::string endSnd, std::string exinf)
{
	durationInSec = dur;
	// Set sound file names :
	startSoundName = startSnd;
	endSoundName = endSnd;
	exerciseInfo = exinf;

	// Fill buffers :
	if( startSoundName.compare("None") != 0 )
	{
		if( !startSoundBuf.LoadFromFile(soundPath+startSoundName)){ std::cerr << "Can't load sound file " << startSoundName << std::endl; }
	}
	else{ std::cout << "Start sound not defined ; using no sound" << std::endl; }
	if( endSoundName.compare("None") != 0 )
	{
		if( !endSoundBuf.LoadFromFile(soundPath+endSoundName)){ std::cerr << "Can't load sound file " << endSoundName << std::endl; }
	}
	else{ std::cout << "End sound not defined ; using no sound" << std::endl; }

	// Associate buffer to sound :
	startSound.SetBuffer(startSoundBuf);
	endSound.SetBuffer(endSoundBuf);
	std::cout << "CTOR ChronoDuration / info : " << startSoundName << " " << startSoundName.compare("None") << " " << endSoundName << " " << endSoundName.compare("None") << " - " << durationInSec << " - do : " << exerciseInfo << std::endl;
}

ChronoDuration::~ChronoDuration(){}

void ChronoDuration::playStartSound(){ if( startSoundName.compare("None") != 0 ){ startSound.Play(); sleep(startSoundBuf.GetDuration()+1); } }
void ChronoDuration::playEndSound(){ if(endSoundName.compare("None") != 0){ endSound.Play(); sleep(endSoundBuf.GetDuration()+1); } }

float ChronoDuration::getDuration(){ return durationInSec; }
std::string ChronoDuration::getStartSoundName(){ return startSoundName; }
std::string ChronoDuration::getEndSoundName(){ return endSoundName; }
std::string ChronoDuration::getExerciseInfo(){ return exerciseInfo; }

void ChronoDuration::displayInfo(sf::RenderWindow & app, int xpos, int ypos, sf::Color color)
{
	std::ostringstream data;
	data << std::setw(30) << std::left << exerciseInfo << std::setw(4) << std::right << durationInSec << "s" <<  std::endl;
	sf::String textToDisp;
	textToDisp.SetText(data.str());
	textToDisp.SetSize(25);
	textToDisp.SetColor(color);
	textToDisp.SetPosition(xpos, ypos);
	app.Draw(textToDisp);
}

void ChronoDuration::displayInfo()
{
/*	sf::SoundBuffer bufStart, bufEnd;
	bufStart.LoadFromFile("sound/"+startSound);
	bufEnd.LoadFromFile("sound/"+endSound);

	sf::Sound sndStart, sndEnd;
	sndStart.SetBuffer(bufStart);
	sndEnd.SetBuffer(bufEnd);
*/
	startSound.Play();
	sleep(startSoundBuf.GetDuration()+1);
	endSound.Play();
	sleep(endSoundBuf.GetDuration()+1);
	
	std::cout << "stsnd : " << startSoundName << "/ dur: " << durationInSec << "s / endsnd : " << endSoundName << std::endl;
	//playStartSound();
	//playEndSound();
//	sndEnd.Play();
//	sleep(bufEnd.GetDuration()+1);
}
