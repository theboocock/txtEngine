/**
 * @file Parser.h
 * Parser.h defines the methods for the Parser.cpp source file.
 *
 * @brief Defines the parser class.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#ifndef _PARSER_H
#define _PARSER_H

//------------------------------------------------------------------------------
/* Include */
//------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <string>
#include "tinyxml.h"
#include "World.h"

/**
   Formats the output to wrap correctly.

   @param[in] str The string to be formatted.
   @param[in] seperator Separator to break the string by.
   @param[out] result Pointer to a vector of strings.
*/
void string_explode(std::string str, std::string seperator, std::vector<std::string> *&result);

/**
   Write description of function here.
   The function should follow these comments.
   Use of "brief" tag is optional. (no point to it)

   The function arguments listed with "param" will be compared
   to the declaration and verified.

   @param[in] error_string An error message to be displayed.
   @param[in] world A pointer to THE world object.
*/
extern void error_parsing(std::string error_string, World *world);

/**
  Creates an item command object from XML.

   @param[in] pCommand Pointer to a TinyXML Node.
   @param[in] parent_id A pointer to the parent id of the parent node.
   @param[in] world A pointer to THE world object.
   @return An ItemCommand object.
*/
extern ItemCommand *make_item_command(TiXmlNode *pCommand,
                                      const char *parent_id, World *world);

/**
  Creates an AreaCommand object from XML.

   @param[in] pCommand Pointer to a TinyXML Node.
   @param[in] parent_id A pointer to the parent id of the parent node.
   @param[in] world A pointer to THE world object.
   @return An AreaCommand object.
*/
extern AreaCommand *make_area_command(TiXmlNode *pCommand,
                                      const char *parent_id, World *world);

/**
  Creates a StateDescriptor object from XML.

   @param[in] pDescription Pointer to a TinyXML Node.
   @param[in] parent_id A pointer to the parent id of the parent node.
   @param[in] world A pointer to THE world object.
   @return A StateDescriptor object.
*/
extern StateDescriptor *make_state_descriptor(TiXmlNode *pDescription,
        const char *parent_id, World *world);

/**
  Creates an Area object from XML.

   @param[in] pArea Pointer to a TinyXML Node.
   @param[in] area_index The index of the area inside world's vector of areas.
   @param[in] world A pointer to THE world object.
   @return An Area object.
*/
extern Area *make_area(TiXmlNode *pArea, int area_index, World *world);

/**
  Creates a World object from XML.

   @param[in] pParent Pointer to a TinyXML Node.
   @param[in] world A pointer to THE world object.
   @return A World object.
*/
extern World *make_world(TiXmlNode *pParent, World *world);

/**
  Starts making the objects for the game.

   @param[in] pParent Pointert to a TinyXML Node.
   @param[in] world Pointer to THE world object.
   @return A World object.
*/
extern World *make_objects( TiXmlNode* pParent, World *world);

/**
   Method to handle reading in the XML game file.

   @param[in] pFilename Path and file name of the game file to read.
   @param[in] world A pointer to a world object.
   @return A world object.
*/
extern World *read_file(const char* pFilename, World *world);

/**
  Creates a combine object for the game.

   @param[in] pCommand Pointer to a TinyXML node.
   @param[in] parent_id The id of the parent node.
   @param[in] world Pointer to the world object
   @return A combine object.
*/
extern combine *make_combine(TiXmlNode *pCommand, const char * parent_id, World *world);

/**
 Creates an item ovject for the game.

   @param[in] pItem Pointer to a TinyXML node.
   @param[in] parent_id The id of the parent node.
   @param[in] world Pointer to the world object.
   @return An Item object.
*/
extern Item *make_item(TiXmlNode *pItem, const char *parent_id, World *world);
#endif
