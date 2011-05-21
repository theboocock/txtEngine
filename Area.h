#ifndef _AREA_H
#define _AREA_H
#include <string>
#include <vector>
#include "Item.h"
#include "StateDescriptor.h"

class Area{
 protected:
   std::vector<Item> items;
   int num_items;
   std::string id;
   std::string curr_desc_id;
   std::vector<StateDescriptor> description;
 public:
   StateDescriptor get_description(){
      return description[0];
   }
   void add_item(Item new_item){
      items.push_back(new_item);
      num_items++;
   }
   std::string get_id(){
      return id;
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
   Area(const char *id, const char *desc){
      this->id = id;
      num_items = 0;
      this->curr_desc_id = desc;
   }
};

#endif
