/*
 *
 * @file combine.cpp
 * @description cpp implementation of combine
 *
 */

#include "combine.h"

combine::combine(std::string first, std::string second_id){
		this->first_id = first_id;
		this->second_id = second_id;
}

combine::~combine(){
}

Item* combine::get_combination(){
	return combination;
}

void combine::set_combination(Item * item){
	this->combination = item;
}
