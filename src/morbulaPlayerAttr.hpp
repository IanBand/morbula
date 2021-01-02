#ifndef PLAYER_ATTR_HPP
#define PLAYER_ATTR_HPP

namespace mbl {
struct PlayerAttribute
{
	// character attributes

	// loosely based on ssbm character attributes
    // https://docs.google.com/spreadsheets/d/1WqxJWDXbPDDYhjV5Vo34qTiCxmHSqg_Wr6GKKyLrH2M/
	// https://docs.google.com/spreadsheets/d/1lgDegOcTFSSW6jgQK3LxAfhFqWQRhO3g7TbsuseVJS8/edit#gid=424158709

	char name[20];

	

	float gravity;
	float rigidity; //landing/impact squash multiplier, wavedash squash/contortion
	float mass;
	int init_health;

	float init_walk_velocity;
	float walk_acceleration;
	float walk_max_velocity;

	float slow_walk_max_velocity;
	float mid_walk_max_velocity;
	float fast_walk_min_velocity;

	float init_dash_velocity;
	float run_acceleration;
	float run_max_velocity;

	float ground_friction;
	int ground_jump_squat_frames;
	float base_vertical_jump_velocity;
	float base_back_horizontal_jump_velocity;  //horizontal jump velocity out of a forward direction jump
	float base_front_horizontal_jump_velocity; //horizontal jump velocity out of a backward direction jump
	float ground_to_air_speed_multiplier;

	// when in the air, players can choose to be spinning or neutral. 
	// These two states change the characters aerial drift attributes.
	float slow_fall_velocity_max;
	float fast_fall_velocity_max;
	float horizontal_air_velocity_max;
	float neutral_air_friction;
	float spinning_air_friction;

	float air_dash_velocity; //velocity given to player when they air dash
	float air_dash_speed_multiplier; //multiply current air speed by this when they air dash?


	int wall_jump_squat_frames;
	float wall_slide_traction;
	float wall_slide_max_velocity;
	float wall_jump_horizontal_velocity;
	float wall_lump_vertical_velocity;
	float wall_jump_airborn_drag;



	
	int shinespark_hold_frames;
	float shinespark_min_recover_angle;
	float shinespark_init_speed; //adds to current forward speed. If character has backwards speed, their speed is replaced with this value
	float shinespark_friction; 

	//ect...

	//beam attributes 
	float base_beam_range;

	// "returning energy" attributes
	float energy_tracking_multiplier;
	float energy_init_velocity;
	float energy_acceleration; //might be the same as energy tracking multiplier
	float energy_init_angle_variance;
	//scattering coefficent
	///...other stuff I cant even think of rn
	//beam particle shape???

	//float fire_beam_offence;
	//float fire_beam_defence;
	//float water_beam_offence;
	//float water_beam_defence;
	//float electric_beam_offence;
	//float electric_beam_defence;

	//might be a different data structure? basically these will deterrmine the short charge frames when charging a shine spark.
	//int booster_charge_frame_1;
	//int booster_charge_frame_2;
	//int booster_charge_frame_3;
	//int booster_charge_frame_4;
	//int booster_charge_frame_5;

	//you would in theory put stats for all common animations and mechanics here.
};

inline PlayerAttribute test_char_attr1 {
	"test_char_1",
	0.002f, //gravity
	1.0f, // rigidity; //landing/impact squash multiplier, wavedash squash/contortion
	1.0f, // mass;
	100 , // init_health;

	1.0f, // init_walk_velocity;
	1.0f, // walk_acceleration;
	1.0f, // walk_max_velocity;

	1.0f, // slow_walk_max_velocity;
	1.0f, // mid_walk_max_velocity;
	1.0f, // fast_walk_min_velocity;

	1.0f, // init_dash_velocity;
	1.0f, // run_acceleration;
	1.0f, // run_max_velocity;

	1.0f, // ground_friction;
	3, // ground_jump_squat_frames;
	1.0f, // base_vertical_jump_velocity;
	1.0f, // base_back_horizontal_jump_velocity;  //horizontal jump velocity out of a forward direction jump
	1.0f, // base_front_horizontal_jump_velocity; //horizontal jump velocity out of a backward direction jump
	1.0f, // ground_to_air_speed_multiplier;

	// when in the air, players can choose to be spinning or neutral. 
	// These two states change the characters aerial drift attributes.
	-0.06f, // slow_fall_velocity_max;
	1.0f, // fast_fall_velocity_max;
	1.0f, // horizontal_air_velocity_max;
	1.0f, // neutral_air_friction;
	1.0f, // spinning_air_friction;
};
inline PlayerAttribute test_char_attr2 {
	"test_char_2",
	0.0026f, //gravity
	1.0f, // rigidity;
	1.0f, // mass;
	100 , // init_health;

	1.0f, // init_walk_velocity;
	1.0f, // walk_acceleration;
	1.0f, // walk_max_velocity;

	1.0f, // slow_walk_max_velocity;
	1.0f, // mid_walk_max_velocity;
	1.0f, // fast_walk_min_velocity;

	1.0f, // init_dash_velocity;
	1.0f, // run_acceleration;
	1.0f, // run_max_velocity;

	1.0f, // ground_friction;
	3, // ground_jump_squat_frames;
	1.0f, // base_vertical_jump_velocity;
	1.0f, // base_back_horizontal_jump_velocity;  //horizontal jump velocity out of a forward direction jump
	1.0f, // base_front_horizontal_jump_velocity; //horizontal jump velocity out of a backward direction jump
	1.0f, // ground_to_air_speed_multiplier;

	// when in the air, players can choose to be spinning or neutral. 
	// These two states change the characters aerial drift attributes.
	-0.05f, // slow_fall_velocity_max;
	1.0f, // fast_fall_velocity_max;
	1.0f, // horizontal_air_velocity_max;
	1.0f, // neutral_air_friction;
	1.0f, // spinning_air_friction;
};
}
#endif