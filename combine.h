/**
 * @file Combine.h
 *
 * Provides combine functionality in the game.
 * An object consists of its id, the id of the first
 * item that can be combined, and the id of the second object
 * that can be combined.
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


//------------------------------------------------------------------------------
/* Include */
//------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "StateDescriptor.h"

class Item;

class combine{
 private:
   StateDescriptor * description; ///< The description when you
                                  ///< combine the things.
   std::string first_id; ///< First item_id.
   std::string second_id; ///< Second item_id.
   Item * combination; ///< The item that is the combination.
   std::string id; ///< Combine id.	
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
      Get the item that is a combination.

      @return A pointer to the combined item.
   */
   Item* get_combination();

   /**
      Get the id of the combined item.

      @return The id of the combined item.
   */
   std::string get_id();

   /**
      Get the id of the first item that made this combined item.

      @return The id of the first item.
   */
   std::string get_first_id();

   /**
      Get the id of the second item that made this combined item.

      @return The id of the second item.
   */
   std::string get_second_id();

   /**
      Sets the combination class member to a new item.

      @param[in] item A pointer to an item that is a combination of two items from inventory.
   */
   void set_combination(Item * item);
 
   /**
      Sets the description of the combined item.

      @param[in] d The description for the item.
   */
   void set_description(StateDescriptor * d);

   /**
      Gets the description of the combined item.

      @return The description of the combined item.
   */
   std::string get_description();
};

#endif 
