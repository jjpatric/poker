//macros to use bool with any C compiler
#define true 1
#define false 0
typedef int bool;
//initialize the hand_size to 5 for a standard poker game
#define hand_size 5

//each pokerhand consists of several things
struct PokerHand{
  //all the suits
  int poker_suits[4];
  //all the ranks
  int poker_ranks[13];
  //this is a bool to determine whether or not a specific card is in the hand or not
  //this is used to repeat cards repeated twice
  bool hand[13][4];
};
//enumeration to rank poker hands from worst to best
enum TypeOfHands{
  high_card,
  //lower values are weaker hands
  pair,
  two_pair,
  trips,
  straight,
  flush,
  full_house,
  quads,
  straight_flush
  //higher values are better
};

struct FinalHand{
  //The Final Hand which a person has it determined by two factors:
  //What TypeOfHand it is
  enum TypeOfHands (best_hand);
  //What it consists of (this is determined by things such as how high the straight is, two pair, full house, or straight flush)
  char TypeOfHand[2];
  //Kickers
  char Kicker[5];

};
