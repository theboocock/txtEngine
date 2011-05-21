#ifndef _AREA_H
#define _AREA_H
#include <string>
#include <vector>
#include "BaseContainer.h"
#include "Item.h"
#include "Variable.h"

class Area : public BaseContainer{
 protected:
   std::vector<Item> items;
   std::vector<Variable> variables;
   int num_items;
 public:
   void add_item(Item new_item){
      items.push_back(new_item);
      num_items++;
   }
   void add_variable(Variable new_var){
      variables.push_back(new_var);
   }
   bool has_item(std::string item_to_find){
      for(unsigned int item_num = 0; item_num < items.size(); item_num++){
         if(items[item_num].get_id().compare(item_to_find) == 0){
            return true;
         }
      }
      return false;
   }
   Item *get_item(std::string item_to_get){
      for(unsigned int item_num = 0; item_num < items.size(); item_num++){
         if(items[item_num].get_id().compare(item_to_get) == 0){
            return &items[item_num];
         }
      }
      return NULL;
   }
   Area(const char *id) : BaseContainer(id){
      num_items = 0;
   }
};

#endif
