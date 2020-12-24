#include "morbula.hpp"
#include "debugLogger.hpp"
#include <cstring>

mbl::Player::Player(
    PlayerAttribute* _player_attr, 
    /* pointer to inputter, */
    EntityInit * _entity_init,
    EntityAttribute* _entity_attr)
:Entity(_entity_init, _entity_attr){

    memcpy(&pa, _player_attr, sizeof(mbl::PlayerAttribute));
    velocity = glm::vec2(0.0f, 0.0f); //init to (0,0)
    
};
void mbl::Player::rollBackState(/* some pointer to a state*/){
    
};
void mbl::Player::computeNextState(){
    //assuming airborne
    velocity.y -= pa.gravity;
    if(velocity.y < pa.slow_fall_velocity_max){
        velocity.y = pa.slow_fall_velocity_max;
    }
    world_position += velocity;
};