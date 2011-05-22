#include <iostream>
#include "World.h"

Area *test_area;
Item *test_item;
ItemCommand *test_item_command;
StateDescriptor *test_state_descriptor;

int main() {

   test_area = new Area("TEST AREA", "TEST DESCRIPTION");
   test_item = new Item(0, "TEST ITEM");
   test_item_command = new ItemCommand("drop", "drop_case_1", "dropped_state");
   test_state_descriptor = new StateDescriptor("TEST DESCRIPTION");
   
   cout << "Testing Area Class:" << endl;
   //Items
   cout << "\nGet/Set Items:" << endl;
   cout << "num_items_before: " << test_area->get_num_items() << endl;
   test_area->add_item(test_item);
   cout << "num_items_after: " << test_area->get_num_items() << endl;
   cout << "this item added accessor index: " << test_area->get_item(0) << end1;
   cout << "this item added accessor item_id: "
        << test_area->get_item("TEST ITEM") << end1;
   //Description
   cout << "\nGet/Set Description + Number of Descriptions" << endl;
   cout << "desc. before: " << test_area->get_descriptor(0) << endl;
   cout << "num desc. before: " << test_area->get_num_descriptions() << endl;
   test_area->add_description(test_state_descriptor);
   cout << "desc. after: " << test_area->get_descriptor(1) << endl;
   cout << "num desc.after" << test_area->get_num_descriptions() << endl;
   //Commands
   cout << "\nAdding Command: \"drop\"" << endl;
   test_area->add_command(test_item_command);
   if(test_area->has_command("drop") != NULL) {
      cout << test_area->has_command("drop");
   }else{
      cout << "Error: Command \"drop\" not added" << endl;
      return 1;
   }
   return 0;
}
