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

#ifndef _AREA_COMMAND_H
#define _AREA_COMMAND_H

//------------------------------------------------------------------------------
/* Include */
//------------------------------------------------------------------------------
#include <vector>
#include <string>

class AreaCommand {
    protected:
        bool locked;
        std::string name;
        std::string status;
        std::string message;
        std::string depends;
        std::string move_to_area;
        std::vector<std::string> *synonyms;

    public:

        /**
          The constructor for an AreaCommand.

           @param[in] callmeby The name of this command.
	   @param[in] areamoveto The area to move to when this command is called.
	   @param[in] status_command The status id to change to.
	   @param[in] depends_command 
	   @param[in] synonyms A vector containing synonyms of 'callmeby'.
	   @param[in] locked If true command cannot be called.
        */
        AreaCommand(const char * callmeby, const char * areatomoveto, const char * status_command, const char * depends_command, std::vector<std::string> *synonyms, bool locked);

        /**
           The AreaCommand Destructor
        */
        ~AreaCommand();

        /**
          Returns what the AreaCommand depends on.

          @return An id of an item the command depends on.
          */
        std::string get_depends();

        /**
          Get the status of the AreaCommand

          @return The status of the AreaCommand.
          */
        std::string get_status();

        /**
          Get the name of the AreaCommand.

          @return The name of the AreaCommand.
          */
        std::string get_name();

        /**
          Get the name of the area to move to when this command is used.

          @return The name of the area to move to.
          */
        std::string get_area();

        /**
          Get the message to print when this command is used.

          @return A message to print for this command.
          */
        std::string get_message();

        /**
          Change the message for this command.

          @param[in] to_message The new message for this command.
          */
        void set_message(const char *to_message);

        /**
          Compares the name of the command with a string.

          @param[in] to_find A string to compare with the command name.
          @return True if the strings match otherwise false.
          */
        bool find(std::string to_find);

        /**
          Unlocks the command so it can be called.
          */
        void unlock();

        /**
          Checks whether this area command is locked.

          @return True if the command is locked or false if it is unlocked.
          */
        bool is_locked();

        /**
         Checks if the area command has a synonym matching a string.

          @param[in] item The name to check
          @return True if the synonym list has the string or false if not.
          */
        bool has_synonym(std::string item);
    };

#endif
