#include "sdlUtil.hpp"
#include "../lib/gca-plus/GCAdapter.h"
#include "inputter.hpp"
#include "morbula.hpp"
#include "debugLogger.hpp"
#include <csignal>

void sigHandler( int signum ) {
   std::cout << "Interrupt signal (" << signum << ") received.\n";

   	// cleanup and close up stuff here  
   	// terminate program
	// https://stackoverflow.com/questions/16768363/exception-handling-and-stacktrace-under-windows-mingw-gcc   	close(); //sdl
	gca::Stop();
	exit(signum);
};


int main( int argc, char *argv[] )
{
	// dev build date/time message
	LOG(" __       __   ______   _______   _______   __    __  __         ______\n/  \\     /  | /      \\ /       \\ /       \\ /  |  /  |/  |       /      \\\n$$  \\   /$$ |/$$$$$$  |$$$$$$$  |$$$$$$$  |$$ |  $$ |$$ |      /$$$$$$  |\n$$$  \\ /$$$ |$$ |  $$ |$$ |__$$ |$$ |__$$ |$$ |  $$ |$$ |      $$ |__$$ |\n$$$$  /$$$$ |$$ |  $$ |$$    $$< $$    $$< $$ |  $$ |$$ |      $$    $$ |\n$$ $$ $$/$$ |$$ |  $$ |$$$$$$$  |$$$$$$$  |$$ |  $$ |$$ |      $$$$$$$$ |\n$$ |$$$/ $$ |$$ \\__$$ |$$ |  $$ |$$ |__$$ |$$ \\__$$ |$$ |_____ $$ |  $$ |\n$$ | $/  $$ |$$    $$/ $$ |  $$ |$$    $$/ $$    $$/ $$       |$$ |  $$ |\n$$/      $$/  $$$$$$/  $$/   $$/ $$$$$$$/   $$$$$$/  $$$$$$$$/ $$/   $$/\n\n")
	LOG("*** This is a development build from ") LOG( __DATE__ ) LOG(" at ") LOG( __TIME__ )
	LOG("\n*** Check https://github.com/IanBand/morbula for the latest development push!\n\n")


	std::signal(SIGINT,  sigHandler);
	std::signal(SIGSEGV, sigHandler);

	//menu state

	//input manager
	std::vector<input::Inputter*> inputs;
	
	//create input(s)
	input::GCInputter gc_input(input::GCPort::P1);
	inputs.push_back(&gc_input);

	//game state
	mbl::Scene morbula_scene;

	uint32_t prev_frame_ts;
	uint32_t cur_ticks;

	//global frame number
	uint32_t frame_number = 0;

	//Start up SDL and create window
	if( !init() )
	{
		std::cout << "Failed to init sdl!" << std::endl;
	}
	else
	{
		//Load media
		if( false ) //init resource load?
		{
			std::cout << "Failed to load media" << std::endl;
		}
		else if(!gca::Setup()){
			std::cout << "Failed to load gca" << std::endl;
		}
		else
		{	
			//Main loop flag
			bool quit = false;


			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				// wait for frame interval
				while(SDL_GetTicks() - prev_frame_ts < SCREEN_TICK_PER_FRAME){
					//do nothing	
				}
				
				// log frame overhead
				//cur_ticks = SDL_GetTicks();
				//LOG("frame overhead: ") LOG(cur_ticks - prev_frame_ts); LOG("\n")
				//prev_frame_ts = cur_ticks;
				
				prev_frame_ts = SDL_GetTicks();

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				// Get inputs
				for(input::Inputter *input : inputs ){
					input->getInputs(frame_number);
					//check if start button is pushed on any inputter  
    			}

				// Compute next game state
				morbula_scene.advanceGameState();

				// Compute next menu state
				
				// Clear previous frame
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				SDL_RenderClear( gRenderer );

				// Draw game state
				morbula_scene.renderStateToSDL( gRenderer );

				// Draw menu state

				// Update screen
				SDL_RenderPresent( gRenderer );

				++frame_number;
			}
		}
	}

	//Free resources and close SDL
	close();

	gca::Stop();

	return 0;
};