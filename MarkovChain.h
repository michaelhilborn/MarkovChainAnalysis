#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "GeneralTree.h"

using namespace std;

class MarkovChain {
public:
    MarkovChain(GeneralTree* mrkvChain, int numMrkvStates);

    vector<double> getTCol(){
    	return t_col;
    }

private:
    vector<vector<double>> levels_matrix;
    vector<vector<double>> q_matrix;
    vector<vector<double>> n_matrix;
    vector<double> t_col;
    vector<double> tm_col;
    GeneralTree chain();
    int numMarkovStates;
    vector<vector<double>> CalculateInverseRref(vector<vector<double>> matrix, vector<vector<double>> i_matrix, int numRows, int numCols);
};
