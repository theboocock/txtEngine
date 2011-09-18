/*
 *
 * @file combine.cpp
 * @description cpp implementation of combine
 *
 */

#include "combine.h"

combine::combine(std::string id,std::string first, std::string second_id){
	this->id = id;	
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

std::string combine::get_id(){
	return id;
}

std::string combine::get_second_id(){
	return second_id;
}

std::string combine::get_first_id(){
	return first_id;
}
