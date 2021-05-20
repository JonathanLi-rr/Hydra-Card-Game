#ifndef __CARD__H__
#define __CARD__H__

#include <iostream>
#include <memory>
#include <string>
class Card{
  
  public:
    Card();
    Card(char suit, int value);
    char suit;
    int value;


    std::string getValue();
    int playableon(Card);
} ;

//void changeCard(std::unique_ptr<Card> card);
void changeCard(std::unique_ptr<Card> &c);
#endif
