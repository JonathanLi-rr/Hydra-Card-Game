#ifndef __PLAYER__H__
#define __PLAYER__H__

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "pile.h"
#include "card.h"
class Player{
  Pile drawPile;
  Pile discardPile;
  std::unique_ptr<Card> reserve;
  std::default_random_engine& rng;
  int drawCount=0;
  int discardCount=0;
  bool reserving = false;
  public:
    

    
    Player(std::default_random_engine& rng);
    std::unique_ptr<Card> draw();
    void swap(std::unique_ptr<Card>& card);
    void addToDraw(std::unique_ptr<Card> card);
    void addToDiscard(std::unique_ptr<Card> card);
    void print();
    bool checkWin();
    int getDrawCount();
    int getDiscardCount();
    bool getReserveCount();
    int totalCount();
    void reserveToDraw();
} ;
#endif
