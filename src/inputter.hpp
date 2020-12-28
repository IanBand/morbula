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
An Inputter maps some typep of user input to
***************************************/
class Inputter {
    public:
    int left_analog;
    int right_analog;
    int primary_stick_x;
    int primary_stick_y;
    int secondary_stick_x;
    int secondary_stick_y;
    
    bool jump, attack1, attack2;
    bool aim_modifier, shield;
    bool grab, cancel, connected;
    virtual getInputs(int frame) = 0;
};

class GCInputter : public Inputter{
    public:
    //information needeed to map ControllerStatus to VirtualInputs
    GameInput buttonA, buttonB, buttonX, buttonY;
	GameInput padLeft, padRight, padUp, padDown;
	GameInput buttonL, buttonR, buttonZ;
    GameInput analogL, analogR;

    //lots and lots of button mapping potential...
    /*
    bool swap_sticks;
    GameInput secondary_analog_up;
    GameInput secondary_analog_left;
    GameInput secondary_analog_right;
    GameInput secondary_analog_down;
    */
    private:
    GCPort port;

    static int last_poll_frame; //ensures one poll per frame for all GC controllers
    static ControllerStatus* status_buffer;
};

class TASInputter : public Inputter{
    /*pointer to input list*/
};

class KeyboardInputter : public Inputter{
};
#endif
    