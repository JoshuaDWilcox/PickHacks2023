






#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

//Game struct
struct Game{
  double pollution = 50; 
  int money = 10;
  int inventory[4]={};
  double inventoryUpgrades[4]={1,1,1,1};
  int pollutionFactors = 1;
  int ending = 0;

  string facts[10]={};
};

struct Event{
  string eventPrompt;
  string* options;
  int numOptions;
  Event()
  {
    eventPrompt="";
    numOptions=0;
    options=new string[0];
  }
  void setNumOptions(int x)
  {
    if(options!=NULL) delete[] options;
    options = new string[x];
    numOptions=x;
  }
  ~Event()
  {
    delete[] options;
  }
};

// desc: prints logo
// pre: none
// post: console print, prompt user for game start
void titleScreen(Game& game);

// desc: couts pollution meter and current money
// pre: none
// post: console print,clears console
void displayNums(Game& game);

// desc: opens main menu
// pre: none
// post: console print, prompts for player choice
void mainMenu(Game& game);

//returns the option they chose
int runEvent(Event& event);

// desc: allows user to purchase an item from the shop, costs are exponential depending on how many of the item they have.
// pre: none
// post: money decreased if item bought, item values incrased accordingly
void buyItem(Game& game);

// desc: open shop menu
// pre: accessed through main menu
// post: console print, prompts for player choice
void shop(Game& game);
  
void event(Game& game);

void updateStats(Game& game);

void itemDescription(Game& game);

void gameOver(Game& game);

#endif //ends FUNCTIONS_H