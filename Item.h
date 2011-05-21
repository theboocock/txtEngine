#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include "BaseContainer.h"

class Item : public BaseContainer{
 protected:
   bool collectable;
 public:
   bool is_collectable(){
      return collectable;
   }
 Item(bool collect, const char *id): BaseContainer(id){
      collectable = collect;
   }
};


#endif
