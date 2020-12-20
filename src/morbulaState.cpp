#include "morbulaState.hpp"
#include "debugLogger.hpp"


/*******************************************************
* Game State                                           *
*******************************************************/
mbl::GameState::GameState(){

    
	//https://www.xspdf.com/resolution/53778619.html
	//https://softwareengineering.stackexchange.com/questions/247245/a-vector-of-pointers-to-different-derived-classes-of-the-same-base-class
	//https://stackoverflow.com/questions/34383979/c-vector-of-base-class-objects/34384868
	// seems like we use a vector of base class smart pointers

    //init test data
    // GameState owns all entity pointers
    entities.push_back(new mbl::Player( &mbl::test_char_attr /*pointer to inputter*/));

    stage_collision = &mbl::test_stage_collision; //crashes without this, need to put stage in another data structure

    camera_position = glm::vec2(0.0f,0.0f); //world space coordinate that the camear is pointing at, set to scene init camera?
    scale = 0.25;
    scene_frame_number = 0;
    rngr = 0; //seed the rng;


    //loadScene();
};
mbl::GameState::~GameState(){
    for(mbl::Entity *entity : entities ){
        delete entity;
    }
}
void mbl::GameState::rollBackGameState(/*some state pointer? */){

};
void mbl::GameState::loadScene(){
    // dont reload assets if current scene already has assets that are used in next scene
    // this is a premature optimization, dont implement it now


    //entities = _entities;
    //stage_collision = _stage_collision;

};
uint16_t mbl::GameState::rng(){
	rngr = rngr * 22695477 + 1;
	return rngr >> 16; //upper 16 bits
};
int mbl::GameState::worldToCameraX(float x){
    return (int) ((x - camera_position.x) * SCREEN_WIDTH * scale + (SCREEN_WIDTH >> 1));
};
int mbl::GameState::worldToCameraY(float y){
    return (int) ((y - camera_position.y) * SCREEN_HEIGHT * -1 * SCREEN_ASPECT * scale + (SCREEN_HEIGHT >> 1));
};
void mbl::GameState::SDL_DrawLineFromWorldCoord( SDL_Renderer* ctx, glm::vec2* camera_position, float scale, float x1, float y1, float x2, float y2)
{
    //convert world space to camera space, draw line
    SDL_RenderDrawLine( ctx,
        (int) ((x1 - camera_position->x) * SCREEN_WIDTH * scale + (SCREEN_WIDTH >> 1)),
        (int) ((y1 - camera_position->y) * SCREEN_HEIGHT * -1 * SCREEN_ASPECT * scale + (SCREEN_HEIGHT >> 1)),
        (int) ((x2 - camera_position->x) * SCREEN_WIDTH * scale + (SCREEN_WIDTH >> 1)),
        (int) ((y2 - camera_position->y) * SCREEN_HEIGHT * -1 * SCREEN_ASPECT * scale + (SCREEN_HEIGHT >> 1))
    );
};
void mbl::GameState::advanceGameState(){
    ++scene_frame_number;
    scale = 0.25;
    scale = std::sin(scene_frame_number * 0.025) * 0.125 + 0.25; 
};
void mbl::GameState::calcCameraPosition(){
    //loop through entities in camera_entity_list
    //keep track of min and max x and y coordinates of the bounding boxes of the entities to create a "camera bounding box." respect camera bounds during this
    //add margins to the master box
    //compute scale from the box
};
void mbl::GameState::renderStateToSDL( SDL_Renderer* ctx /*pointer to render settings*/ ){



    //DEBUG render stage collision
    for(mbl::Surface surface : stage_collision->surfaces){

        mbl::Color sc = mbl::SurfaceColors[surface.surface_type];
        SDL_SetRenderDrawColor( ctx, sc.r, sc.g, sc.b, 0xff );
        SDL_RenderDrawLine( ctx, 
            worldToCameraX(stage_collision->vertices[surface.v1].x),
            worldToCameraY(stage_collision->vertices[surface.v1].y),
            worldToCameraX(stage_collision->vertices[surface.v2].x),
            worldToCameraY(stage_collision->vertices[surface.v2].y)
        );
    }

    //DEBUG render entity collision
    mbl::Color cc = mbl::light_blue;
    SDL_SetRenderDrawColor( ctx, cc.r, cc.g, cc.b, 0xff );

    for(const mbl::Entity *entity : entities ){
        //entity->getRenderInfo();//DEBUG_renderCollision( ctx );
        entity->DEBUG_draw(ctx, &camera_position, scale, mbl::GameState::SDL_DrawLineFromWorldCoord);
            
    }
};

/*******************************************************
* Entity                                               *
*******************************************************/
void mbl::Entity::DEBUG_draw(SDL_Renderer* ctx, glm::vec2* camera_pos, float scale, void drawLine( SDL_Renderer*, glm::vec2*, float, float, float, float, float))
const{
    drawLine(ctx, camera_pos, scale, 1.0f,1.0f,0.0f,0.0f);
};

/*******************************************************
* Player                                               *
*******************************************************/
mbl::Player::Player( CharacterAttribute *_attributes /* pointer to inputter */){
    
    attributes = _attributes;
    //all Entities have these aspects
    world_pos = glm::vec2(0.0f, 1.0f); // TEMP INIT POSITION
    bounding_box_tl	= glm::vec2(0.0f, 0.0f);
	bounding_box_br = glm::vec2(0.0f, 0.0f);
    
    overlay = {0xff,0xff,0xff,0x00};


    ecb_bottom = 0.0f;
	ecb_top = 1.5f;
	ecb_mid = 0.75f;
	ecb_left = 0.5f;	  
	ecb_right = 0.5f;


    visible = true;
	in_camera_view = true;
	use_entity_colission = true; 
	use_stage_colission = true;


};
void mbl::Player::rollBackState(/* some pointer to a state*/){

};
/*
void mbl::Player::DEBUG_renderCollision(SDL_Renderer * ctx){
    //LOG("Entity position: (") LOG(position.x) LOG(", ") LOG(position.y) LOG(")\n")

    // draw base position crosshair
    float crosshair_size = 0.1f; //half of the crosshair size in world space units
    mbl::Color cc = mbl::light_blue;
    
    SDL_SetRenderDrawColor( ctx, cc.r, cc.g, cc.b, 0xff );
    SDL_RenderDrawLine( ctx,
        worldToCameraX(position.x - crosshair_size),
        worldToCameraX(position.y),
        worldToCameraY(position.x + crosshair_size),
        worldToCameraY(position.y)
    );
    SDL_RenderDrawLine( ctx,
        worldToCameraX(position.x),
        worldToCameraX(position.y - crosshair_size),
        worldToCameraY(position.x),
        worldToCameraY(position.y + crosshair_size)
    );
    
}
*/
void mbl::Player::computeNextState(){

};