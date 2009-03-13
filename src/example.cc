/*
 * FILE             $Id$
 *
 * DESCRIPTION      Example use.
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
 *       2007-04-24 (bukovsky)
 *                  First draft.
 */

#include <errno.h>
#include <iostream>
#include <shallocator/shalloc.h>
#include <shallocator/shstring.h>
#include <shallocator/shmap.h>
#include <shallocator/shset.h>
#include <shallocator/shvector.h>
#include <shallocator/shlist.h>
#include <shallocator/shmultiset.h>
#include <shallocator/shmultimap.h>
#include <shallocator/shdeque.h>
#include <shallocator/shstack.h>
#include <shallocator/shmemory.h>

/**
 * @short Simple sh mem holder, parent proces destroy MM struct.
 */
class SHMem_t {
public:
    /**
     * @short Create shmem and save parent proces pid.
     * @param size Size of sh mem what you want.
     */
    SHMem_t(size_t size): parent(getpid()) {
        // allocate shmem
        if (!MM_create(size, 0)) {
            std::cout << "NOTCREATE: " << MM_error() << std::endl;
            throw std::bad_alloc();
        }

        std::cout << "CREATE " << std::endl;
    }

    /**
     * @short Destroy MM if you are parent.
     */
    ~SHMem_t() {
#if 0
        MM_display_info();
#endif

        if (getpid() == parent) {
            std::cout << "DESTROY " << std::endl;
            MM_destroy();
        } else
            std::cout << "NDESTROY " << std::endl;
    }

public:
    pid_t parent;   //< pid of parent proces.
};

typedef SHAllocator::shmap<int, SHAllocator::shstring> Map_t;
typedef SHAllocator::shset<SHAllocator::shstring> Set_t;
typedef SHAllocator::shvector<SHAllocator::shstring> Vector_t;
typedef SHAllocator::shlist<SHAllocator::shstring> List_t;
typedef SHAllocator::shmultiset<SHAllocator::shstring> MultiSet_t;
typedef SHAllocator::shmultimap<int, SHAllocator::shstring> MultiMap_t;
typedef SHAllocator::shstack<
    SHAllocator::shstring, SHAllocator::shdeque<SHAllocator::shstring>
    > Stack_t;

/*
 * This is very simple example. If you want SHAllocator use in real word, you
 * need synchronized acces to sh allocated structures propably by semaphores.
 */
