/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL multimap.
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

#ifndef SHALLOCATOR_SHMULTIMAP_H
#define SHALLOCATOR_SHMULTIMAP_H

#include <map>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/** 
 * @short Shared memory multimap.
 */
template <typename _Key, typename _Tp, typename _Compare = std::less<_Key> >
class shmultimap: public std::multimap<_Key, _Tp, _Compare,
                             Allocator_t<std::pair<const _Key, _Tp> > > {
public:
    /// aloocator typedef
    typedef Allocator_t<std::pair<const _Key, _Tp> > AllocatorType_t;
    /// parent typedef
    typedef std::multimap<_Key, _Tp, _Compare, AllocatorType_t> __parent;

    /** 
     * @short Default constructor creates no elements.
     * @param __comp A comparison functor.
     */
    shmultimap(const _Compare &__comp = _Compare())
        : __parent(__comp, AllocatorType_t()) {}

    /** 
     * @short Construct %shmultimap from std multimap.
     * @param __other other sh multimap.
     */
    template <typename _otherKey, typename _otherTp,
              typename _otherCompare, typename _otherAllocT>
    shmultimap(const std::multimap<_otherKey, _otherTp, _otherCompare,
                         _otherAllocT> &__other)
        : __parent(__other.begin(), __other.end(), _Compare(),
                   AllocatorType_t()) {}

    /** 
     * @short Builds a %shmultimap from a range.
     * @param __first An input iterator.
     * @param __last An input iterator.
     * @param __comp A comparison functor.
     */
    template <typename _InputIterator>
    shmultimap(_InputIterator __first, _InputIterator __last,
          const _Compare &__comp = _Compare())
        : __parent(__first, __last, __comp, AllocatorType_t()) {}
};

}

#endif /* SHALLOCATOR_SHMULTIMAP_H */

