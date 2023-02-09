#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

enum Suit { Club, Diamond, Heart, Spade, NumSuits };
enum CardID { ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, NumFaceValues };

struct Card
{
    Suit suit;
    CardID  cardID;
};

const int NUM_CARDS_IN_DECK = 52;
const int MAX_PLAYER_CARDS = 5;

struct Deck
{
    int nextCardToDeal;
    Card dCards[NUM_CARDS_IN_DECK];
};

struct Player
{
    string name;
    int cardsReceived;
    Card pCards[MAX_PLAYER_CARDS];
    int hitLimit;
    int totalValue;
};

int cardValue(Card & card);
string cardName(Card & card);
void shuffleDeck(Deck & deck);
void initializeDeck(Deck & deck);
Card getNextCard(Deck & deck);
void printDeck(Deck & deck);
void printPlayer(Player & player);
void playRound(Player players[], int numPlayers, Deck & deck);
