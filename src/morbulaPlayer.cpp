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
    if(airborne){
        velocity.y -= pa.gravity;
        if(velocity.y < pa.slow_fall_velocity_max){
            velocity.y = pa.slow_fall_velocity_max;
        }
    }
    else{

        //might replace these with stage methods idk
        mbl::Surface surface = stage->surfaces.at(surface_id);
        glm::vec2 v1 = stage->vertices.at(surface.v1);
        glm::vec2 v2 = stage->vertices.at(surface.v2);


        //when bound to the ground, this is the formula for world pos (pretty sure); bind to different ecb points for other surface types
        world_position = v1 + surface_position * glm::normalize(v2 - v1);
        

        // on first frame of air->surface
        // velocity will be scalar projection of airborne velocity vector onto the surface, multiplied by some constant
        velocity = glm::normalize(v2 - v1) * glm::dot(v2 - v1, velocity) * 0.05f;
    }


    // save prev ecb & position
    prev_world_position = world_position;
    prev_ecb = ecb;

    // in the case of air->surface transition, the world position is not incrimented by velocity..?
    world_position += velocity;
};