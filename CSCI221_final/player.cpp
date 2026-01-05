#include <iostream>
#include <string>
#include "player.hpp"
using namespace std;

    Player::Player(string name, int num){
        player_name = name;
        player_number = num;
        vote = 0;
        answer = 0;
        points = 0;
        next = nullptr;
    }
    //getters
    string Player::getName(){
        return player_name;
    }
    int Player::getNumber(){
        return player_number;
    }
    int Player::getVote(){
        return vote;
    }
    int Player::getAnswer(){
        return answer;
    }
    int Player::getPoints(){
        return points;
    }
    Player * Player::getNext(){
        return next;
    }
    //setters
    void Player::setVote(int pvote){
        vote = pvote;
    }
    int Player::setAnswer(int ans){
        answer = ans;
        return answer;
    }
    void Player::setNext(Player *newnext){
        next = newnext;
    }
    void Player::cardWinner(){
        points = points+2;
    }
    void Player::voteWinner(){
        points = points+1;
    }