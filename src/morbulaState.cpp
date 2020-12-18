#include "morbulaState.hpp"
#include "debugLogger.hpp"

mbl::GameState::GameState(StageCollision *_stage_collision , std::vector<mbl::Entity> *_entities){
    loadScene( _stage_collision, _entities );
};
void mbl::GameState::rollBackGameState(/*some state pointer? */){

};
void mbl::GameState::loadScene(StageCollision *_stage_collision, std::vector<mbl::Entity> *_entities){
    // dont reload assets if current scene already has assets that are used in next scene
    // this is a premature optimization, dont implement it now

    entities = _entities;
    stage_collision = _stage_collision;
    camera_position = glm::vec2(0.0f,0.0f); //world space coordinate that the camear is pointing at, set to scene init camera?
    scale = 0.25;
    scene_frame_number = 0;
    rngr = 0; //seed the rng;
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
void mbl::GameState::advanceGameState(){
    ++scene_frame_number;
    scale = 0.25;
    //scale = std::sin(scene_frame_number * 0.025) * 0.125 + 0.25; 
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
        SDL_SetRenderDrawColor( gRenderer, sc.r, sc.g, sc.b, 0xff );
        SDL_RenderDrawLine( ctx, 
            worldToCameraX(stage_collision->vertices[surface.v1].x),
            worldToCameraY(stage_collision->vertices[surface.v1].y),
            worldToCameraX(stage_collision->vertices[surface.v2].x),
            worldToCameraY(stage_collision->vertices[surface.v2].y)
        );
    }

    //DEBUG render entity collision
    for(mbl::Entity entity : *entities ){
        entity.DEBUG_renderCollision( ctx );
    }
};





mbl::Player::Player( CharacterAttribute *_attributes /* pointer to inputter */){
    
    attributes = _attributes;

    position = glm::vec2(0.0f, 1.0f); // TEMP INIT POSITION

    //all players have these aspects
    camera_box_height = 1.0f;
	camera_box_width = 1.0f;
    visible = true;
    //if these are changed to lists, the player constructor will add its pointer to the lists upon creation, and remove it upon deletion
	in_camera_view = true;
	use_entity_colission = true; 
	use_stage_colission = true;
};
void mbl::Player::rollBackState(/* some pointer to a state*/){

};

void mbl::Player::DEBUG_renderCollision(SDL_Renderer * ctx){
    LOG("Entity position: (") LOG(position.x) LOG(", ") LOG(position.y) LOG(")\n")
}
void mbl::Player::computeNextState(){

};

mbl::EntityRenderInfo mbl::Player::getRenderInfo(){
    mbl::EntityRenderInfo info;
    
    return info;
};