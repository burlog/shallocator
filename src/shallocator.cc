/*
 * FILE             $Id$
 *
 * DESCRIPTION      Library cc.
 *
 * PROJECT          Shared memory STL allocator.
 *
 * AUTHOR           Michal Bukovsky <michal.bukovsky@firma.seznam.cz>
 *
 * LICENSE          see COPYING
 *
 * Copyright (C) Seznam.cz a.s. 2007
 * All Rights Reserved
 *
 * HISTORY
 *       2007-04-24 (bukovsky)
 *                  First draft.
 */

#include <shallocator/shalloc.h>

namespace SHAllocator {

/** 
 * @short Empty pointer for placement new operator.
 */
SHAlloc_t *SHAlloc = 0;

}

//
// Lib is empty. All lib function is in C++ templates in header files.
//

/*
 * Dummy symbol for configure scripts.
 */
extern "C" {
    int lib_shallocator_present() { return 0;}
}

