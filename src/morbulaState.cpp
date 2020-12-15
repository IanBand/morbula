#include "morbulaState.hpp"

mbl::GameState::GameState(StageCollision *_stage_collision /*characters, stage*/){
    loadScene(_stage_collision);
};
void mbl::GameState::loadScene(StageCollision *_stage_collision /*characters, stage*/){
    // dont reload assets if current scene already has assets that are used in next scene
    // this is a premature optimization, dont implement it now
    _stage_collision = _stage_collision;
};
void mbl::GameState::rollBackGameState(/*some state pointer? */){

};
