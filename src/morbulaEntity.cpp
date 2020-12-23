#include "morbula.hpp"
#include "debugLogger.hpp"
#include <cstring>

mbl::Entity::Entity(EntityInit *init, EntityAttribute *_entity_attr){

    // initialize attributes
    world_position    = init->world_position;
    surface_id        = init->surface_id;
    surface_position  = init->surface_position;
    visible           = init->visible;
    overlay           = init->overlay; 

    
    // copy entity attributes
    memcpy(&ea, _entity_attr, sizeof(mbl::EntityAttribute));
    
    // init bounding box
    bounding_box_offset = glm::vec2(0.0f, 0.0f); //always init to (0,0)
    bounding_box_size = ea.init_bounding_box_size;

    //init ecb
    ecb_bottom = 0.0f;
	ecb_top    = ea.base_ecb_height;
	ecb_mid    = ea.base_ecb_height * 0.5;
	ecb_left   = (ecb_right = ea.base_ecb_width * 0.5);
};
/*
void mbl::Entity::computeNextState(){
    ++action_state_frame_count;
};
void mbl::Entity::rollBackState(/* some pointer to a state){
    //set action_state_frame_count to whatever the rollback says it should be
};
*/
mbl::BoundingBox mbl::Entity::boundingBox(){
    //returns world coordinate bounding box for entity
    return {//bounding_box_size + bounding_box_offset
        {world_position.x + bounding_box_offset.x + bounding_box_size.x * 0.5,
         world_position.y + bounding_box_offset.y + bounding_box_size.y},
        {world_position.x + bounding_box_offset.x - bounding_box_size.x * 0.5,
         world_position.y + bounding_box_offset.y /* + 0 */ }
    };
};
void mbl::Entity::DEBUG_ecbDraw(
    SDL_Renderer* ctx, 
    glm::vec2* camera_pos, 
    float scale, 
    void drawLine( SDL_Renderer*, glm::vec2*, float, float, float, float, float)
)const{
    //draw ecb diamond
    drawLine(ctx, camera_pos, scale, 
        world_position.x,
        world_position.y + ecb_bottom,
        world_position.x + ecb_right,
        world_position.y + ecb_mid
    );
    drawLine(ctx, camera_pos, scale, 
        world_position.x + ecb_right,
        world_position.y + ecb_mid,
        world_position.x,
        world_position.y + ecb_top
    );
    drawLine(ctx, camera_pos, scale, 
        world_position.x,
        world_position.y + ecb_top,
        world_position.x - ecb_left,
        world_position.y + ecb_mid
    );
    drawLine(ctx, camera_pos, scale, 
        world_position.x - ecb_left,
        world_position.y + ecb_mid,
        world_position.x,
        world_position.y + ecb_bottom
    );
};

void mbl::Entity::DEBUG_BBDraw(
    SDL_Renderer* ctx, 
    glm::vec2* camera_pos, 
    float scale, 
    void drawLine( SDL_Renderer*, glm::vec2*, float, float, float, float, float)
)const{
    //draw bounding box / camera box
    //bounding_box_size - dimensions of bounding box
	//bounding_box_offset - offset of center of bounding box from base position
    // rewrite using lambdas and bounding box method

    drawLine(ctx, camera_pos, scale, 
        world_position.x + bounding_box_offset.x + bounding_box_size.x * 0.5,
        world_position.y + bounding_box_offset.y + bounding_box_size.y,
        world_position.x + bounding_box_offset.x + bounding_box_size.x * 0.5,
        world_position.y + bounding_box_offset.y + 0
    );
    drawLine(ctx, camera_pos, scale, 
        world_position.x + bounding_box_offset.x + bounding_box_size.x * 0.5,
        world_position.y + bounding_box_offset.y + 0,
        world_position.x + bounding_box_offset.x - bounding_box_size.x * 0.5,
        world_position.y + bounding_box_offset.y + 0
    );
    drawLine(ctx, camera_pos, scale, 
        world_position.x + bounding_box_offset.x - bounding_box_size.x * 0.5,
        world_position.y + bounding_box_offset.y + 0,
        world_position.x + bounding_box_offset.x - bounding_box_size.x * 0.5,
        world_position.y + bounding_box_offset.y + bounding_box_size.y
    );
    drawLine(ctx, camera_pos, scale, 
        world_position.x + bounding_box_offset.x - bounding_box_size.x * 0.5,
        world_position.y + bounding_box_offset.y + bounding_box_size.y,
        world_position.x + bounding_box_offset.x + bounding_box_size.x * 0.5,
        world_position.y + bounding_box_offset.y + bounding_box_size.y
    );
};
void mbl::Entity::DEBUG_posCrossHairDraw(
    SDL_Renderer* ctx, 
    glm::vec2* camera_pos, 
    float scale, 
    void drawLine( SDL_Renderer*, glm::vec2*, float, float, float, float, float)
)const{
    //draw world_position crosshairs
    float crosshair_size = 0.1f;
    drawLine(ctx, camera_pos, scale, 
        world_position.x - crosshair_size,
        world_position.y,
        world_position.x + crosshair_size,
        world_position.y
    );
    drawLine(ctx, camera_pos, scale, 
        world_position.x,
        world_position.y - crosshair_size,
        world_position.x,
        world_position.y + crosshair_size
    );
};

