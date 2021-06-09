//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_UNION_FIND_H
#define DS_HW2_UNION_FIND_H

#include "vector.h"
#include "shared_pointer.h"
#include "node.h"
#include "set.h"

template<typename T>
class UnionFind {
private:
    Vector<SharedPointer<Node<T>>> items;
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
    return Set<T>();
}

template<typename T>
Set<T> UnionFind<T>::find(int i) {
    return Set<T>();
}

template<typename T>
Set<T> UnionFind<T>::unionSets(Set<T> s1, Set<T> s2) {
    return Set<T>();
}

template<typename T>
int UnionFind<T>::getNumberOfItems() {
    return 0;
}

template<typename T>
int UnionFind<T>::getNumberOfSets() {
    return 0;
}

#endif //DS_HW2_UNION_FIND_H
