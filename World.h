#ifndef _WORLD_H
#define _WORLD_H
#include "Area.h"
#include <string>
#include <vector>


class World{
 protected:
   std::string language;
   std::string author;
   std::vector<Area*> areas;
   std::string initial_area;
   int num_areas;
   Area *active_area;
 public:
   std::string get_author();
   std::string get_language();
   Area* get_active_area();
 
   Area *get_area(int index);
   void add_area(Area *new_area);
   int get_num_areas();
   Area *get_area(std::string area_id);
   bool init_active_area();
   void change_area(std::string name);
   World(const char *lang, const char *auth, const char *init_area);
   ~World();   
};

#endif
