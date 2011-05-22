#include "parser.h"
#include "tinyxml.h"

#define WORLD_ATTRIBUTES 3
#define AREA_ATTRIBUTES 3
#define STATE_DESCRIPTION_ATTRIBUTES 1
#define ITEM_ATTRIBUTES 3
#define PARSING_ERROR 2
#define AREA_COMMAND_ATTRIBUTES 3
#define ITEM_COMMAND_ATTRIBUTES 5

World *read_file(const char* pFilename, World *world)
{
   TiXmlDocument doc(pFilename);
   bool loadOkay = doc.LoadFile();

   if (loadOkay)
      {
         printf("\n%s:\n", pFilename);
         return make_objects( &doc, world ); // defined later in the tutorial
      }
   else
      {
         printf("Failed to load file \"%s\"\n", pFilename);
         return NULL;
      }
}

ItemCommand *make_item_command(TiXmlNode *pCommand, const char *parent_id, World *world){
   TiXmlNode* pChild;
   const char *error_tag = "missing tags", *command_chg_col = "true",
      *command_name = "invalid", *command_state = "invalid",
      *command_dep = "false", *command_area = "invalid";
   int attributesFound = 0;
   bool has_name = false, has_state = false,
      has_collect = false, has_collec_dep = false, has_area = false;
   ItemCommand *item_command;
   TiXmlElement *element = pCommand->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "changecollectable")){
         command_chg_col = attributes->Value();
         attributesFound++;
         if(has_collect){
            error_tag = "More than one change collectable tag";
         }
         has_collect = true;
      } else if(!strcmp(attributes->Name(), "name")){
         command_name = attributes->Value();
         attributesFound++;
         if(has_name){
            error_tag = "More than one name tag";
         }
         has_name = true;
      } else if(!strcmp(attributes->Name(), "statedescription")) {
         command_state = attributes->Value();
         attributesFound++;
         if(has_state){
            error_tag = "More than one state description tag.";
         }
         has_state = true;
      } else if(!strcmp(attributes->Name(), "areachange")) {
         command_area = attributes->Value();
         attributesFound++;
         if(has_area){
            error_tag = "More than one change collectable tag.";
         }
         has_area = true;
      } else if(!strcmp(attributes->Name(), "collectabledependent")) {
         command_dep = attributes->Value();
         attributesFound++;
         if(has_collec_dep){
            error_tag = "More than one collectable dependent tag.";
         }
         has_collec_dep = true;
      } else{
         error_tag = attributes->Name();
         fprintf(stderr, "found something but shouldnt have in make_item_command.\n");
         attributesFound++;
      }
      attributes = attributes->Next();
   }
   if(ITEM_COMMAND_ATTRIBUTES == attributesFound && has_collec_dep && has_name && has_state && has_area && has_collect){
      item_command = new ItemCommand(command_name, command_state, command_chg_col, command_dep, command_area);
      for ( pChild = pCommand->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_TEXT){
            item_command->set_message(pChild->ToText()->Value());
         } else {
            std::ostringstream sin;
            sin << "Under parent ";
            sin << parent_id;
            sin << " there is a tag error in ";
            sin << command_name;
            std::string message = sin.str();
            error_parsing(message, world);
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in a item command tag, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message, world);
   }
   return item_command;
}

AreaCommand *make_area_command(TiXmlNode *pCommand, const char *parent_id, World *world){
   TiXmlNode* pChild;
   const char *error_tag = "missing tags", *command_id = "invalid",
      *command_name = "invalid", *command_area = "invlaid";
   int attributesFound = 0;
   bool has_id = false, has_name = false, has_area = false;
   AreaCommand *area_command;
   TiXmlElement *element = pCommand->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "id")){
         command_id = attributes->Value();
         attributesFound++;
         if(has_id){
            error_tag = "More than one id tag";
         }
         has_id = true;
      } else if(!strcmp(attributes->Name(), "name")){
         command_name = attributes->Value();
         attributesFound++;
         if(has_name){
            error_tag = "More than one name tag";
         }
         has_name = true;
      } else if(!strcmp(attributes->Name(), "area")) {
         command_area = attributes->Value();
         attributesFound++;
         if(has_area){
            error_tag = "More than one area tag.";
         }
         has_area = true;
      } else{
         error_tag = attributes->Name();
         fprintf(stderr, "found something but shouldnt have in make_area_command.\n");
         attributesFound++;
      }
      attributes = attributes->Next();
   }
   if(AREA_COMMAND_ATTRIBUTES == attributesFound && has_id && has_name && has_area){
      area_command = new AreaCommand(command_id, command_name, command_area);
      for ( pChild = pCommand->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_TEXT){
            area_command->set_message(pChild->ToText()->Value());
         } else {
            std::ostringstream sin;
            sin << "Under parent ";
            sin << parent_id;
            sin << " there is a tag error in ";
            sin << command_id;
            std::string message = sin.str();
            error_parsing(message, world);
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in a area command tag, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message, world);
   }
   return area_command;
}

