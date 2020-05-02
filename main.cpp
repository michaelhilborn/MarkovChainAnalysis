#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "MarkovChain.h"


using namespace std;

int main() {

    string children;
    int totalLevels;

    ifstream markovTxtFile;
    markovTxtFile.open("./MarkovChainTxt/4-Level-Hairy-Markov-Chain.txt");

    if (!markovTxtFile) cout << "Could not open the file!" << endl;
    int numState;
    string numOfStates;

    getline (markovTxtFile,numOfStates);
    numState = stoi(numOfStates);

    vector<markov_node *> chain;
    for(int i = 0; i < numState; i++){
        chain.push_back(new_markov_node(i));
    }
    int i = 0;
    while(getline(markovTxtFile, children)){

        stringstream ss(children);
        int childIdx;
        
        while(ss>>childIdx){
            chain.at(i)->children.push_back(chain.at(childIdx));
        }
        i++;
    }
    markov_node *root = chain.at(0);

    //cout << "Here is the created chain: \n";
    GeneralTree markovChain(root);
    totalLevels = markovChain.getNumLevels();

    vector<vector<double>> transition_matrix;

    MarkovChain chainEvaluator(&markovChain, numState);
    vector<double> tm_col;
    vector<double> t_col = chainEvaluator.getTCol();

    for(int i = 0; i<totalLevels; i++){
        tm_col.push_back((double) 0);
    }

    vector<double> statesPerLevel;
    for(int i = 0; i<totalLevels; i++){
        statesPerLevel.push_back((double) 0);
    }

    for(unsigned int i = 1; i<chain.size(); i++){
        tm_col.at(chain.at(i)->level-1) = tm_col.at(chain.at(i)->level-1) + (t_col.at(i-1));
        statesPerLevel.at(chain.at(i)->level-1) = statesPerLevel.at(chain.at(i)->level-1) + (double)1;
    }
    for(int i = 0; i<totalLevels; i++){
        cout << "| " << tm_col.at(i) / (double)statesPerLevel.at(i) << " |" << endl;
    }
    return 0;
}
