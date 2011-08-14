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

// $Id$
/**
 * @file Parser.h
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

#ifndef _PARSER_H
#define _PARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include "tinyxml.h"
#include "World.h"

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
extern void error_parsing(std::string error_string, World *world);

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
extern ItemCommand *make_item_command(TiXmlNode *pCommand,
                                         const char *parent_id, World *world);

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
extern AreaCommand *make_area_command(TiXmlNode *pCommand,
                                         const char *parent_id, World *world);

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
extern StateDescriptor *make_state_descriptor(TiXmlNode *pDescription,
                                       const char *parent_id, World *world);

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
extern Area *make_area(TiXmlNode *pArea, int area_index, World *world);

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
extern World *make_world(TiXmlNode *pParent, World *world);

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
extern World *make_objects( TiXmlNode* pParent, World *world);

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
extern World *read_file(const char* pFilename, World *world);

#endif
