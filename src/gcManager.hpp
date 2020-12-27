#ifndef GCM_HPP
#define GCM_HPP
#include<iostream>
#include "../lib/gca-plus/GCAdapter.h"


namespace gcm{

enum Port : int {P1,P2,P3,P4};

// struct that is passed to game
struct VirtualInputs{
    
    double left_analog;
    double right_analog;
    // double trigger_analog; should game read one trigger analog or two?
    double primary_stick_x;
    double primary_stick_y;
    double secondary_stick_x;
    double secondary_stick_y;
    
    
    bool jump, attack1, attack2;
    bool aim_modifier, shield;
    bool grab, cancel, connected;
};
/***********************************
Possible inputs used by the game
***********************************/
enum GameInput: int {
    unused,
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
    //information needeed to map ControllerStatus to VirtualInputs
    GameInput buttonA, buttonB, buttonX, buttonY;
	GameInput padLeft, padRight, padUp, padDown;
	GameInput buttonL, buttonR, buttonZ;
    GameInput analogL, analogR;
    
};
inline InputMap test_input_map = {
    attack1, // A
    attack2, // B
    jump,    // X
    jump,    // Y
    unused,  // Dpad left
    unused,  // Dpad right
    unused,  // Dpad up
    unused,  // Dpad down
    shield,  // L digital
    shield,  // R digital
    grab,    // Z
    unused   // start
};

class GCManager { //may extend input manager base class at some point in the future ...idk

public:
    GCManager();
    void pollInputs();
    void setInputMap(InputMap*, Port);
    VirtualInputs* getInputs(Port);

private:
};
}
#endif