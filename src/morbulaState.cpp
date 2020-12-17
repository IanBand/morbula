#include "morbulaState.hpp"
#include "debugLogger.hpp"

mbl::GameState::GameState(StageCollision *_stage_collision /*characters, stage*/){
    loadScene(_stage_collision);
};
void mbl::GameState::rollBackGameState(/*some state pointer? */){

};
void mbl::GameState::loadScene(StageCollision *_stage_collision /*characters, stage*/){
    // dont reload assets if current scene already has assets that are used in next scene
    // this is a premature optimization, dont implement it now
    stage_collision = _stage_collision;
    camera_position = glm::vec2(0.0f,0.0f); //world space coordinate that the camear is pointing at, set to scene init camera?
    scale = 0.25;
    scene_frame_number = 0;
    rngr = 0; //seed the rng;
};
uint16_t mbl::GameState::rng(){
	rngr = rngr * 22695477 + 1;
	return rngr >> 16; //upper 16 bits
};

void mbl::GameState::advanceGameState(){
    ++scene_frame_number;

    scale = std::sin(scene_frame_number * 0.025) * 0.125 + 0.25; 
};
void mbl::GameState::renderStateToSDL( SDL_Renderer* ctx /*pointer to render settings*/ ){

    //DEBUG render stage colission
    for(mbl::Surface surface : stage_collision->surfaces){

        mbl::Color sc = mbl::SurfaceColors[(int) surface.surface_type];
        SDL_SetRenderDrawColor( gRenderer, sc.r, sc.g, sc.b, 0xff);
        
        //scale = 1 / (camera height in floats). big scale = zoom in 
        SDL_RenderDrawLine( ctx, 
        
            (int) ((stage_collision->vertices[surface.v1].x - camera_position.x) * SCREEN_WIDTH  * scale + (SCREEN_WIDTH / 2)),
            (int) ((stage_collision->vertices[surface.v1].y - camera_position.y) * SCREEN_HEIGHT * -1 * SCREEN_ASPECT * scale + (SCREEN_HEIGHT / 2)),
            (int) ((stage_collision->vertices[surface.v2].x - camera_position.x) * SCREEN_WIDTH  * scale + (SCREEN_WIDTH / 2)),
            (int) ((stage_collision->vertices[surface.v2].y - camera_position.y) * SCREEN_HEIGHT * -1 * SCREEN_ASPECT * scale + (SCREEN_HEIGHT / 2))
        );
        LOG("surface: ") LOG(surface.surface_type) LOG("\n")
    }
};

