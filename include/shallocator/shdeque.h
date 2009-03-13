/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL deque.
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

#ifndef SHALLOCATOR_SHDEQUE_H
#define SHALLOCATOR_SHDEQUE_H

#include <deque>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/**
 * @short Shared memory deque.
 */
template <typename _Tp>
class shdeque: public std::deque<_Tp, Allocator_t<_Tp> > {
public:
    /// aloocator typedef
    typedef Allocator_t<_Tp> AllocatorType_t;
    /// parent typedef
    typedef std::deque<_Tp, AllocatorType_t> __parent;
    /// type of size
    typedef typename __parent::size_type size_type;
    /// type of size
    typedef typename __parent::value_type value_type;

    /**
     * @short Default constructor creates no elements.
     */
    shdeque(): __parent(AllocatorType_t()) {}

    /**
     * @short Create a %shdeque with copies of an exemplar element.
     * @param __n The number of elements to initially create.
     * @param __value An element to copy.
     */
    shdeque(size_type __n, const value_type& __value = value_type())
        : __parent(__n, __value, AllocatorType_t()) {}

    /** 
     * @short Construct %shdeque from std deque.
     * @param __other other %shdeque.
     */
    template <typename _otherTp, typename _otherAllocT>
    shdeque(const std::deque<_otherTp, _otherAllocT> &__other)
        : __parent(__other.begin(), __other.end(), AllocatorType_t()) {}

    /**
     * @short Builds a %shdeque from a range.
     * @param __first An input iterator.
     * @param __last An input iterator.
     */
    template<typename _InputIterator>
    shdeque(_InputIterator __first, _InputIterator __last)
        : __parent(__first, __last, AllocatorType_t()) {}
};

}

#endif /* SHALLOCATOR_SHDEQUE_H */

