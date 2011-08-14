// $Id$
/**
 * @file Area.h
 * Area.h defines the methods for the Area.cpp source file.
 *
 * @brief Defines the Area class.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */
// $Log$

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

   /**
   Write description of function here.
   The function should follow these comments.
   Use of "brief" tag is optional. (no point to it)
     
   The function arguments listed with "param" will be compared 
   to the declaration and verified.
     
   @param[in]     _inArg1 Description of first function argument.
   @param[out]    _outArg2 Description of second function argument.
   @param[in,out] _inoutArg3 Description of third function argument.
   @return Description of returned value.
*/
   std::string get_author();

   /**
   Write description of function here.
   The function should follow these comments.
   Use of "brief" tag is optional. (no point to it)
     
   The function arguments listed with "param" will be compared 
   to the declaration and verified.
     
   @param[in]     _inArg1 Description of first function argument.
   @param[out]    _outArg2 Description of second function argument.
   @param[in,out] _inoutArg3 Description of third function argument.
   @return Description of returned value.
*/
   std::string get_language();

   /**
   Write description of function here.
   The function should follow these comments.
   Use of "brief" tag is optional. (no point to it)
     
   The function arguments listed with "param" will be compared 
   to the declaration and verified.
     
   @param[in]     _inArg1 Description of first function argument.
   @param[out]    _outArg2 Description of second function argument.
   @param[in,out] _inoutArg3 Description of third function argument.
   @return Description of returned value.
*/
   Area* get_active_area();
 
   Area *get_area(int index);
   void add_area(Area *new_area);
   int get_num_areas();
   Area *get_area(std::string area_id);
   bool init_active_area();
   void change_area(std::string name);
   World(const char *lang, const char *auth, const char *init_area);

   /**
   Write description of function here.
   The function should follow these comments.
   Use of "brief" tag is optional. (no point to it)
     
   The function arguments listed with "param" will be compared 
   to the declaration and verified.
     
   @param[in]     _inArg1 Description of first function argument.
   @param[out]    _outArg2 Description of second function argument.
   @param[in,out] _inoutArg3 Description of third function argument.
   @return Description of returned value.
*/
   ~World();   
};

#endif
