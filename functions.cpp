#include "functions.h"


void titleScreen(Game& game){
  cout<<"    ____        ____      __  _                ____                  __                           _               "<<endl;
  cout<<"   / __ \\____  / / /_  __/ /_(_)___  ____     / __ \\____ _____  ____/ /__  ____ ___  ____  ____  (_)_  ______ ___ "<<endl;
  cout<<"  / /_/ / __ \\/ / / / / / __/ / __ \\/ __ \\   / /_/ / __ `/ __ \\/ __  / _ \\/ __ `__ \\/ __ \\/ __ \\/ / / / / __ `__ \\"<<endl;
  cout<<" / ____/ /_/ / / / /_/ / /_/ / /_/ / / / /  / ____/ /_/ / / / / /_/ /  __/ / / / / / /_/ / / / / / /_/ / / / / / /"<<endl;
  cout<<"/_/    \\____/_/_/\\__,_/\\__/_/\\____/_/ /_/  /_/    \\__,_/_/ /_/\\__,_/\\___/_/ /_/ /_/\\____/_/ /_/_/\\__,_/_/ /_/ /_/ \n"<<endl;
  cout<<"                                                Press Enter to Start"<<endl;
  game.facts[0]="Solar power and nuclear power plants do not contribute towards air pollution or create greenhouse gases!";
  game.facts[1]="Solar power is a form of renewable energy, which means it will never run out until the sun gobbles up the solar system!";
  game.facts[2]="Nuclear power was the source of over half America's green energy as of 2021!";
  game.facts[3]="Norway and Iceland run almost completely on green energy!";
  game.facts[4]="Nuclear energy is slowly becoming less expensive as time progresses!";
  game.facts[5]="If you have solar panels at home, you can bypass paying for electricity, and in cases even sell energy back for money!";
  game.facts[6]="Recycling prevents waste, and lessens greenhouse gas emissions that come from the production of waste products!";
  game.facts[7]="Over half of Iowa's energy is from wind power!";
  game.facts[8]="Non-renewable energy (oil, coal, etc) comes from things that are finite, or that will not be renewed within many lifetimes. Renewable energy is from sources that are infinite!";
  game.facts[9]="Litter can cause massive bacteria buildups, and get people sick! Don't litter!";
  cin.ignore(100,'\n');
}


void displayNums(Game& game){
  system("clear");
  if(game.money<0) game.money=0;
  int whichFact = rand()%10;
  cout<<"Fun Fact: "<<game.facts[whichFact];
  cout << endl<<endl<<"Current pollution levels:    ";
  cout<<"<";
  for(int i=0;i<20;i++)
    cout<<(game.pollution/5>=i?"█":"-");
  cout<<">";
  int pollutionAsInt = game.pollution;
  cout<<"  ("<<pollutionAsInt<<"%)";
  cout<<endl<<"Money: $"<<game.money<<endl;
}


void mainMenu(Game& game){
  int choice;
  displayNums(game);
  cout<<endl<<"----------MENU----------"<<endl;
  cout<<"1. Progress Time"<<endl; //trigger an event
  cout<<"2. Manage Property"<<endl; 
  cout<<"3. Help"<<endl;
  cout<<"4. Give up"<<endl;
}


void shop(Game& game){
  int choice=0;
  while(choice!=3){
    displayNums(game);
    cout<<endl<<"----------ITEM MANAGEMENT----------"<<endl;
    cout<<"You have "<<game.inventory[0]<<" solar panels."<<endl;
    cout<<"You have "<<game.inventory[1]<<" nuclear reactors."<<endl;
    cout<<"You have "<<game.inventory[2]<<" fundraising programs."<<endl;
    cout<<"You have "<<game.inventory[3]<<" banks."<<endl<<endl;
    cout<<"1. Buy item"<<endl;
    cout<<"2. Item description" <<endl;
    cout<<"3. Back to menu"<<endl;
    cin>>choice;
    switch(choice){
      case 1:{
        buyItem(game);
        break;
      }
      case 2: {
        itemDescription(game);
        break;
      }
      default:{
        return;
        break;
      }
    }
  }
}


