#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
#include "sdlUtil.hpp" //only needed for SDL_Renderer
#include "morbulaCharAttr.hpp"
#include <vector>
#include <glm/vec2.hpp>

//todo: define scene struct

;namespace mbl{
/*******************************************************
* Colors                                               *
*******************************************************/
struct Color{char r, g, b, a;};
inline const Color white        {0xff,0xff,0xff,0xff};
inline const Color grey         {0x88,0x88,0x88,0xff};
inline const Color orange_gold	{0xfc,0x8c,0x00,0xff};
inline const Color lime			{0x47,0xde,0x45,0xff};
inline const Color purple       {0x4e,0x1e,0x9c,0xff};
inline const Color red	        {0xbf,0x18,0x0f,0xff};
inline const Color light_blue   {0x20,0x9c,0xe8,0xff};
inline const Color deep_blue    {0x0e,0x0e,0xdb,0xff};
inline const Color aqua         {0x20,0xbd,0xb2,0xff};

/*******************************************************
* Stage Data Structures	                               *
*******************************************************/
enum SurfaceType : int
{
    left_wall, //blue
    right_wall, //green
    ground, //grey
    ceiling, //red
    none,
    warp, // ehh there should probably just be warp boxes
    //just add flags for ice, grass (earth?) terrain types, dont make them entirely new enums
};
inline const Color SurfaceColors[] = {
	{0x20,0x40,0xff,0xff},
	{0x40,0xff,0x20,0xff},
	{0x77,0x77,0x77,0xff},
	{0xff,0x20,0x40,0xff}
};
struct Surface
{
    int v1;
    int v2;
    SurfaceType surface_type;

    //add other surface attribute flags here 
    // bool left_ledge;
    // bool right_ledge;
    // bool no_tech;
    // bool no_jump;
	// no_tech and no_jump also apply to walls
    // bool platform; //means you can drop through
	// int crumble_timer; // 0 means no ccrumble
    // function pointer to an event
    // warp id
};

struct StageCollision{ //struct only details collision for now. this should be a whole ass stage struct.
	//include camera bounds, liquid areas + positions
    //a point forms a surface with itself and the next point in the points array
    //the Nth surface is defined by the Nth and (N+1)th points in the points array, and the Nth element in the surfaces array

	std::vector<glm::vec2> vertices; 
    std::vector<Surface> surfaces;
    float height;
    float width;
    int id; //change to stage list enum?
};

inline StageCollision test_stage_collision {
	{
        {-1.0f,-1.0f},
        {1.0f,-1.0f},
        {1.0f,1.0f},
        {-1.0f,1.0f},
	},
	{    
		{0,1,ceiling},
        {1,2,right_wall},
        {2,3,ground},
        {3,0,left_wall}
	},
    100.0f,
    100.0f,
    0
};

/*******************************************************
* Generic Model & Entity Data Structures	           *
*******************************************************/
struct ModelData
{
	//2d model data will just be a list of animations
	//animarions are just a list of images
	//not quite but kinda
};

struct EntityRenderInfo
{
	glm::vec2 *world_position = NULL;      // faster to copy one pointer than to copy 2 floats?
	int action_state_frame_count; 	// animation frame number
	int action_state;  				// animation id, cast from enum
	Color *overlay = NULL;		// pointer to overlay color 
	ModelData *model_data = NULL;

	// renderer will be able to render the model data based on position, action state, and frame count
};

class Entity // abstract class for entitys in a Morbula scene
{
	//entities need some way of advancing the global rng
public:
	virtual void computeNextState(){};
	virtual void rollBackState(/* some pointer to a state*/){};
	virtual EntityRenderInfo getRenderInfo(){}; 
	
	//virtual ModelData *loadModel(); //might not go here
private:
	Color overlay;
	bool use_entity_colission;
	bool use_stage_colission;
	bool visible;
	//implementations of this class will define their own entity states
};


/*******************************************************
* Player Data Structures	                           *
*******************************************************/
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

//struct PlayerState{}; might keep this around for barebones player state for ggpo



struct EnergyState
{
    glm::vec2 position;
    glm::vec2 velocity;
    int energy_value;
    //type
    //owner
    
};
class Player: public Entity
{
public:
	Player(CharacterAttribute* /* pointer to inputter */);
	void computeNextState();
	void rollBackState(/* some pointer to a state*/);
	EntityRenderInfo getRenderInfo(); 

	// ! REMOVE SELF FROM camera_entity_list UPON DISTRUCTION !
private:
	glm::vec2 prev_positions[5]; //keep track of previous positions for trailing effects & colission. dont shift array, just shift current index and have the prev frame indices increase mod 5
	glm::vec2 velocity;

	int cur_health;
	Direction direction; //left or right
	bool grounded; //might just derive this from action state idk
	bool used_dashed = false; //has player used air dash?
	bool fast_falled = false; //has player used fast fall?


	CharacterAttribute *attributes; //do not mutate
	EquipmentState equipment_state;
	PlayerActionState action_state; 
	PlayerActionState prev_action_state; 
	int action_state_frame_count = 0; //how many frames has the player been in the current action state
	

};
/*******************************************************
* Scene Structures                                     *
*******************************************************/
class GameState
{
public:
	GameState(StageCollision * /*other scene stuff*/);
	void advanceGameState();
	void rollBackGameState(/*some state pointer*/);
	void loadScene(StageCollision * /*other scene stuff*/);
	void renderStateToSDL(SDL_Renderer * /*pointer to render settings*/);

	

private:

	//this memory makes up the scene
	std::vector<Entity> entities; //should there be a collidable entities list? or just skil entities that aren't collidable
	StageCollision *stage_collision; //may change, might need to store stage id?
	unsigned int scene_frame_number;
	uint32_t rngr; //register for rng, never directly read this
	uint16_t rng(); //call this function when you want a random number for the game state


	//camera stuff
	//make camera its own class?
	void calcCameraPosition(); // calculate the camera world position and scale based on entities with camera flags
	glm::vec2 camera_position;
	float scale; // pixel per float unit (1px / 1.0f); zoom factor;
	float scale_max;
	float scale_min;
	std::vector<Entity*> camera_entity_list; //list of entity pointers that the camera must include
	int worldToCameraX(float x);
	int worldToCameraY(float y);
	



	//prob wont have these
	//PlayerState players[1]; //up to 4 players. maybe should be pointer cus of ggpo?
    //EnergyState energys[16]; //up to 4 energies active per player?
	//Item items[10]
	//Enemy enimies[10]

};
}

#endif