StateDescriptor *make_state_descriptor(TiXmlNode *pDescription, const char *parent_id, World *world){
   TiXmlNode* pChild;
   const char *state_desc_id = "invalid", *error_tag = "missing tags";
   int attributesFound = 0;
   bool has_id = false;
   StateDescriptor *state_descriptor;
   TiXmlElement *element = pDescription->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "id")){
         state_desc_id = attributes->Value();
         attributesFound++;
         if(has_id){
            error_tag = "More than one id tag";
         }
         has_id = true;
      } /*else if(!strcmp(attributes->Name(), "switch")){
         description_switch = attributes->Value();
         attributesFound++;
      }
        */
      else {
         error_tag = attributes->Name();
         fprintf(stderr, "found something but shouldnt have.\n");
         attributesFound++;
      }
      attributes = attributes->Next();
   }
   if(STATE_DESCRIPTION_ATTRIBUTES == attributesFound && has_id){
      state_descriptor = new StateDescriptor(state_desc_id);
      for ( pChild = pDescription->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_TEXT){
            state_descriptor->set_description(pChild->ToText()->Value());
         } else {
            std::ostringstream sin;
            sin << "Under parent ";
            sin << parent_id;
            sin << " there is a tag error in ";
            sin << state_desc_id;
            std::string message = sin.str();
            error_parsing(message, world);
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in a state descriptor, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message, world);
   }

   return state_descriptor;
}

Item *make_item(TiXmlNode *pItem, const char *parent_id, World *world){
   TiXmlNode* pChild;
   const char *item_id = "invlaid", *error_tag = "missing tags",
      *item_init_desc = "invalid";
   int attributesFound =0;
   bool has_id = false, item_collectable = false, has_collec = false,
      has_init_desc = false;
   Item *item;
   TiXmlElement *element = pItem->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "id")){
         item_id = attributes->Value();
         attributesFound++;
         if(has_id){
            error_tag = "More than one id tag";
         }
         if(world->get_area(parent_id)->has_item(item_id)){
            error_tag = "Trying to create teo items with same id.";
         } else {
            has_id = true;
         }
      } else if(!strcmp(attributes->Name(), "collectable")){
         item_collectable = attributes->Value();
         attributesFound++;
         if(has_collec){
            error_tag = "More than one collectable tag";
         }
         has_collec = true;
      } else if(!strcmp(attributes->Name(), "initialdescription")) {
         item_init_desc = attributes->Value();
         attributesFound++;
         if(has_init_desc){
            error_tag = "More than one initial description tag.";
         }
         has_init_desc = true;
      } else{
         error_tag = attributes->Name();
         fprintf(stderr, "found something but shouldnt have in make_item.\n");
         attributesFound++;
      }
      attributes = attributes->Next();
   }
   if(ITEM_ATTRIBUTES == attributesFound && has_id &&has_init_desc && has_collec){
      item = new Item(item_collectable, item_id, item_init_desc);
      for ( pChild = pItem->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
            if(!strcmp(pChild->Value(), "statedescriptor")){
               item->add_description(make_state_descriptor(pChild, item_id, world));
            }else if(!strcmp(pChild->Value(), "itemcommand")){
               item->add_command(make_item_command(pChild, item_id, world));
            } 
         } else {
            std::ostringstream sin;
            sin << "Under parent ";
            sin << parent_id;
            sin << " there is a tag error in ";
            sin << item_id;
            std::string message = sin.str();
            error_parsing(message, world);
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in an item, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message, world);
   }
   return item;
}

