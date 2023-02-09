//
// PURPOSE: Black Jack Game Driver Program
//
// Author : Atiq Rahman
// Date   : 11-02-2015
// Status : Good
// Remarks: Demos,
//        - Functional C programming with no OOP
//        - enum, struct, functions from algorithm header
// Output :
//        See ReadMe
//

#include "blackJack.h"


// Fill in the players names and hitLimits. You don't need to do anything here.
void initializePlayers(Player players[], string names[], int hitLimits[], int numPlayers)
{
    for (int i = 0; i < numPlayers; i++)
    {
        players[i].name = names[i];
        players[i].hitLimit = hitLimits[i];
    }
}

int main()
{
    Deck deck;

    // Set up the players
    const int numPlayers = 5;
    Player players[numPlayers];
    string names[numPlayers] = { "Fred", "Ben", "Shark", "Raymond", "Dealer" };
    int  hitLimits[numPlayers] = { 16, 17, 18, 18, 17 };
    initializePlayers(players, names, hitLimits, numPlayers);

    initializeDeck(deck);  // This is your initializeDeck routine.  
    // Note the deck will get shuffled each time playRound is called. 

    string response;
    do
    {
        playRound(players, numPlayers, deck);  // You will have to write this routine

        cout << "Do you want to play another round?" << endl;
        cin >> response;
    } while (response == "y" || response == "Y");
}
