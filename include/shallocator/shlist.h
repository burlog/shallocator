/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL list.
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

#ifndef SHALLOCATOR_SHLIST_H
#define SHALLOCATOR_SHLIST_H

#include <list>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/**
 * @short Shared memory list.
 */
template <typename _Tp>
class shlist: public std::list<_Tp, Allocator_t<_Tp> > {
public:
    /// aloocator typedef
    typedef Allocator_t<_Tp> AllocatorType_t;
    /// parent typedef
    typedef std::list<_Tp, AllocatorType_t> __parent;
    /// type of size
    typedef typename __parent::size_type size_type;
    /// type of size
    typedef typename __parent::value_type value_type;

    /**
     * @short Default constructor creates no elements.
     */
    shlist(): __parent(AllocatorType_t()) {}

    /**
     * @short Create a %shlist with copies of an exemplar element.
     * @param __n The number of elements to initially create.
     * @param __value An element to copy.
     */
    shlist(size_type __n, const value_type& __value = value_type())
        : __parent(__n, __value, AllocatorType_t()) {}

    /** 
     * @short Construct %shlist from std list.
     * @param __other other %shlist.
     */
    template <typename _otherTp, typename _otherAllocT>
    shlist(const std::list<_otherTp, _otherAllocT> &__other)
        : __parent(__other.begin(), __other.end(), AllocatorType_t()) {}

    /**
     * @short Builds a %shlist from a range.
     * @param __first An input iterator.
     * @param __last An input iterator.
     */
    template<typename _InputIterator>
    shlist(_InputIterator __first, _InputIterator __last)
        : __parent(__first, __last, AllocatorType_t()) {}
};

}

#endif /* SHALLOCATOR_SHLIST_H */

