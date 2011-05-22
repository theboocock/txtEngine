#ifndef _AREA_H
#define _AREA_H
#include <string>
#include <vector>
#include "Item.h"
#include "StateDescriptor.h"
#include "AreaCommand.h"

class Area{
 protected:
   std::vector<Item*> items;
   int num_items;
   int num_descriptions, num_commands;
   std::string status;
   std::string id;
   std::string curr_desc_id;
   std::vector<StateDescriptor*> description;
   std::vector<AreaCommand*> commands;
 public:
   bool has_description(std::string desc_id){
      for(int desc = 0; desc < num_descriptions; desc++){
         if(!strcmp(description[desc]->get_id().c_str(), desc_id.c_str())){
            return true;
         }
      }
      return false;
   }
   std::string get_status(){
      return status;
   }
   bool has_current_desc(){
      return has_description(curr_desc_id);
   }
   int get_num_items(){
      return num_items;
   }
   
   std::string get_description(){
      for(int desc = 0; desc < num_descriptions; desc++){
         if(!strcmp(description[desc]->get_id().c_str(),curr_desc_id.c_str() )){
            return description[desc]->get_description();
         }
      }
      return "";
   }
   void add_item(Item *new_item){
      items.push_back(new_item);
      num_items++;
   }
   Item *get_item(int index){
      return items[index];
   }
   std::string get_id(){
      return id;
   }
   bool has_item(std::string item_to_find){
      for(unsigned int item_num = 0; item_num < items.size(); item_num++){
         if(items[item_num]->get_id().compare(item_to_find) == 0){
            return true;
         }
      }
      return false;
   }
   Item *get_item(std::string item_id){
      for(unsigned int item_num = 0; item_num < items.size(); item_num++){
         if(items[item_num]->get_id().compare(item_id) == 0){
            return items[item_num];
         }
      }
      return NULL;
   }
   void add_description(StateDescriptor *desc){
      description.push_back(desc);
      num_descriptions++;
      
   }
   void add_command(AreaCommand *command_name){
      commands.push_back(command_name);
      num_commands++;
   }
   int get_num_commands(){
      return num_commands;
   }
   AreaCommand *get_command(int index){
      return commands[index];
   }
   AreaCommand *has_command(std::string command_name){
      for(unsigned int c_num = 0; c_num < commands.size(); c_num++){
         if(!commands[c_num]->get_name().compare(command_name)){
            return commands[c_num];
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
   Area(const char *id, const char *desc_id, std::string status){
      this->status = status;
      this->id = id;
      num_descriptions = 0;
      num_items = 0;
      num_commands = 0;
      this->curr_desc_id = desc_id;
   }
   ~Area(){
      for(unsigned int item_num = 0; item_num < items.size(); item_num++){
         delete items[item_num];
      }
      for(unsigned int desc_num = 0; desc_num < description.size(); desc_num++){
         delete description[desc_num];
      }
      for(unsigned int command_num = 0; command_num < commands.size(); command_num++){
         delete commands[command_num];
      }
   }
};

#endif
