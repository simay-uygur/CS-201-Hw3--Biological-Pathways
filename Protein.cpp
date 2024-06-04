//
// Created by Simay Uygur 22203328 Section 1
//

#include "Protein.h"
#include <string>
#include <iostream>

Protein::Protein(int id ) : proteinId(id), geneList(nullptr), nextPro(nullptr), geneCount(0) {

}

Protein::~Protein() {

    while (geneList != nullptr) {
        Gene* g = geneList;
        geneList = geneList -> getNext();
        delete g;
    }

}

int Protein::getId() const {
    return proteinId;
}


void Protein::addGeneSorted(const int geneId, const std::string geneName) {


    Gene* addingGene = new Gene(geneId, geneName);
    int p = findposOfInsertion(geneId);

    insert(p, addingGene);
    geneCount++;

}


std::string Protein::toString() const {

    std::string s = "Protein ID : " + std::to_string(proteinId) + ", Gene IDs : ";

    Gene* curr = geneList;

    if(geneCount==0)
    {
        s+="None";
        return s;
    }
    s += "[";

    while (curr -> getNext() != nullptr) {

        s += std::to_string(curr->getId()) += ", ";
        curr = curr->getNext();
    }
    s += std::to_string(curr->getId()) +=  "]";

    return s;
}

void Protein::removeGene(int geneID) {

    Gene* currentPtr = geneList;
    Gene* prevPtr = nullptr;

    while (currentPtr != nullptr) {

        if (currentPtr->getId() == geneID) {

            if (prevPtr == nullptr) {
                geneList = currentPtr->getNext();
            }
            else {
                prevPtr->setNext(currentPtr->getNext());
            }

            delete currentPtr;
            geneCount--;
            return;
        }

        prevPtr = currentPtr;
        currentPtr = currentPtr->getNext();
    }



}

bool Protein::insert(int newPos, Gene *insertGene) {
    bool ableToInsert = newPos >= 1 && newPos <= geneCount+1;

    if(ableToInsert)
    {
        if (newPos == 1 || geneList == nullptr) {
            (insertGene)->setNext(geneList);
            geneList = insertGene;
        }
        else
        {
            Gene* previousGene = nullptr;
            Gene* currGene = geneList;

            for(int a=1; a< newPos && currGene != nullptr; a++)
            {
                previousGene = currGene;
                currGene = currGene-> getNext();
            }

            previousGene->setNext(insertGene);
            insertGene->setNext(currGene);


        }
    }
    return ableToInsert;

}

Gene& Protein::getGeneRef(int pos) {

    if (pos < 1 || pos > geneCount) {
        throw std::out_of_range("Invalid position");
    }

    Gene* currGene = geneList;

    for (int i = 1; i < pos; ++i) {
        currGene = currGene->getNext();
    }

    return *currGene;
}

int Protein::getGeneCount() const {
    return geneCount;
}

Protein *Protein::getNextPro() {
    return nextPro;
}

void Protein::setNextPro(Protein *p) {

    nextPro = p;
}

void Protein::display() {

    if(geneCount == 0 || geneList == nullptr)
    {
        std::cout <<"There are no genes to show in protein " << proteinId<< "." << std::endl;
        return;
    }

    std::cout << "Genes in protein " << proteinId << ":" << std::endl;

    Gene *current = geneList;

    do {
        std::cout << current->toString() << std::endl;
        current = current->getNext();

    }  while (current != nullptr);

}

bool Protein::doesGeneIncluded(int geneid) {

    Gene* curGene = geneList;
    bool isIncluded = false;

    while (curGene != nullptr) {
        if(curGene ->getId() == geneid)
            isIncluded = true;
        curGene = curGene->getNext();
    }
    return isIncluded;
}


int Protein::findposOfInsertion(int id){

    int pos = 1;
    Gene* cur = geneList;

    while(cur != nullptr && id > cur->getId())
    {
        cur = cur -> getNext();
        pos++;
    }

    return pos;
}

