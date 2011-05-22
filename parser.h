#ifndef _PARSER_H
#define _PARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include "tinyxml.h"
#include "World.h"


extern void error_parsing(std::string error_string, World *world);
extern ItemCommand *make_item_command(TiXmlNode *pCommand, const char *parent_id, World *world);
extern AreaCommand *make_area_command(TiXmlNode *pCommand, const char *parent_id, World *world);
extern StateDescriptor *make_state_descriptor(TiXmlNode *pDescription,
                                       const char *parent_id, World *world);
extern Area *make_area(TiXmlNode *pArea, int area_index, World *world);
extern World *make_world(TiXmlNode *pParent, World *world);
extern World *make_objects( TiXmlNode* pParent, World *world);
extern World *read_file(const char* pFilename, World *world);

#endif
