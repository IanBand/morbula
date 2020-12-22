#include "morbula.hpp"
#include "debugLogger.hpp"


/*******************************************************
* Game State                                           *
*******************************************************/
mbl::Scene::Scene(){

    
	//https://www.xspdf.com/resolution/53778619.html
	//https://softwareengineering.stackexchange.com/questions/247245/a-vector-of-pointers-to-different-derived-classes-of-the-same-base-class
	//https://stackoverflow.com/questions/34383979/c-vector-of-base-class-objects/34384868
	// seems like we use a vector of base class smart pointers

    //init test data
    // Scene owns all entity pointers
    entities.push_back(new mbl::Player( 
        &mbl::test_char_attr, /*pointer to inputter*/
        glm::vec2(0.5f,1.0f),
        glm::vec2(0.75f,0.75f),
        0.5f,
        0.7f,
        -1
    ));

    stage = &mbl::test_stage; //crashes without this, need to put stage in another data structure

    camera_position = glm::vec2(0.0f,0.2f); //world space coordinate that the camear is pointing at, set to scene init camera?
    scene_frame_number = 0;
    rngr = 0; //seed the rng;


    //loadScene();
};
mbl::Scene::~Scene(){
    for(mbl::Entity *entity : entities ){
        delete entity;
    }
}
void mbl::Scene::rollBackState(/*some state pointer? */){

};
void mbl::Scene::loadScene(){
    // dont reload assets if current scene already has assets that are used in next scene
    // this is a premature optimization, dont implement it now


    //entities = _entities;
    //stage_collision = _stage_collision;

};
uint16_t mbl::Scene::rng(){
	rngr = rngr * 22695477 + 1;
	return rngr >> 16; //upper 16 bits
};
int mbl::Scene::worldToCameraX(float x){
    return (int) ((x - camera_position.x) * SCREEN_WIDTH * scale + (SCREEN_WIDTH >> 1));
};
int mbl::Scene::worldToCameraY(float y){
    return (int) ((y - camera_position.y) * SCREEN_HEIGHT * -1 * SCREEN_ASPECT * scale + (SCREEN_HEIGHT >> 1));
};
void mbl::Scene::SDL_DrawLineFromWorldCoord( SDL_Renderer* ctx, glm::vec2* camera_position, float scale, float x1, float y1, float x2, float y2)
{
    //convert world space to camera space, draw line
    SDL_RenderDrawLine( ctx,
        (int) ((x1 - camera_position->x) * SCREEN_WIDTH * scale + (SCREEN_WIDTH >> 1)),
        (int) ((y1 - camera_position->y) * SCREEN_HEIGHT * -1 * SCREEN_ASPECT * scale + (SCREEN_HEIGHT >> 1)),
        (int) ((x2 - camera_position->x) * SCREEN_WIDTH * scale + (SCREEN_WIDTH >> 1)),
        (int) ((y2 - camera_position->y) * SCREEN_HEIGHT * -1 * SCREEN_ASPECT * scale + (SCREEN_HEIGHT >> 1))
    );
};
void mbl::Scene::advanceGameState(){
    ++scene_frame_number;

    //temp camera zoom demo
    float base_scale = 0.1f;
    scale = base_scale + std::sin(scene_frame_number * 0.025) * 0.01; 

    //calc next state of each entity... at this point Im convinced I have to split this up into the different arrays for different child classes of entity
    //so that their unique computeNextState() functions can be called
    for(mbl::Entity *entity : entities ){
        entity->computeNextState();
    }


};
void mbl::Scene::calcCameraPosition(){
    //loop through entities in camera_entity_list
    //keep track of min and max x and y coordinates of the bounding boxes of the entities to create a "camera bounding box." respect camera bounds during this
    //add margins to the master box
    //compute scale from the box
};
void mbl::Scene::renderStateToSDL( SDL_Renderer* ctx /*pointer to render settings*/ ){
    //DEBUG render stage collision
    for(mbl::Surface surface : stage->surfaces){
        //the direction of a surface is important.
        //each surface can be thought of as an arrow starting from v1
        //in the direction of v2

        mbl::Color sc = mbl::SurfaceColors[surface.surface_type];
        SDL_SetRenderDrawColor( ctx, sc.r, sc.g, sc.b, 0xff );
        SDL_RenderDrawLine( ctx, 
            worldToCameraX(stage->vertices[surface.v1].x),
            worldToCameraY(stage->vertices[surface.v1].y),
            worldToCameraX(stage->vertices[surface.v2].x),
            worldToCameraY(stage->vertices[surface.v2].y)
        );

        /*
        float surface_theta = 
        std::acos(
            glm::dot(
                glm::vec2(1.0f,0.0f), 
                stage_collision->vertices[surface.v2] - stage_collision->vertices[surface.v1]
            )
            /
            glm::length(stage_collision->vertices[surface.v2] - stage_collision->vertices[surface.v1])
        ); 
        LOG(surface_theta) LOG("\n")
        */

    }
    //LOG("\n=-=-=-=-=-=-=-=-=\n");

    //DEBUG render entity collision
    mbl::Color ecbColor = mbl::orange_gold;
    mbl::Color BBColor  = mbl::light_blue;
    mbl::Color cxhColor = mbl::red;
    

    for(mbl::Entity *entity : entities ){
        SDL_SetRenderDrawColor( ctx, ecbColor.r, ecbColor.g, ecbColor.b, 0xff );
        entity->DEBUG_ecbDraw         (ctx, &camera_position, scale, mbl::Scene::SDL_DrawLineFromWorldCoord);

        SDL_SetRenderDrawColor( ctx, BBColor.r,  BBColor.g,  BBColor.b,  0xff );
        entity->DEBUG_BBDraw          (ctx, &camera_position, scale, mbl::Scene::SDL_DrawLineFromWorldCoord);
        
        SDL_SetRenderDrawColor( ctx, cxhColor.r, cxhColor.g, cxhColor.b, 0xff );
        entity->DEBUG_posCrossHairDraw(ctx, &camera_position, scale, mbl::Scene::SDL_DrawLineFromWorldCoord);
    }
};

