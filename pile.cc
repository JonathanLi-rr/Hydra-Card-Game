#include "pile.h"
#include "card.h"
using namespace std;
void Pile::shuffleP(std::default_random_engine& rng){
  shuffle(cards.begin(),cards.end(), rng);
}
unique_ptr<Card> Pile::draw(){
  unique_ptr<Card> temp=move(cards.back());
  cards.pop_back();
  return temp;
}
void Pile::addCard(unique_ptr<Card> card){
  cards.push_back(move(card));
}
Card Pile::getTopCard(){
  return *(cards.back());
}

Pile::Pile(){}
Pile::Pile(std::unique_ptr<Card> card){
  cards.emplace_back(move(card));
}
