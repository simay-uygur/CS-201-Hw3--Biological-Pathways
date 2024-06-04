//
// Created by Simay Uygur 22203328 Section 1
//

#ifndef HW3_2_GENE_H
#define HW3_2_GENE_H
#include <string>

class Gene {
private:
    int geneId;
    std::string geneName;
    Gene* nextGene;

public:
    Gene(int id =0, const std::string &name = "");
    Gene(const Gene &copiedOne);
    ~Gene();

    int getId() const;
    void setNext(Gene* next);

    std::string toString() const;

    std::string getName() const;

    Gene *getNext() const;

};

#endif //HW3_2_GENE_H
