/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL basic_string.
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

#ifndef SHALLOCATOR_SHSTRING_H
#define SHALLOCATOR_SHSTRING_H

#include <string>
#include <shallocator/shalloc.h>

namespace SHAllocator {

/**
 * @short Shared memory string.
 */
template <typename _CharT, typename _Traits>
class shbasic_string: public std::basic_string<_CharT, _Traits,
                                               Allocator_t<_CharT> > {
public:
    /// aloocator typedef
    typedef Allocator_t<_CharT> AllocatorType_t;
    /// parent typedef
    typedef std::basic_string<_CharT, _Traits, AllocatorType_t> __parent;
    /// type of size
    typedef typename __parent::size_type size_type;

    /**
     * @short Default constructor creates an empty string.
     */
    shbasic_string(): __parent(AllocatorType_t()) {}

    /**
     * @short Construct %shstring as copy of a std::string.
     * @param __str Source string.
     */
    shbasic_string(const std::basic_string<_CharT, _Traits> &__str)
        : __parent(__str.data(), __str.size(), AllocatorType_t()) {}

    // probably not needed, use constructor bellow
    //
    ///**
    // * @short Construct %shstring as copy of a substring.
    // * @param __str Source string.
    // * @param __pos Index of first character to copy from.
    // * @param __n Number of characters to copy.
    // */
    //shbasic_string(const shbasic_string &__str, size_type __pos, size_type __n)
    //    : __parent(__str, __pos, __n, AllocatorType_t()) {}

    /**
     * @short Construct %shstring as copy of a substring.
     * @param __str Source string.
     * @param __pos Index of first character to copy from.
     * @param __n Number of characters to copy.
     */
    shbasic_string(const std::basic_string<_CharT, _Traits> &__str,
            size_type __pos, size_type __n)
        : __parent(__str.data(), __pos, __n, AllocatorType_t()) {}

    /**
     * @short Construct %shstring as copy of a C string.
     * @param __s Source C string.
     */
    shbasic_string(const _CharT* __s): __parent(__s, AllocatorType_t()) {}

    /**
     * @short Construct %shstring as multiple characters.
     * @param __n Number of characters.
     * @param __c Character to use.
     */
    shbasic_string(size_type __n, _CharT __c)
        : __parent(__n, __c, AllocatorType_t()) {}

    /**
     * @short Construct %shstring as copy of a range.
     * @param __beg Start of range.
     * @param __end End of range.
     */
    template <class _InputIterator>
    shbasic_string(_InputIterator __beg, _InputIterator __end)
        : __parent(__beg, __end, AllocatorType_t()) {}
};

/**
 * @short string definition.
 */
typedef shbasic_string<char, std::char_traits<char> > shstring;

/**
 * @short wstring definition.
 */
typedef shbasic_string<wchar_t, std::char_traits<wchar_t> > shwstring;

}

#endif /* SHALLOCATOR_SHSTRING_H */

