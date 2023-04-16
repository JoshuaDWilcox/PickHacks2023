//keep yourself safe

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <iomanip>
#include "functions.h"
using namespace std;
int main() {  
  srand(time(NULL));

  cout << setprecision(2);
  int choice;
  bool exit = false;
  Game game;
  titleScreen(game);
  while(exit == false && game.ending == 0){
    mainMenu(game);
    cin>>choice;
    switch (choice){
      case 1:{
        event(game);
        break;
    }
      case 2:{
        shop(game);
        break;
    }
      case 3:{
        system("clear");
        cout<<"----------HELP----------"<<endl;
        cout<<"Tip 1 - Pollution goes up by a base of 1% when you Pass Time."<<endl;
        cout<<"Tip 2 - If you buy solar panels or nuclear power plants, pollution doesn't go up as much, and can even go down! Make sure you don't wait too long before you buy them!"<<endl;
        cout<<"Tip 3 - It is recommended to use your initial money to purchase a fundraiser to start your economy!"<<endl;
        cout<<"Tip 4 - If you don't know what to do, you can always Pass Time."<<endl;
        cout<<"Tip 5 - If pollution is under 25% or above 75%, the chance of a rare event is doubled!"<<endl;
        cout<<"Tip 6 - If pollution reaches 0%, you win! But be careful, if it reaches 100%, you lose."<<endl;
        cout<<"Push Enter to continue.";
        string empty;
        getline(cin,empty);
        cin.ignore(100,'\n');
        break;
    }
      case 4:{
        exit = true;
        cout<<"You monster..."<<endl;
        break;
      }
  }
  }
  return 0;
}