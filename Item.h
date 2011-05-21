#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>

class Item{
 protected:
   bool collectable;
   std::string id;
 public:
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
