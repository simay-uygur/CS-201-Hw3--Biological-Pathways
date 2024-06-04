//
// Created by Simay Uygur 22203328 Section 1
//


#include "Gene.h"


Gene::Gene(int id, const std::string& name) : geneId(id), geneName(name), nextGene(nullptr) {

}

int Gene::getId() const {
    return geneId;
}

std::string Gene::getName() const {
    return geneName;
}

Gene* Gene::getNext() const {
    return nextGene;
}

void Gene::setNext(Gene* next) {
    nextGene = next;
}

Gene::Gene(const Gene &copiedOne):geneId(copiedOne.geneId), geneName(copiedOne.geneName), nextGene(copiedOne.nextGene) {

}

Gene::~Gene() {  //sonra bakarım
    nextGene = nullptr;
}

std::string Gene::toString() const {
    return "GENE " + std::to_string(geneId) + " : " + geneName;
}
