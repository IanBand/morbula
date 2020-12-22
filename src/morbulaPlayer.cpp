#include "morbula.hpp"
#include "debugLogger.hpp"

mbl::Player::Player(
    PlayerAttribute* _attributes, 
    /* pointer to inputter, */
    glm::vec2 init_position,
    glm::vec2 bounding_box_size,
    float base_ecb_height,
    float base_ecb_width,
    int init_surface = -1)
:Entity(
    init_position, 
    bounding_box_size, 
    base_ecb_height, 
    base_ecb_width, 
    init_surface
){
    attributes = _attributes; //must be renamed to player attributes
    velocity = glm::vec2(0.0f, 0.0f); //init to (0,0)
    overlay = {0xff,0xff,0xff,0x00};
};
void mbl::Player::rollBackState(/* some pointer to a state*/){
    
};
void mbl::Player::computeNextState(){
    LOG("fuckyou\n")
};