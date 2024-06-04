//
// Created by Simay Uygur 22203328 Section 1
//

#ifndef HW3_2_PROTEIN_H
#define HW3_2_PROTEIN_H

#include <string>
#include "Gene.h"

class Protein {
private:
    int proteinId;

    Gene* geneList;
    Protein* nextPro;
    int geneCount;

public:
    Protein(int id =0);
    ~Protein();

    int getId() const;

    Protein* getNextPro();
    void setNextPro(Protein *p);

    void addGeneSorted(const int geneId, const std::string geneName);

    std::string toString() const;
    Gene& getGeneRef(int pos);

    void removeGene(int geneID);
    bool insert(int newPos, Gene *insertGene);

    int getGeneCount() const;

    void display();
    bool doesGeneIncluded(int geneid);


    //int searchGeneInd(int geneId);

    int findposOfInsertion(int id);
};



#endif //HW3_2_PROTEIN_H
