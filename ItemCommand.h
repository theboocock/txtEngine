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
   std::vector<std::string>  synonyms;
   bool change_collect, collect_dependent;
   
 public:
   ItemCommand(const char * callmeby, const char * state_mutator,
               bool chng_collec, bool collec_dep, const char *area_chng,
               const char* status_command, const char* depends);
   std::string get_depends();
   bool get_change_collect();
   bool get_collect_dependent();
   std::string get_area_change();
   std::string get_status();
   ~ItemCommand();
   std::string get_message();
   std::string get_name();
   std::string get_state_change();
   bool check_synonyms(std::string command);
   void set_message(const char *to_message);
   
};

#endif
