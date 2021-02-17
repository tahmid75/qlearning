/*
Title: Q-Learning Implementaion in C++
Author: Md Tahmid Hossain
URL: http://www.tahmidhossain.com
*/

#include <iostream>
#include <vector>

using namespace std;

// Reward Matrix
double r[6][6] = {
        {-1, -1,-1,-1, 0, -1},
		{-1, -1, -1, 0, -1, 100},
		{-1, -1, -1, 0, -1, -1},
		{-1, 0, 0,-1, 0, -1},
		{0, -1, -1, 0, -1, 100},
		{-1, 0,-1,-1, 0, 100} };

// Q Matrix
double q[6][6]{
        {0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0} };

double gamma = 0.8;

std::vector<int> available_actions(int state){

    std::vector<int> av_act;

    for (int i = 0; i < 6; i++){
       if(r[state][i] >= 0){
            av_act.push_back(i);
        }
    }

    return av_act;
}


void update(int current_state, int action){

    double max_value = 0;
    std::vector<int> available_acts = available_actions(action);


    for(int j=0; j< available_acts.size(); j++){
        if(q[action][available_acts.at(j)] >= max_value)
        max_value = q[action][available_acts.at(j)];
    }

    q[current_state][action] = (r[current_state][action]) + (gamma* max_value);
}

void testQLearn(){

    int current_state = 2;
    std::vector<int> steps;
    steps.push_back(current_state);


    while(current_state != 5){

        double max_value =0;
        int max_index;

        for(int i=0; i< 6; i++){
            if(q[current_state][i] >= max_value){
                max_value = q[current_state][i];
                max_index = i;
            }
        }

        steps.push_back(max_index);
        current_state = max_index;

    }

    std::cout << "Selected Path: " << endl;

    for (int i=0; i<steps.size(); i++){
        std::cout << steps.at(i) << "  ";
    }
}



int main(){

    int index;
    int action;
    int current_state;
    std::vector<int> available_act;

    for(int i=0; i< 10000; i++){
        current_state = rand() % 7 + 0;
        available_act = available_actions(current_state);
        index = (rand() % (available_act.size()) + 0);
        action = available_act.at(index);
        update(current_state,action);
    }

    std::cout << "Trained Q Matrix: " << endl;

    for (int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            std::cout << (q[i][j] /500)*100 << " , " ;
        }
        std::cout  << endl;
    }

    testQLearn();

    return 0;

}