void buyItem(Game& game){ //Working
  int costs[]={10,100,10,100};
  costs[0]=costs[0]*pow(1.25,game.inventory[0]);
  costs[2]=costs[2]*pow(1.25,game.inventory[2]);
  costs[1]=costs[1]*pow(1.4,game.inventory[1]);
  costs[3]=costs[3]*pow(1.4,game.inventory[3]);
  int input=1;
  string items[]={"Solar panels", "Nuclear reactors", "Fundraising programs", "Banks"};
  while(input!=5){
    displayNums(game);
    cout<<endl<<"----------BUY----------"<<endl;
    for(int i=0;i<4;i++){
      cout<<"$"<<costs[i]<<" - "<<items[i]<<" - Count: "<<game.inventory[i]<<" - Upgrade Factor: "<<game.inventoryUpgrades[i]<<endl;   //$10 - Solar panels - Count: 0
    }
    cout<<endl<<"Enter input (1-4) to purchase an item. Enter 5 to back out."<<endl;
    cin>>input;
    if(input!=5){
      input--; //Easier for coding
    
      if(game.money>=costs[input]) //if they have enough money, 
      {
        game.money-=costs[input]; //take the cost away from their money
        game.inventory[input]++;  //give them their item
        costs[input]=costs[input]*(input%2==1?1.4:1.25);
      }else
      {
        cout<<endl<<"You can't afford that!"<<endl;
      }
    }
  }
}


