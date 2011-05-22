#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include "StateDescriptor.h"
#include "ItemCommand.h"

class Item{
 protected:
   bool collectable;
   std::string id;
   StateDescriptor *description;
   std::vector<ItemCommand*> commands;
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
   void add_command(ItemCommand *command_name){
      commands.push_back(command_name);
   }
   ItemCommand* has_command(const char *command_name){
      for(unsigned int c_num = 0; c_num < commands.size(); c_num++){
         if(!commands[c_num]->find(command_name)){
            return commands[c_num];
         }
      }
      return NULL;
   }
 Item(bool collect, const char *identifier){
      collectable = collect;
      id = identifier;
   }
};

#endif
