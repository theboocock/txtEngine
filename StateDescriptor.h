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

#ifndef _STATE_DESCRIPTOR_H
#define _STATE_DESCRIPTOR_H

//------------------------------------------------------------------------------
/* Include */
//------------------------------------------------------------------------------
#include <string>

class StateDescriptor {
 protected:
   std::string id; ///< The id of the state descriptor.
   std::string description; ///< The description.

 public:
   /**
      Constructor for a state descriptor.
           
      @param[in] identifier The identifier of the descriptor.
   */
   StateDescriptor(const char *identifier);
        
   /**
      Sets the description variable of the object.

      @param[in] desc The description of the object.
   */
   void set_description(const char *desc);

   /**
      StateDescriptor Destructor.
   */
   ~StateDescriptor();

   /**
      Gets the id of the object.
     
      @return The id of the object.
   */
   std::string get_id();

   /**
      Gets the description of the object.

      @return The description of the object.
   */
   std::string get_description();
};

#endif
