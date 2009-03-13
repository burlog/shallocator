/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL multiset.
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

#ifndef SHALLOCATOR_SHMULTISET_H
#define SHALLOCATOR_SHMULTISET_H

#include <set>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/**
 * @short Shared memory multiset.
 */
template <typename _Key, typename _Compare = std::less<_Key> >
class shmultiset: public std::multiset<_Key, _Compare, Allocator_t<_Key> > {
public:
    /// aloocator typedef
    typedef Allocator_t<_Key> AllocatorType_t;
    /// parent typedef
    typedef std::multiset<_Key, _Compare, AllocatorType_t> __parent;

    /**
     * @short Default constructor creates no elements.
     * @param __comp Comparator to use.
     */
    shmultiset(const _Compare& __comp = _Compare())
        : __parent(__comp, AllocatorType_t()) {}

    /** 
     * @short Construct %shmultiset from std multiset.
     * @param __other other %shmultiset.
     */
    template <typename _otherKey, typename _otherCompare, typename _otherAllocT>
    shmultiset(const std::multiset<_otherKey, _otherCompare,
                                   _otherAllocT> &__other)
        : __parent(__other.begin(), __other.end(), _Compare(),
                   AllocatorType_t()) {}

    /**
     * @short Builds a %shmultiset from a range.
     * @param __first An input iterator.
     * @param __last An input iterator.
     * @param __comp A comparison functor.
     */
    template <class _InputIterator>
    shmultiset(_InputIterator __first, _InputIterator __last,
            const _Compare& __comp = _Compare())
        : __parent(__first, __last, __comp, AllocatorType_t()) {}
};

}

#endif /* SHALLOCATOR_SHMULTISET_H */

