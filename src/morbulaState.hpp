#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
#include "sdlUtil.hpp"
#include "morbulaCharAttr.hpp"
#include <vector>
#include "../lib/glm/vec2.hpp"

//todo: define scene struct

;namespace mbl{

inline uint16_t rng(uint32_t seed = 0){
	static uint32_t reg; //just seed with garbage uninitialized data by default lol
	if(seed) reg = seed;

	reg = reg * 22695477 + 1;
	return reg >> 16; //upper 16 bits
}

/**
 * Stage Data Structures
 * 
 */
enum SurfaceType : int
{
    left_wall,
    right_wall,
    ground,
    ceiling,
    platform_ground, // ?
    none,
    warp,
    //just add flags for ice, grass (earth?) terrain types, dont make them entirely new enums
};

struct Surface
{
    int vertex1;
    int vertex2;
    SurfaceType surface_type;

    //add other surface attribute flags here 
    // bool left_ledge;
    // bool right_ledge;
    // bool no_tech;
    // bool no_wall_jump;
    // bool platform; //means you can drop through
    // bool crumble; //would also need crumble timer and shit
    // function pointer to an event
    // int warp id
};

struct StageCollision{ //struct only details collision for now
    //a point forms a surface with itself and the next point in the points array
    //the Nth surface is defined by the Nth and (N+1)th points in the points array, and the Nth element in the surfaces array

	std::vector<glm::vec2> *vertices = NULL; 
    std::vector<Surface> *surfaces = NULL;
    float height;
    float width;
    int id; //change to stage list enum?
};
inline std::vector<glm::vec2> test_vetrices {
        {0.0f,0.0f},
        {0.0f,1.0f},
        {1.0f,1.0f},
        {1.0f,0.0f}
};
inline std::vector<Surface> test_surfaces {    
		{0,1,left_wall},
        {1,2,ground},
        {2,3,right_wall},
        {3,0,ceiling}
};
inline StageCollision test_stage_collision {
	&test_vetrices,
	&test_surfaces,
    100.0f,
    100.0f,
    0
};

/*
player data structrue
*/
enum PlayerActionState : int
{
	//https://smashboards.com/threads/list-of-all-possible-character-states-ie-downdamage-downwait.400270/#post-19055623
	idle,
	walk_1,
	run
};

enum Direction : int
{
	left,
	right,
	//up, down ? 
};

struct EquipmentState
{
	//what equipment the player currently has
	bool speed_booster;
	bool high_jump;

	//beam type
	bool cascade_beam; //absorption energy particals damage other enenimies when they pass over them, and generate more particles
};

struct PlayerState
{

	//color overlay
	//overlay opacity

	glm::vec2 prev_positions[5]; //keep track of previous positions for trailing effects & colission. dont shift array, just shift current index and have the prev frame indices increase mod 5
	glm::vec2 velocity;

	
	
	int health;

	Direction direction; //left or right
	bool grounded; //might just derive this from action state idk
	bool used_dashed; //has player used air dash?
	bool fast_falled; //has player used fast fall?


	EquipmentState equipment_state;
	PlayerActionState action_state; 
	PlayerActionState prev_action_state; 
	int action_state_frame_count; //how many frames has the player been in the current action state
	

};

struct EnergyState
{
    glm::vec2 position;
    glm::vec2 velocity;
    int value;
    //type
    //owner
    
};

/*
generic model/entity structures
*/
struct ModelData
{
	//2d model data will just be a list of animations
	//animarions are just a list of images
	//not quite but kinda
};
struct EntityRenderInfo
{
	//olc::vu2d *world_position;      // faster to copy one pointer than to copy 2 floats?
	int action_state_frame_count; 	// animation frame number
	int action_state;  				// animation id, cast from enum
	// olc::rgbacolor *overlay;		// pointer to overlay color 

	ModelData *model_data = NULL;

	// renderer will be able to render the model data based on position, action state, and frame count
};

class Entity // abstract class 
{
	//entities need some way of advancing the global rng
public:
	virtual void computeNextState();
	virtual void rollBackState(/* some pointer to a state*/);
	virtual EntityRenderInfo getRenderInfo(); 
	
	//virtual ModelData *loadModel(); //might not go here
private:
	//color overlay
	bool use_entity_colission;
	bool use_stage_colission;
	bool visible;


	//implementations of this class will define their own entity states
};

/*
Game State
*/
class GameState
{
public:
	GameState(StageCollision *stage_collision /*other scene stuff*/);
	void advanceGameState();
	void rollBackGameState(/*some state pointer*/);
	void loadScene(StageCollision *stage_collision /*other scene stuff*/);
	void renderStateToSDL( SDL_Renderer* ctx /*pointer to render settings*/ );

private:

	//this memory makes up the scene
	std::vector<Entity> *entities = NULL;
	StageCollision stage; //may change, might need to store stage id?


	//camera stuff
	glm::vec2 camera_position;
	float scale; // pixel per float unit (1px / 1.0f); zoom factor;



	//prob wont have these
	//PlayerState players[1]; //up to 4 players. maybe should be pointer cus of ggpo?
    //EnergyState energys[16]; //up to 4 energies active per player?
	//Item items[10]
	//Enemy enimies[10]

	//there should be an entity base class...?
	//Just start with one player!!
};
}

#endif