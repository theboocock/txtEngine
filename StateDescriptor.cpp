/**
 * @file StateDescriptor.cpp
 * Provides functionality for a StateDescriptor object.
 *
 * @brief Source file for a StateDescriptor.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */

#include "StateDescriptor.h"

StateDescriptor::StateDescriptor(const char *identifier) {
    id = identifier;
    }
void StateDescriptor::set_description(const char *desc) {
    description = desc;
    }
StateDescriptor::~StateDescriptor() {
    }
std::string StateDescriptor::get_id() {
    return id;
    }
std::string StateDescriptor::get_description() {
    return description;
    }

