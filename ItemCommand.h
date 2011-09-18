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

#ifndef _ITEM_COMMAND_H
#define _ITEM_COMMAND_H

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
	bool is_combine();
	
        ItemCommand(const char * callmeby, const char * state_mutator,
                    bool chng_collec, bool collec_dep, const char *area_chng,
                    const char* status_command,const char* depends,
                    std::vector<std::string> * synonyms, std::string unlock, bool combine);
        
        ~ItemCommand();

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
        bool get_change_collect();

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
        bool get_collect_dependent();

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
        std::string get_area_change();

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
        std::string get_state_change();

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
        bool check_synonyms(std::string command);

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

        bool unlocks();

	std::string get_unlockstring();

        std::string unlock_areacommand_string();

        std::string unlock_area_string();

    };

#endif
