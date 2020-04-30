#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "MarkovChain.h"


using namespace std;

int main() {

    string children;

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
            chain.at(childIdx)->level = i+1;
        }
        i++;
    }
    markov_node *root = chain.at(0);

    //cout << "Here is the created chain: \n";
    GeneralTree markovChain(root);

    vector<vector<Fraction>> transition_matrix;

    MarkovChain chainEvaluator(&markovChain, numState);
    vector<Fraction> tm_col;
    vector<Fraction> t_col = chainEvaluator.getTCol();

    for(int i = 0; i<numState; i++){
        Fraction zero(0,1);
        tm_col.push_back(zero);
    }

    vector<Fraction> statesPerLevel;
    for(int i = 0; i<numState; i++){
        Fraction zero(0,1);
        statesPerLevel.push_back(zero);
    }

    for(int i = 1; i<chain.size(); i++){
        tm_col.at(chain.at(i)->level-1) = tm_col.at(chain.at(i)->level-1).Sum(t_col.at(i-1));
        statesPerLevel.at(chain.at(i)->level-1) = statesPerLevel.at(chain.at(i)->level-1).Sum(Fraction(1,1));
    }
    for(int i = 0; i<tm_col.size(); i++){
        cout<<"| ";
        tm_col.at(i).show();
        cout<<" / ";
        statesPerLevel.at(i).show();
        cout<<" |"<<endl;
    }
    return 0;
}
