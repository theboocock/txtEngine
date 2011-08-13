#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include "StateDescriptor.h"
#include "ItemCommand.h"

class Item{
 private:
   bool check_synonyms();
 protected:
   bool collectable;
   int num_descriptions, num_commands;
   std::string id;
   std::string curr_desc_id;
   std::vector<StateDescriptor*> description;
   std::vector<ItemCommand*> commands;
   std::vector<std::string> *synonyms;
 public:
   bool has_description(std::string desc_id);
   bool has_current_desc();
   bool has_synonym(std::string);
   std::string get_description();
   void add_description(StateDescriptor *desc);
   void change_collectable(bool flip);
   bool is_collectable();
   std::string get_id();
   int get_num_commands();
   void add_command(ItemCommand *command_name);
   ItemCommand *get_command(int index);
   ItemCommand *has_command(std::string command_name);
   int get_num_descriptions();
   StateDescriptor *get_descriptor(int index);
   void state_change(std::string to_change);
   Item(bool collect, const char *identifier, const char *initial_state, std::vector<std::string> *synonyms);
   ~Item();
};

#endif
