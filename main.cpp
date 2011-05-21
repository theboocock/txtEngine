/**
 *  Parser code is not mine using freely distributed TinYXML library
 * @author James Boocock
 *
 **/

#include <iostream>
#include <sstream>
#include "tinyxml.h"
#include "BaseContainer.h"

using namespace std;

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

void dump_to_stdout( TiXmlNode* pParent, unsigned int indent = 0 )
{
   if ( !pParent ) return;

   TiXmlNode* pChild;
   TiXmlText* pText;
   int t = pParent->Type();
   printf( "%s", getIndent(indent));
   int num;
   Tags element;
   switch ( t )
      {
      case TiXmlNode::TINYXML_DOCUMENT:
         printf( "Document" );
         break;

      case TiXmlNode::TINYXML_ELEMENT:
         printf( "Element [%s]", pParent->Value());
         element = to_tag(pParent->Value());
         printf( "Element [%d]", element);
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
         dump_to_stdout( pChild, indent+1 );
      }
}

// load the named file and dump its structure to STDOUT

void dump_to_stdout(const char* pFilename)
{
   TiXmlDocument doc(pFilename);
   bool loadOkay = doc.LoadFile();
   if (loadOkay)
      {
         printf("\n%s:\n", pFilename);
         dump_to_stdout( &doc ); // defined later in the tutorial
      }
   else
      {
         printf("Failed to load file \"%s\"\n", pFilename);
      }
}

int main(int argc, char** argV)
{
   //wow
   dump_to_stdout("input.xml");
   return 0;
}
