#ifndef _BASE_CONTAINER_H
#include <vector>
#include <string>
#include "StateDescriptor.h"
#include "EventHandler.h"
#include "Command.h"

class BaseContainer{
 protected:   
   std::vector<StateDescriptor> state_descriptors;
   std::vector<EventHandler> event_handler;
   std::vector<Command> commands;   
   std::string id;   
 public:
   std::string get_id(){return id;}
   BaseContainer(const char *id){
      this->id = id;
   }
};

#endif
