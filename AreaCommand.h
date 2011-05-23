#ifndef _AREA_COMMAND_H
#define _AREA_COMMAND_H

#include<string>

class AreaCommand{
 protected:
   std::string name;
   std::string status;
   std::string message;
   std::string depends;
   std::string move_to_area;
   
 public:
   AreaCommand(const char * callmeby, const char * areatomoveto,const char * status_command, const char * depends_command){
      name = callmeby;
      depends = depends_command;
      status   = status_command;
      move_to_area= areatomoveto;
      message = "";
   }
   std::string get_depends(){
      return depends;
   }
   ~AreaCommand(){}
   std::string get_status(){
      return status;
   }
   std::string get_name(){
      return name;
   }
   std::string get_area(){
      return move_to_area;
   }
   std::string get_message(){
      return message;
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
