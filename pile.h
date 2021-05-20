#ifndef __PILE__H__
#define __PILE__H__

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>

#include "card.h"

class Pile{
  
  public:
    Pile();
    Pile(std::unique_ptr<Card> card);
    std::vector<std::unique_ptr<Card>> cards;
    void shuffleP(std::default_random_engine& rng);
    std::unique_ptr<Card> draw();
    void addCard(std::unique_ptr<Card> card);
    Card getTopCard();

} ;
#endif
