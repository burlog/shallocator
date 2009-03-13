/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL allocator.
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

#ifndef SHALLOCATOR_SHALLOC_H
#define SHALLOCATOR_SHALLOC_H

#include <mm.h>
#include <stdexcept>

#ifdef DEBUG
#include <iostream>
#endif

namespace SHAllocator {

/**
 * @short STL allocator class implemented via libmm Global API.
 */
template <class Type_t>
class Allocator_t {
public:
    // type definitions

    typedef Type_t           value_type;        //< type of value.
    typedef Type_t          *pointer;           //< pointer to value.
    typedef const Type_t    *const_pointer;     //< const pointer to value.
    typedef Type_t          &reference;         //< reference to value.
    typedef const Type_t    &const_reference;   //< const reference to value.
    typedef std::size_t      size_type;         //< type of size.
    typedef std::ptrdiff_t   difference_type;   //< pointer diff.

    // rebind allocator to type OtherType_t
    template <class OtherType_t>
    struct rebind {
        typedef Allocator_t<OtherType_t> other;
    };

public:
    // constructors & destructor

    /**
     * @short Simple constructor - need initialized mm struct from libmm.
     */
    Allocator_t() throw() {}

    /**
     * @short Simple copy constructor - need copy initialized mm struct.
     * @param other other Allocator_t object.
     */
    Allocator_t(const Allocator_t &/*other*/) throw() {}

    /**
     * @short Simple copy constructor - need initialized mm struct from libmm.
     * @param other other Allocator_t object with other type.
     */
    template <class OtherType_t>
    Allocator_t(const Allocator_t<OtherType_t> &/*other*/) throw() {}

    /**
     * @short Empty destructor - nothing to do because the allocator has no
     * state, state has libmm...
     */
    ~Allocator_t() throw() {}

public:
    // alloc functions

    /**
     * @short Return address of values.
     * @param value value.
     * @return address of values.
     */
    pointer address(reference value) const { return &value;}
    /**
     * @short Return address of values.
     * @param value value.
     * @return address of values.
     */
    const_pointer address(const_reference value) const { return &value;}

    /**
     * @short Return maximum number of elements that can be allocated.
     * @return maximum number of elements that can be allocated.
     */
    size_type max_size() const throw() {
        return MM_available() / sizeof(value_type);
    }

    // allocate but don't initialize num elements of type Type_t
    /**
     * @short Allocate but don't initialize num elements of type Type_t.
     * @param num count of elements.
     * @param void void pointer for placement new operator
     * @return pointer to new allocated memory
     */
    pointer allocate(size_type num, const void * = 0) {
        // alloc
        pointer ret = (pointer) MM_malloc(((num)? num: 1) * sizeof(value_type));

#ifdef DEBUG
        std::cout << "Alloc: " << num << "x" << sizeof(value_type)
            << " bytes  at " << (void *)ret << std::endl;
#endif

        // allocated?
        if (!ret)
            throw std::bad_alloc();
        return ret;
    }

    /**
     * @short Initialize elements of allocated storage p with value value.
     * @param p pointer to memory.
     * @param value initialize by this value.
     */
    template <class OtherType_t>
    void construct(pointer p, const OtherType_t &value) {
        new ((void *)p) Type_t(value);
    }

    /**
     * @short Destroy elements of initialized storage p.
     * @param p call destructor for object at p.
     */
    void destroy(pointer p) { p->~Type_t();}

    /**
     * @short Deallocate storage p of deleted elements.
     * @param p deallocate mem at pointer.
     * @param num count of objects -- not needed free know everything.
     */
    void deallocate(pointer p, size_type num) {
#ifdef DEBUG
        std::cout << "DeAlloc: " << num << "x" << sizeof(value_type)
            << " bytes  at " << (void *)p << std::endl;
#endif

        MM_free((void *)p);
    }
};

/**
 * @short Return that all specializations of this allocator are interchangeable.
 * @param left allocator.
 * @param right allocator.
 * @return always true.
 */
template <class T1_t, class T2_t>
bool operator==(const Allocator_t<T1_t> &, const Allocator_t<T2_t> &) throw() {
    return true;
}

/**
 * @short Return that all specializations of this allocator are interchangeable.
 * @param left allocator.
 * @param right allocator.
 * @return always false.
 */
template <class T1_t, class T2_t>
bool operator!=(const Allocator_t<T1_t> &, const Allocator_t<T2_t> &) throw() {
    return false;
}

/**
 * @short Delete object allocated at shmem.
 * @param __p pointer to object.
 */
template <class Type_t>
void destroy(Type_t *__p) {
    // zero?
    if (__p) {
        // create allocator
        Allocator_t<Type_t> allocator;

        // destruct and deallocate
        allocator.destroy(__p);
        allocator.deallocate(__p, 1);
    }
}

/** 
 * @short Fake class for placement new operator.
 */
class SHAlloc_t {};

/** 
 * @short Empty pointer for placement new operator.
 */
extern SHAlloc_t *SHAlloc;

}

/** 
 * @short Placement new operator. Alloc memory for new object.
 * @param size size of allocated object.
 * @param shalloc fake pointer for choosing this new.
 * @return pointer to alloc memory.
 */
inline void *operator new(std::size_t size, SHAllocator::SHAlloc_t *) {
    // alloc
    void *ret = (void *) MM_malloc(size);

#ifdef DEBUG
   std::cout << "GAlloc: " << "1x" << size
        << " bytes  at " << (void *)ret << std::endl;
#endif

    // allocated?
    if (!ret)
        throw std::bad_alloc();
    return ret;
}

/** 
 * @short Placement new operator. Alloc memory for new object.
 * @param size size of allocated object.
 * @param shalloc fake pointer for choosing this new.
 * @return pointer to alloc memory.
 */
inline void *operator new[](std::size_t size, SHAllocator::SHAlloc_t *) {
    // alloc
    void *ret = (void *) MM_malloc(size);

#ifdef DEBUG
    std::cout << "GAlloc: " << "1x" << size
        << " bytes  at " << (void *)ret << std::endl;
#endif

    // allocated?
    if (!ret)
        throw std::bad_alloc();
    return ret;
}

/** 
 * @short Array placement delete operator.
 * @param __p pointer to delete object
 */
inline void operator delete(void *__p, SHAllocator::SHAlloc_t *) throw() {
#ifdef DEBUG
    std::cout << "GDeAlloc: " << (void *)__p << std::endl;
#endif
    MM_free((void *)__p);
}

/** 
 * @short Array placement delete operator.
 * @param __p pointer to delete object
 */
inline void operator delete[](void *__p, SHAllocator::SHAlloc_t *) throw() {
#ifdef DEBUG
    std::cout << "GDeAlloc: " << (void *)__p << std::endl;
#endif
    MM_free((void *)__p);
}

#endif /* SHALLOCATOR_SHALLOC_H */

