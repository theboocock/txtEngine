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
   ItemCommand(const char * identifier,const char * callmeby, const char * state_mutator){
      name = callmeby;
      id   = identifier;
      state_change = state_mutator;
      message = "";
   }
   ~ItemCommand(){}
   std::string get_id(){
      return id;
   }
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
