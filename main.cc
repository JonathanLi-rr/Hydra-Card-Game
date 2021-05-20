#include <iostream>
#include <string>
#include "card.h"
#include "pile.h"
#include  "player.h"
#include "board.h"
using namespace std;

int main(int argc, char *argv[]){
  
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  int mode=0;
 
  
  if  (argc>1){
    for (int i=1;i<argc;i++){
      string testa=argv[i];
      if(testa=="-testing"){
        mode=1;
      }
      if(testa=="-seed"){
        if (i<argc-1){
          try {
              seed = std::stoi( std::string{ argv[i+1] } );
            } 
          catch( std::invalid_argument & e ) {
              std::cerr << e.what() << std::endl;
              return 1;
          } catch( std::out_of_range & e ) {
              std::cerr << e.what() << std::endl;
              return -1;
            }
        }
      }

    }
  }
  std::default_random_engine rng{seed};
  
  int pp=0;
  int val=0;
  while (pp<2){
    cout<<"How many players?"<<endl;
    string input;
    getline(cin, input);
    if (cin.eof()){
      return 0;
    }
    try {
        pp= std::stoi( std::string{input});
        }
    catch(std::invalid_argument & e){
      cerr << "Invalid input, please try again." << endl;
      pp=0;
      

    }
  }
  

  Board b{pp};
  for (int i=0;i<pp;i++){
    b.players.emplace_back(rng);
  }

  
try{
  b.initialize(rng,mode);
  
  b.play(mode);
}
catch(int e){

}

}
