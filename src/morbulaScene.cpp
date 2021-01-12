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

    mbl::Player *test_p1 = new mbl::Player( 
        &mbl::test_char_attr1,
        &mbl::entity_init1,
        &mbl::test_entity_attr1
    );

    /*
    mbl::Player *test_p2 = new mbl::Player( 
        &mbl::test_char_attr2,
        &mbl::entity_init2,
        &mbl::test_entity_attr2
    );
    */

    entities.push_back(test_p1);
    camera_entity_list.push_back(test_p1);//test_p1 is now tracked by the camera
    /*
    entities.push_back(test_p2);
    camera_entity_list.push_back(test_p2);//test_p1 is now tracked by the camera
    */
    stage = &mbl::test_stage; //prog crashes without this

    camera_position = glm::vec2(0.0f,0.2f); //init camera position will be defined in scene data structure
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

    /*
    shitty camera zoom demo
    float base_scale = 0.1f;
    scale = base_scale + std::sin(scene_frame_number * 0.025) * 0.01; 
    */

    for(mbl::Entity *entity : entities ){


        // entity->computeNextStatePhase1(stage);
        // test stage collision
        // entity->computeNextStatePhase2(stage);

        if(entity->surface_id == -1){ // if entity is airborn, i.e. not bound to a surface
            
            //TODO: need a broad surface collide test
            for(int i = 0; i < stage->surfaces.size(); ++i){
                //narrow entity surface collision test
                mbl::Surface surface = stage->surfaces.at(i);
                mbl::Line ecb_transit;
                float floor_position, wall_position_left, wall_position_right, ceiling_position;
                



                switch(surface.surface_type){
                    case mbl::SurfaceType::ground:
                        //test if entity ecb collides with ground
                        ecb_transit = entity->bottomWorldTravelLine();
                        floor_position = surfaceCollidePoint(
                            ecb_transit.p1.x,
                            ecb_transit.p1.y,
                            ecb_transit.p2.x,
                            ecb_transit.p2.y,
                            stage->vertices[surface.v1].x,
                            stage->vertices[surface.v1].y,
                            stage->vertices[surface.v2].x,
                            stage->vertices[surface.v2].y
                        );
                        //test entity ecb left wall collision
                        //test entity ecb right wall collision
                        //test entity ecb ceiling collision

                        //LOG("floor position: ") LOG(floor_position) LOG("\n");

                        //will need 16 cases in theory, 
                        //cases range from no collisions to all collisions
                        //priority of cases will be very important
                        //LOG("floor position of ent: ")LOG(floor_position)LOG("\n")
                        if(floor_position >= 0){ 
                            entity->surface_id = i;
                            entity->surface_position = floor_position;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        entity->computeNextState(stage);
    }


    calcCameraPosition();


};
void mbl::Scene::calcCameraPosition(){
    //loop through entities in camera_entity_list
    //keep track of min and max x and y coordinates of the bounding boxes of the entities to create a "camera bounding box." respect camera bounds during this
    //add margins to the master box
    //compute scale from the box

    mbl::BoundingBox camera_box = camera_entity_list.at(0)->boundingBox();

    for( mbl::Entity *entity : camera_entity_list ){

        mbl::BoundingBox entity_box = entity->boundingBox();

        // adjust camera box to include entity box
        // todo: turn this into overloaded + operator for bounding box class
        if(camera_box.p1.x > entity_box.p1.x)
            camera_box.p1.x = entity_box.p1.x;

        if(camera_box.p1.y > entity_box.p1.y)
            camera_box.p1.y = entity_box.p1.y;

        if(camera_box.p2.x < entity_box.p2.x)
            camera_box.p2.x = entity_box.p2.x;
        
        if(camera_box.p2.y < entity_box.p2.y)
            camera_box.p2.y = entity_box.p2.y;
    }

    // add camera margins
    glm::vec2 camera_margin = glm::vec2(2.0f,2.0f);
    camera_box.p1 -= camera_margin;
    camera_box.p2 += camera_margin;

    /*
    calculate camera position from camera bounding box:
    find mid point of camera box
    camera position smoothing is done by taking a weighted running average of current pos and prev pos
    
    no average:
        camera_position.x = (camera_box.p1.x + camera_box.p2.x) * 0.5f;
        camera_position.y = (camera_box.p1.y + camera_box.p2.y) * 0.5f;
    */
    camera_position.x = (camera_box.p1.x + camera_box.p2.x) * 0.25 + camera_position.x * 0.5f;
    camera_position.y = (camera_box.p1.y + camera_box.p2.y) * 0.25 + camera_position.y * 0.5f;

    /*
    calculate scale from camera bounding box:
    scale has units (screen height / screen width) / (1.0f)
    */

    //get camera dimensions
    glm::vec2 cd = glm::vec2(
        camera_box.p2.x - camera_box.p1.x,
        camera_box.p2.y - camera_box.p1.y
    );

    // (SCREEN_ASPEC_R / (cd.x > cd.y ? cd.x : cd.y))
    //camera zoom smoothing, weighted average of current zoom and prev zoom
    scale =  0.5f * (SCREEN_ASPEC_R / (cd.x > cd.y ? cd.x : cd.y)) + 0.5f * scale;
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
/*
        the line (x3,y3) -> (x4,y4) is the surface
        the line (x1,y1) -> (x2,y2) is the interpolation between prev and projected ECB points.
        u is returned so that it can be used as the entity position on the surface. 0.0f <= u <= 1.0f
        if the lines do not intersect, -1.0f will be returned instead
*/
float mbl::Scene::surfaceCollidePoint(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    //en.wikipedia.org/wiki/Line–line_intersection bless wikipedia

    float denominator, u_numerator, t_numerator;
    denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    /*
    "The intersection point falls within the first line segment if 0.0 ≤ t ≤ 1.0, and it falls within the second line segment if 0.0 ≤ u ≤ 1.0. 
     These inequalities can be tested without need for division." 
    */

    t_numerator =           (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)  ;
    u_numerator = -1.0f * ( (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3) );

    if( 
        0.0f <= t_numerator        &&
        t_numerator <= denominator &&
        0.0f <= u_numerator        &&
        u_numerator <= denominator
    ){
        //lines intersect, only perform division now
        return u_numerator / denominator;
    }
    return -1.0f;
};
