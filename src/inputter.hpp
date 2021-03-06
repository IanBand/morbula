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
    unused, //unused
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

        int cur, prev;

        // each buffer holds a current and previous input
        float left_analog[2];
        float right_analog[2];
        float primary_stick_x[2];
        float primary_stick_y[2];
        float secondary_stick_x[2];
        float secondary_stick_y[2];
        
};

class GCInputter : public Inputter{
    public:
    GCInputter(GCPort);
    void getInputs(int);
    //button mappings; information needeed to map ControllerStatus to VirtualInputs
    GameInput 
        buttonA  = GameInput::attack1, 
        buttonB  = GameInput::attack2, 
        buttonX  = GameInput::jump, 
        buttonY  = GameInput::jump, 
        padLeft  = GameInput::unused, 
        padRight = GameInput::unused, 
        padUp    = GameInput::unused, 
        padDown  = GameInput::unused, 
        buttonL  = GameInput::shield, 
        buttonR  = GameInput::aim_modifier, 
        buttonZ  = GameInput::grab, 
        analogL  = GameInput::cancel, 
        analogR  = GameInput::aim_modifier;

    //lots and lots of button mapping potential...
    /*bool swap_sticks;
    GameInput secondary_analog_up;
    GameInput secondary_analog_left;
    GameInput secondary_analog_right;
    GameInput secondary_analog_down;*/
    private:
    GCPort port;

    static uint32_t last_poll_frame; //ensures one poll per frame for all GC controllers
    static ControllerStatus adapter_buffer[4];
};

class TASInputter : public Inputter{
    /*input list member*/
};

class KeyboardInputter : public Inputter{
};

}
std::ostream& operator<<(std::ostream&, const input::GCInputter&);

#endif
    