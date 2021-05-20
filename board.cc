#include "board.h"
using namespace std;
void Board::initialize(std::default_random_engine& rng, int mode){
  int p=players.size();
  vector<Card> temp;
  
  char suite[]={'S','H','C', 'D'};
  vector<char> suits (suite, suite + sizeof(suite) / sizeof(char) );
  int nums=13;
  for (int i=0;i<p;i++){
      for (int j=0;j<suits.size();j++){
        for (int k=1;k<=nums;k++){
          temp.emplace_back(suits[j], k);
        }

      }
      for (int joker=0;joker<2;joker++){
        temp.emplace_back('J', 2);
      }
  }
  shuffle(temp.begin(),temp.end(), rng);
  int index=0;
  int play=0;

  while (index<temp.size()){
    players[play].addToDraw(make_unique<Card>(temp[index]));
    index++;
    play=index/(nums*4+2);
  }
  unique_ptr<Card> card=move(players[0].draw());
  if (mode==1){
    changeCard(card);
  }
  addHead(move(card));
  print();
  for (int i=0;i<playercount;i++){
    cout<<"Player "<<i+1<<": "<<players[i].totalCount() ;
    cout<<" ("<<players[i].getDrawCount()<<" draw, "<<players[i].getDiscardCount()<<" discard)";
    cout<<endl;
  }
  cout<<endl;
  turn++;

  cout<<"Player "<<(turn+1)<<", it is your turn"<<endl;
  string t;
  getline(cin, t);
  if (cin.eof()){
    throw 1;
  }

}

int Board::getBegin(){
  return headBegin;
}
int Board::getEnd(){
  return headEnd;
}
void Board::print(){
  cout<<endl;
  cout<<"Heads:"<<endl;
  for (int i=headBegin;i<=headEnd;i++){
    cout<<i<<": "<<heads[i-headBegin]->getTopCard().getValue()<<" ("<<heads[i-headBegin]->cards.size()<<")"<<endl;
  }
  cout<<endl;
  
}

void Board::addToHead(std::unique_ptr<Card> card, int head){
  heads[head-headBegin]->addCard(move(card));

}

void Board::addHead(std::unique_ptr<Card> card){
 
  
  unique_ptr<Pile> b=make_unique<Pile>(move(card));
  heads.emplace_back(move(b));
  headEnd++;

}

Board::Board(int pcount):playercount{pcount}{}

