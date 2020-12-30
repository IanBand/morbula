#ifndef INPUTTER_HPP
#define INPUTTER_HPP
#include<iostream>
#include "../lib/gca-plus/GCAdapter.h"


namespace input{

enum GCPort : int {P1,P2,P3,P4};

/***********************************
Possible inputs used by the game
***********************************/
enum GameInput: int {
    connected, //unused
    jump,
    attack1,
    attack2,
    aim_modifier,
    shield,
    grab,
    cancel
};
/***************************************
An Inputter maps some typep of user input to
***************************************/
class Inputter {
    public:
        virtual void getInputs(int frame) = 0;

        bool connected, jump, attack1, 
        attack2, aim_modifier, 
        shield, grab, cancel;

        float left_analog;
        float right_analog;
        float primary_stick_x;
        float primary_stick_y;
        float secondary_stick_x;
        float secondary_stick_y;


    
};

class GCInputter : public Inputter{
    public:
    GCInputter(GCPort);
    void getInputs(int);
    //button mappings; information needeed to map ControllerStatus to VirtualInputs
    GameInput buttonA, buttonB, buttonX, buttonY;
	GameInput padLeft, padRight, padUp, padDown;
	GameInput buttonL, buttonR, buttonZ;
    GameInput analogL, analogR;

    //lots and lots of button mapping potential...
    /*bool swap_sticks;
    GameInput secondary_analog_up;
    GameInput secondary_analog_left;
    GameInput secondary_analog_right;
    GameInput secondary_analog_down;*/
    private:
    GCPort port;

    static uint32_t last_poll_frame; //ensures one poll per frame for all GC controllers
    static ControllerStatus* status_buffer;

    inline std::ostream& operator<<(std::ostream& str, const GCInputter& inp){
        str << "connected: " << inp.connected << ", jump: " << inp.jump
            << ", attack1: " << inp.attack1   << ", attack2: " << inp.attack2
            << ", aim_modifier: " << inp.aim_modifier << ", shield: " << inp.shield
            << ", grab: " << inp.grab << ", cancel: " << inp.cancel << std::endl
            << "left analog: " << inp.left_analog << " right analog: " << inp.right_analog << std::endl
            << "primary stick: (" << inp.primary_stick_x << ", " << inp.primary_stick_y << ")" << std::endl
            << "secondary stick: (" << inp.secondary_stick_x << ", " << inp.secondary_stick_y << ")";
        return str;
    };
};

class TASInputter : public Inputter{
    /*input list member*/
};

class KeyboardInputter : public Inputter{
};


}
#endif
    