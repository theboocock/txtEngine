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
          An accessor for the depends member.

          @return A string 
          */
        std::string get_depends();

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
        std::string get_status();

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
        std::string get_name();

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
        std::string get_area();

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
        std::string get_message();

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
        void set_message(const char *to_message);

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
        bool find(std::string to_find);
        void unlock();
        bool is_locked();
        bool has_synonym(std::string item);
    };

#endif
