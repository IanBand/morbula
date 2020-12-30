#include "inputter.hpp"

// define + init static members
uint32_t input::GCInputter::last_poll_frame = 0;
ControllerStatus* input::GCInputter::status_buffer = NULL;

void input::GCInputter::getInputs(int frame){

    // ensure that the gamecube status buffer is updated only once per frame
    if(last_poll_frame != frame){
        status_buffer = gca::Process();
        last_poll_frame = frame;
    }

    // map phisical gc_inputs to virtual game_inputs
    // loop through the 11 digital buttons on the GC controller & 11 button mappings
    bool *virtual_inputs = &connected;             //virtual input array
    bool *gc_inputs = &(status_buffer[port].buttonA);   //physical input array
    GameInput *button_map = &buttonA;                   //map array

    for(int i = 0; i < 11; ++i){
        virtual_inputs[button_map[i]] = gc_inputs[i];
    }

    //maped analog -> digital inputs 
    virtual_inputs[analogL] = (status_buffer[port].triggerL > 0);
    virtual_inputs[analogR] = (status_buffer[port].triggerR > 0);


    /*
    left_analog = ;
        int right_analog;
        int primary_stick_x;
        int primary_stick_y;
        int secondary_stick_x;
        int secondary_stick_y;
    */





};