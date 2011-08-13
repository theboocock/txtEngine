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
   AreaCommand(const char * callmeby, const char * areatomoveto,const char * status_command, const char * depends_command);
   std::string get_depends();
   ~AreaCommand();
   std::string get_status();
   std::string get_name();
   std::string get_area();
   std::string get_message();
   void set_message(const char *to_message);
   bool find(std::string to_find);
};

#endif
