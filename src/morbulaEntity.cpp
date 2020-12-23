#include "morbula.hpp"
#include "debugLogger.hpp"

mbl::Entity::Entity(
    glm::vec2 init_position, 
    glm::vec2 _bounding_box_size,
    float _base_ecb_height,
    float _base_ecb_width,
    int init_surface = -1
){
    world_position    =  init_position, 
    bounding_box_size = _bounding_box_size,
    base_ecb_height   = _base_ecb_height;
    base_ecb_width    = _base_ecb_width;

    bounding_box_offset = glm::vec2(0.0f, 0.0f); //always init to (0,0)

    //init ecb
    ecb_bottom = 0.0f;
	ecb_top    = base_ecb_height;
	ecb_mid    = base_ecb_height * 0.5;
	ecb_left   = (ecb_right = base_ecb_width * 0.5);

    visible              = true;
	in_camera_view       = true;
	use_entity_colission = true; 
	use_stage_colission  = true;
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

