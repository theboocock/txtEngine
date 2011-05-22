/**
 *  Parser code is not mine using freely distributed TinYXML library
 * @author James Boocock, Toby Herbert, Mike Abrams
 *
 **/

#include <iostream>
#include <sstream>
#include "parser.h"

/*Method signatures */
void gameloop();

// load the named file and dump its structure to STDOUT

World *world;

void print_world_tree(){
   std::ostringstream sin;
   sin << "World:\n";
   for(int area = 0; area < world->get_num_areas(); area++){
      Area *temp_area = world->get_area(area);
      sin << "\tArea: ";
      sin << temp_area->get_id();
      sin << "\n";
      for(int state_desc = 0; state_desc < temp_area->get_num_descriptions(); state_desc++){
         StateDescriptor *temp_desc = temp_area->get_descriptor(state_desc);
         sin << "\t\tDesc: ";
         sin << temp_desc->get_description();
         sin << "\n";
      }
      for(int command = 0; command < temp_area->get_num_commands(); command++){
            AreaCommand *temp_command = temp_area->get_command(command);
            sin << "\t\tCommand: ";
            sin << temp_command->get_name();  
            sin << "\n\t\t\t";
            sin << temp_command->get_message();
            sin << "\n";
      }
      for(int item = 0; item < temp_area->get_num_items(); item++){
         Item *temp_item = temp_area->get_item(item);
         sin << "\t\tItem:";
         sin << temp_item->get_id();
         sin << "\n";
         for(int state_desc = 0; state_desc < temp_item->get_num_descriptions(); state_desc++){
            StateDescriptor *temp_desc = temp_item->get_descriptor(state_desc);
            sin << "\t\t\tDesc: ";
            sin << temp_desc->get_description();
            sin << "\n";
         }
         for(int command = 0; command < temp_item->get_num_commands(); command++){
            ItemCommand *temp_command = temp_item->get_command(command);
            sin << "\t\t\tCommand: ";
            sin << temp_command->get_name();
            sin << "\n\t\t\t";
            sin << temp_command->get_message();
            sin << "\n";
         }
      }
   }
   std::string message = sin.str();
   fprintf(stderr, "Attempt at printing world.\n%s\n", message.c_str());
}

int main(int argc, char** argv)
{
   if(argc > 1){
      world = read_file(argv[1], world);
      /*delete world deletes everything, as the the deconstructor for
        world calls the decontructor for all areas, which calls the
        decontructor for all items and descriptions...
      */
      print_world_tree();
      gameloop();
      delete world;
   }
   return 0;
}

void gameloop(){
   



}
