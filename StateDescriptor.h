#ifndef _STATE_DESCRIPTOR_H
#define _STATE_DESCRIPTOR_H
#include <string>

class StateDescriptor{
 protected:
   std::string id;
   std::string switchable;
   std::string description;

 public:
   StateDescriptor(const char * a, const char * b){
      id = a;
      switchable = b;
   }
   ~StateDescriptor(){}
   
   std::string get_id(){
      return id;
   }
   std::string get_description(){
      return description;
   }
   
};

#endif
