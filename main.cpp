#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "GeneralTree.h"
#include "Fraction.h"


using namespace std;

vector<vector<Fraction>> calculate_q_matrix(GeneralTree markovChain, int numMarkovStates) {

    vector<vector<Fraction>> t_matrix;
    vector<vector<int>> connected_states;
    vector<int> num_adjacent_states;

    for(int j = 0; j< numMarkovStates; j++) {
        vector<int> empty_matrix;
        vector<Fraction> empty_fraction_matrix;
        for (int i = 0; i < numMarkovStates; i++) {
            empty_matrix.push_back(0);
            num_adjacent_states.push_back(0);
            Fraction temp(0, 1);
            empty_fraction_matrix.push_back(temp);
        }
        connected_states.push_back(empty_matrix);
        t_matrix.push_back(empty_fraction_matrix);
    }


    markov_node *root = markovChain.root;
    if (root == NULL)
        return t_matrix;


    // Count States Standard level order traversal code
    // using queue
    queue<markov_node *> q;  // Create a queue
    q.push(root); // Enqueue root
    while (!q.empty()) {
        int n = q.size();
        markov_node *p = q.front();
        q.pop();
        if (p->state_name.compare(root->state_name) != 0) {
            num_adjacent_states.at(p->state_num)++;
        }

        // Enqueue all children of the dequeued item
        for (markov_node *child: p->children) {
            q.push(child);
            connected_states.at(p->state_num).at(child->state_num) ++;
            connected_states.at(child->state_num).at(p->state_num) ++;
            if (p->state_name.compare(root->state_name) != 0) {
                num_adjacent_states.at(p->state_num)++;
            }
        }

        n--;
        // If this node has children
        while (n > 0) {
            // Dequeue an item from queue and print it
            markov_node *p = q.front();
            q.pop();

            if (p->state_name.compare(root->state_name) != 0) {
                num_adjacent_states.at(p->state_num)++;
            }

            // Enqueue all children of the dequeued item
            for (markov_node *child: p->children) {
                q.push(child);
                connected_states.at(p->state_num).at(child->state_num) ++;
                connected_states.at(child->state_num).at(p->state_num) ++;
                if (p->state_name.compare(root->state_name) != 0) {
                    num_adjacent_states.at(p->state_num)++;
                }
            }
            n--;
        }
    }

    for(int i = 0; i<numMarkovStates; i++){
        for(int j = 0; j<numMarkovStates;j++){
            cout << connected_states.at(i).at(j) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i<numMarkovStates; i++){
        cout << num_adjacent_states.at(i) << "\t";
    }
    cout << endl;
    
    for(int i = 0; i<numMarkovStates; i++){
        for(int j = 0; j<numMarkovStates; j++){
            if(j == 0){
                if(i == 0){
                    Fraction temp(1,1);
                    t_matrix.at(j).at(i) = temp;
                }else{
                    Fraction temp(0,1);
                    t_matrix.at(j).at(i) = temp;
                }
            }else{
                int num = connected_states.at(i).at(j);
                int den = num_adjacent_states.at(j);
                Fraction temp(num, den);
                t_matrix.at(j).at(i) = t_matrix.at(j).at(i).Sum(temp);
            }
        }
    }

    vector<vector<Fraction>> q_matrix;
    vector<Fraction> null_vector;
    for(int i = 0; i<numMarkovStates-1; i++){
        Fraction temp(0, 1);
        null_vector.push_back(temp);
    }
    for(int i = 0; i<numMarkovStates-1; i++){
        q_matrix.push_back(null_vector);
    }
    for(int i = 1; i<numMarkovStates; i++){
        for(int j = 1; j<numMarkovStates; j++){
            q_matrix.at(i-1).at(j-1) = t_matrix.at(i).at(j);
        }
    }

    for(int i = 0; i<numMarkovStates-1; i++){
        for(int j = 0; j<numMarkovStates-1; j++){
            q_matrix.at(i).at(j).show();
            cout<< "\t";
        }
        cout<< endl;
    }

    return q_matrix;
}

int main() {

    cout << "Enter First State" << endl;

    string nxtState = "";
    int numState = 0;

    cin >> nxtState;
    markov_node *root = new_markov_node(nxtState, numState);

    // Standard level order traversal code
    // using queue
    queue<markov_node *> q;  // Create a queue
    q.push(root); // Enqueue root
    bool finished = false;

    while (!q.empty() && !finished){
        int n = q.size();

        // If this node has children
        while (n > 0) {
            // Dequeue an item from queue and print it
            markov_node *p = q.front();
            q.pop();
            cout << "Please enter children of node " << p->state_name << " (if no children enter 'done', if finished with tree enter 'finished')" << endl;
            cin >> nxtState;
            while (nxtState.compare("done") != 0) {
                if(nxtState.compare("finished") == 0){
                    finished = true;
                    break;
                }
                numState ++;
                cout << numState << endl;
                markov_node *tempChild = new_markov_node(nxtState, numState);
                p->children.push_back(tempChild);
                cout << "Please enter children of node " << p->state_name << " (if no children enter 'done', if finished with tree enter 'finished')" << endl;
                cin >> nxtState;
            }

            if(nxtState.compare("finished") == 0){
                break;
            }

            // Enqueue all children of the dequeued item
            for (markov_node *child: p->children)
                q.push(child);
            n--;
        }
    }


    //cout << "Here is the created chain: \n";
    GeneralTree markovChain(root);

    //markovChain.printTree(markovChain.root);

    vector<vector<Fraction>> transition_matrix;

    transition_matrix = calculate_q_matrix(markovChain, numState + 1);

    return 0;
}
