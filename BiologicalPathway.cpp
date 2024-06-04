//
// Created by Simay Uygur 22203328- Section 1
//

#include "BiologicalPathway.h"
#include <string>
#include <iostream>

BiologicalPathway::BiologicalPathway() {
    pathwayList = nullptr;
    pathwaysCount =0;
}

BiologicalPathway::~BiologicalPathway() {

    while (pathwayList != nullptr) {
        BioPathway* b = pathwayList;
        pathwayList = pathwayList -> getNext();
        delete b;
    }
    pathwaysCount =0;
}

void BiologicalPathway::addPathway(const int pathwayId, const string pathwayName) {

    if(indexOfSpecifiedPathway(pathwayId) ==-1)  //bulamadı yani
    {
        addBioPSorted(pathwayId,pathwayName);
        std::cout <<"Added pathway "<< pathwayId << "." << std::endl;
    }
    else
    {
        std::cout << "Cannot add pathway. There is already a pathway with ID " << pathwayId << "." << std::endl;
    }

}



void BiologicalPathway::removePathway(const int pathwayId) {
    if(indexOfSpecifiedPathway(pathwayId) ==-1)  //ekleyecek mi emin değilim
    {
        std::cout <<"Cannot remove pathway. There is no pathway with ID "<< pathwayId << "." << std::endl;
    }
    else
    {
        removeBioP(pathwayId);
        std::cout << "Removed pathway "<< pathwayId << "." << std::endl;
    }
}

void BiologicalPathway::printPathways() const {
    if (pathwaysCount == 0) {
        std::cout << "There are no pathways to show." << std::endl;
    }
    else {
        std::cout << "Pathways in the system:" << std::endl;
        for (int i = 1; i <= pathwaysCount; ++i) {
            BioPathway* bio = &getPath(i);
            std::cout << "Pathway " << bio->getId() << " : " << bio->getName() << " ("
                      << bio->getProteinCount() << " Proteins) (" << bio->totalGenes() << " Genes)" << std::endl;
        }
    }
}

int BiologicalPathway::getPathwaysCount() const {
    return pathwaysCount;
}

void BiologicalPathway::addProtein(const int proteinId, const int pathwayId) {
    int indo = indexOfSpecifiedProtein(proteinId);
    int indexPathway = indexOfSpecifiedPathway(pathwayId);

    if(indexPathway == -1)
    {
        std::cout << "Cannot add protein. There is no pathway with ID " << pathwayId << "." << std::endl;
    }
    else if(indo != -1)  //if it is true the protein is used
    {
        std::cout << "Cannot add protein. There is a pathway having a protein with ID " << proteinId << "." << std::endl;
    }
    else{

        std::cout << "Added protein " << proteinId << " to pathway " << pathwayId << "." << std::endl;
        getPath(indexPathway).addProSorted(proteinId);
    }

}

void BiologicalPathway::removeProtein(const int proteinId, const int pathwayId) {

    int indexPathway = indexOfSpecifiedPathway(pathwayId);


    if (indexPathway == -1) {
        std::cout << "Cannot remove protein. There is no pathway with ID " << pathwayId << "." << std::endl;
        return;
    }
    int indo = getPath(indexPathway).findProteinIndex(proteinId);
    if (indo == -1) {
        std::cout << "Cannot remove protein. Pathway " << pathwayId << " does not have a protein with ID " << proteinId << "." << std::endl;
        return;
    }
    else {
        getPath(indexPathway).removeProtein(proteinId);
        std::cout << "Removed protein " << proteinId << " from pathway " << pathwayId << "." << std::endl;
    }

}

void BiologicalPathway::printProteinsInPathway(const int pathwayId) const {
    int pathwayIndex = indexOfSpecifiedPathway(pathwayId);

    if (pathwayIndex == -1) {
        std::cout << "Cannot print proteins. There is no pathway with ID " << pathwayId << "." << std::endl;
        return;
    }

    BioPathway* pathway = &getPath(pathwayIndex);

    int totalNumPro = pathway->getProteinCount();

    if (totalNumPro ==0) {
        std::cout << "There are no proteins to show in pathway " << pathwayId << "." << std::endl;
    }
    else
    {
        pathway->bioPathwayDisp();
    }
}