void event(Game& game){
  displayNums(game);
  cout<<endl<<"----------EVENT----------"<<endl;
  Event e;
  int event=rand()%20+1; // 1-10
  if(  event==1  ||  ( game.pollution < 25  ||  game.pollution > 75 ? event==2 : false )  ){  //RARE EVENTS
    cout<<"\n!!! RARE EVENT !!!\n";
    event = rand()%5+1; //1-5
    switch(event){
      case 1:{
        e.eventPrompt="A strange old bearded man approaches you offering to make your solar panels more efficient... what do you do?";
        e.setNumOptions(3);
        e.options[0]="Accept his help."; //grows sun, solar panel buff
        e.options[1]="Kindly decline his offer."; //he ascends into the clouds and is never seen again
        e.options[2]="Call the police."; //god pollutes
        switch(runEvent(e))
        {
          case 1:{
            cout<<"He raises his hands and the sun appears to grow ever so slightly. (Solar panel buff)"<<endl;
            game.inventoryUpgrades[0]+=0.2;
            
            break;
          }
          case 2:{
            cout<<"He nods, and starts floating upwards! Once he passes the clouds, the sky clears and he is nowhere to be seen. Who was that?"<<endl;
            
            break;
          }
          case 3:{
            cout<<"His face darkens with anger, and the clouds seem to thicken above your solar panels. Then the man suddenly shoots into the sky never to be seen again. (Solar panel nerf)"<<endl;
            game.inventoryUpgrades[0]-=0.1;
            break;
          }
        }
        
        break;
      }
      case 2:{
        e.eventPrompt="Godzilla has surfaced and is heading towards your HeadQuarters.";
        e.setNumOptions(2);
        e.options[0]="Attack him.";
        e.options[1]="Wait.";
        switch(runEvent(e))
        {
          case 1:{
            cout<<"Godzilla releases a wave of toxic radiation, increasing the rate of pollution increase, alongside breaking your nuclear reactors."<<endl;
            game.pollutionFactors+=0.5;
            
            break;
          }
          case 2:{
            cout<<"Godzilla wanted to help you :) he loves environmentally friendly people. He has used his excess radiation to increase the efficiency of your power plants!"<<endl;
            game.inventoryUpgrades[1] += 0.25;
            
            break;
          }
        }
        break;
      }
      case 3:{
        e.eventPrompt="A person has approached you claiming he is from the future. He says that one of your banks will cause a recession by printing too much excess paper.";
        e.setNumOptions(3);
        e.options[0]="Believe him and shut down the bank.";
        e.options[1]="Ignore him.";
        e.options[2]="Ask him how you die.";
        switch(runEvent(e))
        {
          case 1:{
            cout<<"You shut down the bank. The time traveler laughed that you fell for his joke."<<endl;
            game.inventory[3]--;
            if(game.inventory[3] < 0){
              game.inventory[3] = 0;
            }
            break;
          }
          case 2:{
            cout<<"The time traveler gets angry at you. In his anger, he reveals he has been lying and was just trying to trick you. Nothing happens."<<endl;
            break;
          }
          case 3:{
            cout<<"He tells you an elaborate story about you dying from an absurd amount of paper cuts before forgetting what he was doing and leaving."<<endl;
            break;
          }
        }
        break;
      }
      case 4:{
        e.eventPrompt="A yellow-haired man approaches you and offers you a very rusty arrow, then he tells you to stab yourself with it for immense power.";
        e.setNumOptions(2);
        e.options[0]="Accept his generous offer!";
        e.options[1]="Reject his offer...";
        switch(runEvent(e))
        {
          case 1:{
            cout<<"You stab yourself and everything does dark...\n"<<endl;
            game.ending = 3;
            gameOver(game);
            return;
            break;
          }
          case 2:{
            cout<<"He shrugs and you blink and he is gone, but he drops golden knife. It seems valuable."<<endl;
            game.money += 10;
            break;
          }
        }
        break;
      }
      case 5:{
        e.eventPrompt="A large meteor is heading towards earth. Scientists say there are 24 hours left before it annihilates earth. You have one opportunity to stop it. What do you do?";
        e.setNumOptions(5);
        e.options[0]="Fire a nuclear missile at the meteor.";
        e.options[1]="Cry.";
        e.options[2]="Ignore it. Who cares?";
        e.options[3]="Cry.";
        e.options[4]="Ask the scientists to check their calculations.";
        switch(runEvent(e)){
          case 1:{
            cout << "You remember that you do not own nuclear missiles. As if god himself wished to spite you, the meteor somehow causes no damage to any part of the world except to a single one of your solar panels."<<endl;
            game.inventory[0]-=1;
            if (game.inventory[0]<0){
              game.inventory[0]=0;
            }
            break;
          }
          case 2:{
            cout << "You start crying at your imminent doom. After approaching the surface of the planet, the meteor made a deposit at a bank you own, and then left. This... increases bank efficiency?"<<endl;
            game.inventoryUpgrades[3]+=.15;
            break;
          }
          case 3:{
            cout << "You ignore the meteor. Something might've happened, but you have no idea what because you were ignoring the meteor. Maybe you should pay attention next time, genius."<<endl;
          }
          case 4:{
            cout<<"You stub your toe and start crying. This is objectively the worst day of your life. This is rock bottom. This is hell. FLAT OUT HELL. Your toe really hurts. Oh yeah, the meteor missed or something."<<endl;
            break;
          }
          case 5:{
            cout<<"You ask the scientists to double check their calculations. \"Oh, our bad,\" they say. Apparently the intern missed a decimal place. People are extremely thankful to you, and your fundraiser efficiency increases as a result."<<endl;
            game.inventoryUpgrades[2] += .15;
            break;
          }
        }
        break;
      }
    }
  }
  else //COMMON EVENTS
  {
    event = rand()%15+1; //1-16
    switch(event){
      case 1:{
        e.eventPrompt="There has been an oil spill in the Gulf of Mexico! You have recieved multiple requests to send aid for removing the oil. This could cost a bit. What do you do?";
        e.setNumOptions(2);
        e.options[0]="Send aid.";
        e.options[1]="Ignore.";
        switch(runEvent(e))
        {
          case 1:{
            //print what that option means
            cout << "You sent aid to the gulf, costing you some of your money. However, your aid paid off, and you combatted the pollution!"<<endl;
            game.money-=10;
            if (game.money<0){
              game.money=0;
            }
            //change values
            
            break;
          }
          case 2:{
            //print what that option means
            cout << "You didn't send aid to the gulf. It seems the rate of pollution will increase..."<<endl;
            //change values
            game.pollutionFactors+=.1;
            break;
          }
        }
        break;
      }
      case 2:{
        e.eventPrompt="A campaign protesting your company has recently taken the internet by storm. Your PR team is in shambles, so you have to respond yourself. How do you respond?";
        e.setNumOptions(3);
        e.options[0]="Respond aggressively!";
        e.options[1]="Respond politely.";
        e.options[2]="Respond apologetically.";
        switch(runEvent(e))
        {
          case 1:{
            //print what that option means
            cout << "You hold a press meeting where you ranted about the opposition, filled to the brim with ad hominem attacks. You now have to fight a slander lawsuit, costing you some money."<<endl;
            game.money-=5;
            if (game.money<0){
              game.money=0;
            }
            //change values
            break;
          }
          case 2:{
            //print what that option means
            cout << "You politely explain your viewpoints to the opposition, methodically breaking down their points. Public sentiment about you increased, causing your fundraisers to become more effective!"<<endl;
            //change values
            game.inventoryUpgrades[2]+=.2;
            break;
          }
          case 3:{
            cout<<"You apologize profusely, lessening the backlash. After a little while, everything returns to normal."<<endl;
            break;
          }
        }
        break;
      }
      case 3:{
        e.eventPrompt="A tornado rips through your solar panels!";
        e.setNumOptions(1);
        e.options[0]="Damn...";
        switch(runEvent(e))
        {
          case 1:{
            //print what that option means
            cout << "If you had any solar panels, you certainly have less now."<<endl;
            game.inventory[0]-=1;
            if (game.inventory[0]<0){
              game.inventory[0]=0;
            }
            //change values
            break;
          }
        }
        break;
      }
      case 4:{
        e.eventPrompt="A local hackathon is running an environmentally themed competition. Do you want to sponsor the event?";
        e.setNumOptions(2);
        e.options[0]="Sponsor!";
        e.options[1]="Don't sponsor.";
        switch(runEvent(e))
        {
          case 1:{
            //print what that option means
            cout << "You sponsor the hackathon, which shall remain unnamed. This cost a little bit of money, but one of the students somehow made a solar panel and gave it to you."<<endl;
            game.money-=5;
            if (game.money<0){
              game.money=0;
            }
            game.inventory[0]+=1;
            //change values
            break;
          }
          case 2:{
            //print what that option means
            cout << "You decide not to sponsor the hackathon."<<endl;
            //change values
            break;
          }
        }
        break;
      }
      case 5:{
        e.eventPrompt="You receive a suspicious email claiming that your Environmental Science degree has been audited and is invalid. They are asking for money to keep quiet about it";
        e.setNumOptions(2);
        e.options[0]="Send them the money.";
        e.options[1]="Ignore it.";
        switch(runEvent(e))
        {
          case 1:{
            //print what that option means
            cout << "You send the money, and hear nothing back."<<endl;
            game.money-=5;
            if(game.money<0) game.money=0;
            
            //change values
            break;
          }
          case 2:{
            //print what that option means
            cout << "Nothing happens."<<endl;
            //change values
            break;
          }
        }
        break;
      }
      case 6:{
        e.eventPrompt="The government has noticed that you are doing good work for the environment, and you receive a grant.";
        e.setNumOptions(0);
        runEvent(e);
        game.money+=10;
        break;
      }
      case 7:{
        e.eventPrompt = "A wave of new enviromentally friendly people have joined your cause!";
        e.setNumOptions(0);
        runEvent(e);
        game.pollution -= 2;
        break;
      }
      case 8:{
        e.eventPrompt = "You find some litter on the ground while on your daily walk in the woods.";
        e.setNumOptions(2);
        e.options[0]="Pick it up";
        e.options[1]="Leave it";
        switch(runEvent(e)){
          case 1:{
            cout<<"The forest feels a tiny bit cleaner...";
            game.pollution-=0.5;
            break;
          }
          case 2:{
            cout<<"You feel dirty as you walk away, leaving the forest unclean.";
            game.pollution+=0.5;
            break;
          }
        }
        break;
      }
      case 9:{
        e.eventPrompt = "You find an abandoned briefcase on a bench in the forest.";
        e.setNumOptions(2);
        e.options[0]="Take it!";
        e.options[1]="Leave it!";
        switch(runEvent(e)){
          case 1:{
            cout<<"You found $5 in it!";
            game.money+=5;
            break;
          }
          case 2:{
            cout<<"You wonder what could've been inside...";
            break;
          }
        }
        break;
      }
      case 10:{
        e.eventPrompt = "You find an abandoned briefcase on a bench in the forest.";
        e.setNumOptions(2);
        e.options[0]="Take it!";
        e.options[1]="Leave it!";
        switch(runEvent(e)){
          case 1:{
            cout<<"Mr. ##### jumps out of the bushes with a camera pointed at you. He confronts you on why you took the briefcase. A fundraising campaign may be ruined by public backlash...";
            game.inventory[2]--;
            if(game.inventory[2]<0) game.inventory[2]=0;
            break;
          }
          case 2:{
            cout<<"Mr. ##### jumps out of the bushes with a camera pointed at you. He offers you $10 for being a good person and not stealing the briefcase.";
            game.money+=10;
            break;
          }
        }
        break;
      }
      case 11:{
        e.eventPrompt = "Walking through the grocery store, you catch a glimpse of some tree seeds that would grow well in your area.";
        e.setNumOptions(2);
        e.options[0]="Buy and plant them.";
        e.options[1]="Ignore it.";
        switch(runEvent(e)){
          case 1:{
            if(game.money>=2){
              cout<<"The trees will eventually blossom into natural CO2 to O2 converters! The air feels fresher.";
              game.money-=2;
              game.pollution-=1;
            }
            
            break;
          }
          case 2:{
            cout<<"You return home feeling upset that you didn't grow a tree.";
            break;
          }
        }
        break;
      }
      case 12:{
        e.eventPrompt = "Someone has stolen all the money from one of your banks...";
        e.setNumOptions(2);
        e.options[0]="Lose the bank.";
        e.options[1]="Pay to catch the robber.";
        switch(runEvent(e)){
          case 1: {
            cout<<"One of your banks went bankrupt..."<<endl;
            game.inventory[3]--;
            if(game.inventory[3] < 0){
              game.inventory[3] = 0;
            }
            break;
          }
          case 2:{
            cout<<"You catch the criminal and your bank doesn't go bankrupt. But it costs some money..."<<endl;
            game.money -= 10;
          }
        }
        break;
      }
      case 13:{
        
        e.eventPrompt = "The government is trying to pass a law to restrict fundraising!";
        e.setNumOptions(3);
        e.options[0]="Let it pass.";
        e.options[1]="Lobby against it.";
        e.options[2]="Challenge the president to a match of chess!"; 
        switch(runEvent(e)){
          case 1: {
            cout<<"The law is passed and your fundraising is restricted..."<<endl;
            game.inventory[2]--;
             if(game.inventory[2] < 0){
              game.inventory[2] = 0;
            }
            break;
          }
          case 2:{
            cout<<"You lobby against the bill and get it to not pass the house. It costs you some money to pay the lobbyists, though."<<endl;
            game.money -= 5;
            break;
          }
          case 3:{
            int chance = rand()%2+1;
            if (chance == 1){
              cout<<"The president en passented for checkmate, and the bill is passed with even more force..."<<endl;
              game.inventoryUpgrades[2] -= 0.15;
            }
            if (chance == 2){
              cout<<"You use the secret technique en passant to checkmate the President of the United States, *REDACTED*, and *REDACTED* agreed to veto the bill!"<<endl;
            }
            break;
          }
        }
        break;
      }
      case 14:{
        e.eventPrompt = "You are having a business meeting with some associates next to a river. Suddenly, a man falls into the river next to you!";
        e.setNumOptions(3);
        e.options[0]="Start the rescue helicopter!"; 
        e.options[1]="Jump into the river and save the man.";
        e.options[2]="ignore.";
        switch(runEvent(e)){
          case 1: {
            cout << "HEY! The man is successfully retrieved from the water, and is very thankful for the help. It turns out he was an executive in an independent nuclear research lab and offers to help upgrade some parts for your nuclear reactors, improving their efficiency.";
            game.inventoryUpgrades[1]+=.15;
            break;
          }
          case 2: {
            //code
            cout << "You jump into the river and eventually manage to save the man. He was very thankful for your assistance and handed you some money before being rushed to the hospital for hypothermia."<<endl;
            game.money+=5;
            break;
          }
          case 3: {
            //code
            cout << "You ignore the man. Later you find, much to your dismay, that the man is actually a higher up at a nuclear research lab. He noticed that you purposefully ignored him, and cut off the lab's connections with you, weakening your nuclear plant efficiency."<<endl;
            game.inventoryUpgrades[2]-=.15;
            break;
          }
        }
        break;
      }
      case 15:{
        e.eventPrompt = "A very angry customer came into your office. One of your employees apologetically tells you that she was demanding to speak to a manager.";
        e.setNumOptions(1);
        e.options[0]="...Okay?"; 
        switch(runEvent(e)){
          case 1: {
            cout << "You press the comically large red button on your table, opening a trapdoor in the floor of your office. The customer is dropped into a very bio-diverse, and large and a lake, shark tank (the sharks are happy, don't worry). You laugh maniacally."<<endl;
            break;
          }
        }
        break;
      }
    }
  }
  cout<<endl<<"Push enter to continue.";
  string empty;
  getline(cin,empty);
  cin.ignore(100,'\n');
  updateStats(game);
}


