/**
 *  Parser code is not mine using freely distributed TinYXML library
 * @author James Boocock
 *
 **/

#include <iostream>
#include <sstream>
#include "tinyxml.h"
#include "World.h"

#define WORLD_ATTRIBUTES 3
#define AREA_ATTRIBUTES 2
#define STATE_DESCRIPTION_ATTRIBUTES 1
#define ITEM_ATTRIBUTES 3
#define PARSING_ERROR 2
#define AREA_COMMAND_ATTRIBUTES 3
#define ITEM_COMMAND_ATTRIBUTES 3

World* world;

void error_parsing(std::string error_string);
StateDescriptor *make_state_descriptor(TiXmlNode *pDescription, const char *parent_id);

ItemCommand *make_item_command(TiXmlNode *pCommand, const char *parent_id){
   TiXmlNode* pChild;
   const char *error_tag = "missing tags", *command_id = "invalid",
      *command_name = "invalid", *command_state = "invlaid";
   int attributesFound = 0;
   bool has_id = false, has_name = false, has_state = false;
   ItemCommand *item_command;
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
      } else if(!strcmp(attributes->Name(), "statedescription")) {
         command_state = attributes->Value();
         attributesFound++;
         if(has_state){
            error_tag = "More than one state description tag.";
         }
         has_state = true;
      } else{
         error_tag = attributes->Name();
         fprintf(stderr, "found something but shouldnt have in make_item_command.\n");
         attributesFound++;
      }
      attributes = attributes->Next();
   }
   if(ITEM_COMMAND_ATTRIBUTES == attributesFound && has_id && has_name && has_state){
      item_command = new ItemCommand(command_id, command_name, command_state);
      for ( pChild = pCommand->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_TEXT){
            item_command->set_message(pChild->ToText()->Value());
         } else {
            std::ostringstream sin;
            sin << "Under parent ";
            sin << parent_id;
            sin << " there is a tag error in ";
            sin << command_id;
            std::string message = sin.str();
            error_parsing(message);
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in a item command tag, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message);
   }
   return item_command;
}

AreaCommand *make_area_command(TiXmlNode *pCommand, const char *parent_id){
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
            error_parsing(message);
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in a area command tag, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message);
   }
   return area_command;
}

Item *make_item(TiXmlNode *pItem, const char *parent_id){
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
         has_id = true;
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
               item->add_description(make_state_descriptor(pChild, item_id));
            }else if(!strcmp(pChild->Value(), "itemcommand")){
               item->add_command(make_item_command(pChild, item_id));
            } 
         } else {
            std::ostringstream sin;
            sin << "Under parent ";
            sin << parent_id;
            sin << " there is a tag error in ";
            sin << item_id;
            std::string message = sin.str();
            error_parsing(message);
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in an item, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message);
   }
   return item;
}

StateDescriptor *make_state_descriptor(TiXmlNode *pDescription, const char *parent_id){
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
            error_parsing(message);
         }
      }
   } else {
      std::ostringstream sin;
      sin << "Under parent ";
      sin << parent_id;
      sin << " there is an attribute error in a state descriptor, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message);
   }

   return state_descriptor;
}

Area *make_area(TiXmlNode *pArea, int area_index) {
   TiXmlNode* pChild;
   int attributesFound = 0;
   const char *area_id = "invalid", *desc_id = "invalid", *error_tag = "missing tags";
   bool has_id = false, has_desc = false;
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
      } else {
         error_tag = attributes->Name();         
      }
      attributes=attributes->Next();
   }  
   if(attributesFound == AREA_ATTRIBUTES && has_desc && has_id){
      area = new Area(area_id, desc_id);
      for ( pChild = pArea->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
               if(!strcmp(pChild->Value(), "statedescriptor")){
                  area->add_description(make_state_descriptor(pChild, area_id));
               } else if(!strcmp(pChild->Value(), "item")){
                  area->add_item(make_item(pChild, area_id));
               } else if(!strcmp(pChild->Value(), "areacommand")){
                  area->add_command(make_area_command(pChild, area_id));
               }               
         } else {
            std::ostringstream sin;
            sin << "Under area ";
            sin << area_index;
            sin << ", there is tag that doesn't go there found: ";
            sin << error_tag;
            std::string message = sin.str();
            error_parsing(message);
         }
      }
   } else {
       std::ostringstream sin;
       sin << "Under area ";
       sin << area_index;
       sin << " there is an attribute error, found: ";
       sin << error_tag;
       std::string message = sin.str();
       error_parsing(message);
   }
   if(area->has_current_desc()){
      return area;
   } else {
      error_parsing("The current area can't find inital description.");
   }
   return area;
}
void make_world(TiXmlNode *pParent){
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
               world->add_area(make_area(pChild, num_of_areas));
            }
         } else {
            error_parsing("ignoring a tag below world, its not an area.");
         }
      }
   }else{
      std::ostringstream sin;
      sin << "In make_world there is an attribute error, found: ";
      sin << error_tag;
      std::string message = sin.str();
      error_parsing(message);
   }
}

void error_parsing(std::string message){
   const char *error_string = message.c_str();
   fprintf(stderr,"ERROR: [%s]\n", error_string);
   exit(2);
}


void make_objects( TiXmlNode* pParent, unsigned int indent = 0 )
{
   if ( !pParent ) return;
   TiXmlNode* pChild; 
   pParent = pParent->FirstChild();
   pChild = pParent->NextSibling();
   int t = pChild->Type();
   std::cout << t << std::endl;
   if(t == TiXmlNode::TINYXML_ELEMENT){
      make_world(pChild);
 }
}
// load the named file and dump its structure to STDOUT

void make_objects(const char* pFilename)
{
   TiXmlDocument doc(pFilename);
   bool loadOkay = doc.LoadFile();
   if (loadOkay)
      {
         printf("\n%s:\n", pFilename);
        make_objects( &doc ); // defined later in the tutorial
      }
   else
      {
         printf("Failed to load file \"%s\"\n", pFilename);
      }
}

void print_world_tree(){
   std::ostringstream sin;
   sin << "World:\n";
   for(int area = 0; area < world->get_num_areas(); area++){
      Area *temp_area = world->get_area(area);
      sin << "\tArea ";
      sin << temp_area->get_id();
      sin << "\n";
      for(int state_desc = 0; state_desc < temp_area->get_num_descriptions(); state_desc++){
         StateDescriptor *temp_desc = temp_area->get_descriptor(state_desc);
         sin << "\t\tDesc: ";
         sin << temp_desc->get_description();
         sin << "\n";
      }
      for(int item = 0; item < temp_area->get_num_items(); item++){
         Item *temp_item = temp_area->get_item(item);
         sin << "\t\tItem:";
         sin << temp_item->get_id();
         sin << "\n";
         for(int state_desc = 0; state_desc < temp_item->get_num_descriptions(); state_desc++){
            StateDescriptor *temp_desc = temp_item->get_descriptor(state_desc);
            sin << "\t\t\tDesc: ";
            sin << temp_desc->get_description();
            sin << "\n";
         }
      }
   }
   std::string message = sin.str();
   fprintf(stderr, "Attempt at printing world.\n%s\n", message.c_str());
}

int main(int argc, char** argv)
{
   make_objects("testInput.xml");
   /*delete world deletes everything, as the the deconstructor for
     world calls the decontructor for all areas, which calls the
     decontructor for all items and descriptions...
    */
   print_world_tree();
   delete world;
   return 0;
}
