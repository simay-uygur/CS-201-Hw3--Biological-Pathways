//
// Created by Simay Uygur 22203328 Section 1
//

#include "BioPathway.h"
#include <string>
#include <iostream>

std::string BioPathway::toString() {
    return "Pathway " + std::to_string(biologicalPathwayId) + " : " + biologicalPathwayName + " (" + std::to_string(proteinCount) + " Proteins) ("
           + std::to_string(totalGenes()) + " Genes)";
}

int BioPathway::getProteinCount() const {
    return proteinCount;
}

int BioPathway::totalGenes() {
    int a =0;
    if(proteinCount == 0)
        return 0;

    Protein* curP = proteinList;

    while(curP != nullptr)
    {
        a+= curP->getGeneCount();
        curP = curP->getNextPro();
    }
    return a;

}

Protein &BioPathway::getProtein(int pos) {

    if (pos < 1 || pos > proteinCount) {
        throw std::out_of_range("Invalid position");
    }

    Protein* currP = proteinList;

    for (int i = 1; i < pos; ++i) {
        currP = currP->getNextPro();
    }

    return *currP;
}

BioPathway::BioPathway(int id, std::string name): biologicalPathwayId(id), biologicalPathwayName(name) ,proteinList(
        nullptr), nextPathway(nullptr), proteinCount(0){

}

BioPathway::~BioPathway() {

    while (proteinList != nullptr) {
        Protein* p = proteinList;
        proteinList = proteinList->getNextPro();
        delete p;
    }
}

bool BioPathway::insertProtein(int insertPos, Protein *p) {

    if (insertPos < 1 || insertPos > proteinCount + 1)
        return false;

    if (insertPos == 1) {
        p->setNextPro(proteinList);
        proteinList = p;
    }
    else {
        Protein* prevProtein = nullptr;
        Protein* currPro = proteinList;

        for(int a=1; a< insertPos && currPro != nullptr; a++)
        {
            prevProtein = currPro;
            currPro = currPro-> getNextPro();
        }

        prevProtein->setNextPro(p);
        p->setNextPro(currPro);


    }

    proteinCount++;
    return true;
}

bool BioPathway::removeProtein(int proteinId) {

    Protein* currentProteinTraversing = proteinList;
    Protein* prevProtein = nullptr;

    while (currentProteinTraversing != nullptr) {

        if (currentProteinTraversing->getId() == proteinId) {

            if (prevProtein == nullptr) {
                proteinList = currentProteinTraversing->getNextPro();
            }
            else
            {
                prevProtein->setNextPro(currentProteinTraversing->getNextPro());
            }
            delete currentProteinTraversing;
            proteinCount--;
            return true;
        }
        prevProtein = currentProteinTraversing;
        currentProteinTraversing = currentProteinTraversing->getNextPro();
    }

    return false;
}


BioPathway *BioPathway::getNext() {
    return nextPathway;
}

std::string BioPathway::getName() {
    return biologicalPathwayName;
}


int BioPathway::getId() const {
    return biologicalPathwayId;
}

void BioPathway::bioPathwayDisp() {
    if(proteinCount == 0 )
        std::cout << "There are no proteins to show in pathway " << std::to_string(biologicalPathwayId) << std::endl;
    else
    {

        std::cout << "Proteins in pathway " << std::to_string(biologicalPathwayId) << ":" << std::endl;

        for(int i=1; i<= proteinCount; ++i)
        {
            std::cout << getProtein(i).toString() << std::endl;
        }

    }
}

void BioPathway::setNext(BioPathway *p) {

    nextPathway = p;
}

int BioPathway::findProteinIndex(int pId) {

    int i=1;
    Protein* curP = proteinList;

    while (curP  != nullptr )
    {
        if(curP->getId() == pId)
            return i;
        curP = curP->getNextPro();
        i++;
    }

    return  -1;
}

void BioPathway::addProSorted(const int pID) {


    Protein* addingPro = new Protein(pID);
    int p = findposOfInsertion(pID);
    insert(p,addingPro);
    proteinCount++;



}

int BioPathway::findposOfInsertion(int id){

    int pos = 1;
    Protein* cur = proteinList;

    while(cur != nullptr && id > cur->getId())
    {
        cur = cur -> getNextPro();
        pos++;
    }

    return pos;
}


bool BioPathway::insert(int newPos, Protein* insertPro) {
    bool ableToInsert = newPos >= 1 && newPos <= proteinCount+1;

    if (ableToInsert) {

        if (newPos == 1 || proteinList == nullptr) {
            (insertPro)->setNextPro(proteinList);
            proteinList = insertPro;
        } else {
            Protein* previousPro = nullptr;
            Protein* currentPro = proteinList;

            for (int a = 1; a < newPos && currentPro != nullptr; a++) {
                previousPro = currentPro;
                currentPro = currentPro->getNextPro();
            }

            previousPro->setNextPro(insertPro);
            insertPro->setNextPro(currentPro);
        }
    }

    return ableToInsert;
}
