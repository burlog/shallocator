/*
 * FILE             $Id$
 *
 * DESCRIPTION      Shared memory STL auto_ptr.
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
 *       2007-06-12 (bukovsky)
 *                  Stolen from GNU stdc++ STL.
 */

#ifndef SHALLOCATOR_SHMEMORY_H
#define SHALLOCATOR_SHMEMORY_H

#include <shallocator/shalloc.h>

namespace SHAllocator {

  /**
   *  A wrapper class to provide auto_ptr with reference semantics.
   *  For example, an auto_ptr can be assigned (or constructed from)
   *  the result of a function which returns an auto_ptr by value.
   *
   *  All the auto_ptr_ref stuff should happen behind the scenes.
   */
  template<typename _Tp1>
    struct shauto_ptr_ref
    {
      _Tp1* _M_ptr;

      explicit
      shauto_ptr_ref(_Tp1* __p): _M_ptr(__p) { }
    };


  /**
   *  @brief  A simple smart pointer providing strict ownership semantics.
   *
   *  The Standard says:
   *  <pre>
   *  An @c auto_ptr owns the object it holds a pointer to.  Copying
   *  an @c auto_ptr copies the pointer and transfers ownership to the
   *  destination.  If more than one @c auto_ptr owns the same object
   *  at the same time the behavior of the program is undefined.
   *
   *  The uses of @c auto_ptr include providing temporary
   *  exception-safety for dynamically allocated memory, passing
   *  ownership of dynamically allocated memory to a function, and
   *  returning dynamically allocated memory from a function.  @c
   *  auto_ptr does not meet the CopyConstructible and Assignable
   *  requirements for Standard Library <a
   *  href="tables.html#65">container</a> elements and thus
   *  instantiating a Standard Library container with an @c auto_ptr
   *  results in undefined behavior.
   *  </pre>
   *  Quoted from [20.4.5]/3.
   *
   *  Good examples of what can and cannot be done with auto_ptr can
   *  be found in the libstdc++ testsuite.
   *
   *  @if maint
   *  _GLIBCXX_RESOLVE_LIB_DEFECTS
   *  127.  auto_ptr<> conversion issues
   *  These resolutions have all been incorporated.
   *  @endif
   */
  template<typename _Tp>
    class shauto_ptr
    {
    private:
      _Tp* _M_ptr;

    public:
      /// The pointed-to type.
      typedef _Tp element_type;

      /**
       *  @brief  An %auto_ptr is usually constructed from a raw pointer.
       *  @param  p  A pointer (defaults to NULL).
       *
       *  This object now @e owns the object pointed to by @a p.
       */
      explicit
      shauto_ptr(element_type* __p = 0) throw() : _M_ptr(__p) { }

      /**
       *  @brief  An %auto_ptr can be constructed from another %auto_ptr.
       *  @param  a  Another %auto_ptr of the same type.
       *
       *  This object now @e owns the object previously owned by @a a,
       *  which has given up ownsership.
       */
      shauto_ptr(shauto_ptr& __a) throw() : _M_ptr(__a.release()) { }

      /**
       *  @brief  An %auto_ptr can be constructed from another %auto_ptr.
       *  @param  a  Another %auto_ptr of a different but related type.
       *
       *  A pointer-to-Tp1 must be convertible to a
       *  pointer-to-Tp/element_type.
       *
       *  This object now @e owns the object previously owned by @a a,
       *  which has given up ownsership.
       */
      template<typename _Tp1>
        shauto_ptr(shauto_ptr<_Tp1>& __a) throw() : _M_ptr(__a.release()) { }

      /**
       *  @brief  %auto_ptr assignment operator.
       *  @param  a  Another %auto_ptr of the same type.
       *
       *  This object now @e owns the object previously owned by @a a,
       *  which has given up ownsership.  The object that this one @e
       *  used to own and track has been deleted.
       */
      shauto_ptr&
      operator=(shauto_ptr& __a) throw()
      {
        reset(__a.release());
        return *this;
      }

