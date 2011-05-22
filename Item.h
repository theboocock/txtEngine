#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include "StateDescriptor.h"
#include "ItemCommand.h"

class Item{
 protected:
   bool collectable;
   int num_descriptions;
   std::string id;
   std::string curr_desc_id;
   std::vector<StateDescriptor*> description;
   std::vector<ItemCommand*> commands;
 public:
   bool has_description(std::string desc_id){
      for(int desc = 0; desc < num_descriptions; desc++){
         if(!strcmp(description[desc]->get_id().c_str(), desc_id.c_str())){
            return true;
         }
      }
      return false;
   }
   bool has_current_desc(){
      return has_description(curr_desc_id);
   }
   void add_description(StateDescriptor *desc){
      description.push_back(desc);
      num_descriptions++;    
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
   Item(bool collect, const char *identifier, const char *initial_state){
      collectable = collect;
      id = identifier;
      num_descriptions = 0;
      curr_desc_id = initial_state;
   }
};

#endif
