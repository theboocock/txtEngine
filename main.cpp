/**
 *  Parser code is not mine using freely distributed TinYXML library
 * @author James Boocock
 *
 **/

#include <iostream>
#include <sstream>
#include <stack>
#include "tinyxml.h"
#include "World.h"

#define WORLD_ATTRIBUTES 3
#define AREA_ATTRIBUTES 2
#define PARSING_ERROR 2
using namespace std;


World* world;
/*enum Tags{WORLD, AREA, STATEDESCRIPTOR, ITEM, STATECHANGE, EVENTHANDLER, STATECONDITIONAL, COMMAND, MESSAGE, NOVALUE};

Tags to_tag(const char * totag)
{  
   if(!strcmp(totag, "world")){
      return WORLD;
   }
   else if(!strcmp(totag, "area")){      
      return AREA;
   }
   else if(!strcmp(totag, "statedescriptor")){
      return STATEDESCRIPTOR;
   }
   else if(!strcmp(totag, "item")){
      return ITEM;
   }
   else if(!strcmp(totag, "statechange")){
      return STATECHANGE;
   }
   else if(!strcmp(totag, "eventhandler")){
      return EVENTHANDLER;
   }
   else if(!strcmp(totag, "stateconditional")){
      return STATECONDITIONAL;
   }
   else if(!strcmp(totag, "command")){
      return COMMAND;
   }
   else if(!strcmp(totag, "message")){
      return MESSAGE;
   } else {
      return NOVALUE;
   }
}   

void parse_element(TiXmlNode* pParent){
   Tags element;
   element = to_tag(pParent->Value());
   printf( "Element [%d]", element);
   switch(element){  
   case WORLD:
      break;
   case AREA:
      break;
   case STATEDESCRIPTOR:
      break;
   case ITEM:
      break;
   case STATECHANGE:
      break;     
   case STATECONDITIONAL:
      break;
   case EVENTHANDLER:
      break;
   case COMMAND:
      break;
   case MESSAGE:
      break;
   case NOVALUE:
      break;
   }
}*/

void error_parsing(const char * error_string);
Area *make_area(TiXmlNode *pArea) {
   TiXmlNode* pChild;
   int attributesFound = 0;
   const char *area_id, *desc_id;
   Area *area;
   TiXmlElement *element = pArea->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while(attributes){
      if(!strcmp(attributes->Name(), "id")) {
         area_id = attributes->Value();
         attributesFound++;
      } else if (!strcmp(attributes->Name(), "initialdescription")){
         desc_id = attributes->Value();
         attributesFound++;
      }
      attributes=attributes->Next();
   }
  
   if(attributesFound == AREA_ATTRIBUTES){
      area = new Area(area_id, desc_id);
      for ( pChild = pArea->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
         {
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
               if(!strcmp(pChild->Value(), "statedescriptor")){
                  cout << "statedescrp" << endl;
               } else if(!strcmp(pChild->Value(), "item")){
                  cout << "item-lololol" << endl;
               } else if(!strcmp(pChild->Value(), "command")){
                  cout << "command-byach" << endl;
               }               
            } else {
               error_parsing("ignoring some tag that is out of place in make_area");
            }
         }
   } else {
      error_parsing("One or more of you area attributes are wrong.");
   }

   return area;
}
void make_world(TiXmlNode *pParent){
const char  *author, *language, *initialarea;
   int attributesFound = 0;
   TiXmlNode* pChild;
   TiXmlElement *element = pParent->ToElement();
   TiXmlAttribute *attributes = element->FirstAttribute();
   while (attributes){
      if(!strcmp(attributes->Name(),"author")){
         author = attributes->Value();
         attributesFound++;
      }
      else if(!strcmp(attributes->Name(),"language")){
         language = attributes->Value();
         attributesFound++;
      }
      else if(!strcmp(attributes->Name(),"initialarea")){
         initialarea = attributes->Value();
         attributesFound++;
      }
      attributes=attributes->Next();
   }
   if(attributesFound == WORLD_ATTRIBUTES){
      world = new World(author, language, initialarea);
      for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()){
         if(pChild->Type() == TiXmlNode::TINYXML_ELEMENT){
            if(!strcmp(pChild->Value(),"area")){
               world->add_area( make_area(pChild) );
            }
         } else {
            error_parsing("ignoring something in make_world");
         }
      }
   }else{
      error_parsing("one or more of the attributes required for world are missing");
   }
}

void error_parsing(const char * error_string){
   fprintf(stderr,"ERROR: [%s]", error_string);
   exit(2);
}


void make_objects( TiXmlNode* pParent, unsigned int indent = 0 )
{
   if ( !pParent ) return;
   TiXmlNode* pChild; 
   pParent = pParent->FirstChild();
   pChild = pParent->NextSibling();
   int t = pChild->Type();
   cout << t << endl;
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

int main(int argc, char** argV)
{
   //wow
   
   make_objects("input.xml");
   delete world;
   return 0;
}
