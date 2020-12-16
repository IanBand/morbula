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

    camera_position = glm::vec2(0.0f,0.0f);

    //DEBUG render stage colission
    
    for(int i = 0; i < stage_collision->surfaces.size(); ++i){
        LOG("surface: ") LOG(stage_collision->surfaces[i].surface_type) LOG("\n")
    }




    //stage.verticies[]

    //convert world space to camera space

};