int runEvent(Event& event){
  int input;
  cout<<event.eventPrompt<<endl;
  for(int i=0;i<event.numOptions;i++)
  {
    cout<<i+1<<". "<<event.options[i]<<endl;
  }
  if(event.options->length()!=0&&event.options->length()!=1){
    cout<<"Choose an option from above (1-"<<event.numOptions<<"): ";
    cin>>input;
  }
  else{
    input = 0;
  }
    
  return input; 
}


void updateStats(Game& game){
  game.pollution = game.pollution + game.pollutionFactors-(game.inventory[0]*.01*game.inventoryUpgrades[0])*game.inventory[1]*game.inventoryUpgrades[1];
  game.money = game.money + game.inventory[2]*(game.inventory[3]+1)*3*game.inventoryUpgrades[2]*game.inventoryUpgrades[3];
  if(game.pollution<=0){
    game.pollution=0;
    game.ending=1;
    gameOver(game);
  }
  else if(game.pollution>=100)
  {
    game.pollution=100;
    game.ending=2;
    gameOver(game);
  }
} 


void itemDescription(Game& game){
  int choice=0;
  while(choice!=5)
  {
    displayNums(game);
    cout<<endl<<"----------DESC----------"<<endl;
    string items[]={"Solar panels", "Nuclear reactors", "Fundraising programs", "Banks"};
    cout << "1. "<<items[0]<<endl<<"2. "<<items[1]<<endl<<"3. "<<items[2]<<endl<<"4. "<<items[3]<<endl;
    cout<<endl<<"Enter input (1-4) to see an item's description. Enter 5 to back out."<<endl;
    cin >> choice;
    displayNums(game);
    cout<<endl<<"----------DESC----------"<<endl;
    switch (choice){
      case 1:
        cout<<"Solar panels are a staple form of green energy, allowing you to get energy from the sun! This will work to reduce your pollution by .01% per event."<<endl<<endl;
        break;
      case 2:
        cout<<"Nuclear reactors are a form of green energy, allowing you to harness the power of nuclear fission to generate electricity. This will increase the effectiveness of your solar panels by 100% per reactor."<<endl<<endl;
        break;
      case 3:
        cout<<"Fundraising campaigns allow you to both educate the public about important problems in our society, and gather funds to combat those problems. This will increase your money by $5 per event."<<endl<<endl;
        break;
      case 4:
        cout<<"While fundraising campaigns allow you to gather interest, banks allow you to gather interest. For every bank, the effectiveness of your fundraising campaigns will increase by 100%."<<endl<<endl;
        break;
    }
    if(choice==5)
      return;
    cout << "Press enter to return to options.";
    string empty;
    getline(cin,empty);
    cin.ignore(100,'\n');
  }

}


