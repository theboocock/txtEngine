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
enum Tags{WORLD, AREA, STATEDESCRIPTOR, ITEM, STATECHANGE, EVENTHANDLER, STATECONDITIONAL, COMMAND, MESSAGE, NOVALUE};

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

const unsigned int NUM_INDENTS_PER_SPACE=2;

const char * getIndent( unsigned int numIndents )
{
   static const char * pINDENT="                                      + ";
   static const unsigned int LENGTH=strlen( pINDENT );
   unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
   if ( n > LENGTH ) n = LENGTH;
   return &pINDENT[ LENGTH-n ];
}

// same as getIndent but no "+" at the end
const char * getIndentAlt( unsigned int numIndents )
{
   static const char * pINDENT="                                        ";
   static const unsigned int LENGTH=strlen( pINDENT );
   unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
   if ( n > LENGTH ) n = LENGTH;

   return &pINDENT[ LENGTH-n ];
}
void error_parsing(const char * error_string);

int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
   if ( !pElement ) return 0;

   TiXmlAttribute* pAttrib=pElement->FirstAttribute();
   int i=0;
   int ival;
   double dval;
   const char* pIndent=getIndent(indent);
   printf("\n");
   while (pAttrib)
      {
         printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());
         if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
         if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
         printf( "\n" );
         i++;
         pAttrib=pAttrib->Next();
      }
   return i;	
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
}

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
   printf( "%s", getIndent(indent));
   int num;
   TiXmlText *pText;
   Tags element;
   pParent = pParent->FirstChild();
   pChild = pParent->NextSibling();
   int t = pChild->Type();
   cout << t << endl;
   if(t == TiXmlNode::TINYXML_ELEMENT){
      make_world(pChild);
   } else {
      cout << "DADADADADADA" << endl;
   switch (t)
      {
      case TiXmlNode::TINYXML_DOCUMENT:
         printf( "Document" );
         break;

      case TiXmlNode::TINYXML_ELEMENT:
         printf( "Element [%s]", pParent->Value());
         //parse_element(pParent);
         num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
         switch(num)
            {
            case 0:  printf( " (No attributes)"); break;
            case 1:  printf( "%s1 attributes", getIndentAlt(indent)); break;
            default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
            }
         break;
      
      case TiXmlNode::TINYXML_COMMENT:
         printf( "Comment: [%s]", pParent->Value());
         break;

      case TiXmlNode::TINYXML_UNKNOWN:
         printf( "Unknown" );
         break;

      case TiXmlNode::TINYXML_TEXT:
         pText = pParent->ToText();
         element = to_tag(pParent->Parent()->Value());
         printf( "Element [%d]", element);
         printf( "Text: [%s]", pText->Value() );
         break;

      case TiXmlNode::TINYXML_DECLARATION:
         printf( "Declaration" );
         break;
      default:
         break;
      }
   printf( "\n" );
   for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
      {
         make_objects(pChild, indent+1);
        
      }
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
