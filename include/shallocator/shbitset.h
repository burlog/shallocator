/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL bitset.
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
 *       2007-04-27 (bukovsky)
 *                  First draft.
 */

#ifndef SHALLOCATOR_SHBITSET_H
#define SHALLOCATOR_SHBITSET_H

// std::bitset is strange. They dont use allocator as other containers.
// If you need it, write and try it.
#error std::bitset is not supported by SHAllocator library.

#endif /* SHALLOCATOR_SHBITSET_H */

