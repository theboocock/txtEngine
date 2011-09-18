#include "World.h"

std::string World::get_author() {
    return author;
    }
std::string World::get_language() {
    return language;
    }
Area* World::get_active_area() {
    return active_area;
    }
Area* World::get_area(int index) {
    return areas[index];
    }
void World::add_area(Area *new_area) {
    areas.push_back(new_area);
    num_areas++;
    }
int World::get_num_areas() {
    return num_areas;
    }
Area *World::get_area(std::string area_id) {
    for(unsigned int area_num = 0; area_num < areas.size(); area_num++) {
        if(areas[area_num]->get_id().compare(area_id) == 0) {
            return areas[area_num];
            }
        }
    return NULL;
    }
bool World::init_active_area() {
    for(unsigned int area_num = 0; area_num < areas.size(); area_num++) {
        if(areas[area_num]->get_id().compare(initial_area) == 0) {
            active_area = areas[area_num];
            return true;
            }
        }
    return false;
    }
void World::change_area(std::string name) {
    for(unsigned int area_num = 0; area_num < areas.size(); area_num++) {
        if(areas[area_num]->get_id().compare(name) == 0) {
            active_area = areas[area_num];
            }
        }
    }
World::World(const char *lang, const char *auth, const char *init_area) {
    language = lang;
    author = auth;
    initial_area = init_area;
    num_areas = 0;
    Area* inventory = new Area("inventory","","");
    Area* garbage = new Area("garbage","","");
    add_area(inventory);
    add_area(garbage);

    }
World::~World() {
    for(unsigned int area_num = 0; area_num < areas.size(); area_num++) {
        delete areas[area_num];
        }
    }


