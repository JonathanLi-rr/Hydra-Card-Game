#include "card.h"
#include <string>
using namespace std;
Card::Card(){}
Card::Card(char suit, int value):suit{suit}, value{value}{}

string Card::getValue(){
  string a="";
  if (value==1){
    a=a+"A";
  }
  else if (value==11){
    a=a+"J";
  }
  else if (value==12){
    a=a+"Q";
  }
  else if (value==13){
    a=a+"K";
  }
  else{
    a=a+to_string(value);
  }
  a=a+suit;
  return a;

}

int Card::playableon(Card other){
  if (value<other.value){
    return 1;
  }
  else if (value==other.value){
    return 2;
  }
  else if (other.value==1){
    return 1;
  }
  else{
    return 0;
  }
}

void changeCard(unique_ptr<Card> &c){
  
  bool j=false;
  while (true){
    cout<<"Card Value?"<<endl;
    string val;
    int jv;
    getline(cin, val);
    if (cin.eof()){
      throw 1;
    }
    if (val=="Joker"){
      c->value=2;
      c->suit='J';
      j=true;
      break;
    }
    else if (val=="A"){
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
        
        jv=0;
      }
      if ((2<=jv)&& (jv<=10)){
        c->value=jv;
        break;
      }
      else{
        
      }
    }
  }

  if (!j){
    
    while (true){
      cout<<"Suit?"<<endl;
      string val;
      getline(cin, val);
      if (val=="S"){
        c->suit='S';
        break;
      }
      else if (val=="H"){
        c->suit='H';
        break;
      }
      else if (val=="C"){
        c->suit='C';
        break;
      }
      else if (val=="D"){
        c->suit='D';
        break;
      }

    }
  }
}
