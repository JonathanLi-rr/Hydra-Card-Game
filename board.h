#ifndef __BOARD__H__
#define __BOARD__H__

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include "pile.h"
#include "player.h"
class Board{
  int turn=0;
  std::vector<std::unique_ptr<Pile>> heads;
  int headBegin=1;
  int headEnd=0;
  int playercount;

  void winDeclare(int p);
  public:
    
    std::vector<Player> players;
    
    
    Board(int pcount);
    void print();
    void initialize(std::default_random_engine& rng, int mode);
    void addToHead(std::unique_ptr<Card> card, int head);
    void play(int mode);
    int getBegin();
    int getEnd();
    void addHead(std::unique_ptr<Card> card);
} ;
#endif
