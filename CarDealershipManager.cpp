//
// Created by Itai on 09/06/2021.
//

#include "CarDealershipManager.h"

StatusType CarDealershipManager::AddAgency() {
    return FAILURE;
}

StatusType CarDealershipManager::SellCar(int agencyID, int typeID, int k) {
    return FAILURE;
}

StatusType CarDealershipManager::UniteAgencies(int agencyID1, int agencyID2) {
    return FAILURE;
}

StatusType CarDealershipManager::GetIthSoldType(int agencyID, int i, int *res) {
    return FAILURE;
}

CarDealershipManager::CarDealershipManager() : agencies(init,unionAgencies) {}

SharedPointer<Agency> CarDealershipManager::init() {
    auto a = SharedPointer<Agency>(new Agency);
    a->typesTree = SharedPointer<BTree23<CarNode>>(new BTree23<CarNode>());
    a->sellsTree = SharedPointer<BTree23<SellsNode>>(new BTree23<SellsNode>());
    return a;
}

SharedPointer<Agency> CarDealershipManager::unionAgencies(SharedPointer<Agency> a1, SharedPointer<Agency> a2) {
    auto a = SharedPointer<Agency>(new Agency);
    a->typesTree = SharedPointer<BTree23<CarNode>>(new BTree23<CarNode>(a1->typesTree,a2->typesTree));
    a->sellsTree = SharedPointer<BTree23<SellsNode>>(new BTree23<SellsNode>(a1->sellsTree,a2->sellsTree));
}
