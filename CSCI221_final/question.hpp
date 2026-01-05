/*
Mars Dailey 
header file for question class
12/8/2025
*/
#ifndef _QUESTION_H_
#define _QUESTION_H_

#define ROUNDS 7
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class Question{
    private:
        vector<string> questions;
        vector<int> answers;
        int intArr[ROUNDS];
        queue<string> roundQ;
        queue<int> roundA;
    public:
        Question(ifstream &qfile, ifstream &afile);
        void addRounds();
        int removeRound(); //removes the round from each of the queues and returns the answer
        string getQuest(); // prints the question
        int getAns(); // returns answer without modifying the queue
        void printArr();// prints arrays/vectors for testing purposes
};

#endif