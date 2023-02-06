//Alex Clements
//March 21, 2019
//Purpose: To create a game of blackjack that will be fully functional
//Program: Dev C++ 5.11
//Data Dictionary: wins: The total number of wins the user has. losses: The total number of losses the user has. Draws: The total number of draws the user has. user_total: The total that the user has in their hand during the game.
//dealer_total: The total that the dealer has in their hand during the game. ucard1: The first user card they start with. ucard2: The second user card they start with. dcard1: The first dealer card they start with.
//dcard2: The second dealer they start with. hitcard: The value of the randomly generated card that comes up when someone wants to hit. continueGame: The user-inputted value if they want to continue the game or not
//choice: The user-inputted value if they want to hit or stand. gameStatus: If no one has gotten Blackjack, this is where the result is determined. card: Holds the cards. card_value: Holds the value of those cards. suit: Holds the suits.



//Bringing in libraries
#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
using namespace std;

    
	
//Declaring functions
int card_random();   
int suit_random();  


//Starting program
int main()
{	
	//Declaring variables
	int wins=0,losses=0,draws=0,user_total,dealer_total,ucard1,ucard2,dcard1,dcard2,hitcard;
	char continueGame,choice,gameStatus=true;
	
	//Needed for random
	srand(time(0));

	//Essentially creates the deck as it has the cards, their values and the suits. A random group of these gets called upon when a card is needed. 
	char card[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
	int card_value[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
	char suit[] = { 'D', 'H', 'S', 'C' };

	//Outputs greeting message and asks the user if they want to begin 
	cout <<"Welcome to BlackJack"<<endl;
	cout <<"Dealer must hit on 15 and stand on 16"<<endl;
	cout <<""<<endl;
	cout<<"Would you like to begin? (Y/N) --> ";
	cin>>continueGame;
	
	//Loop to determine how long the game will be running based on user input and # of losses
	while(continueGame=='Y'&&losses<10)
	{
		//Gets a random card value for each starting card
		dcard1 = card_random();
		dcard2 = card_random();
		ucard1 = card_random();
		ucard2 = card_random();

		//If there are two aces, one is 11 and one is 1
		if (dcard1 == 12 && dcard2 == 12)
			dealer_total = 12;
		
		//Calculates the dealer total based on the random card values if the previous condition is not met 
		else
			dealer_total = card_value[dcard1] + card_value[dcard2];

		//If there are two aces, one is 11 and one is 1
		if (ucard1 == 12 && ucard2 == 12)
			user_total = 12;
			
		//Calculates the user total based on the random card values if the previous condition is not met
		else
			user_total = card_value[ucard1] + card_value[ucard2];

		//Outputs what one of the dealer's card is 
		cout <<"One of the dealer's cards is the "<<card[dcard2]<<" of "<< suit[suit_random()] << endl << endl;

		//Outputs what the user's cards are and gets a random suit to go with them
		cout <<"Your cards are:"<<endl<<card[ucard1]<<" of "<<suit[suit_random()]<<endl<<card[ucard2]<<" of "<<suit[suit_random()]<< endl;

		//If the user's total is 21 after just dealing the first two cards
		while (user_total == 21) 
		{
			cout<<"Blackjack!"<<endl;
			wins++;
			cout<<"Dealer's other card was the"<<card[dcard1]<<" of "<<suit[suit_random()]<<". The dealer had "<<dealer_total << endl;

			//If the dealer's total is 21 too, it's a tie
			if (dealer_total == 21) 
			{
				cout << "The game is a tie" << endl;
				draws++;
				gameStatus = false;
				break;
			}

			//If anything other than a tie happens, the game ends because the user won
			else 
			{
				gameStatus = false;
				break;
			}
		} 
		
		//While the user's choice is not to stand, the user's total is less than 21 and the game keeps going
		while (choice != 'S' && user_total < 21 && gameStatus != false) 
		{
			//Outputs the user's total and prompts for whether they want to stand or not
			cout << "You have "<<user_total<<". Type 'H' to hit or 'S' to stand: ";
			cin >> choice;

			//Checks based on user's choice
			switch (choice) 
			{
				//If the user inputs H for a hit			
				case ('H'):
					
				//Gets a random card for when the user wants to hit
				hitcard = card_random();
					
					//If there is an ace and user total is greater than 10, the ace value becomes 1
					if (hitcard == 12 && user_total > 10) 
					{
						user_total += 1;
						cout << "You have been dealt the A of " << suit[suit_random()]<<". You have "<<user_total<<"." << endl;
					}
					
					//If anything else happens, the user gets a card and it outputs those results
					else
					{
						user_total += card_value[hitcard];
						cout << "You have been dealt the " << card[hitcard] << " of " << suit[suit_random()]<<". You have "<<user_total<<"." << endl;
					}
					
					//If the user's total is greater than 21
					if (user_total > 21) 
					{
						//The user busts, it outputs that, adds 1 to the losses and makes the game status false as the game is over
						cout << "You busted." << endl;
						losses++;
						gameStatus = false;
						break;
					}
					
					//If the user's total is 21
					else if(user_total==21)
					{
						//The user gets a blackjack, it outputs that, adds 1 to the wins and makes the game status false as the game is over
						cout<<"Blackjack!"<<endl;
						wins++;
						gameStatus = false;
						break;
					}
	
				//If the user wants to stand then it exits the switch 
				case ('S'):
				break;
	
				//Anything else is invalid and gets out of the switch
				default:
					cout << "Invalid choice." << endl;
					break;
				
			}
		}  

	
		//This determines if the game is over
		while (gameStatus) 
		{
			//Says that the user did stand as well as tell's the user what the dealer's cards and total is 
			cout<<"You have chosen to stand."<<endl<<"The dealer's other card was the "<<card[dcard1]<<" of "<<suit[suit_random()]<<". The dealer has "<<dealer_total<<"."<<endl;

			//If the dealer total is less than 16 then it gets another card to hit with 
			while (dealer_total < 16) 
			{
				hitcard = card_random();
				
				//If an Ace gets generated and the total is greater than 10 then the Ace becomes 1 
				if (hitcard == 12 && dealer_total > 10) 
				{
					dealer_total += 1;
					cout << "The dealer has been dealt the A of " << suit[suit_random()]<<". The dealer has "<<dealer_total<<"." << endl;
				}
				
				//If anything else happens the random card is added to the total and outputs those reesults
				else 
				{
					dealer_total += card_value[hitcard];
					cout << "The dealer has been dealt the " << card[hitcard] << " of " << suit[suit_random()]<<". The dealer has "<<dealer_total<<"." << endl;
				}
			} 

			//If the dealer's total is greater than 21, they bust and the game ends
			if (dealer_total > 21) 
			{
				cout << "The dealer has busted!" << endl;
				wins++;
				gameStatus = false;
			}
			
			//If the dealer's total is 21 and the user's is not, the user loses and the game ends
			else if(dealer_total==21&&dealer_total>user_total)
			{
				cout<<"The dealer got Blackjack! You lose.";
				losses++;
				gameStatus = false;
			}
			
			//If the dealer's total is less than 21 and the user's total is greater than the dealer's total, the user wins and the game ends
			else if (dealer_total <= 21 && user_total > dealer_total) 
			{
				cout << "You have a higher total than the dealer!" << endl;
				wins++;
				gameStatus = false;
			}
			
			//If the dealer's total is less than 21 but still greater than the user's total, the user loses and the game ends
			else if (dealer_total <= 21 && user_total < dealer_total) 
			{
				cout << "The dealer has a higher total than you." << endl;
				losses++;
				gameStatus = false;
			}
			
			//If the user has the same value as the dealer, they tie and the game ends
			else 
			{
				cout << "You have tied the dealer." << endl;
				draws++;
				gameStatus = false;
			}
		} 
			
		
		 
		
		//Outputs the current game results
		cout<<"\nYou've won "<<wins<<", lost "<<losses<<" and had "<<draws<<" draw(s).";
		
		//Asks user if they want to play again and takes in that input 
		cout<<" Are you wanting to play again? (Y/N) --> ";
		cin>>continueGame;
		
		//If the user wants to continue the game, everything gets set back to the default 
		if(continueGame=='Y')
		{
			choice='H';
			gameStatus = true;
			user_total = 0;
			dealer_total = 0;
		}
		
		//If anything else happens it ends (user doesn't want to play)
		else
		{
			return 0;
		}
	}
		
	//Outputs the ending results of the game
	cout<<"Thank you for playing. You finished with "<<wins<<" wins, "<<losses<<" losses and "<<draws<<" draws. ";
	cout<<"\nHave fun not wasting your life continuing with this. ";
}

//Gets random card when this function is called
int card_random() 
{
	return rand() % 12 + 1;
} 

//Gets random suit when this function is called
int suit_random() {
	return rand() % 3 + 1;
}


	






