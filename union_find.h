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
    SharedPointer<T> (*init)();
    SharedPointer<T> (*unionValues)(SharedPointer<T>, SharedPointer<T>);
public:
    explicit UnionFind(SharedPointer<T> (*init)(), SharedPointer<T> (*unionValues)(SharedPointer<T> item1, SharedPointer<T> item2));
    int getNumberOfItems();
    int getNumberOfSets();
    Set<T> makeSet();
    Set<T> find(int i);
    Set<T> unionSets(Set<T> s1, Set<T> s2);
};

template<typename T>
Set<T> UnionFind<T>::makeSet() {
    auto setNode = SharedPointer<SetNode<T>>(
            new SetNode<T>(
                    { .value=init(),
                      .parent=SharedPointer<T>(),
                      .size=1
                    }
            ));

    items.add(setNode);

    sets++;
    return {.value=setNode->value,.size=setNode->size,.root=setNode};
}

template<typename T>
Set<T> UnionFind<T>::find(int i) {
    if (i >= items.getCount())
        return {.value=SharedPointer<T>(),.root=SharedPointer<T>()};

    SharedPointer<SetNode<T>> n = items[i];

    // find
    SharedPointer<SetNode<T>> r = n;
    while (!r->parent.isEmpty()) {
        r = r->parent;
    }

    // shrink
    while (!n->parent.isEmpty()) {
        auto tmp = n->parent;
        n->parent = r;
        n = tmp;
    }

    return {.root=r,.size=r->size,.value=r->value};
}

template<typename T>
Set<T> UnionFind<T>::unionSets(Set<T> s1, Set<T> s2) {
    bool s1Smaller = s1.size < s2.size;
    Set<T> small = s1Smaller ? s1 : s2;
    Set<T> big = s1Smaller ? s2 : s1;

    small.root->parent = big.root;
    big.size += small.size;
    big.value = unionValues(big.value, small.value);

    sets--;
    return {.root=big,.size=big.size,.value=big.value};
}

template<typename T>
int UnionFind<T>::getNumberOfItems() {
    return items.getCount();
}

template<typename T>
int UnionFind<T>::getNumberOfSets() {
    return sets;
}

template<typename T>
UnionFind<T>::UnionFind(SharedPointer<T> (*init)(), SharedPointer<T> (*unionValues)(SharedPointer<T>, SharedPointer<T>))
                    : init(init), unionValues(unionValues) { }

#endif //DS_HW2_UNION_FIND_H
