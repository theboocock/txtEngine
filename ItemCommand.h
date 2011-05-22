#ifndef _ITEM_COMMAND_H
#define _ITEM_COMMAND_H

#include <string>

class ItemCommand{
 protected:
   std::string name;
   std::string id;
   std::string state_change;
   std::string message;
   
 public:
   ItemCommand(const char * callmeby, const char * identifier, const char * state_mutator){
      name = callmeby;
      id   = identifier;
      state_change = state_mutator;
      message = "";
   }
   ~ItemCommand(){}
   std::string get_id(){
      return id;
   }
   std::string get_name(){
      return name;
   }
   std::string get_statechange(){
      return state_change;
   }
   void set_message(const char *to_message){
      message = to_message;
   }
   bool find(std::string to_find){
      if(!to_find.compare(name)){
         return true;
      } else {
         return false;
      }
   }
   
};

#endif
