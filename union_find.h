//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_UNION_FIND_H
#define DS_HW2_UNION_FIND_H

#include "vector.h"
#include "shared_pointer.h"
#include "set_node.h"
#include "set.h"

template<typename T>
class UnionFind {
private:
    Vector<SharedPointer<SetNode<T>>> items;
    int sets;
public:
    int getNumberOfItems();
    int getNumberOfSets();
    Set<T> makeSet(int i);
    Set<T> find(int i);
    Set<T> unionSets(Set<T> s1, Set<T> s2);
};

template<typename T>
Set<T> UnionFind<T>::makeSet(int i) {
    // TODO
    if (i >= items.getCount()) {

    }
    return items.add();
}

template<typename T>
Set<T> UnionFind<T>::find(int i) {
    if (i >= items.getCount())
        return nullptr;

    SharedPointer<SetNode<T>> n = items[i];

    SharedPointer<SetNode<T>> r = n;
    while (!r->parent.isEmpty()) {
        r = r->parent;
    }

    while (!n->parent.isEmpty()) {
        auto tmp = n->parent;
        n->parent = r;
        n = tmp;
    }

    return Set<T>{};
}

template<typename T>
Set<T> UnionFind<T>::unionSets(Set<T> s1, Set<T> s2) {
    return Set<T>();
}

template<typename T>
int UnionFind<T>::getNumberOfItems() {
    return items.getCount();
}

template<typename T>
int UnionFind<T>::getNumberOfSets() {
    return sets;
}

#endif //DS_HW2_UNION_FIND_H
