#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "GeneralTree.h"
#include "Fraction.h"

using namespace std;

class MarkovChain {
public:
    MarkovChain(GeneralTree* mrkvChain, int numMrkvStates);

private:
    vector<vector<Fraction>> levels_matrix;
    vector<vector<Fraction>> q_matrix;
    vector<Fraction> t_col;
    vector<Fraction> tm_col;
    GeneralTree chain();
    int numMarkovStates;
};
