/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL vector.
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

#ifndef SHALLOCATOR_SHVECTOR_H
#define SHALLOCATOR_SHVECTOR_H

#include <vector>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/**
 * @short Shared memory vector.
 */
template <typename _Tp>
class shvector: public std::vector<_Tp, Allocator_t<_Tp> > {
public:
    /// aloocator typedef
    typedef Allocator_t<_Tp> AllocatorType_t;
    /// parent typedef
    typedef std::vector<_Tp, AllocatorType_t> __parent;
    /// type of size
    typedef typename __parent::size_type size_type;
    /// type of size
    typedef typename __parent::value_type value_type;

    /**
     * @short Default constructor creates no elements.
     */
    shvector(): __parent(AllocatorType_t()) {}

    /**
     * @short Create a %shvector with copies of an exemplar element.
     * @param __n The number of elements to initially create.
     * @param __value An element to copy.
     */
    shvector(size_type __n, const value_type& __value = value_type())
        : __parent(__n, __value, AllocatorType_t()) {}

    /** 
     * @short Construct %shvector from std vector.
     * @param __other other %shvector.
     */
    template <typename _otherTp, typename _otherAllocT>
    shvector(const std::vector<_otherTp, _otherAllocT> &__other)
        : __parent(__other.begin(), __other.end(), AllocatorType_t()) {}

    /**
     * @short Builds a %shvector from a range.
     * @param __first An input iterator.
     * @param __last An input iterator.
     */
    template<typename _InputIterator>
    shvector(_InputIterator __first, _InputIterator __last)
        : __parent(__first, __last, AllocatorType_t()) {}
};

}

#endif /* SHALLOCATOR_SHVECTOR_H */

