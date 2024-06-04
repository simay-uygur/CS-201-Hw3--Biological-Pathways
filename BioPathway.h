//
// Created by Simay Uygur 22203328 Section 1
//

#ifndef HW3_2_BIOPATHWAY_H
#define HW3_2_BIOPATHWAY_H

#include <string>
#include "Protein.h"

class BioPathway {
private:
    int biologicalPathwayId;
    std::string biologicalPathwayName;
    Protein* proteinList; // Pointer to the first protein in the pathwayList
    BioPathway* nextPathway; // Pointer to the next pathwayList
    int proteinCount;


public:
    BioPathway(int id =0, std::string name="");
    ~BioPathway();


    std::string toString();

    int getProteinCount() const;

    int totalGenes();
    Protein& getProtein(int pos);

    bool insertProtein(int insertPos, Protein *p);

    bool removeProtein(int proteinId);

    void addProSorted(const int pID);

    BioPathway* getNext();
    std::string getName();
    int getId() const;

    void bioPathwayDisp();

    void setNext( BioPathway *p);
    int findProteinIndex(int pId);

    int findposOfInsertion(int id);

    bool insert(int newPos, Protein *insertPro);
};


#endif //HW3_2_BIOPATHWAY_H
