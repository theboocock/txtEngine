/**
 * @file ItemCommand.cpp
 * Provides the functionality for an ItemCommand.
 *
 * @brief Source file for an ItemCommand.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#include "ItemCommand.h"
#include <iostream>

ItemCommand::ItemCommand(const char * callmeby, const char * state_mutator,
                         bool chng_collec, bool collec_dep, const char *area_chng,
                         const char* status_command, const char* depends,
                         std::vector<std::string> *syns, std::string unlocks, bool combine) {
   this->call_combine = combine;
   name = callmeby;
   this->depends = depends;
   state_change = state_mutator;
   area_change = area_chng;
   change_collect = chng_collec;
   collect_dependent = collec_dep;
   status = status_command;
   message = "";
   synonyms = syns;
   unlock = unlocks;
}

bool ItemCommand::is_combine(){
   return call_combine;
}


std::string ItemCommand::get_depends() {
   return depends;
}

bool ItemCommand::get_change_collect() {
   return change_collect;
}

bool ItemCommand::get_collect_dependent() {
   return collect_dependent;
}

std::string ItemCommand::get_area_change() {
   return area_change;
}

std::string ItemCommand::get_status() {
   return status;
}

ItemCommand::~ItemCommand() {
   if(synonyms!=NULL){
      delete synonyms;
   }
}
std::string ItemCommand::get_message() {
   return message;
}

std::string ItemCommand::get_name() {
   return name;
}

std::string ItemCommand::get_state_change() {
   return state_change;
}

void ItemCommand::set_message(const char *to_message) {
   message = to_message;
}

bool ItemCommand::check_synonyms(std::string command) {
   std::vector<std::string>& synonymsRef = *synonyms;
   if(synonyms == NULL) {
      return false;
   }
   for(unsigned int count = 0; count < synonyms->size(); count++) {
      if(!synonymsRef[count].compare(command)) {
         return true;
      }
   }
   return false;
}

bool ItemCommand::unlocks() {
   if(unlock.compare(NONE)==0) {
      return false;
   }
   return true;
}

std::string ItemCommand::unlock_area_string() {
   size_t found;
   found = unlock.find_first_of('/');
   return unlock.substr(0,found);
}

std::string ItemCommand::unlock_areacommand_string() {
   size_t found;
   found = unlock.find_first_of('/');
   return unlock.substr(found + 1, unlock.size());
}

std::string ItemCommand::get_unlock_string(){
   return unlock;
}
