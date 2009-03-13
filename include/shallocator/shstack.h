/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL stack.
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

#ifndef SHALLOCATOR_SHSTACK_H
#define SHALLOCATOR_SHSTACK_H

#include <stack>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/**
 * @short Shared memory stack.
 */
template <typename _Tp, typename _Sequence>
class shstack: public std::stack<_Tp, _Sequence> {
public:
    /// parent typedef
    typedef std::stack<_Tp, _Sequence> __parent;

    /**
     * @short Default constructor creates no elements.
     * @param __c init sequence. Data will be copied.
     */
    explicit
    shstack(const _Sequence &__c = _Sequence()): __parent(__c) {}
};

}

#endif /* SHALLOCATOR_SHSTACK_H */

