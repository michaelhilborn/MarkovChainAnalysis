//Created by Michael Hilborn on 4-27

#include "MarkovChain.h"

void printMatrix(vector<vector<double>> matrix, int numRows, int numCols){
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j<numCols; j++){
            cout << matrix.at(i).at(j) << "\t";
        }
        cout<<endl;
    }
}
//I modified this code from a tutorial on GeeksforGeeks
vector<vector<double>> MarkovChain::CalculateInverseRref(vector<vector<double>> matrix, vector<vector<double>> i_matrix, int numRows, int numCols){
    int lead = 0; 

    while (lead < numRows) {
        double f, g;

        for (int r = 0; r < numRows; r++) { // for each row ...
            /* calculate divisor and multiplier */
            f = matrix.at(lead).at(lead);
            g = matrix.at(r).at(lead)/(matrix.at(lead).at(lead));

            for (int c = 0; c < numCols; c++) { // for each column ...
                if (r == lead){
                    matrix.at(r).at(c) = matrix.at(r).at(c)/(f);           // make pivot = 1
                    i_matrix.at(r).at(c) = i_matrix.at(r).at(c)/(f);
                }else{
                    matrix.at(r).at(c) = 
                        matrix.at(r).at(c)-(matrix.at(lead).at(c)*(g));  // make other = 0
                    i_matrix.at(r).at(c) =
                        i_matrix.at(r).at(c)-(i_matrix.at(lead).at(c)*(g));
                }
            }
        }

        lead++;
    }
    return i_matrix;
}

MarkovChain::MarkovChain(GeneralTree* mrkvChain, int numMrkvStates) {

    vector<vector<double>> t_matrix;
    vector<vector<double>> connected_states;
    vector<double> num_adjacent_states;

    for(int j = 0; j< numMrkvStates; j++) {
        vector<double> empty_matrix;
        vector<double> empty_fraction_matrix;
        for (int i = 0; i < numMrkvStates; i++) {
            empty_matrix.push_back(0.0);
            num_adjacent_states.push_back(0.0);
            empty_fraction_matrix.push_back(0.0);
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
        num_adjacent_states.at(p->state_num)++;

        // Enqueue all children of the dequeued item
        for (markov_node *child: p->children) {
            q.push(child);
            connected_states.at(p->state_num).at(child->state_num) += 1.0;
            connected_states.at(child->state_num).at(p->state_num) += 1.0;
            if (p->state_name.compare(root->state_name) != 0) {
                num_adjacent_states.at(p->state_num)+=1.0;
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
                connected_states.at(p->state_num).at(child->state_num) += 1.0;
                connected_states.at(child->state_num).at(p->state_num) += 1.0;
                if (p->state_name.compare(root->state_name) != 0) {
                    num_adjacent_states.at(p->state_num)+=1.0;
                }
            }
            n--;
        }
    }
    
    for(int i = 0; i<numMrkvStates; i++){
        for(int j = 0; j<numMrkvStates; j++){
            if(j == 0){
                if(i == 0){
                    t_matrix.at(j).at(i) = 1.0;
                }else{
                    t_matrix.at(j).at(i) = 0.0;
                }
            }else{
                int num = connected_states.at(i).at(j);
                int den = num_adjacent_states.at(j);
                double newEntry = (double)num/den;
                t_matrix.at(j).at(i) = t_matrix.at(j).at(i) + (newEntry);
            }
        }
    }

    vector<double> null_vector;
    for(int i = 0; i<numMrkvStates-1; i++){
        null_vector.push_back(0.0);
    }
    for(int i = 0; i<numMrkvStates-1; i++){
        q_matrix.push_back(null_vector);
    }
    for(int i = 1; i<numMrkvStates; i++){
        for(int j = 1; j<numMrkvStates; j++){
            q_matrix.at(i-1).at(j-1) = t_matrix.at(i).at(j);
        }
    }

    vector<vector<double>> iminusq_matrix;
    for(int i = 0; i<numMrkvStates-1; i++){
        iminusq_matrix.push_back(null_vector);
    }

    for(int i = 0; i<numMrkvStates-1; i++){
        for(int j = 0; j<numMrkvStates-1; j++){
            if(i == j)
                iminusq_matrix.at(i).at(j) = 1.0 - (q_matrix.at(i).at(j));
            else
                iminusq_matrix.at(i).at(j) = 0.0 - (q_matrix.at(i).at(j));
        }
    }
    vector<vector<double>> i_matrix;
    for(int i = 0; i<numMrkvStates-1;i++){
        vector<double> temp;
        for(int j = 0; j<numMrkvStates-1; j++){
            if(i==j){
                temp.push_back(1.0);
            }else{
                temp.push_back(0.0);
            }
        }
        i_matrix.push_back(temp);
    }

    n_matrix = CalculateInverseRref(iminusq_matrix, i_matrix, numMrkvStates-1, numMrkvStates-1);
    
    for(int i = 0; i<numMrkvStates-1; i++){
        double sum = 0;
        for(int j = 0; j<numMrkvStates-1; j++){
            sum = sum + (n_matrix.at(i).at(j));
        }
        t_col.push_back(sum);
    }
    
}