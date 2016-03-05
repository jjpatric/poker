/*
Poker Hand Simulator by Justin Stevens
Deals out a random poker hand, and then tells the user what hand they have.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "poker.h"

struct PokerHand MakeHand(struct PokerHand Player_Cards){
  int i,j;
  for (i=0; i<=12; i++){
    Player_Cards.poker_ranks[i]=0;
    for(j=0; j<=3; j++){
      Player_Cards.poker_suits[j]=0;
      //iniitialize
      Player_Cards.hand[i][j]=0;
    }
  }

  const char ranks[]={'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
  const char suits[]={'s', 'h', 'c', 'd'};
  srand((unsigned) time(NULL));
  int card_counter=0, card_rank, card_suit;
  while(card_counter<hand_size){
    //rank is random number from 1 to 13
    card_rank=rand()%13;
    //suit is random number from 1 to 4
    card_suit=rand()%4;
    if(Player_Cards.hand[card_rank][card_suit]){
      //if it's in the hand, then continue and disregard everything else
      continue;
    }
    Player_Cards.hand[card_rank][card_suit]=true;
    //add the rank to the poker_ranks variable
    Player_Cards.poker_ranks[card_rank]+=1;
    Player_Cards.poker_suits[card_suit]+=1;
    printf("%c%c ", ranks[card_rank], suits[card_suit]);
    card_counter+=1;
  }
  printf("\n");
  return Player_Cards;
}

struct FinalHand BestFiveCards(struct PokerHand Player_Cards){
  const char ranks[]={'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
  const char suits[]={'s', 'h', 'c', 'd'};
  struct FinalHand Final;
  int i;
  Final.best_hand=high_card;
  for(i=0; i<13; i++){
    //incrementing through all the ranks
    switch(Player_Cards.poker_ranks[i]){
      case 4:
        //if there are 4 of a kind, then we have quads
        Final.best_hand=quads;
        Final.TypeOfHand[0]=ranks[i];
        break;
      case 3:
        //if there are 3 of a kind, then we have trips
        if(Final.best_hand==pair){
          Final.best_hand=full_house;
          Final.TypeOfHand[1]=Final.TypeOfHand[0];
          Final.TypeOfHand[0]=ranks[i];
        }
        else{
        Final.best_hand=trips;
        Final.TypeOfHand[0]=ranks[i];
        }
        break;
      case 2:
        //if there is 2 of a kind, then we have a pair
        if(Final.best_hand==trips){
          Final.best_hand=full_house;
          Final.TypeOfHand[1]=ranks[i];
        }
        if(Final.best_hand==pair){
          Final.best_hand=two_pair;
          Final.TypeOfHand[1]=ranks[i];
        }
        else{
          Final.best_hand=pair;
          Final.TypeOfHand[0]=ranks[i];
        }
        break;
      case 1:
        //otherwise, it's just a high card
        if(Final.best_hand==high_card){
          Final.best_hand=high_card;
          Final.TypeOfHand[0]=ranks[i];
        }
        break;
      default:
        break;
      }
    }

    if(Final.best_hand<flush){
      for(i=0; i<=4; i++){
        if(Player_Cards.poker_suits[i]==5){
          Final.best_hand=flush;
          Final.TypeOfHand[0]=suits[i];
        }
      }
    }

    if(Final.best_hand<=flush){
      if(Player_Cards.poker_ranks[0]==1 && Player_Cards.poker_ranks[9]==1 && Player_Cards.poker_ranks[10]==1 && Player_Cards.poker_ranks[11]==1 && Player_Cards.poker_ranks[12]==1){
        if(Final.best_hand==flush){
          Final.best_hand=straight_flush;
          Final.TypeOfHand[1]=ranks[3];
        }
        else{
        Final.best_hand=straight;
        Final.TypeOfHand[0]=ranks[3];
        }
      }
      for(i=0; i<=8; i++){
        //below line uses purely for testing purposes
        //printf("%d %d %d %d %d\n", Player_Cards.poker_ranks[i], Player_Cards.poker_ranks[i+1], Player_Cards.poker_ranks[i+2], Player_Cards.poker_ranks[i+3], Player_Cards.poker_ranks[i+4]);
        if(Player_Cards.poker_ranks[i]==1 && Player_Cards.poker_ranks[i+1]==1 && Player_Cards.poker_ranks[i+2]==1 && Player_Cards.poker_ranks[i+3]==1 && Player_Cards.poker_ranks[i+4]==1){
          if(Final.best_hand==flush){
            Final.best_hand=straight_flush;
            Final.TypeOfHand[1]=ranks[i+4];
          }
          else{
          Final.best_hand=straight;
          Final.TypeOfHand[0]=ranks[i+4];
          }
        }
        else{
          continue;
        }
      }
    }

    return Final;
}
void PrintCards(struct FinalHand besthand){
  if(besthand.best_hand==high_card){
    printf("High Card %c", besthand.TypeOfHand[0]);
  }
  else if(besthand.best_hand==pair){
    printf("Pair of %cs", besthand.TypeOfHand[0]);
  }
  else if(besthand.best_hand==two_pair){
    printf("Two Pair %c and %c", besthand.TypeOfHand[0], besthand.TypeOfHand[1]);
  }
  else if(besthand.best_hand==trips){
    printf("Trip %cs", besthand.TypeOfHand[0]);
  }
  else if(besthand.best_hand==full_house){
    printf("Full House %c full of %c", besthand.TypeOfHand[0], besthand.TypeOfHand[1]);
  }
  else if (besthand.best_hand==quads){
    printf("Quad %cs", besthand.TypeOfHand[0]);
  }
  else if (besthand.best_hand==straight){
    printf("Straight %c high", besthand.TypeOfHand[0]);
  }
  else if (besthand.best_hand==flush){
    switch(besthand.TypeOfHand[0]){
      case 's':
        printf("Flush: Spades ");
        break;
      case 'h':
        printf("Flush: Hearts");
        break;
      case 'd':
        printf("Flush:  Diamonds");
        break;
      case 'c':
        printf("Flush:  Clubs");
        break;
      default:
        break;
    }
  }

  else if (besthand.best_hand==straight_flush){
    switch(besthand.TypeOfHand[0]){
      case 's':
        printf("Straight Flush: Spades, %c high ", besthand.TypeOfHand[1]);
        break;
      case 'h':
        printf("Straight Flush:  Hearts, %c high ", besthand.TypeOfHand[1]);
        break;
      case 'd':
        printf("Straight Flush:  Diamonds, %c high ", besthand.TypeOfHand[1]);
        break;
      case 'c':
        printf("Straight Flush:  Clubs, %c high ", besthand.TypeOfHand[1]);
        break;
      default:
        break;
      }

    }


  printf("\n");
}


int main(){
  struct PokerHand player1;
  player1=MakeHand(player1);

  struct PokerHand player2;
  player2=MakeHand(player2);
  /*
  //Testing Purposes
  int i;

  player1.poker_suits[0]=5;
  for(i=0; i<13; i++){
    if(i==0 || i==9 || i==10 || i==11 || i==12){
      player1.poker_ranks[i]=1;
    }
    else{
      player1.poker_ranks[i]=0;
    }
  } */
  struct FinalHand besthand1=BestFiveCards(player1);
  PrintCards(besthand1);

return 0;
}