void BiologicalPathway::addGene(const int geneID, const string geneName, const int proteinId) {

    int pathwayIndex = indexOfPathwayWithSpecificProtein(proteinId);
    int proIndex = indexOfSpecifiedProtein(proteinId);

    int geneINd = indexOfSpecifiedGene(geneID);
    if (proIndex == -1) {
        std::cout << "Cannot add gene. There is no protein with ID " << proteinId << "." << std::endl;
        return;
    }

    BioPathway* pathway = &getPath(pathwayIndex);  //referansa çevirince düzeldi

    if (geneINd != -1) {
        std::cout << "Cannot add gene. Gene " << geneID << " is already in use." << std::endl;

    }
    else
    {

        Protein* y = &(pathway ->getProtein(proIndex));
        y -> addGeneSorted(geneID,geneName);
        std::cout << "Added gene " << geneID << " to protein " << proteinId << "." << std::endl;
    }
}

void BiologicalPathway::removeGene(const int geneID, const int proteinId) {

    int proteinIndex = indexOfSpecifiedProtein(proteinId);
    int pathwayIndex = indexOfPathwayWithSpecificProtein(proteinId);

    if (proteinIndex == -1) {
        std::cout << "Cannot remove gene. There is no protein with ID " << proteinId << "." << std::endl;
        return;
    }

    BioPathway *pathway = &getPath(pathwayIndex);

    if(!pathway->getProtein(proteinIndex).doesGeneIncluded(geneID))
    {
        std::cout << "Cannot remove gene. There is no gene " << geneID << " encoding protein " << proteinId << "." << std::endl;
        return;
    }


    std::cout << "Removed gene " << geneID << " from protein " << proteinId << "." << std::endl;
    pathway->getProtein(proteinIndex).removeGene(geneID); //içinde handle etmesini umuyorum.


}

void BiologicalPathway::printGenesOfProtein(const int proteinId) const {
    int indPro = indexOfSpecifiedProtein(proteinId);
    int indPath = indexOfPathwayWithSpecificProtein(proteinId);

    if(indPro == -1)
    {
        std::cout << "Cannot print genes. There is no protein with ID "<< proteinId << "." << std::endl;
    }
    else if(indPath != -1)   //artık çalışıyo ama
    {
        BioPathway& bio = getPath(indPath);
        bio.getProtein(indPro).display();   //umarım
    }

}

int BiologicalPathway::indexOfSpecifiedPathway(int pathWayid) const {
    for (int i = 1; i <= pathwaysCount; ++i) {
        BioPathway* b = &getPath(i);
        if(b->getId() == pathWayid)
            return i;
    }
    return -1;

}

int BiologicalPathway::indexOfSpecifiedProtein(int proId) const {

    for (int i = 1; i <= pathwaysCount; ++i) {
        BioPathway* b = &getPath(i);
        for(int g=1;g <= b->getProteinCount(); ++g )
        {
            Protein* p = &(b->getProtein(g));
            if ( p->getId() == proId) {
                return g;
            }
        }

    }
    return -1;
}

int BiologicalPathway::indexOfSpecifiedGene(int geneId) const {
    // i am getting bad access error
    for (int i = 1; i <= pathwaysCount; ++i) {
        BioPathway* b = &getPath(i);
        for (int p = 1; p <=  b->getProteinCount(); ++p) {
            Protein* pro = &(b->getProtein(p));
            for (int g = 1; g <= pro->getGeneCount(); ++g) {
                Gene* geneSelected = &(pro->getGeneRef(g));
                if ( geneSelected -> getId() == geneId) {
                    return g;
                }
            }
        }
    }
    return -1;
}

