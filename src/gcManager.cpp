#include "gcManager.hpp"

using namespace gcm;

GCManager::GCManager(){
    if(!gca::Setup()){
        std::cout << "Unable to init GameCube Adapter!" << std::endl;
        
    }else{

    }
};
void GCManager::pollInputs(){

    bool virtualButtonInputs [7]; //size equal to number of game inputs

    //poll GCA, convert ControllerStatus to VirtualInput

    //check if in previous poll, the controller was unplugged
    //if so, record the analog values as the inital analog values

    //use InputMap to translate ControllerStatus into VirtualInput
    //if(cont_status.buttonA) virtualButtonInputs[maps[port].buttonA] = true;



    
};

void GCManager::setInputMap(InputMap*, Port){

};


VirtualInputs* GCManager::getInputs(Port p){
    return &virtual_inputs[p];
};