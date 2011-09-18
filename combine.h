/**
 * @file Combine.h
 * Combine.h defines the methods for the Combine.cpp source file.
 * 
 * @brief Defines the Combine class.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#ifndef COMBINE_H_
#define COMBINE_H_

#include <iostream>
#include <string>
#include "StateDescriptor.h"

class Item;

class combine{
 private:
   // the description when you combine the things
   StateDescriptor * description;
   // First item_id 
   std::string first_id;
   // Second item_id
   std::string second_id;
   // The item that is the combination
   Item * combination;
   // combine id
   std::string id;	
 public:
   /**
      Constructor for a combine object.

      @param[in] id The id for the object.
      @param[in] first_id The id of the first item to combine.
      @param[in] second_id The id of the second object to combine.
   */
   combine(std::string id, std::string first_id, std::string second_id);

   /**
      Destructor for combine object.
   */
   ~combine();

   /**
      Get 

      @param[in]     _inArg1 Description of first function argument.
      @param[out]    _outArg2 Description of second function argument.
      @param[in,out] _inoutArg3 Description of third function argument.
      @return Description of returned value.
   */
   Item* get_combination();

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
   std::string get_id();
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
   std::string get_first_id();
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
   std::string get_second_id();
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
   void set_combination(Item * item);
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
   void set_description(StateDescriptor * d);

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
   std::string get_description();
};

#endif 