Area *make_area(TiXmlNode *pArea, int area_index, World *world) {
   TiXmlNode* pChild;
   int attributesFound = 0;
   const char *area_id = "invalid", *desc_id = "invalid",
      *error_tag = "missing tags", *area_is_win = "false";
   bool has_id = false, has_desc = false, has_is_win = false;
   Area *area;
   TiXmlElement *element = pArea->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "id")) {
         area_id = attributes->Value();
         attributesFound++;
         if(has_id){
            error_tag = "More than one id tag";
         }
         has_id = true;
      } else if (!strcmp(attributes->Name(), "initialdescription")){
         desc_id = attributes->Value();
         attributesFound++;
         if(has_desc){
            error_tag = "More than one initialdescription tag";
         }
         has_desc = true;
      } else if (!strcmp(attributes->Name(), "iswin")){
         area_is_win = attributes->Value();
         attributesFound++;
         if(has_is_win){
            error_tag = "More than one is win tag";
         }
         has_is_win = true;
      } else {
         error_tag = attributes->Name();         
      }
      attributes=attributes->Next();
   }  
   if(attributesFound == AREA_ATTRIBUTES && has_desc && has_id && has_is_win){
      area = new Area(area_id, desc_id, area_is_win);
      for ( pChild = pArea->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
               if(!strcmp(pChild->Value(), "statedescriptor")){
                  area->add_description(make_state_descriptor(pChild, area_id, world));
               } else if(!strcmp(pChild->Value(), "item")){
                  area->add_item(make_item(pChild, area_id, world));
               } else if(!strcmp(pChild->Value(), "areacommand")){
                  area->add_command(make_area_command(pChild, area_id, world));
               }               
         } else {
            std::ostringstream sin;
            sin << "Under area ";
            sin << area_index;
            sin << ", there is tag that doesn't go there found: ";
            sin << error_tag;
            std::string message = sin.str();
            error_parsing(message, world);
         }
      }
   } else {
       std::ostringstream sin;
       sin << "Under area ";
       sin << area_index;
       sin << " there is an attribute error, found: ";
       sin << error_tag;
       std::string message = sin.str();
       error_parsing(message, world);
   }
   if(area->has_current_desc()){
      return area;
   } else {
      error_parsing("The current area can't find inital description.", world);
   }
   return area;
}
World *make_world(TiXmlNode *pParent, World *world){
   const char  *author = "invalid", *language = "invalid",
      *initialarea = "invalid", *error_tag = "missing tags";
   int attributesFound = 0, num_of_areas = 0;
   bool has_auth = false, has_lang = false, has_init = false;
   TiXmlNode* pChild;
   TiXmlElement *element = pParent->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while (attributes){
      if(!strcmp(attributes->Name(),"author")){
         author = attributes->Value();
         attributesFound++;
         if(has_auth){
            error_tag = "More than one author tag";
         }
         has_auth = true;
      }
      else if(!strcmp(attributes->Name(),"language")){
         language = attributes->Value();
         attributesFound++;
         if(has_lang){
            error_tag = "More than one language tag";
         }
         has_lang = true;
      }
      else if(!strcmp(attributes->Name(),"initialarea")){
         initialarea = attributes->Value();
         attributesFound++;
         if(has_init){
            error_tag = "More than one initialarea tag";
         }
         has_init = true;
      }
      attributes=attributes->Next();
   }
   if(attributesFound == WORLD_ATTRIBUTES && has_init && has_lang && has_auth){
      world = new World(author, language, initialarea);
      for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
            if(!strcmp(pChild->Value(),"area")){
               num_of_areas++;
               world->add_area(make_area(pChild, num_of_areas, world));
            }
         } else {
            error_parsing("ignoring a tag below world, its not an area.", world);
         }
      }
   }else{
      std::ostringstream sin;
      sin << "In make_world there is an attribute error, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message, world);
   }
   if(!world->init_active_area()){
      std::ostringstream sin;
      sin << "initial area not found in the list of areas ";
      std::string message = sin.str();
      error_parsing(message, world);
   }
   for(int area = 0; area < world->get_num_areas(); area++){
      Area *temp_area = world->get_area(area);
      for(int item = 0; item < temp_area->get_num_items(); item++){
         Item *temp_item = temp_area->get_item(item);
         for(int next_area = area + 1; next_area < world->get_num_areas(); next_area++){
            if(world->get_area(next_area)->has_item(temp_item->get_id())){
               std::ostringstream sin;
               sin << "There are two items in the game with id: ";
               sin << temp_item->get_id();
               sin << " one in ";
               sin << temp_area->get_id();
               sin << " the other in ";
               sin << world->get_area(next_area)->get_id();
               error_parsing(sin.str(), world);
            }
         }
      }
   }
   return world;   
}

void error_parsing(std::string message, World *world){
   const char *error_string = message.c_str();
   fprintf(stderr,"ERROR: [%s]\n", error_string);
   
   if(world){
      delete world;
   }
   
   exit(2);
}


World *make_objects( TiXmlNode* pParent, World *world)
{
   if(pParent->Type() == TiXmlNode::TINYXML_DOCUMENT){
      pParent = pParent->FirstChild();
      if(pParent->Type() == TiXmlNode::TINYXML_DECLARATION){
         pParent = pParent->NextSibling();
         if(pParent->Type() == TiXmlNode::TINYXML_ELEMENT){
            return make_world(pParent, world);
         } else{
            error_parsing("xml document element not found", world);   
         }
      }else{
         error_parsing("Missing XML declaration", world);
         
      }
   }else {
      error_parsing("Missing world element", world);     
   }
   return NULL;
}
