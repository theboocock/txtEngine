#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include "StateDescriptor.h"

class Item{
 protected:
   bool collectable;
   std::string id;
   StateDescriptor *description;
 public:
   void set_description(StateDescriptor *desc){
      description = desc;
   }
   bool is_collectable(){
      return collectable;
   }
   std::string get_id(){
      return id;
   }
 Item(bool collect, const char *id){
      collectable = collect;
      this->id = id;
   }
};


#endif