void Board::play(int mode){
  bool cont=true;
  while (cont){
    for (int h=headBegin;h<=headEnd;h++){
     
      if ((players[turn].getDiscardCount())+(players[turn].getDrawCount())==0){
        if (players[turn].getReserveCount()){
          players[turn].reserveToDraw();
          break;
        }
      }
      print();
      unique_ptr<Card> c=move(players[turn].draw());
      

      for (int i=0;i<playercount;i++){
        cout<<"Player "<<i+1<<": "<<players[i].totalCount() ;
        cout<<" ("<<players[i].getDrawCount()<<" draw, "<<players[i].getDiscardCount()<<" discard)";
        if (i==turn){
          cout<<" + 1 in hand, "<<headEnd-h<< " remaining, ";
          if (players[i].getReserveCount()){
            cout<<1;
          }
          else{
            cout<<0;
          }
          cout<<" in reserve";
        }
        cout<<endl;
      }
      cout<<endl;


      bool swaped=false;
      bool immed=false;
      int m=-1;
      while(true){
        if (mode==1){
          changeCard(c);
        }
        cout<<"Player "<<turn+1<<", you are holding a ";
        if (c->suit=='J'){
          cout<<"Joker";
        }
        else{
          cout<<c->getValue();
        }
        cout<<". Your move?"<<endl;
        string input;
        //cin>>input;
        getline(cin, input);
        if (cin.eof()){
          throw 1;
          cont=false;
          break;
        }
        try {
          m= std::stoi( std::string{input});
        }
        catch(std::invalid_argument & e){
            cerr << "Invalid input, please try again." << endl;
            m=-1;
        }

        if (!((m<=0)||(m>0 && m<headBegin) || (m>headEnd))){
            if (c->suit=='J'){
              while(true){
                cout<<"Joker value?"<<endl;
                string val;
                int jv;
                getline(cin, val);
                if (val=="A"){
                  c->value=1;
                  break;
                }
                else if (val=="J"){
                  c->value=11;
                  break;
                }
                else if (val=="Q"){
                  c->value=12;
                  break;
                }
                else if (val=="K"){
                  c->value=13;
                  break;
                }
                else{
                  try {
                    jv= std::stoi( std::string{val});
                  }
                  catch(std::invalid_argument & e){
                    cerr << "Invalid input, please try again." << endl;
                    jv=0;
                  }
                  if ((2<=jv)&& (jv<=10)){
                    c->value=jv;
                    break;
                  }
                  else{
                    cerr << "Invalid input, please try again." << endl;
                  }
                }
              }

            }
            int f=c->playableon(heads[m-headBegin]->getTopCard());
            if (f>0){
              addToHead(move(c), m);

              if (f==2){
                immed=true;
              }
              if (players[turn].checkWin()){
                winDeclare(turn+1);
                cont=false;
                return;
              }
              break;
            }
            else{
              if (m!=headBegin){
                cerr << "Invalid input, please try again." << endl;
                m=-1;
              }
              else{
                for (int h2=headBegin;h2<=headEnd;h2++){
                    if ((c->playableon(heads[h2-headBegin]->getTopCard()))>0){
                      m=-1;
                    }
                }
                if (m>0){
                  players[turn].addToDiscard(move(c));
                  if (players[turn].getReserveCount()){
                    players[turn].reserveToDraw();
                  }
                  int hs=heads[0]->cards.size();
                  for (int hi=0;hi<hs;hi++){
                    players[turn].addToDiscard(move(heads[0]->cards[hi]));
                  }
                  heads.erase(heads.begin());
                  headBegin++;
                  unique_ptr<Card>c1=move(players[turn].draw());
                  if (mode==1){
                    changeCard(c1);
                  }
                  addHead(move(c1));
                  unique_ptr<Card>c2=move(players[turn].draw());
                  if (mode==1){
                    changeCard(c2);
                  }
                  addHead(move(c2));
                  immed=true;
                  if (players[turn].checkWin()){
                    winDeclare(turn+1);
                    cont=false;
                    return;
                    
                  }
                  break;
                }
                else{
                  cerr << "Invalid input, please try again." << endl;
                }
              }
            }
        }
        else if (m==0){
          
          if (swaped==false){
            bool r=players[turn].getReserveCount();
            if ((r==false) && ((headEnd-headBegin+1)<=1)){
              cerr << "Invalid input, please try again." << endl;
            }
            else{
              players[turn].swap(c);
              swaped=true;
              if (!r){
                break;
              }
            }
          }
          else{
              cerr << "Invalid input, please try again." << endl;
          }

          
        }

        
      }
      

      if(immed){
          break;
      }

    }
    if (players[turn].getReserveCount()){
      players[turn].reserveToDraw();
    }
    if  (!cont){
      winDeclare(turn+1);
      return;
    }
    turn++;
    if (turn==playercount){
      turn=0;
    }
    print();
    for (int i=0;i<playercount;i++){
      cout<<"Player "<<i+1<<": "<<players[i].totalCount() ;
      cout<<" ("<<players[i].getDrawCount()<<" draw, "<<players[i].getDiscardCount()<<" discard)";
      cout<<endl;
    }
    cout<<endl;
    cout<<"Player "<<(turn+1)<<", it is your turn"<<endl;
    string t;
    getline(cin, t);
    if (cin.eof()){
      throw 1;
    } 

  }
}

void Board::winDeclare(int p){
  cout<<"Player "<<p<<" wins!"<<endl;
}
