/**
 *  Parser code is not mine using freely distributed TinYXML library
 * @author James Boocock, Toby Herbert, Mike Abrams
 *
 **/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include "parser.h"

#define DEFAULT_VALUE "default_value"
#define MAX_CHARACTERS_PER_LINE 100
#define WIN "win"
#define DIE "die"
#define NONE "none"
#define LOOK "look"
#define BAG "bag"
#define INVENTORY "inventory"
#define QUIT "quit"

bool game_over = false;

/*Method signatures */
void gameloop();
std::string two_word_command(std::string command1, std::string command2);
std::string one_word_command(std::string command);
void print_inventory();
std::string word_wrap(std::string input_string);
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
	  if(world != NULL){
      //print_world_tree();
      gameloop();
      delete world;
	  }
   }
   return 0;
}

void gameloop(){
   std::string last_area = DEFAULT_VALUE;
   while(!game_over){
      std::ostringstream sin;
      std::ostringstream commandstream;
      std::ostringstream itemstream;
      if(last_area.compare(world->get_active_area()->get_id()) != 0){
         last_area = world->get_active_area()->get_id();
         sin << world->get_active_area()->get_description();
         if(!strcmp(world->get_active_area()->get_status().c_str(), WIN) || !strcmp(world->get_active_area()->get_status().c_str(), DIE)){
            game_over = true;
         } else {
            for(int items = 0; items < world->get_active_area()->get_num_items();items++){
               itemstream << world->get_active_area()->get_item(items)->get_description();
            }
         }
         std::cout << word_wrap(sin.str())<<word_wrap(itemstream.str());
      }
      if(!game_over){
         std::cout << ">>";
         std::string line;
         std::getline(std::cin, line);
         std::string command1 , command2;
         std::string checkmorewords;
         std::istringstream iss(line);
         if(iss >> command1){
            if (iss >> command2){
               if(!(iss >> checkmorewords)){
                  commandstream << two_word_command(command1 ,command2);
               } else {
                  std::cout << "Please enter one or two word commands only" << std::endl;            
               }
            } else {
               std::string from_one_word = one_word_command(command1);
               if(!strcmp(from_one_word.c_str(), DEFAULT_VALUE)){
                  last_area = DEFAULT_VALUE;
               } else {
                  commandstream << from_one_word;
               }
            }
         } else {
            std::cout << "Please enter one or two word commands only" << std::endl;     
         }
         std::cout << "\n" << word_wrap(commandstream.str());
      }
   }

}

std::string two_word_command(std::string command1, std::string command2){
   std::ostringstream result;
   std::transform(command1.begin(), command1.end(),
                  command1.begin(), ::tolower);
   std::transform(command2.begin(), command2.end(),
                  command2.begin(), ::tolower);
   for(int item = 0; item < world->get_active_area()->get_num_items(); item++){
      Item *temp_item = world->get_active_area()->get_item(item);
      if(!strcmp(temp_item->get_id().c_str(), command2.c_str())){
         ItemCommand *temp_item_command = temp_item->has_command(command1);
         if(temp_item_command != NULL){
            //do item command here
            if(temp_item_command->get_collect_dependent() == temp_item->is_collectable()){
               if(!strcmp(world->get_active_area()->get_status().c_str(), WIN)||!strcmp(world->get_active_area()->get_status().c_str() ,DIE)){
                  game_over = true;
               }
               temp_item->state_change(temp_item_command->get_state_change());
               temp_item->change_collectable(temp_item_command->get_change_collect());
               world->get_area(temp_item_command->get_area_change())->add_item(temp_item);
               world->get_active_area()->remove_item(item);
               result << temp_item_command->get_message();
               result << "\n";
               return result.str();
            }
         } else {
            result << "There is no command ";
            result << command1;
            result << " for item ";
            result << command2;
            return result.str();
         }
      }
   }
   for(int item = 0; item < world->get_area(INVENTORY)->get_num_items(); item++){
      Item *temp_item = world->get_area(INVENTORY)->get_item(item);
      if(!strcmp(temp_item->get_id().c_str(), command2.c_str())){
         ItemCommand *temp_item_command = temp_item->has_command(command1);
         if(temp_item_command != NULL){
            //do item command here
            if(temp_item_command->get_collect_dependent() == temp_item->is_collectable()){
               if(!strcmp(world->get_active_area()->get_status().c_str(),WIN)||!strcmp(world->get_active_area()->get_status().c_str() ,DIE)){
                  game_over = true;
               }
               temp_item->state_change(temp_item_command->get_state_change());
               temp_item->change_collectable(temp_item_command->get_change_collect());
               if( world->get_area(temp_item_command->get_area_change()) !=NULL){
                  world->get_area(temp_item_command->get_area_change())->add_item(temp_item);
               } else {
                  world->get_active_area()->add_item(temp_item);
               }
               world->get_area(INVENTORY)->remove_item(item);
               result << temp_item_command->get_message();
               result << "\n";
               return result.str();
            }
         } else {
            result << "There is no command ";
            result << command1;
            result << " for item ";
            result << command2;
            return result.str();
         }
      }
   }
   return "I don't understand that. \n";  
}

std::string one_word_command(std::string command){
   std::transform(command.begin(), command.end(),
                  command.begin(), ::tolower);
   if(!command.compare(QUIT)){
      game_over = true;
      return DEFAULT_VALUE;
   }
   if(!command.compare(LOOK)){
      return DEFAULT_VALUE;
   } else if(!command.compare(BAG)){
     print_inventory();
     return "";
   } else if(!command.compare(INVENTORY)){
      print_inventory();
      return "";
   }
   AreaCommand *temp_area_command = world->get_active_area()->has_command(command);
   if(temp_area_command != NULL){
      if(!strcmp(world->get_active_area()->get_status().c_str(), WIN)|| !strcmp(world->get_active_area()->get_status().c_str() ,DIE)){
         game_over = true;
      }
      world->change_area(temp_area_command->get_area());
      return temp_area_command->get_message();
   } else {
      return "I don't understand that. \n";
   }
   
}

void print_inventory(){
   std::ostringstream sin;
   int num = 1;
   sin << "INVENTORY: \n" ;
   std::string inv = INVENTORY;
   for(int items = 0; items < world->get_area(inv)->get_num_items(); items++){
      sin << num++ << " = " << world->get_area(INVENTORY)->get_item(items)->get_description();
      if(items  < world->get_area(inv)->get_num_items() - 1){
         sin << "\n";
      }
   }
  
   std::cout << "\n" <<  sin.str();
   
}
   
std::string word_wrap(std::string input_string){

	std::istringstream iss(input_string);
	std::string formatted;
	std::string line;
      std::string word;
      while (iss >> word)
   {
      if (line.length() + word.length() > MAX_CHARACTERS_PER_LINE)
      {
         formatted +=line+"\n";

         line.clear();
	  }
		 line += word + " ";
   }

   if (!line.empty())
   {
      formatted += line +"\n";
   }
   return formatted + "\n";
}