void gameOver(Game& game){
  if (game.ending == 1){
    cout<<"!!! CONGRATULATIONS !!!"<<endl;
    cout<<"__  ______  __  __   _       _______   __   ______"<<endl;
    cout<<"\\ \\/ / __ \\/ / / /  | |     / /  _/ | / /  / / / /"<<endl;
    cout<<" \\  / / / / / / /   | | /| / // //  |/ /  / / / /"<<endl;
    cout<<" / / /_/ / /_/ /    | |/ |/ // // /|  /  /_/_/_/  "<<endl;
    cout<<"/_/\\____/\\____/     |__/|__/___/_/ |_/  (_|_|_)  "<<endl;
  }
  if (game.ending == 2){
    cout<<"   _________    __  _________   ____ _    ____________ "<<endl;
    cout<<"  / ____/   |  /  |/  / ____/  / __ \\ |  / / ____/ __ \\"<<endl;
    cout<<" / / __/ /| | / /|_/ / __/    / / / / | / / __/ / /_/ /"<<endl;
    cout<<"/ /_/ / ___ |/ /  / / /___   / /_/ /| |/ / /___/ _, _/ "<<endl;
    cout<<"\\____/_/  |_/_/  /_/_____/   \\____/ |___/_____/_/ |_|  "<<endl;
  }
  if(game.ending == 3){
    cout<<"   _________    __  _________   ____ _    ____________   ___ "<<endl;
    cout<<"  / ____/   |  /  |/  / ____/  / __ \\ |  / / ____/ __ \\ /__ \\"<<endl;
    cout<<" / / __/ /| | / /|_/ / __/    / / / / | / / __/ / /_/ /  / _/"<<endl;
    cout<<"/ /_/ / ___ |/ /  / / /___   / /_/ /| |/ / /___/ _, _/  /_/  "<<endl;
    cout<<"\\____/_/  |_/_/  /_/_____/   \\____/ |___/_____/_/ |_|  (_) \n"<<endl;
    cout<<"The arrow gave you tetanus and you died instantly somehow"<<endl;
  }
}