#ifndef _WORLD_H
#include "Area.h"
#include <string>
#include <vector>

class World{
 protected:
   std::string language;
   std::string author;
   std::string id;
   std::vector<Area> areas;
   Area active_area;
 public:
   std::string get_id(){return id;}
   std::string get_author(){return author;}
   std::string get_language(){return language;}
   Area get_active_area(){return active_area;}
   void add_area(Area new_area){
      areas.push_back(new_area);
   }
   void change_area(std::string name){
      for(int area_num = 0; area_num < areas.size(); area_num++){
         if(areas[area_num].get_id().compare(name) == 0){
            active_area = areas[area_num];
         }
      }
   }
   std::string command(std::string command){
      Item item;
      if(active_area.has_item(command)){
         item = active_area.get_item(command);
      }
   }
   World(const char *lang, const char *auth, const char *id){
      this->language = lang;
      this->author = auth;
      this->id = id;
   }
};

#endif
