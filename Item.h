#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include "StateDescriptor.h"

class Item{
 protected:
   bool collectable;
   std::string id;
   StateDescriptor *description;
   std::vector<Command*> commands;
 public:
   void set_description(StateDescriptor *desc){
      description = desc;
   }
   bool is_collectable(){
      return collectable;
   }
   std::string get_id(){
      return id;
   }
   void add_command(Command* command){
      commands.push_down(command);
   }
 Item(bool collect, const char *identifier){
      collectable = collect;
      id = identifier;
   }
};

#endif
