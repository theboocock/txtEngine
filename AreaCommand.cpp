/**
 * @file AreaCommand.cpp
 * Provides the functionality for an AreaCommand in the game.
 *
 * @brief Source file for area command functionality.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#include "AreaCommand.h"

AreaCommand::AreaCommand(const char * callmeby, const char * areatomoveto,
                         const char * status_command, const char * depends_command,
                         std::vector<std::string> *syns, bool lock) {
    name = callmeby;
    depends = depends_command;
    status   = status_command;
    move_to_area= areatomoveto;
    message = "";
    synonyms = syns;
    locked = lock;
    }
std::string AreaCommand::get_depends() {
    return depends;
    }
AreaCommand::~AreaCommand() {
   if(synonyms!=NULL){
      delete synonyms;
   }
}
std::string AreaCommand::get_status() {
    return status;
    }
std::string AreaCommand::get_name() {
    return name;
    }
std::string AreaCommand::get_area() {
    return move_to_area;
    }
std::string AreaCommand::get_message() {
    return message;
    }
void AreaCommand::set_message(const char *to_message) {
    message = to_message;
    }
bool AreaCommand::find(std::string to_find) {
    if(!to_find.compare(name)) {
        return true;
        }
    else {
        return false;
        }
    }

void AreaCommand::unlock() {
    locked = false;
    }

bool AreaCommand::is_locked() {
    return locked;
    }

bool AreaCommand::has_synonym(std::string item) {
   std::vector<std::string>& synonymsRef = *synonyms;
   if(synonyms == NULL) {
      return false;
   }
   for(unsigned int count = 0; count < synonyms->size(); count++) {
      if(synonymsRef[count].compare(item) == 0) {
         return true;
      }
   }
   return false;
}
