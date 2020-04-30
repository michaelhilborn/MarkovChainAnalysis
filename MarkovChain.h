#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "GeneralTree.h"
#include "Fraction.h"

using namespace std;

class MarkovChain {
public:
    MarkovChain(GeneralTree* mrkvChain, int numMrkvStates);

    vector<Fraction> getTCol(){
    	return t_col;
    }

private:
    vector<vector<Fraction>> levels_matrix;
    vector<vector<Fraction>> q_matrix;
    vector<vector<Fraction>> n_matrix;
    vector<Fraction> t_col;
    vector<Fraction> tm_col;
    GeneralTree chain();
    int numMarkovStates;
    vector<vector<Fraction>> CalculateInverseRref(vector<vector<Fraction>> matrix, vector<vector<Fraction>> i_matrix, int numRows, int numCols);
};
