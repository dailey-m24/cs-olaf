/*
Mars Dailey
player node class header file
12/8/2025
*/
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
using namespace std;

class Player{
    private:
        string player_name;
        int player_number;
        int vote;
        int answer;
        int points;
        Player *next;
    public:
        Player(string name, int num);
        //getters
        string getName();
        int getNumber();
        int getVote();
        int getAnswer();
        int getPoints();
        Player *getNext();
        //setters
        void setVote(int pvote);
        int setAnswer(int ans);
        void setNext(Player *newnext);
        void cardWinner();
        void voteWinner();
};

#endif