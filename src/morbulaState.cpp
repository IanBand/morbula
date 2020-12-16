#include "morbulaState.hpp"
#include "debugLogger.hpp"

mbl::GameState::GameState(StageCollision *_stage_collision /*characters, stage*/){
    loadScene(_stage_collision);
};
void mbl::GameState::loadScene(StageCollision *_stage_collision /*characters, stage*/){
    // dont reload assets if current scene already has assets that are used in next scene
    // this is a premature optimization, dont implement it now
    stage_collision = _stage_collision;
};
void mbl::GameState::rollBackGameState(/*some state pointer? */){

};

void mbl::GameState::renderStateToSDL( SDL_Renderer* ctx /*pointer to render settings*/ ){

    camera_position = glm::vec2(0.0f,0.0f); //world space coordinate that the camear is pointing at

    //DEBUG render stage colission
    for(mbl::Surface surface : stage_collision->surfaces){
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
        
        //stage_collision->vertices[surface.v1]
        
        //convert world space to screen space
        //subtract camera position
        //flip y
        //divide by camera height
        //multiply by screen height
        
        	
        //SDL_RenderDrawLine( context, x1, y1, x2, y2) - screen space
        LOG("surface: ") LOG(surface.surface_type) LOG("\n")
    }

};