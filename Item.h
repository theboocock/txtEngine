/**
 * @file Item.h
 * Item.h defines the methods for the Item.cpp source file.
 *
 * @brief Defines the Item class.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
#include <cstring>
#include "StateDescriptor.h"
#include "ItemCommand.h"
#include "combine.h"

class Area;

class Item {

 protected:
   bool collectable;
   int num_descriptions, num_commands, num_items;
   std::string id;
   bool container;
   bool locked;
   combine * combine_var;
   std::vector<Item *> contains;
   std::string curr_desc_id;
   std::vector<StateDescriptor*> description;
   std::vector<ItemCommand*> commands;
   std::vector<std::string> *synonyms;
   std::string depends;
   std::string name;
 public:
   /**
      Removes an item from inside this item by id.

      @param A string - the id of the item to remove.
   */
   void remove_item(std::string item_id);

   /**
      Flips the locked variable for this item..
   */
   void flip_locked();

   /**
      Checks whether the the Item is locked.

      @return True if the item is locked otherwise false.
   */
   bool is_locked();

   /**
      Checks whether the the Item is a container for
      other items.

      @return True if the item is a container or false if not.
   */
   bool has_container();

   /**
      Returns a string with all items the item contains.

      @return A string of items this item contains.
   */
   std::string print_contained_items();

   /**
      Returns a pointer to an item by id or null if
      it does not exist.

      @param item_id The id of the item to get.
      @return A pointer to an item.
   */
   Item* get_item(std::string item_id);

   /**
      Adds an item to the contains vector.

      @param The pointer to an item.
   */
   void add_item(Item*);


   /**
      Checks whether this Item can combine with another.

      @return True if this item can be combined with another otherwise false.
   */
   bool has_combine();

   /**
      Accessor for a combine object.

      @return A pointer to a combine object.
           
   */
   combine * get_combine();

   /**
      A mutator for a combine object.

      @param[in] c A pointer to a combine object.
   */
   void set_combine(combine * c);
	
   /**
      Check whether this item has a certain description id.

      @param[in] desc_id A string of an item description id.
      @return True if this item contains the discription otherwise false.
   */
   bool has_description(std::string desc_id);

   /**
      Check whether this item has the current description.
      Calls has_description method passing the curr_desc_id.

      @return True if the item has the current description otherwise false.
   */
   bool has_current_desc();

   /**
      Checks whether this item has a particular synonym.
     
      @param[in] item A string that may be a synonym.
      @return True if the item has the synonym otherwise false.
   */
   bool has_synonym(std::string item);

   /**
      Gets the item description.
           
      @return The description of the item.
   */
   std::string get_description();

   /**
      Add a StateDescriptor for this item.

      @param[in] desc A pointer to a StateDescriptor object to add.
   */
   void add_description(StateDescriptor *desc);

   /**
      Flip the value of collectable for this item.

      @param[in] flip True flips the value, false leaves it unchanged.
   */
   void change_collectable(bool flip);

   /**
      Checks whether this item is collectable.
       
      @return Description of returned value.
   */
   bool is_collectable();

   /**
   Gets the id of the item.

      @return A string - the id of the item.
   */
   std::string get_id();

   /**
      Gets the number of commands for this item.
      
      @return The number of commands this item has.
   */
   int get_num_commands();

   /**
      Add a command to this item.

      @param[in] command_name A pointer to an ItemCommand object.
   */
   void add_command(ItemCommand *command_name);

   /**
     Gets a command from the commands vector for this item by index.

      @param[in] index The index of the item in the vector.
      @return An ItemCommand object at the specified index.
   */
   ItemCommand *get_command(int index);

   /**
      Gets a command from the commands vector of this item by command_name.
     
      @param[in] command_name A string - the name of the command.
      @return An ItemCommand object with the specified name.
   */
   ItemCommand *get_command(std::string command_name);

   /**
      Get the number of descriptions for this item.
     
      @return The number of descriptions for this item.
   */
   int get_num_descriptions();

   /**
      Get a StateDescriptor from the descriptions vector by index.

      @param[in] index The index of the StateDescriptor in the vector.
      @return A StateDescriptor at the specified index.
   */
   StateDescriptor *get_descriptor(int index);

   /**
      Changes the state of the item.

      @return Returns a string - what the item depends on.
   */
   std::string get_depends();
   
   /**
     Changes the state of the item.

      @param[in] to_change A string - to change the state of the item to.
   */
   void state_change(std::string to_change);

   /**
     The constructor for an Item.

     @param[in] collect Whether this item is collectable or not.
     @param[in] identifier An identifier for this item.
     @param[in] initial_state The initial state of the item.
     @param[in] synonyms A vector of synonyms for the name of this item.
     @param[in] depends An item this item depends on.
     @param[in] container Whether this item is a container.
     @param[in] locked Whether this item is locked.
   */
   Item(bool collect, const char *identifier, const char *initial_state,
        std::vector<std::string> *synonyms, const char * depends, bool container, bool locked, const char* name);

   /**
      The destructor for an Item.
   */
   std::string get_name();
   ~Item();
};

#endif