int main() {
#if 0
    MM_display_info();
#endif

    // alloc shmem. 0 means to allocate the maximum allowed size.
    SHMem_t shmem(1024*1024);
#if 0
    MM_display_info();
#endif

    // create shmap
    Map_t *map = 0;
    {
        std::map<int, SHAllocator::shstring> xmap;
        xmap.insert(std::make_pair(100, "XMAP"));

        map = new (SHAllocator::SHAlloc) Map_t(xmap);
    }

    // add data to map
    map->insert(std::make_pair(1, "A"));
    map->insert(std::make_pair(2, "B"));
    map->insert(std::make_pair(3, "C"));
    map->insert(std::make_pair(4, "D"));
    map->insert(std::make_pair(5, "E"));

    Set_t *set = new (SHAllocator::SHAlloc) Set_t();

    MultiSet_t *multiset = new (SHAllocator::SHAlloc) MultiSet_t();

    MultiMap_t *multimap = new (SHAllocator::SHAlloc) MultiMap_t();

    Vector_t *vector = new (SHAllocator::SHAlloc)
        Vector_t(1, SHAllocator::shstring("klara"));
    vector->resize(10);

    List_t *list = new (SHAllocator::SHAlloc)
        List_t(1, SHAllocator::shstring("klara"));
    list->resize(10);

    std::vector<std::string> stdvector;
    stdvector.push_back("stdstring 1");
    stdvector.push_back("stdstring 2");
    stdvector.push_back("stdstring 3");

    Vector_t *vector2 = new (SHAllocator::SHAlloc) Vector_t(stdvector);

    // dump vector
    for (Vector_t::const_iterator it = vector2->begin();
            it != vector2->end(); ++it)
        std::cout << "INIT: " << *it << std::endl;

    std::set<std::string> stdset;
    stdset.insert("stdstring 1");
    stdset.insert("stdstring 2");
    stdset.insert("stdstring 3");

    Set_t *set2 = new (SHAllocator::SHAlloc) Set_t(stdset);

    // dump set
    for (Set_t::const_iterator it = set2->begin();
            it != set2->end(); ++it)
        std::cout << "INITSET: " << *it << std::endl;

    std::map<int, std::string> stdmap;
    stdmap.insert(std::make_pair(1, "stdstring 1"));
    stdmap.insert(std::make_pair(2, "stdstring 2"));
    stdmap.insert(std::make_pair(3, "stdstring 3"));

    Map_t *map2 = new (SHAllocator::SHAlloc) Map_t(stdmap);

    // dump map
    for (Map_t::const_iterator it = map2->begin();
            it != map2->end(); ++it)
        std::cout << "INITMAP: " << it->first
            << " -> " << it->second << std::endl;

    SHAllocator::destroy(set2);
    SHAllocator::destroy(map2);
    SHAllocator::destroy(vector2);

    Stack_t *stack = new (SHAllocator::SHAlloc) Stack_t();
    stack->push("nula");

    // do fork
    if (fork()) {
        // PARENT

        set->insert("franta");
        set->insert("pepa");
        set->insert("honza");

        multiset->insert("franta");
        multiset->insert("pepa");
        multiset->insert("honza");
        multiset->insert("franta");
        multiset->insert("pepa");
        multiset->insert("honza");

        (*vector)[1] = SHAllocator::shstring("karolina");
        (*vector)[2] = "johanka";
        (*vector)[3] = "dorka";

        list->push_back("karolina");
        list->push_front("dorka");
        list->push_back("johanka");

        // add some data
        map->insert(std::make_pair(6, std::string("N99", 1, 3)));
        map->insert(std::make_pair(7, "9"));
        map->insert(std::make_pair(8, "9"));
        map->insert(std::make_pair(9, "9"));
        map->insert(std::make_pair(10, "9"));
        map->insert(std::make_pair(11, "9"));

        // add some data
        multimap->insert(std::make_pair(6, SHAllocator::shstring("N99", 1, 3)));
        multimap->insert(std::make_pair(6, "9"));
        multimap->insert(std::make_pair(7, "9"));
        multimap->insert(std::make_pair(7, "9"));
        multimap->insert(std::make_pair(8, "9"));
        multimap->insert(std::make_pair(8, "9"));

        // add some data to stack
        stack->push("jedna");
        stack->push("dva");
        stack->push("tri");

        // wait for child change map
        sleep(2);

        // dump map
        for (Map_t::const_iterator it = map->begin(); it != map->end(); ++it)
            std::cout
                << "PARENT: MAP: " << it->first << " -> " << it->second << std::endl;

        if (set->empty())
            std::cout << "PARENT: SET IS EMPTY" << std::endl;

        if (multiset->empty())
            std::cout << "PARENT: MULTISET IS EMPTY" << std::endl;

        // wait while child exit
        sleep(1);

        // dump vector
        for (Vector_t::const_iterator it = vector->begin();
                it != vector->end(); ++it)
            std::cout << "PARENT: VECTOR: " << *it << std::endl;

        // dump list
        for (List_t::const_iterator it = list->begin();
                it != list->end(); ++it)
            std::cout << "PARENT: LIST: " << *it << std::endl;

        // destroy map
        SHAllocator::destroy(map);
        SHAllocator::destroy(set);
        SHAllocator::destroy(vector);
        SHAllocator::destroy(list);
        SHAllocator::destroy(multiset);
        SHAllocator::destroy(multimap);

    } else {
        // CHILD
#if 0
        MM_display_info();
#endif

        // wait for parent change map
        sleep(1);

        // dump map
        for (Map_t::const_iterator it = map->begin(); it != map->end(); ++it)
            std::cout
                << "CHILD: MAP: " << it->first
                << " -> " << it->second << std::endl;

        // dump set
        for (Set_t::const_iterator it = set->begin(); it != set->end(); ++it)
            std::cout << "CHILD: SET: " << *it << std::endl;

        // dump multiset
        for (MultiSet_t::const_iterator it = multiset->begin();
                it != multiset->end(); ++it)
            std::cout << "CHILD: MULTISET: " << *it << std::endl;

        // dump multimap
        for (MultiMap_t::const_iterator it = multimap->begin();
                it != multimap->end(); ++it)
            std::cout
                << "CHILD: MULTIMAP: " << it->first
                << " -> " << it->second << std::endl;

        while (!stack->empty()) {
            std::cout << "CHILD: STACK: " << stack->top() << std::endl;
            stack->pop();
        }

        // add to vector
        vector->push_back("vojta");

        // add to list
        list->push_back("vojta");

        // clear set
        set->clear();

        // clear multiset
        multiset->clear();

        // erase some data
        map->erase(1);
        map->erase(2);
        map->erase(3);
        map->erase(4);
        map->erase(5);

        sleep(1);

#if 0
        MM_display_info();
#endif

    }

    return EXIT_SUCCESS;
}

