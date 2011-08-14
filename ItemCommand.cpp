#include "ItemCommand.h"

ItemCommand::ItemCommand(const char * callmeby, const char * state_mutator,
                         bool chng_collec, bool collec_dep, const char *area_chng,
                         const char* status_command, const char* depends,
                         std::vector<std::string> *syns){
   name = callmeby;
   this->depends = depends;
   state_change = state_mutator;
   area_change = area_chng;
   change_collect = chng_collec;
   collect_dependent = collec_dep;
   status = status_command;
   message = "";
   synonyms = syns;
}
std::string ItemCommand::get_depends(){
   return depends;
}
bool ItemCommand::get_change_collect(){
   return change_collect;
}
bool ItemCommand::get_collect_dependent(){
   return collect_dependent;
}
std::string ItemCommand::get_area_change(){
   return area_change;
}
std::string ItemCommand::get_status(){
   return status;
}
ItemCommand::~ItemCommand(){}
std::string ItemCommand::get_message(){
   return message;
}
std::string ItemCommand::get_name(){
   return name;
}
std::string ItemCommand::get_state_change(){
   return state_change;
}
void ItemCommand::set_message(const char *to_message){
   message = to_message;
}

bool ItemCommand::check_synonyms(std::string command){
   std::vector<std::string>& synonymsRef = *synonyms;
   if(synonyms == NULL){
      return false;
   }
   for(unsigned int count = 0; count < synonyms->size(); count++){
      if(!synonymsRef[count].compare(command)){
         return true;
      }
   } return false;   
}

