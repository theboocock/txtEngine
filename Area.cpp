#include "Area.h"

bool Area::has_description(std::string desc_id) {
   for(int desc = 0; desc < num_descriptions; desc++) {
      if(!description[desc]->get_id().compare(desc_id)) {
         return true;
      }
   }
   return false;
}

std::string Area::get_status() {
   return status;
}

bool Area::has_current_desc() {
   return has_description(curr_desc_id);
}

int Area::get_num_items() {
   return num_items;
}

std::string Area::get_description() {
   for(int desc = 0; desc < num_descriptions; desc++) {
      if(!description[desc]->get_id().compare(curr_desc_id)) {
         return description[desc]->get_description();
      }
   }
   return "";
}

void Area::remove_item(int index) {
   items.erase(items.begin()+index);
   num_items--;
}

void Area::remove_item(std::string item_id){
   for(unsigned int i=0; i < items.size(); i++){
   	if(items[i]->item_id.compare(item_id)) items.erase(i);
   }else if(items[i]->has_synonym(item_id)) {
        items.erase(i);
      }else{
	items->remove_item(item_id);
      }
}

void Area::add_item(Item *new_item) {
   items.push_back(new_item);
   num_items++;
}

Item *Area::get_item(int index) {
   return items[index];
}

std::string Area::get_id() {
   return id;
}

bool Area::has_item(std::string item_to_find) {
   for(unsigned int item_num = 0; item_num < items.size(); item_num++) {
      if(items[item_num]->get_id().compare(item_to_find) == 0) {

         return true;
      }
      else if(items[item_num]->has_synonym(item_to_find)) {
         return items[item_num];
      }
   }
   return false;
}

Item * Area::get_item(std::string item_id, unsigned int &index) {
   for(unsigned int item_num = 0; item_num < items.size(); item_num++) {
      if(items[item_num]->get_id().compare(item_id) == 0) {
         index = item_num;
         return items[item_num];
      }
      else if(items[item_num]->has_synonym(item_id)) {

         index = item_num;
         return items[item_num];
      }
   }
   return NULL;
}

void Area::add_description(StateDescriptor *desc) {
   description.push_back(desc);
   num_descriptions++;

}

void Area::add_command(AreaCommand *command_name) {
   commands.push_back(command_name);
   num_commands++;
}

int Area::get_num_commands() {
   return num_commands;
}

AreaCommand *Area::get_command(int index) {
   return commands[index];
}

AreaCommand *Area::has_command(std::string command_name) {
   for(unsigned int c_num = 0; c_num < commands.size(); c_num++) {
      if(!commands[c_num]->get_name().compare(command_name)) {
         return commands[c_num];
      } else if(commands[c_num]->has_synonym(command_name)) {
         return commands[c_num];
      }
   }
    
   return NULL;
}

int Area::get_num_descriptions() {
   return num_descriptions;
}

StateDescriptor *Area::get_descriptor(int index) {
   return description[index];
}

Area::Area(const char *id, const char *desc_id, const char* status) {
   this->status = status;
   this->id = id;
   num_descriptions = 0;
   num_items = 0;
   num_commands = 0;
   this->curr_desc_id = desc_id;
}

Area::~Area() {
   for(unsigned int item_num = 0; item_num < items.size(); item_num++) {
      delete items[item_num];
   }
   for(unsigned int desc_num = 0; desc_num < description.size(); desc_num++) {
      delete description[desc_num];
   }
   for(unsigned int command_num = 0; command_num < commands.size(); command_num++) {
      delete commands[command_num];
   }
}

void Area::unlock(std::string area_command_id) {
   for(unsigned int c_num = 0; c_num < commands.size(); c_num++) {
      if(!commands[c_num]->get_name().compare(area_command_id)) {
         commands[c_num]->unlock();
      }

   }
}
