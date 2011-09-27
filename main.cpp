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
std::vector<std::string> commandList;
std::vector<std::string> filterList;

//------------------------------------------------------------------------------
/* Method Prototypes */
//------------------------------------------------------------------------------

/**
 @brief The main gameloop.
 */
void gameloop();

/**
 @brief A method to handle one word commands.
 @param[in] command A single word command in the form of a string.
 @return Output of the command.
 */
std::string one_word_command(std::string command);

/**
 @brief A method to handle two word commands.
 @param[in] command A two word command in the form of a string.
 @return Output of the command.
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
std::string three_word_command(std::string command);

/**
 Prints out the contents of the inventory vector.
 */
void print_inventory();

/**
 Wraps the output to a specified size.
 
 @param[in] input_string The output of the game to be wrapped
 @return A wrapped string, properly formatted.
 */
std::string word_wrap(std::string input_string);

/**
 This method is used for debug purposes only:
 Prints out the parsed XML file in a tree structure.
 */
void print_world_tree();

/**
 Loads a game from a .sav file.
 */
void load(char* const file);

/**
 Saves a game to a .sav file by dumping the command list vector
 to a file.
 */
void save(char* const file);

/**
 Checks the input string for words that are in the filterList
 vector. If they are in the list they are removed from the string.
 
 @param[in] input_string A string to be filtered
 @return A string with words from filterList removed.
 */
std::string input_filter(std::string input_string);

/**
 Reads words from a specified file into
 the filterList vector.
 
 @param[in] str A string of a file path to a list of words to ignore.
 */
void read_filter_list(std::string str);

void process_input(std::string to_process, bool load);
void read_filter_list(const char* file);
std::string get_all_area_commands();
std::string valid_item_command_inv(Item * temp_item, int item);
std::string valid_item_command_area(Item* temp_item, int items);
std::string get_all_item_commands();
void external_output(std::string command);

//------------------------------------------------------------------------------
/* Method Definitions */
//------------------------------------------------------------------------------