      /**
       *  @brief  %auto_ptr assignment operator.
       *  @param  a  Another %auto_ptr of a different but related type.
       *
       *  A pointer-to-Tp1 must be convertible to a pointer-to-Tp/element_type.
       *
       *  This object now @e owns the object previously owned by @a a,
       *  which has given up ownsership.  The object that this one @e
       *  used to own and track has been deleted.
       */
      template<typename _Tp1>
        shauto_ptr&
        operator=(shauto_ptr<_Tp1>& __a) throw()
        {
          reset(__a.release());
          return *this;
        }

      /**
       *  When the %auto_ptr goes out of scope, the object it owns is
       *  deleted.  If it no longer owns anything (i.e., @c get() is
       *  @c NULL), then this has no effect.
       *
       *  @if maint
       *  The C++ standard says there is supposed to be an empty throw
       *  specification here, but omitting it is standard conforming.  Its
       *  presence can be detected only if _Tp::~_Tp() throws, but this is
       *  prohibited.  [17.4.3.6]/2
       *  @endif
       */
      ~shauto_ptr() { SHAllocator::destroy(_M_ptr); }

      /**
       *  @brief  Smart pointer dereferencing.
       *
       *  If this %auto_ptr no longer owns anything, then this
       *  operation will crash.  (For a smart pointer, "no longer owns
       *  anything" is the same as being a null pointer, and you know
       *  what happens when you dereference one of those...)
       */
      element_type&
      operator*() const throw()
      {
        _GLIBCXX_DEBUG_ASSERT(_M_ptr != 0);
        return *_M_ptr;
      }

      /**
       *  @brief  Smart pointer dereferencing.
       *
       *  This returns the pointer itself, which the language then will
       *  automatically cause to be dereferenced.
       */
      element_type*
      operator->() const throw()
      {
        _GLIBCXX_DEBUG_ASSERT(_M_ptr != 0);
        return _M_ptr;
      }

      /**
       *  @brief  Bypassing the smart pointer.
       *  @return  The raw pointer being managed.
       *
       *  You can get a copy of the pointer that this object owns, for
       *  situations such as passing to a function which only accepts
       *  a raw pointer.
       *
       *  @note  This %auto_ptr still owns the memory.
       */
      element_type*
      get() const throw() { return _M_ptr; }

      /**
       *  @brief  Bypassing the smart pointer.
       *  @return  The raw pointer being managed.
       *
       *  You can get a copy of the pointer that this object owns, for
       *  situations such as passing to a function which only accepts
       *  a raw pointer.
       *
       *  @note  This %auto_ptr no longer owns the memory.  When this object
       *  goes out of scope, nothing will happen.
       */
      element_type*
      release() throw()
      {
        element_type* __tmp = _M_ptr;
        _M_ptr = 0;
        return __tmp;
      }

      /**
       *  @brief  Forcibly deletes the managed object.
       *  @param  p  A pointer (defaults to NULL).
       *
       *  This object now @e owns the object pointed to by @a p.  The
       *  previous object has been deleted.
       */
      void
      reset(element_type* __p = 0) throw()
      {
        if (__p != _M_ptr)
          {
            SHAllocator::destroy(_M_ptr);
            _M_ptr = __p;
          }
      }

      /**
       *  @brief  Automatic conversions
       *
       *  These operations convert an %auto_ptr into and from an auto_ptr_ref
       *  automatically as needed.  This allows constructs such as
       *  @code
       *    auto_ptr<Derived>  func_returning_auto_ptr(.....);
       *    ...
       *    auto_ptr<Base> ptr = func_returning_auto_ptr(.....);
       *  @endcode
       */
      shauto_ptr(shauto_ptr_ref<element_type> __ref) throw()
      : _M_ptr(__ref._M_ptr) { }

      shauto_ptr&
      operator=(shauto_ptr_ref<element_type> __ref) throw()
      {
        if (__ref._M_ptr != this->get())
          {
            SHAllocator::destroy(_M_ptr);
            _M_ptr = __ref._M_ptr;
          }
        return *this;
      }

      template<typename _Tp1>
        operator shauto_ptr_ref<_Tp1>() throw()
        { return shauto_ptr_ref<_Tp1>(this->release()); }

      template<typename _Tp1>
        operator shauto_ptr<_Tp1>() throw()
        { return shauto_ptr<_Tp1>(this->release()); }
  };

}

#endif /* SHALLOCATOR_SHMEMORY_H */

