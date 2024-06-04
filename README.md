# CS-201-Hw3--Biological-Pathways
This is a homework assignment given by Bilkent University in the CS 201 course.

Overview:

In this homework, a system is implemented to manage biological pathways using linked lists. This involves storing pathways, proteins, and genes, each with unique IDs, in sorted linked lists. The IDs of pathways, proteins, and genes are unique within their respective categories but not across categories.

Detailed Requirements:

Pathways:
Attributes: Each pathway has a unique ID and a name.
Operations:
addPathway: Adds a new pathway. Checks for unique ID.
removePathway: Removes a pathway and its associated proteins and genes.
printPathways: Prints pathways in ascending order of IDs.


Proteins:
Attributes: Each protein has a unique ID and a list of encoder gene IDs. Each protein belongs to a single pathway.
Operations:
addProtein: Adds a new protein to a pathway. Checks for unique protein ID.
removeProtein: Removes a protein from a pathway.
printProteinsInPathway: Prints proteins in a pathway, in ascending order of IDs.


Genes:
Attributes: Each gene has a unique ID and name. Each gene encodes a single protein.
Operations:
addGene: Adds a gene to a protein. Checks for unique gene ID.
removeGene: Removes a gene from a protein.
printGenesOfProtein: Prints genes in a protein, in ascending order of IDs.
