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
    //memcpy(&ea, _entity_attr, sizeof(mbl::EntityAttribute));
    ea = *_entity_attr;
    
    // init bounding box
    bounding_box_offset = glm::vec2(0.0f, 0.0f); //always init to (0,0)
    bounding_box_size = ea.init_bounding_box_size;

    //init ecb
    ecb.bottom = 0.0f;
	ecb.top    = ea.base_ecb_height;
	ecb.mid    = ea.base_ecb_height * 0.5;
	ecb.left   = (ecb.right = ea.base_ecb_width * 0.5);
    prev_ecb = ecb;
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
    /*
        p1 and p2 should satisfy:
        p1.x < p2.x
        p1.y < p2.y
    */
    return {//bounding_box_size + bounding_box_offset        
        {world_position.x + bounding_box_offset.x - bounding_box_size.x * 0.5,
         world_position.y + bounding_box_offset.y /* + 0 */ },
        {world_position.x + bounding_box_offset.x + bounding_box_size.x * 0.5,
         world_position.y + bounding_box_offset.y + bounding_box_size.y}
    };
};
mbl::Line mbl::Entity::bottomWorldTravelLine(){
    return {{world_position.x,      world_position.y      + ecb.bottom},
            {prev_world_position.x, prev_world_position.y + prev_ecb.bottom}}; 
};
mbl::Line mbl::Entity::topWorldTravelLine(){
    return {{world_position.x,      world_position.y      + ecb.top},
            {prev_world_position.x, prev_world_position.y + prev_ecb.top}}; 
};
mbl::Line mbl::Entity::leftWorldTravelLine(){
    return {{world_position.x      - ecb.left,      world_position.y      + ecb.mid},
            {prev_world_position.x - prev_ecb.left, prev_world_position.y + prev_ecb.mid}}; 
};
mbl::Line mbl::Entity::rightWorldTravelLine(){
    return {{world_position.x      + ecb.right,      world_position.y      + ecb.mid},
            {prev_world_position.x + prev_ecb.right, prev_world_position.y + prev_ecb.mid}};
};
void mbl::Entity::DEBUG_ecbDraw(
    SDL_Renderer* ctx, 
    glm::vec2* camera_pos, 
    float scale, 
    void drawLine( SDL_Renderer*, glm::vec2*, float, float, float, float, float)
)const{
    /*
    mbl::Color sc = mbl::lime;
    SDL_SetRenderDrawColor( ctx, sc.r, sc.g, sc.b, 0xff );
    SDL_RenderDrawLine( ctx, 
        worldToCameraX(world_position.x),
        worldToCameraY(world_position.y + ecb.bottom),
        worldToCameraX(prev_world_position.x),
        worldToCameraY(prev_world_position.y + prev_ecb.bottom)
    );
    */
    
    //draw ecb diamond
    // bottom -> right
    drawLine(ctx, camera_pos, scale, 
        world_position.x,
        world_position.y + ecb.bottom,
        world_position.x + ecb.right,
        world_position.y + ecb.mid
    );
    // right -> top
    drawLine(ctx, camera_pos, scale, 
        world_position.x + ecb.right,
        world_position.y + ecb.mid,
        world_position.x,
        world_position.y + ecb.top
    );
    // top -> left
    drawLine(ctx, camera_pos, scale, 
        world_position.x,
        world_position.y + ecb.top,
        world_position.x - ecb.left,
        world_position.y + ecb.mid
    );
    // left -> bottom
    drawLine(ctx, camera_pos, scale, 
        world_position.x - ecb.left,
        world_position.y + ecb.mid,
        world_position.x,
        world_position.y + ecb.bottom
    );

    //draw ecb travel lines
    //top
    drawLine(ctx, camera_pos, scale, 
        world_position.x,
        world_position.y + ecb.top,
        prev_world_position.x,
        prev_world_position.y + prev_ecb.top
    );
    //left
    drawLine(ctx, camera_pos, scale, 
        world_position.x - ecb.left,
        world_position.y + ecb.mid,
        prev_world_position.x - prev_ecb.left,
        prev_world_position.y + prev_ecb.mid
    );
    //right
    drawLine(ctx, camera_pos, scale, 
        world_position.x + ecb.right,
        world_position.y + ecb.mid,
        prev_world_position.x + prev_ecb.right,
        prev_world_position.y + prev_ecb.mid
    );
    //bottom
    drawLine(ctx, camera_pos, scale, 
        world_position.x,
        world_position.y + ecb.bottom,
        prev_world_position.x,
        prev_world_position.y + prev_ecb.bottom
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

