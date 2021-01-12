#include "inputter.hpp"

// define + init static members
uint32_t input::GCInputter::last_poll_frame = 0;
ControllerStatus input::GCInputter::adapter_buffer[4];

std::ostream& operator<<(std::ostream& os, const input::GCInputter& inp){
        os << "connected: " << inp.connected << ", jump: " << inp.jump
            << ", attack1: " << inp.attack1   << ", attack2: " << inp.attack2
            << ", aim_modifier: " << inp.aim_modifier << ", shield: " << inp.shield
            << ", grab: " << inp.grab << ", cancel: " << inp.cancel << std::endl
            << "left analog: " << inp.left_analog[inp.cur] << " right analog: " << inp.right_analog[inp.cur] << std::endl
            << "primary stick: (" << inp.primary_stick_x[inp.cur] << ", " << inp.primary_stick_y[inp.cur] << ")" << std::endl
            << "secondary stick: (" << inp.secondary_stick_x[inp.cur] << ", " << inp.secondary_stick_y[inp.cur] << ")";
        return os;
};

input::GCInputter::GCInputter(GCPort _port){
    port = _port;
};
void input::GCInputter::getInputs(int frame){
    //TODO: map start button

    cur = frame & 1;
    prev = (cur + 1) & 1;

    // ensure that the gamecube status buffer is updated only once per frame
    if(last_poll_frame != frame){
        gca::Process(adapter_buffer);
        last_poll_frame = frame;
    }

    // map phisical gc_inputs to virtual game_inputs

    bool *virtual_inputs = &connected;                   //virtual input array
    bool *gc_inputs = &(adapter_buffer[port].buttonA);   //physical input array
    GameInput *button_map = &buttonA;                    //button -> input map

    //clear all 8 virtual inputs
    for(int i = 0; i < 8; ++i){
        virtual_inputs[i] = false;
    }

    // loop through the 11 digital buttons on the GC controller & 11 button mappings
    for(int i = 0; i < 11; ++i){
        virtual_inputs[button_map[i]] |= gc_inputs[i];
    }
    

    //maped analog -> digital inputs
    virtual_inputs[analogL] |= (adapter_buffer[port].triggerL > 4); //analog press threshold
    virtual_inputs[analogR] |= (adapter_buffer[port].triggerR > 4);

    //could do this in a loop or memcopy or somethin like above
    // x % 2 == x & 1, write to different parts of the buffer based on frame parity
    left_analog[cur]       = adapter_buffer[port].triggerL; // could instead subtract "analog press threshold" here, & calc virtual analog L/R binary input from these values 
    right_analog[cur]      = adapter_buffer[port].triggerR;
    primary_stick_x[cur]   = adapter_buffer[port].mainStickHorizontal;
    primary_stick_y[cur]   = adapter_buffer[port].mainStickVertical;
    secondary_stick_x[cur] = adapter_buffer[port].cStickHorizontal;
    secondary_stick_y[cur] = adapter_buffer[port].cStickVertical;

    connected = adapter_buffer[port].connected;

    std::cout << *this << std::endl << std::endl;

};