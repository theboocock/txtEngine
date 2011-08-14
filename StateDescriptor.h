// $Id$
/**
 * @file StateDescriptor.h
 * Area.h defines the methods for StateDescriptor.cpp
 *
 * @brief Dscribes the StateDescriptor class.
 *
 * @author Michael Abrams
 * @author James Boocock
 * @author Toby Herbert
 * @author Tatai Nikora
 * @version 0.3
 */
// $Log$

#ifndef _STATE_DESCRIPTOR_H
#define _STATE_DESCRIPTOR_H
#include <string>

class StateDescriptor {
    protected:
        std::string id;
        std::string description;

    public:
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
        StateDescriptor(const char *identifier);
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
        void set_description(const char *desc);

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
        ~StateDescriptor();

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
        std::string get_description();
    };

#endif
