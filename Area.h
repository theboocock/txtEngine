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

#ifndef _AREA_H
#define _AREA_H
#include <string>
#include <vector>
#include <iostream>
#include "Item.h"
#include "StateDescriptor.h"
#include "AreaCommand.h"

class Area {
 protected:
   std::vector<Item*> items;
   int num_descriptions, num_commands, num_items;
   std::string status;
   std::string id;
   std::string curr_desc_id;
   std::vector<StateDescriptor*> description;
   std::vector<AreaCommand*> commands;
 public:

   /**
      Checks if an area has this description.

      @param[in] desc_id A description ID.
      @return Returns true if 'description' holds desc_id, otherwise returns false.
   */
   bool has_description(std::string desc_id);

   /**
      This accessor method returns the status of the area.

      @return The status of the Area.
   */
   std::string get_status();

   /**
      Calls the has_description method.
	
      The function arguments listed with "param" will be compared
      to the declaration and verified.
      @see has_description();
      @return True if the area has the current description otherwise false.
   */
   bool has_current_desc();

   /**
      Accessor for the number of items in the Area.
        
      @return The number of items in the area.
   */
   int get_num_items();

   /**
      Get the area description.

      @return String description of the area.
   */
   std::string get_description();

   /**
      Remove an item from the area by index.

      @param[in] index The index of the item to remove.
      @return Description of returned value.
   */
   void remove_item(int index);

   /**
      Removes an item from the area by the item id.

      @param[in] item_id The id of the item to be removed.
   */
   void remove_item(std::string item_id);

   /**
      Adds an item to the area.

      @param[in] new_item A pointer to the item to add to the items vector.
   */
   void add_item(Item *new_item);

   /**
      Get the item in the area from items vector by index.

      @param[in] index The index of the item in the vector.
      @return A pointer to the item.
   */
   Item *get_item(int index);

   /**
      Get the area id.

      @return The id of the area.
   */
   std::string get_id();

   /**
      Checks whether the area has an item.

      @param[in] item_to_find
      @return True if the area (items vector) contains the item.
   */
   bool has_item(std::string item_to_find);

   /**
      Gets a pointer to the item by item id and sets index to the
      index of the item in the vector.

      @param[in] item_id The id of the item.
      @param[out] index The address of the item's index member variable.
      @return A pointer to the item.
   */
   Item *get_item(std::string item_id, unsigned int &item);

   /**
      Adds a StateDescriptor to an area.

      @param[in] desc A pointer to a StateDescriptor object.
   */
   void add_description(StateDescriptor *desc);

   /**
      Adds an AreaCommand to an area.

      @param[in] A pointer to an AreaCommand.
   */
   void add_command(AreaCommand *command_name);

   /**
      Get the number of commands for this area.

      @return The number of AreaCommands for this area.
   */
   int get_num_commands();

   /**
      Get an AreaCommand for this area by index.

      @param[in] index The index of the AreaCommand in the commands vector.
      @return A pointer to the AreaCommand or null if it doesn't exist.
   */
   AreaCommand *get_command(int index);

   /**
      Gets an AreaCommand for this area by name.

      @param[in] command_name The name of the command to get.
      @return A pointer to the AreaCommand or null if it doesn't exist.
   */
   AreaCommand *has_command(std::string command_name);

   /**
      Get the number if descriptions for the area.

      @return The number of descriptions for this area.
   */
   int get_num_descriptions();

   /**
      Gets a StateDescriptor for the area by index.
         
      @param[in] index The index of the StateDescriptor in the description vector.
      @return A pointer to the StateDescriptor or null if it doesn't exist.
   */
   StateDescriptor *get_descriptor(int index);

   /**
      Unlocks an AreaCommand of this area.
         
      @param[in] area_command_id The id of an AreaCommand to unlock.
   */
   void unlock(std::string area_command_id);

   /**
      The constructor for an Area object.
	 
      @param[in] id The id of the area.
      @param[in] desc_id The id of the area description.
      @param[in] status The status of the area.
   */
   Area(const char *id, const char *desc_id, const char* status);

   /**
      Area Deconstructor.
   */
   ~Area();
};

#endif
