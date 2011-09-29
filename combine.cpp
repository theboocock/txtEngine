/**
 * @file Combine.cpp
 *
 * Provides combine functionality in the game.
 * An object consists of its id, the id of the first
 * item that can be combined, and the id of the second object
 * that can be combined.
 *
 * @brief Source file for Combine functionality.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#include "combine.h"
#include "Item.h"

combine::combine(std::string id,std::string first, std::string second_id){
	this->description = NULL;
	this->id = id;	
	this->first_id = first;
	this->second_id = second_id;
}

void combine::set_description(StateDescriptor * d){
	this->description = d;
}

std::string combine::get_description(){
	return this->description->get_description();
}

combine::~combine(){
	if(combination!=NULL){
		delete combination;
	}
}

Item* combine::get_combination(){
	Item* temp = combination;
	combination = NULL;
	return temp;
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
