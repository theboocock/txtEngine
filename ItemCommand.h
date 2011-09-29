/**
 * @file ItemCommand.h
 * ItemCommand.h defines the methods for the ItemCommand.cpp source file.
 *
 * @brief Defines the ItemCommand class.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#ifndef _ITEM_COMMAND_H
#define _ITEM_COMMAND_H


//------------------------------------------------------------------------------
/* Include */
//------------------------------------------------------------------------------
#include "Constants.h"
#include <vector>
#include <string>

class ItemCommand {
 protected:
   std::string name;
   std::string state_change;
   std::string message;
   std::string area_change;
   std::string depends;
   std::string status;
   std::string unlock;
   bool call_combine;
   std::vector<std::string> *synonyms;
   bool change_collect, collect_dependent;

 public:

    /**
      The constructor for an ItemCommand object.

      @param[in] callmeby
      @param[in] state_mutator
      @param[in] chng_collec
      @param[in] collec_dep
      @param[in] area_chng
      @param[in] status_command
      @param[in] depends
      @param[in] synonyms
      @param[in] unlock
      @param[in] combine
   */
   ItemCommand(const char * callmeby, const char * state_mutator,
               bool chng_collec, bool collec_dep, const char *area_chng,
               const char* status_command,const char* depends,
               std::vector<std::string> * synonyms, std::string unlock, bool combine);
        
    /**
      The destructor for an ItemCommand object.
   */
   ~ItemCommand();

   /**
     Get the id of an item that this ItemCommand depends on.

      @return The id of an item that this command depends on.
   */
   std::string get_depends();

   /**
      Check whether this item command makes the item collectable.

      @return True if the item command changes whether the item is collectable otherwise false.
   */
   bool get_change_collect();

   /**
      Check whether this item command depends on having an item in inventory.

      @return True if the command depends on possessing an item.
   */
   bool get_collect_dependent();

   /**
     Get the id of the area the item changes to when this command is called.

      @return The id of the area to change to.
   */
   std::string get_area_change();

   /**
    Get the status of the item command.

      @return The status of the command.
   */
   std::string get_status();

   /**
     Get the message - this is displayed automatically when the item 
     command is called.

      @return A message to display.
   */
   std::string get_message();

   /**
     Get the name of the item command.

      @return The name of the item command.
   */
   std::string get_name();

   /**
   Get the state the item will change to when this command is called.

      @return The state for item to change to.
   */
   std::string get_state_change();

   /**
    Check if the item command has any synonyms.

      @return True if a synonym for this command exists otherwise false.
   */
   bool check_synonyms(std::string command);

   /**
     Sets the message to be displayed when the command is called.

      @param[in] to_message A string - the message to be displayed.
   */
   void set_message(const char *to_message);
   
   /**
      Checks whether this item command will combine two items.

      @return True if the command will combine items, otherwise false.
   */
   bool is_combine();
   
   /**
     Checks whether this item command will unlock an item.

      @return True if the command unlocks an item.
   */
   bool unlocks();

      /**
      Gets the areacommand this item command unlocks.

      @return An areacommand.
   */
   std::string unlock_areacommand_string();
   
      /**
     Gets the area this item command unlocks.

      @return An area.
   */
   std::string unlock_area_string();

      /**
     Get the unlock string.

      @return The unlock string.
   */
   std::string get_unlock_string();

};

#endif
