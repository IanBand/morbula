#include "sdlUtil.hpp"
#include "../lib/gca-plus/GCAdapter.h"
#include "morbulaState.hpp"
#include "debugLogger.hpp"


int main( int argc, char* argv[] )
{
	LOG("Application is running in debug mode\n")

	/** maybe turn the top level into something like this one day?
	 * Game game(argc, argv);
	 * if(game.init()){
	 * 		while(game.active()){
	 * 			game.runFrame()
	 * 		}
	 * }
	 * 
	*/

	//game state

	//menu state
	//input manager


	Uint32 prev_frame_ts;
	Uint32 frame_number = 0;



	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to init sdl!\n" );
	}
	else if(!gca::Setup()){
		printf( "Failed to init gca!\n" );
	}
	else
	{
		//Load media
		if( false ) //init resource load?
		{
			printf( "Failed to load media!\n" );
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
				prev_frame_ts = SDL_GetTicks();
				LOG("running frame# ") LOG(frame_number) LOG(", rng: ") LOG(mbl::rng()) LOG("\n")

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				// Get player input

				// Compute next game state

				// Compute next menu state
				
				// Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );


				
				//Render red filled quad
				SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				if(frame_number % 2 == 0){
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );	
				}
				else{
					SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				}	
				SDL_RenderFillRect( gRenderer, &fillRect );



				// Draw game state

					// layer 0
					// layer 1
					// layer 2
					// ect

				// Draw menu state


				// Update screen
				SDL_RenderPresent( gRenderer );
				++frame_number;
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}