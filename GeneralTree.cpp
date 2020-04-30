//
// Created by mhilborn on 4/26/20.
//

#include "GeneralTree.h"
#define SPACING 10

markov_node *new_markov_node(int num){
    markov_node *temp = new markov_node;
    temp->state_name = to_string(num);
    temp->state_num = num;
    return temp;
}
GeneralTree::GeneralTree(markov_node * _root) {
    this->root = _root;
    if (_root == NULL)
        return;

    int l = 0;
    this->root->level = l;
    l++;

    // Standard level order traversal code
    // using queue
    queue<markov_node *> q;  // Create a queue
    q.push(_root); // Enqueue root
    while (!q.empty()) {
        int n = q.size();

        // Dequeue an item from queue and print it
        markov_node *p = q.front();
        p->level = l;
        q.pop();

        // Enqueue all children of the dequeued item
        for (int i = 0; i < p->children.size(); i++)
            q.push(p->children[i]);

        n--;
        // If this node has children
        while (n > 0) {
            // Dequeue an item from queue and print it
            markov_node *p = q.front();
            p->level = l;
            q.pop();

            // Enqueue all children of the dequeued item
            for (int i = 0; i < p->children.size(); i++)
                q.push(p->children[i]);
            n--;
        }
        l++;
    }
}

void GeneralTree::printTreeHelper(markov_node *root, int space) {
     if(root == NULL)
         return;
     space += SPACING;

    for(int i = 0; i<root->children.size()/2;i++)
        printTreeHelper(root->children.at(i), space);

    cout<<endl;
    for(int i = SPACING; i < space; i++)
        cout<<" ";
    cout<<root->state_name<<endl;

    for(int i = root->children.size()/2; i<root->children.size(); i++){
        printTreeHelper(root->children.at(i), space);
    }

}

void GeneralTree::printTree(markov_node *root) {
    printTreeHelper(root, 0);
}
