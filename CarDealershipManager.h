//
// Created by Itai on 09/06/2021.
//

#ifndef DS_HW2_CARDEALERSHIPMANAGER_H
#define DS_HW2_CARDEALERSHIPMANAGER_H

#include "library2.h"
#include "union_find.h"
#include "agency.h"

class CarDealershipManager {
private:
    UnionFind<Agency> agencies;
    static SharedPointer<Agency> init();
    static SharedPointer<Agency> unionAgencies(SharedPointer<Agency> a1, SharedPointer<Agency> a2);
public:
    CarDealershipManager();
    StatusType AddAgency();
    StatusType SellCar(int agencyID, int typeID, int k);
    StatusType UniteAgencies(int agencyID1, int agencyID2);
    StatusType GetIthSoldType(int agencyID, int i, int* res);
};


#endif //DS_HW2_CARDEALERSHIPMANAGER_H
