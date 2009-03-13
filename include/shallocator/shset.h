/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL set.
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
 *       2007-04-25 (bukovsky)
 *                  First draft.
 */

#ifndef SHALLOCATOR_SHSET_H
#define SHALLOCATOR_SHSET_H

#include <set>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/**
 * @short Shared memory set.
 */
template <typename _Key, typename _Compare = std::less<_Key> >
class shset: public std::set<_Key, _Compare, Allocator_t<_Key> > {
public:
    /// aloocator typedef
    typedef Allocator_t<_Key> AllocatorType_t;
    /// parent typedef
    typedef std::set<_Key, _Compare, AllocatorType_t> __parent;

    /**
     * @short Default constructor creates no elements.
     * @param __comp Comparator to use.
     */
    shset(const _Compare& __comp = _Compare())
        : __parent(__comp, AllocatorType_t()) {}

    /** 
     * @short Construct %shset from std set.
     * @param __other other %shset.
     */
    template <typename _otherKey, typename _otherCompare, typename _otherAllocT>
    shset(const std::set<_otherKey, _otherCompare, _otherAllocT> &__other)
        : __parent(__other.begin(), __other.end(), _Compare(),
                   AllocatorType_t()) {}

    /**
     * @short Builds a %shset from a range.
     * @param __first An input iterator.
     * @param __last An input iterator.
     * @param __comp A comparison functor.
     */
    template <class _InputIterator>
    shset(_InputIterator __first, _InputIterator __last,
            const _Compare& __comp = _Compare())
        : __parent(__first, __last, __comp, AllocatorType_t()) {}
};

}

#endif /* SHALLOCATOR_SHSET_H */

