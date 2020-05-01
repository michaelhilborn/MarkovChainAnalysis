//Created by Michael Hilborn on 4-27

#include "MarkovChain.h"

void printMatrix(vector<vector<Fraction>> matrix, int numRows, int numCols){
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j<numCols; j++){
            matrix.at(i).at(j).show();
            cout<<"\t";
        }
        cout<<endl;
    }
}
vector<vector<Fraction>> MarkovChain::CalculateInverseRref(vector<vector<Fraction>> matrix, vector<vector<Fraction>> i_matrix, int numRows, int numCols){
    int lead = 0; 

    while (lead < numRows) {
        Fraction f, g;

        for (int r = 0; r < numRows; r++) { // for each row ...
            /* calculate divisor and multiplier */
            f = matrix.at(lead).at(lead);
            g = matrix.at(r).at(lead).Division(matrix.at(lead).at(lead));

            for (int c = 0; c < numCols; c++) { // for each column ...
                if (r == lead){
                    matrix.at(r).at(c) = matrix.at(r).at(c).Division(f);           // make pivot = 1
                    i_matrix.at(r).at(c) = i_matrix.at(r).at(c).Division(f);
                }else{
                    matrix.at(r).at(c) = 
                        matrix.at(r).at(c).Difference(matrix.at(lead).at(c).Product(g));  // make other = 0
                    i_matrix.at(r).at(c) =
                        i_matrix.at(r).at(c).Difference(i_matrix.at(lead).at(c).Product(g));
                }
            }
        }

        lead++;
    }
    return i_matrix;
}

MarkovChain::MarkovChain(GeneralTree* mrkvChain, int numMrkvStates) {

    vector<vector<Fraction>> t_matrix;
    vector<vector<int>> connected_states;
    vector<int> num_adjacent_states;

    for(int j = 0; j< numMrkvStates; j++) {
        vector<int> empty_matrix;
        vector<Fraction> empty_fraction_matrix;
        for (int i = 0; i < numMrkvStates; i++) {
            empty_matrix.push_back(0);
            num_adjacent_states.push_back(0);
            Fraction temp(0, 1);
            empty_fraction_matrix.push_back(temp);
        }
        connected_states.push_back(empty_matrix);
        t_matrix.push_back(empty_fraction_matrix);
    }


    markov_node *root = mrkvChain->root;
    if (root == NULL)
        return;


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
    
    for(int i = 0; i<numMrkvStates; i++){
        for(int j = 0; j<numMrkvStates; j++){
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

    vector<Fraction> null_vector;
    for(int i = 0; i<numMrkvStates-1; i++){
        Fraction temp(0, 1);
        null_vector.push_back(temp);
    }
    for(int i = 0; i<numMrkvStates-1; i++){
        q_matrix.push_back(null_vector);
    }
    for(int i = 1; i<numMrkvStates; i++){
        for(int j = 1; j<numMrkvStates; j++){
            q_matrix.at(i-1).at(j-1) = t_matrix.at(i).at(j);
        }
    }

    vector<vector<Fraction>> iminusq_matrix;
    for(int i = 0; i<numMrkvStates-1; i++){
        iminusq_matrix.push_back(null_vector);
    }

    Fraction one(1,1);
    Fraction zero(0,1);

    for(int i = 0; i<numMrkvStates-1; i++){
        for(int j = 0; j<numMrkvStates-1; j++){
            if(i == j)
                iminusq_matrix.at(i).at(j) = one.Difference(q_matrix.at(i).at(j));
            else
                iminusq_matrix.at(i).at(j) = zero.Difference(q_matrix.at(i).at(j));
        }
    }
    vector<vector<Fraction>> i_matrix;
    for(int i = 0; i<numMrkvStates-1;i++){
        vector<Fraction> temp;
        for(int j = 0; j<numMrkvStates-1; j++){
            if(i==j){
                Fraction newFraction(1,1);
                temp.push_back(newFraction);
            }else{
                Fraction newFraction(0,1);
                temp.push_back(newFraction);
            }
        }
        i_matrix.push_back(temp);
    }

    n_matrix = CalculateInverseRref(iminusq_matrix, i_matrix, numMrkvStates-1, numMrkvStates-1);
    
    for(int i = 0; i<numMrkvStates-1; i++){
        Fraction sum(0,1);
        for(int j = 0; j<numMrkvStates-1; j++){
            sum = sum.Sum(n_matrix.at(i).at(j));
        }
        t_col.push_back(sum);
    }
    
}