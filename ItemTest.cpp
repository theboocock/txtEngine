#include <iostream>
#include <sstream>
#include <string>
#include "tinyxml.h"
#include "World.h"


Item * test_item;
StateDescriptor* state_descriptor;
ItemCommand * item_command;
ItemCommand * test_command;
using namespace std;
int main(){
   test_item = new Item(true, "lamp", "glowinglamp");
   state_descriptor = new StateDescriptor("glowinglamp");
   state_descriptor->set_description(" A glowing lamp on the table");
   item_command = new ItemCommand("get", "get1", "glowinglamp");
   
   test_item->add_description(state_descriptor);
   test_item->add_command(item_command);
   cout << test_item->has_command(item_command->get_name()) << endl;
   cout << test_item->has_current_desc() << endl;
   
   cout << state_descriptor->get_id() << endl;
   cout << state_descriptor->get_description() << endl;
   cout << test_item->get_id() << endl;
   cout << test_item->is_collectable() << endl;
   return 0;
   
}


