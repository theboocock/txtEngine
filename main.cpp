/**
 * @file Main.cpp
 * Main file for the game. 
 *
 * @licence Open-source
 * @date 14/08/2011
 * @brief The main file for txtEngine.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 * @remark Parser code is freely distributed TinyXML library
 *
 */

/*! \mainpage Documentation for the txtEngine Project
 *
 * \section date_sec Date Updated:
 * 14-08-2011
 *
 * \section about_sec What is txtEngine?
 * txtEngine is an interpreter for text only adventure games. Games are
 * written using the XML language making it easy for anyone to write and
 * play their own games.
 *
 * \section links_sec Links:
 *
 * <ul>
 * <li>txtEngine Project Site on Github:
 * <a href="https://github.com/smilefreak/txtEngine">
 * https://github.com/smilefreak/txtEngine</a><br></li>
 *
 * <li>Facebook Fanpage: <a href="http://www.facebook.com/txtEngine">
 * http://www.facebook.com/txtEngine</a><br></li>
 *
 * <li>TinyXML Documentation:
 * <a href="http://www.grinninglizard.com/tinyxmldocs/index.html">
 * http://www.grinninglizard.com/tinyxmldocs/index.html</a><br></li>
 * </ul>
 *
 * \section bugs_sec Report Bugs:
 * Please report any bugs here:
 * <a href="https://github.com/smilefreak/txtEngine/issues">
 * https://github.com/smilefreak/txtEngine/issues</a><br>
 *
 * \section author_sec Authors:
 * Toby Herbert, Michael Abrams, James Boocock, Tatai Nikora
 * 
 * 
 */

//------------------------------------------------------------------------------
/* Include */
//------------------------------------------------------------------------------

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include "parser.h"
#include "Constants.h"

//------------------------------------------------------------------------------
/* Global Variables */
//------------------------------------------------------------------------------

World *world;
bool game_over = false;

//------------------------------------------------------------------------------
/* Method Prototypes */
//------------------------------------------------------------------------------

/**
   @brief The main gameloop.
*/
void gameloop();

/**
     Write description of function here.
     The function should follow these comments.
     Use of "brief" tag is optional. (no point to it)
     
     The function arguments listed with "param" will be compared 
     to the declaration and verified.
     
     @param[in]     _inArg1 Description of first function argument.
     @param[out]    _outArg2 Description of second function argument.
     @param[in,out] _inoutArg3 Description of third function argument.
     @return Description of returned value.
     */
std::string one_word_command(std::string command);

/**
     Write description of function here.
     The function should follow these comments.
     Use of "brief" tag is optional. (no point to it)
     
     The function arguments listed with "param" will be compared 
     to the declaration and verified.
     
     @param[in] command1 The first word.
     @param[in] command2 The second word.
     @return A string
     */
std::string two_word_command(std::string command1, std::string command2);

/**
     Write description of function here.
     The function should follow these comments.
     Use of "brief" tag is optional. (no point to it)
     
     The function arguments listed with "param" will be compared 
     to the declaration and verified.
     
     @param[in]     _inArg1 Description of first function argument.
     @param[out]    _outArg2 Description of second function argument.
     @param[in,out] _inoutArg3 Description of third function argument.
     @return Description of returned value.
     */
void print_inventory();

/**
     Write description of function here.
     The function should follow these comments.
     Use of "brief" tag is optional. (no point to it)
     
     The function arguments listed with "param" will be compared 
     to the declaration and verified.
     
     @param[in]     _inArg1 Description of first function argument.
     @param[out]    _outArg2 Description of second function argument.
     @param[in,out] _inoutArg3 Description of third function argument.
     @return Description of returned value.
     */
std::string word_wrap(std::string input_string);

/**
   This method is used for debug purposes only:
   Prints out the parsed XML file in a tree structure.
*/
void print_world_tree();

void load_game();
void save_game();

