#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "MarkovChain.h"


using namespace std;

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

    MarkovChain chainEvaluator(&markovChain, numState + 1);

    return 0;
}
