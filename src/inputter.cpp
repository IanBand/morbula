#include "inputter.hpp"

// define + init static members
uint32_t input::GCInputter::last_poll_frame = 0;
ControllerStatus* input::GCInputter::status_buffer = NULL;


/*std::ostream& operator<<(std::ostream& os, const shapes::Triangle& tri){
    os << tri.fuck << std::endl;
    return os;
}*/
std::ostream& operator<<(std::ostream& os, const input::GCInputter& inp){
        os << "connected: " << inp.connected << ", jump: " << inp.jump
            << ", attack1: " << inp.attack1   << ", attack2: " << inp.attack2
            << ", aim_modifier: " << inp.aim_modifier << ", shield: " << inp.shield
            << ", grab: " << inp.grab << ", cancel: " << inp.cancel << std::endl
            << "left analog: " << inp.left_analog << " right analog: " << inp.right_analog << std::endl
            << "primary stick: (" << inp.primary_stick_x << ", " << inp.primary_stick_y << ")" << std::endl
            << "secondary stick: (" << inp.secondary_stick_x << ", " << inp.secondary_stick_y << ")";
        return os;
};

input::GCInputter::GCInputter(GCPort _port){
    port = _port;
};
void input::GCInputter::getInputs(int frame){

    // ensure that the gamecube status buffer is updated only once per frame
    if(last_poll_frame != frame){
        status_buffer = gca::Process();
        last_poll_frame = frame;
    }

    // map phisical gc_inputs to virtual game_inputs
    // loop through the 11 digital buttons on the GC controller & 11 button mappings

    //bool *virtual_inputs = &connected;                  //virtual input array
    //bool *gc_inputs = &(status_buffer[port].buttonA);   //physical input array
    //GameInput *button_map = &buttonA;                   //map array


    //seg faults because this thread does not have access to status_buffer. 
    //Thats probably why a new status buffer was being allocated every call of Process()
    //maybe try passing in a static buffer that GCInputter owns
    //if not just allocate one every poll and delete like how the vanilla library did it, nbd.

    /*
    for(int i = 0; i < 11; ++i){
        virtual_inputs[button_map[i]] = gc_inputs[i];
    }
    */

    //maped analog -> digital inputs 
    //virtual_inputs[analogL] = (status_buffer[port].triggerL > 0);
    //virtual_inputs[analogR] = (status_buffer[port].triggerR > 0);

    //could do this in a loop or memcopy or somethin
    /*
    left_analog       = status_buffer[port].triggerL;
    right_analog      = status_buffer[port].triggerR;
    primary_stick_x   = status_buffer[port].mainStickHorizontal;
    primary_stick_y   = status_buffer[port].mainStickVertical;
    secondary_stick_x = status_buffer[port].cStickHorizontal;
    secondary_stick_y = status_buffer[port].cStickVertical;

    connected = status_buffer[port].connected;
    */

};