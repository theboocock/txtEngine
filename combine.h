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

		combine(std::string id,std::string first_id, std::string second_id);
		~combine();
		Item* get_combination();
		std::string get_id();
		std::string get_first_id();
		std::string get_second_id();
		void set_combination(Item * item);
	private:
		// First item_id 
		std::string first_id;
		// Second item_id
		std::string second_id;
		//The item that is the combination
		Item * combination;
		// combine
		std::string id;
};

#endif 
