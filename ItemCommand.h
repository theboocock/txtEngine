#ifndef _ITEM_COMMAND_H
#define _ITEM_COMMAND_H

class ItemCommand{
 protected:
   std::String name;
   std::String id;
   std::String state_change;
   std::String message;
   
 public:
   Command(const char * callmeby, const char * identifier, const char * state_mutator){
      name = callmeby;
      id   = identifier;
      state_change = state_mutator;
      message = "";
   }
   ~Command(){}
   std::String get_id(){
      return id;
   }
   std::String get_name(){
      return name;
   }
   std::String get_statechange(){
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
