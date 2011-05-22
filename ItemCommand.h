#ifndef _ITEM_COMMAND_H
#define _ITEM_COMMAND_H

#include <string>

class ItemCommand{
 protected:
   std::string name;
   std::string state_change;
   std::string message;
   std::string area_change;
   bool change_collect, collect_dependent;
   
 public:
   ItemCommand(const char * callmeby, const char * state_mutator,
               bool chng_collec, bool collec_dep, const char *area_chng){
      name = callmeby;
      state_change = state_mutator;
      area_change = area_chng;
      change_collect = chng_collec;
      collect_dependent = collec_dep;
      message = "";
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
