#ifndef _STATE_DESCRIPTOR_H
#define _STATE_DESCRIPTOR_H
#include <string>

class StateDescriptor{
 protected:
   std::string id;
   std::string description;

 public:
   StateDescriptor(const char *identifier);
   void set_description(const char *desc);
   ~StateDescriptor();
   std::string get_id();
   std::string get_description();
};

#endif
