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
    string state_name;
    int state_num;
    int level;
    vector<markov_node *> children;
};

markov_node *new_markov_node(string state, int num);

class GeneralTree {
public:
    markov_node* root;

    GeneralTree(markov_node * _root);

    void printTree(markov_node *root);

private:
    void printTreeHelper(markov_node *root, int space);

};


#endif //MARKOVCHAINANALYSIS_GENERALTREE_H
