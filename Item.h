#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include "StateDescriptor.h"
#include "ItemCommand.h"

class Item{
 protected:
   bool collectable;
   int num_descriptions, num_commands;
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
   void change_collectable(bool flip){
      if(flip){
         collectable = !collectable;
      }
   }
   bool is_collectable(){
      return collectable;
   }
   std::string get_id(){
      return id;
   }
   int get_num_commands(){
      return num_commands;
   }
   void add_command(ItemCommand *command_name){
      commands.push_back(command_name);
      num_commands++;
   }
   ItemCommand *get_command(int index){
      return commands[index];
   }
   ItemCommand *has_command(std::string command_name){
      ItemCommand *checkingValidity;
      for(unsigned int c_num = 0; c_num < commands.size(); c_num++){
         if(!commands[c_num]->get_name().compare(command_name)){
            checkingValidity = commands[c_num];
            if(has_description(checkingValidity->get_state_change())){
               return checkingValidity;
            }
         }
      }
      return NULL;
   }
   int get_num_descriptions(){
      return num_descriptions;
   }
   StateDescriptor *get_descriptor(int index){
      return description[index];
   }
   void state_change(std::string to_change){
      curr_desc_id = to_change;
   }
   Item(bool collect, const char *identifier, const char *initial_state){
      collectable = collect;
      id = identifier;
      num_descriptions = 0;
      num_commands = 0;
      curr_desc_id = initial_state;
   }
   ~Item(){
      for(unsigned int command_num = 0; command_num < commands.size(); command_num++){
         delete commands[command_num];
      }
      for(unsigned int desc_num = 0; desc_num < description.size(); desc_num++){
         delete description[desc_num];
      }
   }
};

#endif
