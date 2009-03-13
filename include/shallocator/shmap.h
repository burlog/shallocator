/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL map.
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
 *       2007-04-23 (bukovsky)
 *                  First draft.
 */

#ifndef SHALLOCATOR_SHMAP_H
#define SHALLOCATOR_SHMAP_H

#include <map>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/** 
 * @short Shared memory map.
 */
template <typename _Key, typename _Tp, typename _Compare = std::less<_Key> >
class shmap: public std::map<_Key, _Tp, _Compare,
                             Allocator_t<std::pair<const _Key, _Tp> > > {
public:
    /// aloocator typedef
    typedef Allocator_t<std::pair<const _Key, _Tp> > AllocatorType_t;
    /// parent typedef
    typedef std::map<_Key, _Tp, _Compare, AllocatorType_t> __parent;

    /** 
     * @short Default constructor creates no elements.
     * @param __comp A comparison functor.
     */
    shmap(const _Compare &__comp = _Compare())
        : __parent(__comp, AllocatorType_t()) {}

    /** 
     * @short Construct %shmap from std map.
     * @param __other other sh map.
     */
    template <typename _otherKey, typename _otherTp,
              typename _otherCompare, typename _otherAllocT>
    shmap(const std::map<_otherKey, _otherTp, _otherCompare,
                         _otherAllocT> &__other)
        : __parent(__other.begin(), __other.end(), _Compare(),
                   AllocatorType_t()) {}

    /** 
     * @short Builds a %shmap from a range.
     * @param __first An input iterator.
     * @param __last An input iterator.
     * @param __comp A comparison functor.
     */
    template <typename _InputIterator>
    shmap(_InputIterator __first, _InputIterator __last,
          const _Compare &__comp = _Compare())
        : __parent(__first, __last, __comp, AllocatorType_t()) {}
};

}

#endif /* SHALLOCATOR_SHALLOC_H */

