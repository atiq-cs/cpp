#include "blackJack.h"
#include <time.h>
#include <algorithm>

// Return the numeric value of the card
// two, three, four, five, six, seven, eight, nine return 2,3,4,5,6,7,8,9 respectively
// Ace always returns 1  (I know Ace can sometimes be 11 in Black Jack, but this is a simplification)
// Jack, Queen, and King returns 10

int cardValue(Card & card)
{
    //*****Place your code here
    // from example ten has value 10
    if (card.cardID >= ace && card.cardID <= ten)
        return (int)(card.cardID + 1);
    if (card.cardID >= jack && card.cardID <= king)
        return 10;
    // handle invalid card ID
    return 0;
}

// Return a string name for the card.   Some examples:
// AC    for the  Ace of Clubs
// 2D    for the  Two of Diamonds
// 9H    for the  Nine of Hearts
// TC    for the  Ten of Clubs
// JD    for the  Jack of Diamonds
// QH    for the  Queen of Hearts
// KS    for the  King of Spades

string cardName(Card & card)
{
    //*****Place your code here
    // Suits: Club, Diamond, Heart, Spade, NumSuits
    string suits_string_map[] = {"C", "D","H","S", "N"};
    // card ID: ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, NumFaceValues
    string cardID_string_map[] = { "A","2", "3", "4", "5","6","7","8","9", "T", "J", "Q", "K", "N" };

    // handle invalid input; not required if input is good
    if (card.suit < Club || card.suit > NumSuits)
        return "";
    if (card.cardID < ace || card.cardID > NumFaceValues)
        return "";

    // return map for valid inputs
    return cardID_string_map[card.cardID]+suits_string_map[card.suit];
}


// Shuffle a Deck structure.  Make sure you set the "nextCardToDeal"=0
void shuffleDeck(Deck & deck)
{
    //*****Place your code here
    int numCardsRemaining = NUM_CARDS_IN_DECK;

    srand((unsigned int) time(NULL));
    int current_index = NUM_CARDS_IN_DECK - numCardsRemaining;

    // make a random pick of card for each card index
    while (numCardsRemaining > 0) {
        int new_card_index = current_index+rand() % numCardsRemaining;
        swap(deck.dCards[current_index], deck.dCards[new_card_index]);

        numCardsRemaining--;
        current_index++;
    }
    deck.nextCardToDeal = 0;
}

// Return the card at the index of "nextCardToDeal", then increment this index by one.

Card getNextCard(Deck & deck)
{
    //*****Place your code here
    deck.nextCardToDeal++;
    return deck.dCards[deck.nextCardToDeal - 1];
}

// Print out the Deck of cards

void printDeck(Deck & deck)
{
    //*****Place your code here
    for (int s = Club; s <= Spade; s++) {
        for (int n = ace; n <= king; n++) {
            cout << cardName(deck.dCards[s * 13 + n]) << "/" << cardValue(deck.dCards[s * 13 + n]) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Fill in the Deck with one of each possible card.  This is done by looping through
// all of the "Suit" values and all of the "CardID" values (i.e. 2 nested loops)
// Although it shouldn't happen, you might want to check to make sure you don't 
// exceed "NUM_CARDS_IN_DECK"

void initializeDeck(Deck & deck)
{
    //*****Place your code here
    for (int s = Club; s <= Spade; s++) {
        for (int n = ace; n <= king; n++) {
            struct Card card = {(Suit)s, (CardID) n};
            deck.dCards[s * 13 + n] = card;
        }
    }
}

// Deal cards for the Player from the Deck.  
//   Start by zeroing out totalValue and cardsReceived. 
//   Repeated call the getNextCard(deck) routine. Cards are stored in pCards array at the index of 
//   cardsReceived.  The cardsReceived index is incremented and the totalValue is updated.  
//   This process continues until either cardsReceived == MAX_PLAYER_CARDS or 
//   player.hitLimit < player.totalValue.

void dealCards2Player(Player  & player, Deck & deck)
{
    //*****Place your code here
    for (player.cardsReceived = player.totalValue = 0; player.cardsReceived < MAX_PLAYER_CARDS && player.hitLimit >= player.totalValue; player.totalValue += cardValue(player.pCards[player.cardsReceived]), player.cardsReceived++)
        player.pCards[player.cardsReceived] = getNextCard(deck);
}

// print out player name, totalValue of cards, hitLimit and all of the cards received

void printPlayer(Player & player)
{
    //*****Place your code here
    cout << "Player: " << player.name;
    cout << " total=" << player.totalValue;
    cout << " hitLimit=" << player.hitLimit;
    for (int i = 0; i < player.cardsReceived; i++)
        cout << " " << cardName(player.pCards[i]);
    cout << endl;
}

// Shuffle the Deck, and then print out the shuffled deck.  
// Then for every player, call dealCards2Player.  
// Call printPlayer to print out each player's situation
// Then go through the players and determine the winner.  
// The winner is the player who has the highest totalValue
// without exceeding 21.

void playRound(Player players[], int numPlayers, Deck & deck)
{
    //*****Place your code here
    shuffleDeck(deck);
    cout << endl << "Shuffled Deck " << endl;
    printDeck(deck); // Print out the shuffled deck
    for (int i = 0; i < numPlayers; i++) {
        dealCards2Player(players[i], deck);
        printPlayer(players[i]);
    }
    // determine winner
    int max_index = -1;
    for (int i = 0; i < numPlayers; i++) {
        if (max_index == -1 && players[i].totalValue <= 21)
            max_index = i;
        else if (players[i].totalValue <= 21 && players[i].totalValue > players[max_index].totalValue)
            max_index = i;
    }
    if (max_index == -1)
        cout << "There is no winner!" << endl;
    else
        cout << "Winner = " << players[max_index].name<< " with a value of " << players[max_index].totalValue << endl;
}