int BiologicalPathway::indexOfPathwayWithSpecificProtein(const int proteinid) const {

    for (int i = 1; i <= pathwaysCount; ++i) {
        BioPathway* b = &getPath(i);
        for(int g=1;g <= b->getProteinCount(); ++g )
        {
            Protein* prosSelected = &(b->getProtein(g));
            if (prosSelected->  getId() == proteinid) {
                return i;
            }
        }

    }
    return -1;
}

int BiologicalPathway::indexOfPathwayWithSpecificGene(int geneId) const {

    for (int i = 1; i <= pathwaysCount; ++i) {
        BioPathway* b = &getPath(i);
        for (int p = 1; p <=  b->getProteinCount(); ++p) {
            Protein* pro = &(b->getProtein(p));
            for (int g = 1; g <= pro->getGeneCount(); ++g) {
                if (pro->getGeneRef(g).getId() == geneId) {
                    return i;
                }
            }
        }
    }
    return -1;
}

BioPathway& BiologicalPathway::getPath(int pos) const {

    if (pos < 1 || pos > pathwaysCount) {
        throw std::out_of_range("Invalid position");
    }

    BioPathway* currPath = pathwayList;

    for (int i = 1; i < pos; ++i) {
        currPath = currPath->getNext();
    }

    return *currPath;
}

bool BiologicalPathway::addBioPSorted(int wantedRid, const string name) {

    BioPathway* addingPath = new BioPathway(wantedRid,name);

    if(pathwaysCount == 0 || wantedRid < pathwayList ->getId())
    {
        addingPath ->setNext(pathwayList);
        pathwayList = addingPath;

    }
    else
    {
        BioPathway* curP = pathwayList;
        while (curP -> getNext() != nullptr && wantedRid > curP->getNext()->getId())
        {
            curP = curP ->getNext();
        }

        addingPath->setNext(curP->getNext());
        curP->setNext(addingPath);
    }

    pathwaysCount++;
    return true;
}


bool BiologicalPathway::removeBioP(int wantedRid) {
    BioPathway* currentBiopathway = pathwayList;
    BioPathway* prevBiopathyaw = nullptr;

    while (currentBiopathway != nullptr) {

        if (currentBiopathway->getId() == wantedRid) {

            if (prevBiopathyaw == nullptr)
            {
                pathwayList = currentBiopathway->getNext();
            }
            else
            {
                prevBiopathyaw->setNext(currentBiopathway->getNext());
            }
            delete currentBiopathway;
            pathwaysCount--;
            return true;
        }
        prevBiopathyaw = currentBiopathway;

        currentBiopathway = currentBiopathway->getNext();
    }

    return false;
}


void BiologicalPathway::addPathwaySorted(const int bioPathId, const std::string bioPathName) {

    BioPathway* addingGene = new BioPathway(bioPathId, bioPathName);
    int p = findposOfInsertion(bioPathId);
    insert(p,addingGene);
    pathwaysCount++;

}

int BiologicalPathway::findposOfInsertion(int id){

    int pos = 1;
    BioPathway* cur = pathwayList;

    while(cur != nullptr && id > cur->getId())
    {
        cur = cur -> getNext();
        pos++;
    }

    return pos;
}

bool BiologicalPathway::insert(int newPos, BioPathway* insertPath) {
    bool ableToInsert = newPos >= 1 && newPos <= pathwaysCount+1;

    if(ableToInsert)
    {
        if (newPos == 1 || pathwayList == nullptr) {
            (insertPath)->setNext(pathwayList);
            pathwayList = insertPath;
        }
        else
        {
            BioPathway* previouspathway = nullptr;
            BioPathway* currpathway = pathwayList;

            for(int a=1; a< newPos && currpathway != nullptr; a++)
            {
                previouspathway = currpathway;
                currpathway = currpathway-> getNext();
            }

            previouspathway->setNext(insertPath);
            insertPath->setNext(currpathway);

        }
    }
    return ableToInsert;

}

