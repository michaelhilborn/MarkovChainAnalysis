#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "GeneralTree.h"
#include "Fraction.h"


using namespace std;

int numMarkovStates = 0;

vector<vector<Fraction>> calculate_q_matrix(GeneralTree markovChain) {

    vector<vector<Fraction>> q_matrix;
    vector<vector<int>> connected_states;
    vector<int> num_adjacent_states;

    for(int j = 0; j<numMarkovStates; j++) {
        vector<int> empty_matrix;
        for (int i = 0; i < numMarkovStates; i++) {
            empty_matrix.push_back(0);
            num_adjacent_states.push_back(0);
        }
        connected_states.push_back(empty_matrix);
    }


    markov_node *root = markovChain.root;
    if (root == NULL)
        return q_matrix;


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
        for (int i = 0; i < p->children.size(); i++) {
            q.push(p->children[i]);
            num_adjacent_states.at(p->state_num)++;
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
            for (int i = 0; i < p->children.size(); i++) {
                q.push(p->children[i]);
                num_adjacent_states.at(p->state_num)++;
            }
            n--;
        }
    }
    for(int i = 0; i < numMarkovStates; i++){
        for(int j = 0; j<numMarkovStates; j++){

        }
    }
}

int main() {

    cout << "Enter First State" << endl;

    string nxtState;
    int numState;

    cin >> nxtState;
    markov_node *root = new_markov_node(nxtState, numState);
    numState++;

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
                markov_node *tempChild = new_markov_node(nxtState, numState);
                p->children.push_back(tempChild);
                cout << "Please enter children of node " << p->state_name << " (if no children enter 'done', if finished with tree enter 'finished')" << endl;
                cin >> nxtState;
            }

            if(nxtState.compare("finished") == 0){
                break;
            }

            // Enqueue all children of the dequeued item
            for (int i=0; i<p->children.size(); i++)
                q.push(p->children[i]);
            n--;
        }
    }

    numMarkovStates = numState;
    cout << "Here is the created chain: \n";
    GeneralTree markovChain(root);

    markovChain.printTree(markovChain.root);

    vector<vector<Fraction>> transition_matrix;

    transition_matrix = calculate_q_matrix(markovChain);

    return 0;
}
