#ifndef _ITEM_COMMAND_H
#define _ITEM_COMMAND_H

#include <string>

class ItemCommand{
 protected:
   std::string name;
   std::string state_change;
   std::string message;
   std::string area_change;
   std::string depends;
   std::string status;
   bool change_collect, collect_dependent;
   
 public:
   ItemCommand(const char * callmeby, const char * state_mutator,
               bool chng_collec, bool collec_dep, const char *area_chng,
               const char* status_command, const char* depends){
      name = callmeby;
      this->depends = depends;
      state_change = state_mutator;
      area_change = area_chng;
      change_collect = chng_collec;
      collect_dependent = collec_dep;
      status = status_command;
      message = "";
   }
   std::string get_depends(){
      return depends;
   }
   bool get_change_collect(){
      return change_collect;
   }
   bool get_collect_dependent(){
      return collect_dependent;
   }
   std::string get_area_change(){
      return area_change;
   }
   std::string get_status(){
      return status;
   }
   ~ItemCommand(){}
   std::string get_message(){
      return message;
   }
   std::string get_name(){
      return name;
   }
   std::string get_state_change(){
      return state_change;
   }
   void set_message(const char *to_message){
      message = to_message;
   }
   
};

#endif
