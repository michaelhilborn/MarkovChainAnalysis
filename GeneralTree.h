//
// Created by mhilborn on 4/26/20.
//

#ifndef MARKOVCHAINANALYSIS_GENERALTREE_H
#define MARKOVCHAINANALYSIS_GENERALTREE_H
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

struct markov_node{
    int state_num;
    string state_name;
    int level;
    vector<markov_node *> children;
};

markov_node *new_markov_node(int num);

class GeneralTree {
public:
    markov_node* root;

    GeneralTree(markov_node * _root);

    void printTree(markov_node *root);

    int getNumLevels(){
    	return numLevels;
    }

private:
	int numLevels;
    void printTreeHelper(markov_node *root, int space);

};


#endif //MARKOVCHAINANALYSIS_GENERALTREE_H
