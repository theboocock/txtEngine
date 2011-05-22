#include <iostream>
#include <sstream>
#include "tinyxml.h"
#include "World.h"

using namespace std;

Area *test_area;
Item *test_item;
AreaCommand *test_item_command;
StateDescriptor *test_state_descriptor;

int main() {

   test_area = new Area("TEST AREA", "TEST DESCRIPTION");
   test_item = new Item(true, "TEST ITEM", "TEST DESCRIPTION");
   test_item_command = new AreaCommand("north", "bathroom", "kitchen");
   test_state_descriptor = new StateDescriptor("TEST DESCRIPTION");
   
   cout << "Testing Area Class:" << endl;
   //Items
   cout << "\nGet/Set Items:" << endl;
   cout << "num_items_before: " << test_area->get_num_items() << endl;
   test_area->add_item(test_item);
   cout << "num_items_after: " << test_area->get_num_items() << endl;
   cout << "mem. location of item accessor(index): " <<
      test_area->get_item(0) << endl;
   cout << "mem. location of accessor(item_id): " <<
      test_area->get_item("TEST ITEM") << endl;
   //Description
   cout << "\nGet/Set Description + Number of Descriptions" << endl;
   cout << "num desc. before: " << test_area->get_num_descriptions() << endl;
   test_area->add_description(test_state_descriptor);
   cout << "desc. after: " << test_area->get_descriptor(0) << endl;
   cout << "num desc. after: " << test_area->get_num_descriptions() << endl;
   //Commands
   cout << "\nAdding Command: \"north\"" << endl;
   test_area->add_command(test_item_command);
   if(test_area->has_command("north") != NULL) {
      cout << "north is at mem. location: " <<
         test_area->has_command("north") << endl;
   }else{
      cout << "Error: Command \"north\" not added" << endl;
      return 1;
   }
   return 0;
}
