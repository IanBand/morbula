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

    static glm::vec2 zero_vec(0.0f, 0.0f);
    
    bool airborne = surface_id == -1; //scene method, aka "the collider" assigns a new surface_id to the entity if it has collided with one
    mbl::Surface surface;
    glm::vec2 v1, v2, surface_dir_unit_vec;
    float surface_length;


    switch(action_state){
        default: 
            break;
        case idle:
            break;
        case walk_1:
        case walk_2:
        case walk_3:
            break;
        case dash:
            break;
        case run:
            break;
        case freefall:
            // aerial drift
            //if glm::length(stick_val.x) < some_stick_zone_cutoff
            //      stick_val
            //velocity += stick_val * pa.

            //fastfall
            break;
        case spinfall:
            // aerial drift
            break;
    }
    
    // save prev ecb & position
    prev_world_position = world_position;
    prev_ecb = ecb;
    prev_airborne = airborne;
	
    if(prev_action_state == action_state)
        ++action_state_frame_count;
    prev_action_state = action_state;


    // old shit

    /*

    else{
        //entity is bound to a surface

        // get surface info
        // might replace these with stage methods idk
        surface = stage->surfaces.at(surface_id);
        v1 = stage->vertices.at(surface.v1);
        v2 = stage->vertices.at(surface.v2);
        surface_dir_unit_vec = glm::normalize(v2 - v1);
        surface_length = glm::distance(v2,v1); // this should be kept precalculated in the stage data, and only updated when the stage animates.



        if(!prev_airborne){// first frame of landing on surface

            // velocity will be scalar projection of airborne velocity vector onto the surface, multiplied by some constant
            // velocity = surface_dir_unit_vec * glm::dot(surface_dir_unit_vec, velocity) * 0.05f;

            //when bound to the ground, this is the formula for world pos (pretty sure); bind to different ecb points for other surface types
            world_position = v1 + surface_position * surface_length * surface_dir_unit_vec;
        }

        
        if(glm::length(surface_position * surface_dir_unit_vec) > surface_length){
            // transition to v2 connected surface, if same type
        }
        else if(surface_position < 0){
            // transition to v1 connected surface, if same type
        }
        

        // bound to surface

        
        // decelerate player
        if(velocity != zero_vec){
            deceleration = 
            if(velocity.x < )
            velocity -= surface_dir_unit_vec
        }
        
    }
    




    
    if(airborne){
        world_position += velocity;
    }
    */
    
};