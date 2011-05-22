#ifndef _AREA_COMMAND_H
#define _AREA_COMMAND_H

#include<string>

class AreaCommand{
 protected:
   std::string name;
   std::string id;
   std::string message;
   std::string move_to_area;
   
 public:
   AreaCommand(const char * identifier, const char * callmeby, const char * areatomoveto){
      name = callmeby;
      id   = identifier;
      move_to_area= areatomoveto;
      message = "";
   }
   ~AreaCommand(){}
   std::string get_id(){
      return id;
   }
   std::string get_name(){
      return name;
   }
   std::string get_area(){
      return move_to_area;
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
