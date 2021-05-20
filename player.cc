#include "player.h"
using namespace std;
unique_ptr<Card> Player::draw(){
  if (drawCount==0){
    discardPile.shuffleP(rng);
    for (int i=0;i<discardCount;i++){
      addToDraw(move(discardPile.cards[i])); 
    }
    discardPile.cards.clear();
    drawCount=discardCount;
    discardCount=0;
  }
  drawCount--;
  return drawPile.draw();
}

void Player::swap(std::unique_ptr<Card>& card){
  //cout<<"swapstart"<<endl;
  if (!reserving){
      reserve=move(card);
      //cout<<"DDDD    "<<reserve->getValue()<<endl;
      reserving=true;
      
  }
  else{
    auto k=make_unique<Card>();
  
    k=move(reserve);
    reserve=move(card);
    card=move(k);
  }
  //cout<<"swapend"<<endl;
}

int Player::getDrawCount(){
  return drawCount;
}
int Player::getDiscardCount(){
  return discardCount;
}
bool Player::getReserveCount(){
  return reserving;
}
int Player::totalCount(){
  int a=drawCount+discardCount;
  /*if (reserving){
    a++;
  }*/
  return a;
}

void Player::addToDraw(std::unique_ptr<Card> card){
  drawPile.addCard(move(card));
  drawCount++;
}

void Player::addToDiscard(std::unique_ptr<Card> card){
  discardPile.addCard(move(card));
  discardCount++;
}

void Player::print(){
  cout<<"drawpile"<<endl;
  for (int i=0;i<drawCount;i++){
    cout<<drawPile.cards[i]->getValue()<<endl;
  }
  cout<<"discardpile"<<endl;
  for (int i=0;i<discardCount;i++){
    cout<<discardPile.cards[i]->getValue()<<endl;
  }

  cout<<"reserve"<<endl;
  if (reserving)
    cout<<reserve->getValue()<<endl;
}
bool Player::checkWin(){
  return ((discardCount==0) && (drawCount==0) && (reserving==false));
}

void Player::reserveToDraw(){
  if (reserving){
    addToDraw(move(reserve));
    reserving=false;
  }
}

Player::Player(std::default_random_engine& rng):rng{rng}{
  

}
