/*
 *
 * @file combine.h
 * @description deals with the combine command
 *
 */

#ifndef COMBINE_H_
#define COMBINE_H_

#include <iostream>
#include <string>

class Item;

class combine{
	
	public:

		combine(std::string first_id, std::string second_id);
		~combine();
		Item* get_combination();
		void set_combination(Item * item);
	private:
		// First item_id 
		std::string first_id;
		// Second item_id
		std::string second_id;
		//The item that is the combination
		Item * combination;

};

#endif 
