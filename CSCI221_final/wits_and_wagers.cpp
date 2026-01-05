/*
Mars Dailey
CSCI221 Final Project: Main Program
    see "operation instructions" file for compiling instructions
12/8/2025
Citations:
    Buzzfeed - ideas for some questions
        https://www.buzzfeed.com/abbyzinman/general-knowledge-trivia-numerical
    Pubquiz - ideas for some questions
        https://pubquizquestions.net/questions/general-knowledge/page-420
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "player.hpp"
#include "question.hpp"
using namespace std;

class Game{
    private:
        Player *first;
        int numPlayers;
        vector<int> ans; // array of answers; vote = ans[i]+2
    public:
        Game(int numplay){
            first = nullptr;
            numPlayers = numplay;
        }
        ~Game() { // deconstructor
		    Player * current = first;
		    Player * temp = NULL;
		
    		if (current == NULL) {
			    return;
		    } else if (current->getNext() == NULL) { // single element list
			    delete current;
			    first = NULL;
			    return;
		    } 
		    while (current->getNext() != NULL) {
			    temp = current->getNext();
			    delete current;
			    current = temp;
		    }
        }

        void printArr(vector<int> vec){
            for (int i = 0; i<vec.size(); i++){
                cout << vec[i] << endl; 
            }
        }
 
        bool addPlayer(string name, int number){ 
            Player *current = first;
            Player *newPlayer = new Player(name,number);
            if (first == nullptr){
                first = newPlayer;
                return true;
            } else {
                while (current->getNext() != nullptr){
                    current = current->getNext();
                }
                current->setNext(newPlayer);
                return true;
            }
            return false;
        }

        void collectAnswers(string ques){
            Player *current = first;
            while(current!=nullptr){
                sleep(1); // code to clear screen, used in 2d array lab
				puts ("\033[H\033[J");
                cout << "The question is: \""<<ques << "\"\n";
                cout << current->getName() << ", enter your guess: \n";
                int guess;
                while(!(cin>>guess)){
                    cin.clear();
                    cin.ignore();
                    cout << "Not a valid answer. Try again.\n";
                }
                ans.push_back(current->setAnswer(guess)); //i made setAnswer add and return the answer
                current = current->getNext();
            }
            printArr(ans);
            cout << "Processing...\n";
        }

        void sortAnswers(){
            int current;
            int index;
            for(int i = 1; i<ans.size(); i++){
                current = ans[i];
                index = i;
                while (index > 0 && ans[index-1] > current){ // while theres still more to compare and the previous element is greater than current
                    ans[index] = ans[index-1];
                    index--;
                }
                ans[index] = current;
            }
        }

        void displayAnswers(){ 
            for (int i=0; i<ans.size();i++){
                if (ans[i]==ans[i-1]){
                    ans.erase(ans.begin()+i-1);
                }
            }//combines duplicates

            cout << "1: less than " << ans[0] << endl;
            for (int i=0; i<ans.size();i++){
                cout << i+2 << ": " << ans[i] << endl;
            }
        }

        void collectVotes(string ques){
            sleep(1);
            puts ("\033[H\033[J");
            cout << "\nAll answers have been recorded.\nNow it's time to vote for which one you think \nis the closest to the correct answer (*WITHOUT GOING OVER*). \nBe sure to enter the option number that corresponds \nto the answer, not the numerical answer itself.\n";
            cout << "\nEnter Y when you are ready to continue.\n";
            char cont;
            cin >> cont;//doesnt have to be Y, i just want to give them an option
            Player *current = first;
            while(current!=nullptr){
                sleep(1);
			    puts ("\033[H\033[J");
                cout <<ques<<endl;
                displayAnswers();
                cout << current->getName() << ", enter your vote: \n";
                cin.ignore();
                int vote;
                while((!(cin>>vote))||(vote>ans.size()+1||vote<1)){
                    cin.clear();
                    cin.ignore();
                    cout << "Not a valid answer. Try again.\n";
                }
                current->setVote(vote); 
                current = current->getNext();
            }
        }

        void leaderboard(){ 
            vector<string> playerName;
            vector<int> playerPoints;
            
            Player *curr = first;
            int i = 0;
            while(curr!=nullptr){
                playerName.push_back(curr->getName());
                playerPoints.push_back(curr->getPoints());
                i++;
                curr=curr->getNext();
            }// fill vectors
            int current;
            string currentName;
            int index;
            for(int i = 1; i<playerPoints.size(); i++){
                current = playerPoints[i];
                currentName = playerName[i];
                index = i;
                while (index > 0 && playerPoints[index-1] > current){ 
                    playerPoints[index] = playerPoints[index-1];
                    playerName[index] = playerName[index-1];
                    index--;
                } 
                playerPoints[index] = current;
                playerName[index] = currentName;
            } // sort vectors based on points
            
            int place=0;
            for(int i=playerName.size()-1;i>=0;i--){
                ++place;
                cout << place <<": ";
                cout << playerName[i]<< ", " << playerPoints[i] << " points\n"; 
            }
            cout << "\nCongratulations, " << playerName.back() << ", you are the winner!\n";
        }

        int findWinner(int answer){
            int winner;
            cout << "Correct Answer: " << answer << endl;
            if(ans[0]>answer){//If answer is less than the lowest answer
                    cout << "No one's answer wins this round.\n";
                    Player *current = first;
                    while(current!=nullptr){//While loop traversal to count votes
                        if (current->getVote() == 1) 
                            current->voteWinner();
                        current = current->getNext();
                    }
                    while (!ans.empty()){
                        ans.pop_back();
                    }//clear ans vector so that it is empty for next round
                    return -1;
            }

            for (int i=0;i<ans.size();i++){ //loop through each answer
                if (i != ans.size()-1 && ans[i]<=answer && ans[i+1]>answer){ //if right answer and not last answer
                    winner = ans[i];
                    Player *current = first;
                    while (current!=nullptr){ //loop through each person
                        if (current->getVote() == i+2){//i+2 because the lowest answer is at index 0 but players enter 2 to vote for it.
                            current->voteWinner();
                        }
                        if (current->getAnswer() == winner){
                            current->cardWinner();
                            cout << current->getName() << "'s answer wins!\n";
                        }
                        current = current->getNext();
                    } // count votes and get winner
                } else if (i==ans.size() - 1 && answer>=ans[i]){ //if the last answer is the right one
                    winner = ans[i];
                    Player *current = first;
                    while (current!=nullptr){ 
                        if (current->getVote() == i+2){
                            current->voteWinner();
                        }
                        if (current->getAnswer() == winner){
                            current->cardWinner();
                            cout << current->getName() << "'s answer wins!\n";
                        }
                        current = current->getNext();
                    } //count votes and get winner
                } 
            } //for loop

            while (!ans.empty()){
                ans.pop_back();
            }//clear ans so that it is empty for next round

            return winner;
        } //findWinner

};//class Game

int main(int argc, char * argv[]){
    //open file stuff
    if(argc<3){
        cerr << "<ERROR> Usage: " << argv[0] << " <input_filename1> <input_filename2>" << endl;
        exit(1);
    }
    string questFile = argv[1];
    string ansFile = argv[2];
    ifstream inputqFile;
    ifstream inputaFile;
    
	inputqFile.open(questFile);
    if (inputqFile.fail()){
        cerr << "Question file opening failed." << endl;
        exit(1);
    }
    inputaFile.open(ansFile);
    if (inputaFile.fail()){
        cerr << "Answer file opening failed." << endl;
        exit(1);
    }
    
    cout <<"\nWits and Wagers is a trivia game that involves 4-20 players. \n";
    cout <<"Each round, you will be asked a random trivia question that warrants a numerical answer.\n";
    cout <<"The players will submit their own answers, then place bets on \n";
    cout <<"whose answer they think is closest to the right answer WITHOUT GOING OVER.\n";
    cout <<"\nFor example, if the correct answer is 75 and the two nearest responses are 76 and 62, the winner \n";
    cout <<"would be 62, even though 76 is closer. Don't let it trip you up!\n";
    cout <<"\nPlayers are given 2 points if they have the winning answer, \n";
    cout <<"and 1 point if they vote for the winning answer.\n";
    cout <<"The player with the most points after 7 questions is the winner!\n";
    cout <<"Enjoy the game!\n";

    Question Wits(inputqFile, inputaFile);
    Wits.addRounds();

    int numplayers;
    cout << "\nHow many people are playing? At least 4 recommended.\nEnter number of players here:\n";
    while (!(cin>>numplayers)){
        cin.clear();
        cin.ignore();
        cout << "invalid input. try again!\n";
    }

    Game Gameplay(numplayers);
    cin.ignore();
    for (int i=1; i<=numplayers;i++){
        cout << "Player " << i << ", enter your name: \n";
        string playName;
        while(!getline(cin, playName)){
            cin.clear();
            cin.ignore();
            cout << "Not a valid answer. Try again.\n";
        }
        Gameplay.addPlayer(playName, i);
    }

    for(int round=1;round<=ROUNDS;round++){
        cout << "Round " << round << " starting...\n";
        string roundQuestion = Wits.getQuest();
        Gameplay.collectAnswers(roundQuestion);
        Gameplay.sortAnswers();
        Gameplay.collectVotes(roundQuestion);
        int roundAnswer = Wits.getAns();
        Gameplay.findWinner(roundAnswer);
        cout<<"Enter Y to continue, or Q to quit the program.\n";
        char cont;
        cin>>cont;
        if (cont=='Q'||cont=='q'){
            cout <<"Thanks for playing! Here is your ranking:\n";
            Gameplay.leaderboard();
            cout<<"Now quitting the program...\n";
            return 0;
        }//doesnt actually matter if they don't hit Y, i just wanted to give them an option
        
        Wits.removeRound();
    }
    cout << "Good Game! Here is where you stand after the final round:\n";
    Gameplay.leaderboard();


    return 0;
}