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

#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <vector>
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

    public:

	bool is_locked();

	bool has_container();

	/**
           Returns a string with all items item contains.
	   
         */
        std::string print_contained_items();

	/**
           Returns a pointer to an item by id or null if
	   
         */
        Item* get_item(std::string item_id);

	/**
           Adds an item to the contains vector
	   
        */
        void add_item(Item*);

        /**
           Checks whether this Item has an inside area.
         */
        bool has_inside();

        /**
           Checks whether this Item can combine with another.
         */
        bool has_combine();

        /**
           Accessors and mutators for inside.
        */
        Area * get_inside();
	
	/**
           Accessors and mutators for inside and combine.
        */
        combine * get_combine();
	
	
        void set_inside(Area * a);
	
	
        void set_combine(combine * c);
	
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
        bool has_description(std::string desc_id);

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
        bool has_synonym(std::string);

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
        void change_collectable(bool flip);

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
        bool is_collectable();

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
        void add_command(ItemCommand *command_name);

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
        ItemCommand *get_command(int index);

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
        ItemCommand *get_command(std::string command_name);

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
        void state_change(std::string to_change);

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
        Item(bool collect, const char *identifier, const char *initial_state,
             std::vector<std::string> *synonyms, const char * depends, bool container, bool locked);

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
        ~Item();

        std::string get_depends();
    };

#endif
