//
// Created by Simay Uygur 22203328 Section 1
//

#ifndef HW3_2_BIOLOGICALPATHWAY_H
#define HW3_2_BIOLOGICALPATHWAY_H

#include <string>
#include "BioPathway.h"

using namespace std;
class BiologicalPathway {
public:
    BiologicalPathway();
    ~BiologicalPathway();
    void addPathway( const int pathwayId, const string pathwayName );
    void removePathway( const int pathwayId );
    void printPathways() const;
    void addProtein( const int proteinId, const int pathwayId );
    void removeProtein( const int proteinId, const int pathwayId );
    void printProteinsInPathway( const int pathwayId ) const;
    void addGene( const int geneID, const string geneName, const int proteinId );
    void removeGene( const int geneID, const int proteinId );
    void printGenesOfProtein( const int proteinId ) const;


    int getPathwaysCount() const;

    //bool isProteinUsed(int id) const;
    int indexOfSpecifiedPathway(int pathWayid) const;
    int indexOfSpecifiedProtein(int proId) const;
    int indexOfSpecifiedGene(int geneId) const;

    int indexOfPathwayWithSpecificProtein(const int proteinid) const;
    int indexOfPathwayWithSpecificGene(int geneId) const;

    //bool removeProteinPathway(int proteinId);

    //void addProSortedPathway(const int pID);

    BioPathway & getPath(int pos) const;

    bool addBioPSorted(int id, const string name);
    bool removeBioP(int wantedRid);


private:
    BioPathway* pathwayList;
    int pathwaysCount;

    int findposOfInsertion(int id);

    bool insert(int newPos, BioPathway *insertPath);

    void addPathwaySorted(const int bioPathId, const string bioPathName);
};

#endif
