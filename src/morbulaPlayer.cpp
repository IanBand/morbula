#include "morbula.hpp"
#include "debugLogger.hpp"
#include <cstring>

mbl::Player::Player(
    PlayerAttribute* _player_attr, 
    /* pointer to inputter, */
    EntityInit * _entity_init,
    EntityAttribute* _entity_attr)
:Entity(_entity_init, _entity_attr){

    //memcpy(&pa, _player_attr, sizeof(mbl::PlayerAttribute));
    pa = *_player_attr;
    
    velocity = glm::vec2(0.012f, 0.1f); //init to (0,0)
    
};
void mbl::Player::rollBackState(/* some pointer to a state*/){
    
};
void mbl::Player::computeNextState(mbl::Stage* stage){
    
    bool airborne = surface_id == -1;

    //LOG("surface_id of player: ")LOG(surface_id); LOG("\n")
    if(airborne){
        velocity.y -= pa.gravity;
        if(velocity.y < pa.slow_fall_velocity_max){
            velocity.y = pa.slow_fall_velocity_max;
        }
    }
    else{
        velocity = {0.0f,0.0f};
    }


    // save prev ecb & position
    prev_world_position = world_position;
    prev_ecb = ecb;

    world_position += velocity;
};