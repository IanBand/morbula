#ifndef ENTITY_ATTR_HPP
#define ENTITY_ATTR_HPP
#include <glm/vec2.hpp>

namespace mbl{
/*******************************************************
* Temp Stuff                                           *
*******************************************************/
struct ModelData
{
	//2d model data will just be a list of animations
	//animarions are just a list of images
	//not quite but kinda
};

/*******************************************************
* Entity Attributes                                    *
*******************************************************/
//these values are meant to be unique to an entity or class of entities
struct EntityAttribute{
    glm::vec2 init_bounding_box_size;
    float base_ecb_height;
    float base_ecb_width;

	mbl::ModelData *model_data = NULL;

	//classification info? for now Ill use these but I may keep lists of pointers to entities to keep track of which use what collisions
	//if these are changed to lists, the Entity constructor(?) will add its pointer to the lists upon creation, and remove it upon deletion
	bool in_camera_view;
	bool use_entity_colission; 
	bool use_stage_colission;
};
inline EntityAttribute test_entity_attr1 = {
	{0.75f,0.75f},
	0.5f,
	0.5f,
	NULL,
	true,
	true,
	true
};
inline EntityAttribute test_entity_attr2 = {
	{0.75f,0.75f},
	0.6f,
	0.4f,
	NULL,
	true,
	true,
	true
};
}
#endif