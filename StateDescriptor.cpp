#include "StateDescriptor.h"

StateDescriptor::StateDescriptor(const char *identifier){
      id = identifier;
   }
void StateDescriptor::set_description(const char *desc){
      description = desc;
   }
StateDescriptor::~StateDescriptor(){
   }   
std::string StateDescriptor::get_id(){
      return id;
   }
std::string StateDescriptor::get_description(){
      return description;
   }

