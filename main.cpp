////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <ctime>
#include <iostream>
#include <sstream>

#include "Chrono.h"

#define DAYINSEC 86400
#define WIN_H 75
#define WIN_W 400

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
const std::string soundPath = "sound/";

sf::Color f(float);

int main(int argc, char** argv)
{
    // Create main window
    sf::RenderWindow App(sf::VideoMode(400, 75), "Combo Chrono !");
    //sf::RenderWindow App(sf::VideoMode(400, 75), "Combo Chrono !", sf::Style::Fullscreen);

    Chrono krono;
    krono.loadSchedule("defaultsched.txt");
    // Load media
    //std::vector<sf::SoundBuffer> bufferSounds;
    sf::SoundBuffer bufferSound0;
    sf::SoundBuffer bufferSound1;
    sf::SoundBuffer bufferSound2;
    sf::Sound Sound0;
    sf::Sound Sound1;
    sf::Sound Sound2;
    
    bufferSound0.LoadFromFile(soundPath+"headshot.wav");
    bufferSound1.LoadFromFile(soundPath+"megakill.wav");
    bufferSound2.LoadFromFile(soundPath+"multikill.wav");
    
    Sound0.SetBuffer(bufferSound0);
    Sound1.SetBuffer(bufferSound1);
    Sound2.SetBuffer(bufferSound2);

/*
State machine :

0 : Loading screen
1 : Main screen : lancer / pauser / stopper chrono // flags 

*/

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
		datess << now->tm_hour / 10 << now->tm_hour % 10 << ":"
                << now->tm_min / 10 << now->tm_min % 10 << ":"
                << now->tm_sec / 10 << now->tm_sec % 10 << "-"
				<< now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec << "/" << 3600*23+60*59+59+1 << " - " << krono.getElapsedTime();
				
				//<< (now->tm_year+1900)
                //<< (now->tm_mon+1) / 10 << (now->tm_mon+1) % 10
                //<< now->tm_mday / 10  << now->tm_mday % 10
                //<< "-"
	// -------------------------------------------------------------
	krono.countTime();

        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed){ App.Close(); }
            
	    if (Event.Type == sf::Event::KeyPressed)
	    {
		if( Event.Key.Code == sf::Key::Escape){ App.Close(); }

	    	if(App.GetInput().IsKeyDown(sf::Key::R)){ krono.startChrono(); }
	    	if(App.GetInput().IsKeyDown(sf::Key::Space)){ krono.pauseChrono(); }

	    	if(App.GetInput().IsKeyDown(sf::Key::A)){ Sound0.Play(); }
	    	if(App.GetInput().IsKeyDown(sf::Key::Z)){ Sound1.Play(); }
	    	if(App.GetInput().IsKeyDown(sf::Key::E)){ Sound2.Play(); }
	    	//if(App.GetInput().IsKeyDown(sf::Key::T)){ krono.countTime(); }
	    	//if(App.GetInput().IsKeyDown(sf::Key::Y)){ std::cout << "Time from SFML : " << App.GetFrameTime() << std::endl; }
	    }
        }
//	if( !(now->tm_sec % 10) ){ Sound0.Play(); }
//	if( !((now->tm_sec+4) % 10) ){ Sound1.Play(); }
//	if( !((now->tm_sec+7) % 10) ){ Sound2.Play(); }

        // Clear screen
        App.Clear(sf::Color(f(now->tm_hour * 3600 + now->tm_min * 60 + now->tm_sec)));

		//Draw date and time
		sf::String Texte;
		Texte.SetText(datess.str());
		Texte.SetSize(25);
		Texte.SetPosition(WIN_W / 6, WIN_H / 2 - 12);
		App.Draw(Texte);

        // Draw apredefined shape
        //App.Draw(sf::Shape::Circle(200, 200, 100, sf::Color::Yellow, 10, sf::Color::Blue));

        // Finally, display the rendered frame on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}

sf::Color f(float timeInSec)
{
//	sf::Color correspondingColor( 127*(1+sin(3600*M_PI*timeInSec/DAYINSEC)), 127*(1+sin(3600*M_PI*timeInSec/DAYINSEC)), 127*(1+sin(3600*M_PI*timeInSec/DAYINSEC)));
	//sf::Color correspondingColor( 127*(1+sin(3600*M_PI*timeInSec/DAYINSEC)), 127*(1+sin(M_PI*timeInSec/DAYINSEC)), 127*(1+sin(60*M_PI*timeInSec/DAYINSEC)));
	sf::Color correspondingColor(63+64*(1+sin(3600*M_PI*timeInSec/DAYINSEC)), 63+64*(1+sin(M_PI*timeInSec/DAYINSEC)), 63+64*(1+sin(60*M_PI*timeInSec/DAYINSEC)));
	return correspondingColor;
}
