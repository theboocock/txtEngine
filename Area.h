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
   bool has_description(std::string desc_id);
   std::string get_status();
   bool has_current_desc();
   int get_num_items();
   std::string get_description();
   void remove_item(int index);
   void add_item(Item *new_item);
   Item *get_item(int index);
   std::string get_id();
   bool has_item(std::string item_to_find);
   Item *get_item(std::string item_id);
   void add_description(StateDescriptor *desc);
   void add_command(AreaCommand *command_name);
   int get_num_commands();
   AreaCommand *get_command(int index);
   AreaCommand *has_command(std::string command_name);
   int get_num_descriptions();
   StateDescriptor *get_descriptor(int index);
   Area(const char *id, const char *desc_id, const char* status);
   ~Area();
};

#endif