//------------------------------------------------------------------------------
/* Method Definitions */
//------------------------------------------------------------------------------

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
               itemstream << "\n";
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
   if(!strcmp(command1.c_str(), GO)){
      return one_word_command(command2);
   }
   unsigned int item = NULL;
   Item *temp_item = world->get_active_area()->get_item(command2, item);
   if(temp_item != NULL){
      ItemCommand *temp_item_command = temp_item->get_command(command1);
      if(temp_item_command != NULL){
         if(world->get_area(INVENTORY)->has_item(temp_item_command->get_depends()) ||
            !strcmp(world->get_active_area()->get_id().c_str(), temp_item_command->get_depends().c_str()) ||
            !strcmp(temp_item_command->get_depends().c_str(), NONE)){
            if(temp_item_command->get_collect_dependent() == temp_item->is_collectable()){
               if(!strcmp(temp_item_command->get_status().c_str(), WIN)||
                  !strcmp(temp_item_command->get_status().c_str() ,DIE)){
                  game_over = true;
               }
               temp_item->state_change(temp_item_command->get_state_change());
               temp_item->change_collectable(temp_item_command->get_change_collect());
               if(temp_item_command->unlocks()){
                  if(!temp_item_command->unlock_area_string().compare(world->get_active_area()->get_id())){
                     world->get_active_area()->unlock(temp_item_command->unlock_areacommand_string());
                  } else {
                     return "You can't do that. \n";
                  }
               }
               if(world->get_area(temp_item_command->get_area_change()) != NULL){
                  world->get_area(temp_item_command->get_area_change())->add_item(temp_item);
               } else {
                  world->get_active_area()->add_item(temp_item);
               }
               world->get_active_area()->remove_item(item);
               result << temp_item_command->get_message();
               result << "\n";
               return result.str();
            }
         } else {
            return "You can't do that.\n";
         }
      } else {
         result << "There is no command ";
         result << command1;
         result << " for item ";
         result << command2;
         return result.str();
      }
   }
   temp_item = NULL;
   temp_item = world->get_area(INVENTORY)->get_item(command2, item);
   if(temp_item != NULL){
         ItemCommand *temp_item_command = temp_item->get_command(command1);
         if(temp_item_command != NULL){
            if(temp_item_command->get_collect_dependent() == temp_item->is_collectable()){
               if(!strcmp(world->get_active_area()->get_status().c_str(),WIN)||!strcmp(world->get_active_area()->get_status().c_str() ,DIE)){
                  game_over = true;
               }
               temp_item->state_change(temp_item_command->get_state_change());
               temp_item->change_collectable(temp_item_command->get_change_collect());
                     if(temp_item_command->unlocks()){
                        if(!temp_item_command->unlock_area_string().compare(world->get_active_area()->get_id())){
                           world->get_active_area()->unlock(temp_item_command->unlock_areacommand_string());
                        } else {
                           return "You can't do that. \n";
                        }
                     }
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
   return "I don't understand that. \n";  
}

std::string one_word_command(std::string command){
   std::transform(command.begin(), command.end(),
                  command.begin(), ::tolower);
   
   if(!command.compare(HELP)){
      return HELP_COMMAND;
   }
   if(!command.compare(N)){
      command = NORTH;
   }
   if(!command.compare(S)){
      command = SOUTH;
   }
   if(!command.compare(E)){
      command = EAST;
   }
   if(!command.compare(W)){
      command = WEST;
   }
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
      if(world->get_area(INVENTORY)->has_item(temp_area_command->get_depends()) ||
         !strcmp(temp_area_command->get_depends().c_str(), NONE)) {
         if(!temp_area_command->is_locked()){
         world->change_area(temp_area_command->get_area());
         return temp_area_command->get_message();
         }
         return "That way is locked";
      } else {
         return "You can't do that.\n";
      }
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
   while (iss >> word) {
      if (line.length() + word.length() > MAX_CHARACTERS_PER_LINE) {
         formatted +=line+"\n";
         line.clear();
      }
      line += word + " ";
   }
   if (!line.empty()) {
      formatted += line +"\n";
   }
   return formatted + "\n";
}

int main(int argc, char** argv){
   std::string userinput;
   if(argc > 1){
      do{
         world = read_file(argv[1], world);
         if(world != NULL){
            /*Debug Only*/
            //print_world_tree();
            gameloop();
            delete world;         
            std::cout << "Would you like to play again? (please enter yes for affirmative)" << std::endl;
            std::getline (std::cin,userinput);  
            game_over = true;
            if(!userinput.compare("yes")){
               game_over = false;
            }
         } else {
            game_over = true;
         }
      }while (!game_over);   
   }
   return 0;
}
