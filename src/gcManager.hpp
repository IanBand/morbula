#ifndef GCM_HPP
#define GCM_HPP
#include <glm/vec2.hpp>

namespace gcm{

enum GCPort : int {P1,P2,P3,P4};

// struct that is passed to game
struct VirtualInputBank{
    
    float left_analog;
    float right_analog;
    glm::vec2 primary_stick;
    glm::vec2 secondary_stick;
    
    bool jump;
    bool attack1;
    bool attack2;
    bool aim_modifier;
    bool shield;
    bool grab;
    bool cancel;

    bool plugged_in;
};
/***********************************
Possible inputs used by the game
***********************************/
enum GameInput: int {
    jump,
    attack1,
    attack2,
    aim_modifier,
    shield,
    grab,
    cancel
};
/***************************************
maps phisical button data to game inputs
***************************************/
struct InputMap{

    float init_left_analog;
    float init_right_analog;
    glm::vec2 init_primary_stick;
    glm::vec2 init_secondary_stick;

    //need to look at how button data is read by gca
};

class GCManager { //may extend input manager base class at some point in the future ...idk

public:
    GCManager();
    void pollInputs();
    void setInputMap(InputMap*, GCPort);
    VirtualInputBank* getInputBank(GCPort);

private:
    InputMap maps[4];
    VirtualInputBank banks[4];

};




}
#endif