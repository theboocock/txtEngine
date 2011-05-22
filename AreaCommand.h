#ifndef _AREA_COMMAND_H
#define _AREA_COMMAND_H

class AreaCommand{
 protected:
   std::String name;
   std::String id;
   std::String message;
   std::String move_to_area;
   
 public:
   Command(const char * callmeby, const char * identifier, const char * areatomoveto){
      name = callmeby;
      id   = identifier;
      move_to_area= areatomoveto;
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
      return stateChange;
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
