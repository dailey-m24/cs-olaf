/*
Mars Dailey
cpp file for question class
12/8/2025
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "question.hpp"
using namespace std;

    Question::Question(ifstream &qfile, ifstream &afile){
        srand(time(0));
        while(!qfile.eof()){
            string q;
            while (getline(qfile, q)){
                questions.push_back(q);
            }
        }
        while(!afile.eof()){
            int a;
            while (afile >> a){
                answers.push_back(a);
            }
        }
        
        vector<int> temp;
        for(int i=0;i<questions.size();i++){
            temp.push_back(i);
        } // fills temporary vector with numbers that correspond to the number of questions
        for (int i=0;i<ROUNDS;i++){
            int num = rand()%temp.size();
            intArr[i]=temp[num];
            temp[num]=temp.back();
            temp.pop_back();
        } // fills int vector with numbers from the temporary vector, 
          // then deletes that option from the temp vector to avoid repeats

        
    }

    void Question::addRounds(){
        for (int i=0;i<ROUNDS;i++){
            roundQ.push(questions[intArr[i]]);
            roundA.push(answers[intArr[i]]);
        }
    }

    int Question::removeRound(){
        roundQ.pop();
        int ans = roundA.front();
        roundA.pop();
        return ans;
    } //removes the round from each of the queues and returns the answer

    string Question::getQuest(){
        return roundQ.front();
    } // returns the question

    int Question::getAns(){
        return roundA.front();
    } // returns answer without modifying the queue

    void Question::printArr(){
        cout << "Questions from file:\n";
        for (int i=0;i<questions.size();i++){
            cout << questions[i]<<endl;
        }
        cout << "\nAnswers from file:\n";
        for (int i=0;i<answers.size();i++){
            cout << answers[i]<<endl;
        }
        cout << "\nInt array:\n";
        for (int i=0;i<ROUNDS;i++){
            cout << intArr[i]<<endl;
        }
        cout << "\nRound questions:\n";
        for (int i=0;i<ROUNDS;i++){
            cout << questions[intArr[i]]<<endl;
        }
        cout << "\nRound answers\n";
        for (int i=0;i<ROUNDS;i++){
            cout << answers[intArr[i]]<<endl;
        }
    } // prints arrays/vectors for testing purposes