void print_world_tree() {
    std::ostringstream sin;
    sin << "World:\n";
    for(int area = 0; area < world->get_num_areas(); area++) {
        Area *temp_area = world->get_area(area);
        sin << "\tArea: ";
        sin << temp_area->get_id();
        sin << "\n";
        for(int state_desc = 0; state_desc < temp_area->get_num_descriptions(); state_desc++) {
            StateDescriptor *temp_desc = temp_area->get_descriptor(state_desc);
            sin << "\t\tDesc: ";
            sin << temp_desc->get_description();
            sin << "\n";
        }
        for(int command = 0; command < temp_area->get_num_commands(); command++) {
            AreaCommand *temp_command = temp_area->get_command(command);
            sin << "\t\tCommand: ";
            sin << temp_command->get_name();
            sin << "\n\t\t\t";
            sin << temp_command->get_message();
            sin << "\n";
        }
        for(int item = 0; item < temp_area->get_num_items(); item++) {
            Item *temp_item = temp_area->get_item(item);
            sin << "\t\tItem:";
            sin << temp_item->get_id();
            sin << "\n";
            for(int state_desc = 0; state_desc < temp_item->get_num_descriptions(); state_desc++) {
                StateDescriptor *temp_desc = temp_item->get_descriptor(state_desc);
                sin << "\t\t\tDesc: ";
                sin << temp_desc->get_description();
                sin << "\n";
            }
            for(int command = 0; command < temp_item->get_num_commands(); command++) {
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

void process_input(std::string line, bool load) {
    commandList.push_back(line);
    std::ostringstream commandstream;
    std::string command1 , command2, command3;
    std::string checkmorewords;
    std::istringstream iss(line);
    if(iss >> command1) {
        if (iss >> command2) {
            if(!(iss >> command3)) {
                commandstream << two_word_command(command1 ,command2);
            }
            else if(!(iss >> checkmorewords)){
                std::stringstream s2;
                s2 << command1 << " " << command2 << " " << command3;
                checkmorewords = s2.str();
                commandstream << three_word_command(checkmorewords);
            } else {
                std::cout << TOOMANYWORDS << std::endl;
            }    
        } else {
            std::string from_one_word = one_word_command(command1);
            commandstream << from_one_word;
        }
    }
    else {
        std::cout << TOOMANYWORDS << std::endl;
    }
    if(!load){
        std::cout << "\n" << commandstream.str() << std::endl;
    }
}

/* 
 * Return all possible area commands availiable for the current state of the world
 *
 * @return string containing all availiable area commando on one line each
 *
 * */

std::string get_all_area_commands(){
	std::string commands;
	for(int ac = 0; ac < world->get_active_area()->get_num_commands(); ac++){
        AreaCommand *temp_area_command = world->get_active_area()->get_command(ac);
        assert(temp_area_command != NULL);
		if(world->get_area(INVENTORY)->has_item(temp_area_command->get_depends()) ||
           !strcmp(temp_area_command->get_depends().c_str(), NONE)) {
			if(!temp_area_command->is_locked()) {
				commands += temp_area_command->get_name();
				commands += "\n";
			}
		}
        
	}
	return commands;
    
}

std::string valid_item_command_inv(Item * temp_item, int item){
    std::string command_output = "";
    for(int i = 0; i < temp_item->get_num_commands(); i++){
        ItemCommand * temp_item_command= temp_item->get_command(i);
        assert(temp_item_command != NULL);
        if(temp_item_command->get_collect_dependent() == temp_item->is_collectable()) {
            command_output += temp_item_command->get_name();
            command_output +=" "; 
            command_output += temp_item->get_name();
            command_output += "\n";	
        }
    }
	return command_output;
    
    
}

std::string valid_item_command_area(Item* temp_item, int items){
	std::string command_output = "";
	unsigned int pv;
	if(world->get_area(INVENTORY)->has_item(world->get_active_area()->get_item(temp_item->get_id(),pv)->get_depends()) ||
       !strcmp(world->get_active_area()->get_id().c_str(), world->get_active_area()->get_item(temp_item->get_id(),pv)->get_depends().c_str()) ||
       !strcmp(world->get_active_area()->get_item(temp_item->get_id(),pv)->get_depends().c_str(), NONE)){
		
		for(int i = 0; i < temp_item->get_num_commands(); i++){
			ItemCommand * temp_item_command = temp_item->get_command(i);
			assert(temp_item_command != NULL);
			if(world->get_area(INVENTORY)->has_item(temp_item_command->get_depends()) ||
               !strcmp(world->get_active_area()->get_id().c_str(), temp_item_command->get_depends().c_str()) ||
               !strcmp(temp_item_command->get_depends().c_str(), NONE)) {
				if(temp_item_command->get_collect_dependent() == temp_item->is_collectable()) {
					if(temp_item_command->unlocks()) {
						if(temp_item_command->get_unlock_string().find_first_of('/') == std::string::npos){
							std::string temp_item_id = temp_item_command->unlock_area_string(); 
							if(world->get_active_area()->has_item(temp_item_id) || 
                               world->get_area(INVENTORY)->has_item(temp_item_id)){
								command_output += temp_item_command->get_name();
								command_output += " ";
								command_output += temp_item->get_name();
								command_output += "\n";	 
							}
						}else if(!temp_item_command->unlock_area_string().compare(world->get_active_area()->get_id()))
						{
							command_output += temp_item_command->get_name();
							command_output += " ";
							command_output += temp_item->get_name();
							command_output += "\n";	 
						}
					} else {
						command_output += temp_item_command->get_name();
						command_output += " ";
						command_output += temp_item->get_name();
						command_output += "\n";	 
					}
				}
			}
		}
	}
	return command_output;
}

/* :
 * Return all the possible commands availiable for the current stage the world
 *
 * @return string containing each availiable command on one line each
 *
 */

std::string get_all_item_commands(){
	std::stringstream itemstream;
	std::string command_output = "";
	for(int item = 0; item < world->get_area(INVENTORY)->get_num_items(); item++){
		Item* temp_item = world->get_area(INVENTORY)->get_item(item);
		assert(temp_item != NULL);
		command_output += valid_item_command_inv(temp_item, item);
        if(!temp_item->is_locked() && temp_item->has_container()){
            command_output += "put item ";
			command_output += temp_item->get_name();
			command_output += "\n";
            for(int item_in_item = 0; item_in_item < temp_item->get_num_items(); item_in_item++){
				Item * within = temp_item->get_item(item_in_item);
				command_output += valid_item_command_area(within,item_in_item);
            }
        } 
        combine * temp_combine = temp_item->get_combine();
        if(temp_combine != NULL){
            std::cout << temp_combine->get_first_id()<< "   " << temp_combine->get_second_id() << std::endl;
            command_output += "combine ";
            command_output +=  temp_combine->get_first_id();
            command_output += " ";
			command_output +=  temp_combine->get_second_id();
			command_output += "\n";
            
            
        }
	}
	for(int items = 0; items < world->get_active_area()->get_num_items(); items++){
        Item * temp_item = world->get_active_area()->get_item(items);
		command_output += valid_item_command_area(temp_item, items);
        if(!temp_item->is_locked() && temp_item->has_container()){
            command_output += "put item ";
			command_output += temp_item->get_name();
			command_output += "\n";
            for(int item_in_item = 0; item_in_item < temp_item->get_num_items(); item_in_item++){
				Item * within = temp_item->get_item(item_in_item);
				command_output += valid_item_command_area(within,item_in_item);
            }
        }
	}
	return command_output;
}

void external_output(std::string command){
	std::stringstream print;
    
    std::cout << "{";
    std::cout << "\"response\": \"";
    process_input(command, false);
    std::cout << "\",";
	std::cout << "\"inventory\": [";
	for(int items = 0; items < world->get_area(INVENTORY)->get_num_items(); items++) {
        std::cout << "{\"name\":\"" << world->get_area(INVENTORY)->get_item(items)->get_name() << "\",";
        std::cout << "\"description\":\"" << world->get_area(INVENTORY)->get_item(items)->get_description() << "\"},";
	}
	std::cout << "],";
	std::cout << "\"areaname\": \"" << world->get_active_area()->get_area_name() << "\",";
	std::cout << "\"areadescription\": \"" << world->get_active_area()->get_description() << "\"";
        std::cout << "\"commandlist\": [";
        std::cout << get_all_item_commands();
        std::cout << get_all_area_commands();
	std::cout << "}";
}

void gameloop() {
    std::string last_area = DEFAULT_VALUE;
    while(!game_over) {
        std::ostringstream sin;
        if(last_area.compare(world->get_active_area()->get_id()) != 0) {
            last_area = world->get_active_area()->get_id();
            sin << world->get_active_area()->get_description();
            if(!strcmp(world->get_active_area()->get_status().c_str(), WIN) || !strcmp(world->get_active_area()->get_status().c_str(), DIE)) {
                game_over = true;
            }
            std::cout << word_wrap(sin.str())<<std::endl;
        }
        if(!game_over) {
            std::cout << ">>";
            std::string line;
            std::getline(std::cin, line);
            line = input_filter(line);
            process_input(line, false);
        }
    }
}

std::string two_word_command(std::string command1, std::string command2) {
    std::ostringstream result;
    std::transform(command1.begin(), command1.end(),
                   command1.begin(), ::tolower);
    std::transform(command2.begin(), command2.end(),
                   command2.begin(), ::tolower);
    std::vector<std::string> containers_in_area;
    if(!strcmp(command1.c_str(), GO)) {
        return one_word_command(command2);
    }
    unsigned int item =-1 ;
    Item *temp_item = world->get_active_area()->get_item(command2, item);
    if(temp_item != NULL) {
        if(world->get_area(INVENTORY)->has_item(temp_item->get_depends()) ||
           !strcmp(world->get_active_area()->get_id().c_str(), world->get_active_area()->get_item(temp_item->get_id(),item)->get_depends().c_str()) ||
           !strcmp(world->get_active_area()->get_item(temp_item->get_id(),item)->get_depends().c_str(), NONE)){
            ItemCommand *temp_item_command = temp_item->get_command(command1);
            if(temp_item_command != NULL) {
                if(world->get_area(INVENTORY)->has_item(temp_item_command->get_depends()) ||
                   !strcmp(world->get_active_area()->get_id().c_str(), temp_item_command->get_depends().c_str()) ||
                   !strcmp(temp_item_command->get_depends().c_str(), NONE)) {
                    if(temp_item_command->get_collect_dependent() == temp_item->is_collectable()) {
                        if(!strcmp(temp_item_command->get_status().c_str(), WIN)||
                           !strcmp(temp_item_command->get_status().c_str() ,DIE)) {
                            game_over = true;
                        }
                        temp_item->state_change(temp_item_command->get_state_change());
                        temp_item->change_collectable(temp_item_command->get_change_collect());
                        if(temp_item_command->unlocks()) {
                            if(temp_item_command->get_unlock_string().find_first_of('/') == std::string::npos){
                                std::string temp_item_id = temp_item_command->unlock_area_string();
                                if(world->get_active_area()->has_item(temp_item_id)){
                                    unsigned int this_is_pointless = 0;
                                    world->get_active_area()->get_item(temp_item_id, this_is_pointless)->flip_locked();
                                } else if(world->get_area(INVENTORY)->has_item(temp_item_id)){
                                    unsigned int this_is_pointless = 0;
                                    world->get_area(INVENTORY)->get_item(temp_item_id, this_is_pointless)->flip_locked();
                                } else {
                                    std:: cout << "congrats you found a bug";
                                }
                            } else {
                                if(!temp_item_command->unlock_area_string().compare(world->get_active_area()->get_id())) {
                                    world->get_active_area()->unlock(temp_item_command->unlock_areacommand_string());
                                }
                                else {
                                    return "You can't do that. \n";
                                }
                            }
                        }
                        world->get_active_area()->remove_item(temp_item->get_id());
                        if(world->get_area(temp_item_command->get_area_change()) != NULL) {
                            world->get_area(temp_item_command->get_area_change())->add_item(temp_item);
                        }
                        else {
                            world->get_active_area()->add_item(temp_item);
                        }    
                        result << temp_item_command->get_message();
                        result << "\n";
                        return result.str();
                    }
                }
                else {
                    return "You can't do that.\n";
                }
            }
            else {
                //Command does not exist for that item.
                result << "There is no command ";
                result << command1;
                result << " for item ";
                result << command2;
                return result.str();
            }
        }
    }
    temp_item = NULL;
    temp_item = world->get_area(INVENTORY)->get_item(command2, item);
    if(temp_item != NULL) {
        
        ItemCommand *temp_item_command = temp_item->get_command(command1);
        if(temp_item_command != NULL) {
            if(temp_item_command->get_collect_dependent() == temp_item->is_collectable()) {
                if(!strcmp(world->get_active_area()->get_status().c_str(),WIN)||!strcmp(world->get_active_area()->get_status().c_str() ,DIE)) {
                    game_over = true;
                }
                temp_item->state_change(temp_item_command->get_state_change());
                temp_item->change_collectable(temp_item_command->get_change_collect());
                if(temp_item_command->unlocks()) {
                    if(temp_item_command->get_unlock_string().find_first_of('/') == std::string::npos){
                        std::string temp_item_id = temp_item_command->unlock_area_string();
                        unsigned int unknown = 0;
                        if(world->get_active_area()->has_item(temp_item_id)){
                            world->get_active_area()->get_item(temp_item_id, unknown)->flip_locked();
                        } else if(world->get_area(INVENTORY)->has_item(temp_item_id)){
                            world->get_area(INVENTORY)->get_item(temp_item_id, unknown)->flip_locked();
                        } else {
                            std:: cout << "You cant do that\n";
                        }
                    } else {
                        if(!temp_item_command->unlock_area_string().compare(world->get_active_area()->get_id())) {
                            world->get_active_area()->unlock(temp_item_command->unlock_areacommand_string());
                        }
                        
                        else {
                            return "You can't do that. \n";
                        }
                    }
                }
                world->get_area(INVENTORY)->remove_item(temp_item->get_id());
                if( world->get_area(temp_item_command->get_area_change()) !=NULL) {
                    world->get_area(temp_item_command->get_area_change())->add_item(temp_item);
                }
                else {
                    world->get_active_area()->add_item(temp_item);
                }
                
                result << temp_item_command->get_message();
                result << "\n";
                return result.str();
            }
        }
        else {
            
            result << "There is no command ";
            result << command1;
            result << " for item ";
            result << command2;
            return result.str();
        }
    }
    return "I don't understand that. \n";
}

std::string three_word_command(std::string command){
    std::transform(command.begin(), command.end(),
                   command.begin(), ::tolower);
    std::stringstream word(command);
    std::string first_id;
    std::string second_id;
    std::string action;
    word >> action >>first_id >>second_id;
    if(!action.compare(COMBINE) || !action.compare(MIX)) {
        unsigned int item_1;
        unsigned int item_2;
        Item * have_item_1 = world->get_area(INVENTORY)->get_item(first_id,item_1);
        Item * have_item_2 = world->get_area(INVENTORY)->get_item(second_id,item_2);
        if(have_item_2 != NULL  && have_item_1 != NULL){
            combine * temp_combine;
            if(have_item_1->has_combine()){
                std::string id_combine = have_item_2->get_id();
                temp_combine = have_item_1->get_combine();
                if(!temp_combine->get_second_id().compare(id_combine)){
                    world->get_area(GARBAGE)->add_item(have_item_2);
                    world->get_area(GARBAGE)->add_item(have_item_1);
                    world->get_area(INVENTORY)->remove_item(have_item_2->get_id());
                    world->get_area(INVENTORY)->remove_item(have_item_1->get_id());
                    world->get_area(INVENTORY)->add_item(temp_combine->get_combination());
                    return temp_combine->get_description() + "\n";
                }
            } 
            else if(have_item_2->has_combine()){
                std::string id_combine = have_item_2->get_id();
                temp_combine = have_item_2->get_combine();
                if(!temp_combine->get_first_id().compare(id_combine)){
                    world->get_area(GARBAGE)->add_item(have_item_2);
                    world->get_area(GARBAGE)->add_item(have_item_1);
                    world->get_area(INVENTORY)->remove_item(have_item_1->get_id());
                    world->get_area(INVENTORY)->remove_item(have_item_2->get_id());
                    world->get_area(INVENTORY)->add_item(temp_combine->get_combination());
                    return temp_combine->get_description() + "\n";
                }
                else {
                    return	"no combine information found for these two items\n";
                }
            } else {
                return "no combine information found for these two items\n";
            }
        } else {
            return "One or more item names incorrect for combine \n";
        }
    } else if(!action.compare(PUT) || !action.compare(STORE)){
        unsigned int item;
        unsigned int item2;
        Item * have_item = world->get_area(INVENTORY)->get_item(first_id,item);
        if(have_item != NULL){
            Item* box = world->get_area(INVENTORY)->get_item(second_id,item2);
            if(box == NULL) {
                box = world->get_active_area()->get_item(second_id,item2);
            }
            if(box != NULL){
                if(box->has_container()){
                    if(!box->is_locked()){
                        box->add_item(have_item);
                        world->get_area(INVENTORY)->remove_item(item);
                        std::stringstream ss;
                        ItemCommand *temp_item_command = have_item->get_command("drop");
                        if(temp_item_command != NULL) {
                            have_item->state_change(temp_item_command->get_state_change());
                            
                        } else {
                            ss << "BUG: \n";
                            ss << "There is no drop command in XML for that item.";
                            ss << " so description hasn't changed. Item still moved.\n";
                        }
                        ss <<"You put the "<< first_id << " in the " << second_id << "\n"; 
                        have_item->change_collectable(true);
                        return ss.str();
                    }
                    return "The box is locked";
                }
                return "this item has no storage";
            }
            return "second item is not in inventory or the area you are in. \n";
        }		
        return "I don't understand that. \n";
    }
    return "I don't understand that. \n";
}

std::string one_word_command(std::string command) {
    std::transform(command.begin(), command.end(),
                   command.begin(), ::tolower);
    
    if(!command.compare(HELP)) {
        return HELP_COMMAND;
    }
    if(!command.compare(N)) {
        command = NORTH;
    }
    if(!command.compare(S)) {
        command = SOUTH;
    }
    if(!command.compare(E)) {
        command = EAST;
    }
    if(!command.compare(W)) {
        command = WEST;
    }
    if(!command.compare(QUIT)) {
        game_over = true;
        return DEFAULT_VALUE;
    }
    
    if(!command.compare(LOOK)) {
        std::stringstream itemstream;
        std::string combinelist;
        for(int items = 0; items < world->get_active_area()->get_num_items(); items++) {
            if(world->get_area(INVENTORY)->has_item(world->get_active_area()->get_item(items)->get_depends()) ||
               !strcmp(world->get_active_area()->get_id().c_str(), world->get_active_area()->get_item(items)->get_depends().c_str()) ||
               !strcmp(world->get_active_area()->get_item(items)->get_depends().c_str(), NONE)){
                itemstream << world->get_active_area()->get_item(items)->get_description();
                if(world->get_active_area()->get_item(items)->has_container() &&
                   !world->get_active_area()->get_item(items)->is_locked()){
                    combinelist+= ((world->get_active_area()->get_item(items)->print_contained_items()));
                    
                    combinelist +="\n";
                }
                itemstream << "\n"; 
            } 
        }
        std::stringstream sSs;
        sSs << word_wrap(itemstream.str())<< std::endl << combinelist;
        return sSs.str();
    }
    if (!command.compare(SAVE)) {
        std::cout << "Please enter a save filename: " << std::endl;
        std::string filename;
        getline(std::cin, filename);
        save((char* const)filename.c_str());
        return "saved";
    }
    else if(!command.compare(BAG)) {
        print_inventory();
        return "";
    }
    else if(!command.compare(INVENTORY)) {
        print_inventory();
        return "";
    }
    AreaCommand *temp_area_command = world->get_active_area()->has_command(command);
    if(temp_area_command != NULL) {
        if(world->get_area(INVENTORY)->has_item(temp_area_command->get_depends()) ||
           !strcmp(temp_area_command->get_depends().c_str(), NONE)) {
            if(!temp_area_command->is_locked()) {
                world->change_area(temp_area_command->get_area());
                return temp_area_command->get_message();
            }
            return "That way is locked";
        }
        else {
            return "You can't do that.\n";
        }
    }
    else {
        return "I don't understand that. \n";
    }
    
}

void print_inventory() {
    std::ostringstream sin;
    int num = 1;
    sin << "INVENTORY: \n" ;
    std::string inv = INVENTORY;
    for(int items = 0; items < world->get_area(inv)->get_num_items(); items++) {
        sin << num++ << " = " << world->get_area(INVENTORY)->get_item(items)->get_description();
        if(items  < world->get_area(inv)->get_num_items() - 1) {
            sin << "\n";
        }
    }
    
    std::cout << "\n" <<  sin.str();
    
}

std::string word_wrap(std::string input_string) {
    
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

void load(char* const file) {
    std::ifstream myfile (file);
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            std::string line;
            getline (myfile,line);
            process_input(line, true); // true because we are loading.
        }
        myfile.close();
    }
}

void save(char* const file) {
    std::ofstream saveFile;
    saveFile.open(file);
    for (unsigned int i=0; i < commandList.size(); i++) {
        if(commandList[i].compare(SAVE))
            saveFile << commandList[i] << std::endl;
    } 
    saveFile.close();
}

std::string input_filter(std::string str){
    std::istringstream iss(str);
    std::string ret ="";
    std::string word;
    while (iss >> word) {
        bool contains = false;
        for(unsigned int i = 0; i < filterList.size(); i++){
            if(word==filterList[i]) contains = true; 
        }
        if(!contains) ret += word + " ";
    }
    return ret;
}

/**
 Reads in words from file to filterList
 vector.
 
 */
void read_filter_list(const char* file){
    std::ifstream myfile (file);
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            std::string line;
            getline (myfile,line);
            filterList.push_back(line);
        }
        myfile.close();
    }else{
        std::cout << IGNORELISTERROR << std::endl;
    }
}

int main(int argc, char** argv) {
    std::string userinput;
    if(argc == 1) {
        std::cout << "Usage:\n txtgame input-file [save-file]" << std::endl;
    } else if (strstr(argv[1], "-exec") && argc == 5) {
        world = read_file(argv[2], world);
        
        if(world != NULL) {
            load(argv[3]);
            external_output(argv[4]);
            save(argv[3]);
        }
    } else if(argc > 1) {
        do {
            world = read_file(argv[1], world);
            if(world != NULL) {
                //Debug Only
                // print_world_tree();
                const char *file_f = (IGNORELIST);
                read_filter_list(file_f);
                if (argc > 2)
                    load(argv[2]);
                gameloop();
                delete world;
                std::cout << "Would you like to play again? (please enter yes for affirmative)" << std::endl;
                std::getline (std::cin,userinput);
                game_over = true;
                if(!userinput.compare("yes") || !userinput.compare("y")) {
                    game_over = false;
                }
            }
            else {
                game_over = true;
            }
        } while (!game_over);
    } 
    return 0;
}
