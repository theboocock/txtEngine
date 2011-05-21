#ifndef _ITEM_H
#include <string>
#include <vector>
#include "BaseContainer.h"

class Item{
 protected:
   bool collectable = false;
 public:
   bool is_collectable(){
      return collectable;
   }
 Item(bool collectable, const char *id): BaseContainer(id){
      this->collectable = collectable;
   }
}


#endif
