//
// Created by Itai on 09/06/2021.
//

#include "library2.h"
#include "CarDealershipManager.h"
#include <exception>

void *Init() {
    try {
        return (void*)(new CarDealershipManager());
    }
    catch (std::bad_alloc& e) {
        return nullptr;
    }
}

StatusType AddAgency(void *DS) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->AddAgency();
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->SellCar(agencyID,typeID,k);
}

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->UniteAgencies(agencyID1,agencyID2);
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res) {
    if (DS == nullptr) return INVALID_INPUT;
    return ((CarDealershipManager*)DS)->GetIthSoldType(agencyID,i,res);
}

void Quit(void** DS) {
    if (DS != nullptr) delete ((CarDealershipManager*)*DS);
    *DS = nullptr;
}
