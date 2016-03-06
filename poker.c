/*
Poker Hand Simulator by Justin Stevens and Zeb Burke-Conte
Deals out a random poker hand, and then tells the user what hand they have.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "poker.h"

void AsciiCard(int card_rank, int card_suit) {
  const char ranks[]={'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
  const char* suits[]={"♠", "♥", "♦", "♣"};
  if(card_suit != -1 && card_rank != -1) {
    printf(" ______ \n|%c     |\n|%s     |\n", ranks[card_rank], suits[card_suit]);
  } else if(card_rank != -1) {
    printf(" ______ \n|%c     |\n|      |\n", ranks[card_rank]);
  } else if(card_suit != -1) {
    printf(" ______ \n|      |\n|%s     |\n", suits[card_suit]);
  }
}

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
    AsciiCard(card_rank, card_suit);
    //printf("%c%c \n", ranks[card_rank], suits[card_suit]);
    card_counter+=1;
  }
  printf("\n");
  return Player_Cards;
}


struct FinalHand BestFiveCards(struct PokerHand Player_Cards){
  struct FinalHand Final;
  int i;
  Final.best_hand=high_card;
  for(i=0; i<13; i++){
    //incrementing through all the ranks
    switch(Player_Cards.poker_ranks[i]){
      case 4:
        //if there are 4 of a kind, then we have quads
        Final.best_hand=quads;
        Final.TypeOfHand[0]=i;
        break;
      case 3:
        //if there are 3 of a kind, then we have trips
        if(Final.best_hand==pair){
          Final.best_hand=full_house;
          Final.TypeOfHand[1]=Final.TypeOfHand[0];
          Final.TypeOfHand[0]=i;
        }
        else{
        Final.best_hand=trips;
        Final.TypeOfHand[0]=i;
        }
        break;
      case 2:
        //if there is 2 of a kind, then we have a pair
        if(Final.best_hand==trips){
          Final.best_hand=full_house;
          Final.TypeOfHand[1]=i;
        }
        if(Final.best_hand==pair){
          Final.best_hand=two_pair;
          Final.TypeOfHand[1]=i;
        }
        else{
          Final.best_hand=pair;
          Final.TypeOfHand[0]=i;
        }
        break;
      case 1:
        //otherwise, it's just a high card
        if(Final.best_hand==high_card){
          Final.best_hand=high_card;
          Final.TypeOfHand[0]=i;
        }
        break;
      default:
        break;
      }
    }

    if(Final.best_hand<flush){
      for(i=0; i<4; i++){
        if(Player_Cards.poker_suits[i]==5){
          Final.best_hand=flush;
          Final.TypeOfHand[0]=i;
        }
      }
    }

    if(Final.best_hand<=flush){
      if(Player_Cards.poker_ranks[0]==1 && Player_Cards.poker_ranks[1]==1 && Player_Cards.poker_ranks[2]==1 && Player_Cards.poker_ranks[3]==1 && Player_Cards.poker_ranks[12]==1){
        if(Final.best_hand==flush){
          Final.best_hand=straight_flush;
          Final.TypeOfHand[1]=3;
        }
        else{
        Final.best_hand=straight;
        Final.TypeOfHand[0]=3;
        }
      }
      for(i=0; i<=8; i++){
        //below line uses purely for testing purposes
        //printf("%d %d %d %d %d\n", Player_Cards.poker_ranks[i], Player_Cards.poker_ranks[i+1], Player_Cards.poker_ranks[i+2], Player_Cards.poker_ranks[i+3], Player_Cards.poker_ranks[i+4]);
        if(Player_Cards.poker_ranks[i]==1 && Player_Cards.poker_ranks[i+1]==1 && Player_Cards.poker_ranks[i+2]==1 && Player_Cards.poker_ranks[i+3]==1 && Player_Cards.poker_ranks[i+4]==1){
          if(Final.best_hand==flush){
            Final.best_hand=straight_flush;
            Final.TypeOfHand[1]=i+4;
          }
          else{
          Final.best_hand=straight;
          Final.TypeOfHand[0]=i+4;
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
  const char ranks[]={'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
  const char suits[]={'s', 'h', 'c', 'd'};
  if(besthand.best_hand==high_card){
    printf("High Card %c", ranks[besthand.TypeOfHand[0]]);
  }
  else if(besthand.best_hand==pair){
    printf("Pair of %cs", ranks[besthand.TypeOfHand[0]]);
  }
  else if(besthand.best_hand==two_pair){
    printf("Two Pair %c and %c", ranks[besthand.TypeOfHand[0]], besthand.TypeOfHand[1]);
  }
  else if(besthand.best_hand==trips){
    printf("Trip %cs", ranks[besthand.TypeOfHand[0]]);
  }
  else if(besthand.best_hand==full_house){
    printf("Full House %c full of %c", ranks[besthand.TypeOfHand[0]], besthand.TypeOfHand[1]);
  }
  else if (besthand.best_hand==quads){
    printf("Quad %cs", ranks[besthand.TypeOfHand[0]]);
  }
  else if (besthand.best_hand==straight){
    printf("Straight %c high", ranks[besthand.TypeOfHand[0]]);
  }
  else if (besthand.best_hand==flush){
    switch(suits[besthand.TypeOfHand[0]]){
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
    switch(suits[besthand.TypeOfHand[0]]){
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

void PrintAsciiCards(struct FinalHand besthand) {
  if(besthand.best_hand==high_card){
    AsciiCard(besthand.TypeOfHand[0], -1);
  }
  else if(besthand.best_hand==pair){
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
  }
  else if(besthand.best_hand==two_pair){
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[1], -1);
    AsciiCard(besthand.TypeOfHand[1], -1);
  }
  else if(besthand.best_hand==trips){
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
  }
  else if(besthand.best_hand==full_house){
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[1], -1);
    AsciiCard(besthand.TypeOfHand[1], -1);
  }
  else if (besthand.best_hand==quads){
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
    AsciiCard(besthand.TypeOfHand[0], -1);
  }
  else if (besthand.best_hand==straight){
    if(besthand.TypeOfHand[0] == 3) {
      AsciiCard(12, -1);
      AsciiCard(0, -1);
      AsciiCard(1, -1);
      AsciiCard(2, -1);
      AsciiCard(3, -1);
    } else {
      AsciiCard(besthand.TypeOfHand[0] - 4, -1);
      AsciiCard(besthand.TypeOfHand[0] - 3, -1);
      AsciiCard(besthand.TypeOfHand[0] - 2, -1);
      AsciiCard(besthand.TypeOfHand[0] - 1, -1);
      AsciiCard(besthand.TypeOfHand[0], -1);
    }
  }
  else if (besthand.best_hand==flush){
    AsciiCard(-1, besthand.TypeOfHand[0]);
    AsciiCard(-1, besthand.TypeOfHand[0]);
    AsciiCard(-1, besthand.TypeOfHand[0]);
    AsciiCard(-1, besthand.TypeOfHand[0]);
    AsciiCard(-1, besthand.TypeOfHand[0]);
  }

  else if (besthand.best_hand==straight_flush){
    if(besthand.TypeOfHand[1] == 3) {
      AsciiCard(12, besthand.TypeOfHand[0]);
      AsciiCard(0, besthand.TypeOfHand[0]);
      AsciiCard(1, besthand.TypeOfHand[0]);
      AsciiCard(2, besthand.TypeOfHand[0]);
      AsciiCard(3, besthand.TypeOfHand[0]);
    } else {
      AsciiCard(besthand.TypeOfHand[1] - 4, besthand.TypeOfHand[0]);
      AsciiCard(besthand.TypeOfHand[1] - 3, besthand.TypeOfHand[0]);
      AsciiCard(besthand.TypeOfHand[1] - 2, besthand.TypeOfHand[0]);
      AsciiCard(besthand.TypeOfHand[1] - 1, besthand.TypeOfHand[0]);
      AsciiCard(besthand.TypeOfHand[1], besthand.TypeOfHand[0]);
    }
  }

  printf("\n");
}

struct FinalHand WhoWins(struct FinalHand besthands[], int player_count){
  int i;
  int player_number;
  struct FinalHand Winner;
  Winner.best_hand=high_card;
  for(i=0; i<player_count; i++){
    if(besthands[i].best_hand>Winner.best_hand){
      Winner.best_hand=besthands[i].best_hand;
      player_number=i;
      Winner.TypeOfHand[0]=besthands[i].TypeOfHand[0];
      Winner.TypeOfHand[1]=besthands[i].TypeOfHand[1];
    }
    else if(besthands[i].best_hand==Winner.best_hand){
      if(besthands[i].TypeOfHand[0]>Winner.TypeOfHand[0]){
        player_number=i;
        Winner.TypeOfHand[0]=besthands[i].TypeOfHand[0];
        Winner.TypeOfHand[1]=besthands[i].TypeOfHand[1];
      }
    }
    else{
      continue;
    }

  }
  printf("Player %d wins with: ", player_number);
  PrintCards(Winner);
  PrintAsciiCards(Winner);

  return Winner;

}

int main(){
  srand((unsigned) time(NULL));
  int player_count, i;
  printf("How many players do you want to have? ");
  scanf("%d", &player_count);
  printf("\n");
  struct PokerHand players[player_count];
  struct FinalHand besthands[player_count];
  for(i=0; i<player_count; i++){
    printf("Player %d: \n", i);
    players[i]=MakeHand(players[i]);
    besthands[i]=BestFiveCards(players[i]);
    PrintCards(besthands[i]);
    printf("\n");

  }
  WhoWins(besthands, player_count);
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


  return 0;
}
