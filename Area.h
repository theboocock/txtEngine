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
        int num_items;
        int num_descriptions, num_commands;
        std::string status;
        std::string id;
        std::string curr_desc_id;
        std::vector<StateDescriptor*> description;
        std::vector<AreaCommand*> commands;
    public:

        /**
         Checks whether the description ID passed in is in the vector of
         StateDescriptors for the area and returns true or false accordingly.

         @param[in] desc_id A description ID.
         @return Returns true if 'description' holds desc_id, otherwise returns false.
         */
        bool has_description(std::string desc_id);

        /**
         This accessor method returns a string representing the status of the area
         from the protected 'status' member variable.

         @return The status of the Area.
         */
        std::string get_status();

        /**
         Calls the has_description method.
	
         The function arguments listed with "param" will be compared
         to the declaration and verified.
	 @see has_description();
         @return
         */
        bool has_current_desc();

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
        int get_num_items();

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
        void remove_item(int index);

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
        void remove_item(std::string item_id);

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
        void add_item(Item *new_item);

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
        Item *get_item(int index);

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
        bool has_item(std::string item_to_find);

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
        Item *get_item(std::string item_id, unsigned int &item);

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
        void add_description(StateDescriptor *desc);

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
        void add_command(AreaCommand *command_name);

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
        int get_num_commands();

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
        AreaCommand *get_command(int index);

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
        AreaCommand *has_command(std::string command_name);

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
        int get_num_descriptions();

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
        StateDescriptor *get_descriptor(int index);

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

        void unlock(std::string area_command_id);

        Area(const char *id, const char *desc_id, const char* status);

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
        ~Area();
    };

#endif
