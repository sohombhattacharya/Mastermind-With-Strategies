// Sohom Bhattacharya
// Homework 3
// October 11, 2013


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;



int rollDie(int sides)
{
	srand(time(NULL));


	int roll = rand()%sides + 1;
	return roll;
}


int nthDigit(int &combination, int position)
{
	    int testComb = combination;
		int g_thousandsdigit;
		int g_hundredsdigit;
		int g_tensdigit;
		int g_onesdigit;
		int digits = 0;
				int position_value = 0;

		while (testComb != 0)
		{
			testComb /= 10;
			digits++;
		}

		if (position > 0 && digits == 4)
		{
			g_thousandsdigit = combination/1000;
							g_hundredsdigit = (combination - 1000*g_thousandsdigit)/100;
							g_tensdigit = (combination - (1000*g_thousandsdigit + 100*g_hundredsdigit))/10;
							g_onesdigit = combination - 1000*g_thousandsdigit - 100*g_hundredsdigit - 10*g_tensdigit;


		if (position == 3)
		position_value = (combination - 1000*g_thousandsdigit)/100;

		if (position == 2)
		position_value = (combination - (1000*g_thousandsdigit + 100*g_hundredsdigit))/10;


		if (position == 1)
		position_value = combination - 1000*g_thousandsdigit - 100*g_hundredsdigit - 10*g_tensdigit;


		if (position == 4)
		position_value = combination/1000;
		}
		return position_value;

}

void clearnthDigit(int &combination, int position)
{
			nthDigit(combination, position);
			int value; 
			if (position == 1)
				value = nthDigit(combination, position);
			if (position == 2)
				value = nthDigit(combination, position)*(pow(10,1));
			if (position == 3)
				value = nthDigit(combination,position)*(pow(10,2));
			if (position == 4)
				value = nthDigit(combination, position)*(pow(10,3));
			
			combination = combination - value;

			
}

void evaluate (int answer, int guess, int& black, int& white)
{
 black = 0;
 white = 0;
		int counter = 1;
		int counter2 = 1;
		int counter3 = 1;
		while (counter <= 4)
		{
			if (nthDigit(guess,counter) == nthDigit(answer,counter))
			{
				black++;
				clearnthDigit(answer,counter);
			}

			counter++;
		}

		while (counter3 <= 4)
		{ int counter4 = 1;
			while (counter4 <= 4)

			{
				if (nthDigit(guess,counter3) == nthDigit(answer,counter4))
				{
				white++;
				clearnthDigit(guess,counter3);
				}
				counter4++;
			}
			counter3++;
		}

}

int generateAnswer()
{
	int combination;
	int ones = rollDie(8);
	int tens = rollDie(8);
	int hundreds = rollDie(8);
	int thousands = rollDie(8);

	combination = 1000*thousands + 100*hundreds + 10*tens + ones;

	
	return combination;

}

void generateSearchSpace(int guesses[], int length)
{
			

		
	int h = 0; 
	{
	for (int i = 1; i <=8; i++)
	{
	for (int j = 1; j <=8; j++)
	{
	for (int k = 1; k <=8; k++)
	{
	for (int l = 1; l <=8; l++)
	{
	guesses[h] = 1000*i + 100*j + 10*k + l;
	h++;
	}
	}
	}
	}
	}

	
}


void trim(int guesses[], int& length, int guess, int black, int white)
{

	int counter = 0;
	int counter2 = 0; 
	int testBlack, testWhite;
	for (int i = 0; i < length; i++)
	{
		int answer = guesses[i];
		
		evaluate(answer,guess, testBlack, testWhite);

		if (testBlack == black && testWhite == white)
		{
			guesses[counter2] = guesses[i];
			counter2 = counter2 + 1;
		}


	}
			length = counter2;

	
}



int methodicalEliminate(int answer)
{
	int counter = 0;
	int guesses [4906];
	int black = 0;
	int white = 0;
	int new_length = 4096;
	generateSearchSpace(guesses,4906);
	
	while (guesses[0] != answer)
	{
		counter = counter + 1;
		cout << "Guessing at ... " << guesses[0] << '\n';
		
		evaluate(answer, guesses[0], black, white);
		trim(guesses, new_length, guesses[0],black, white);
		

		

	}
	if (guesses[0] == answer)
		{counter = counter + 1;
		cout << "Guessing at ... " << guesses[0] << '\n';
		cout << "Methodical Eliminate took " << counter << " tries" << '\n' << endl;
		}

	return counter;
}

int guessAndEliminate(int answer)
{
int new_counter = 0;
int next_length = 4096;
int new_guesses[4096];
generateSearchSpace(new_guesses,4096);
int black = 0;
int white = 0;
int j = rand()%next_length + 1;  	

while (new_guesses[j] != answer)
	{
		
		new_counter = new_counter + 1;
		cout << "Guessing at ... " << new_guesses[j] << '\n';
		
		evaluate(answer, new_guesses[j], black, white);
		trim(new_guesses, next_length, new_guesses[j],black, white);
		j = rand()%next_length;  	

	}
	if (new_guesses[j] == answer)
		{new_counter = new_counter + 1;
	cout << "Guessing at ... " << new_guesses[j] << '\n';
		cout << "Guess and Eliminate took " << new_counter << " tries" << '\n' << endl;
		}

return new_counter; 

}

int guessThreeandEliminate(int answer)
{
	int third_counter = 0;
	int third_guesses [4096];
	int black = 0;
	int white = 0;
	int length = 4096;
	int third_new_length = 4096;
	generateSearchSpace(third_guesses,4906);
	int first;
	int second;
	int third;
	int i = 1;

	for (int j = 0; j < 3; j++)
	{
		third_counter = third_counter + 1;
		int i = rand()%third_new_length + 1;
		cout << "Guessing at ... " << third_guesses[i] << '\n';
		if (third_guesses[i] == answer)
		{
			third_counter = third_counter + 1;
			cout << "Guessing at ... " << third_guesses[i] << '\n';
		cout << "Guess Three and Eliminate took " << third_counter << " tries" << '\n' << endl;
		
		}
	if (j == 0) 
		first = i;
	if (j == 1)
		second = i;
	if (j == 2)
		third = i;
	}

	evaluate(answer, first, black, white);
	trim(third_guesses, third_new_length, first, black, white);

	evaluate(answer, second, black, white);
	trim(third_guesses, third_new_length, second, black, white);

	evaluate(answer, third, black, white);
	trim(third_guesses, third_new_length, third, black, white);

	i = rand()%third_new_length + 1;  

	while (third_guesses[i] != answer)
	{
		
		third_counter = third_counter + 1;
		cout << "Guessing at ... " << third_guesses[i] << '\n';
		
		evaluate(answer, third_guesses[i], black, white);
		trim(third_guesses, third_new_length, third_guesses[i],black, white);
		
		/*if (third_new_length == 1)
			i = 0;
			*/
		i = rand()%third_new_length;  	

		
	}
	if (third_guesses[i] == answer)
		{third_counter = third_counter + 1;
		cout << "Guessing at ... " << third_guesses[i] << '\n';
		cout << "Guess Three and Eliminate took " << third_counter << " tries" << '\n' << endl;
		}



	return third_counter; 


}


void playMastermind()
{

	string play_again = "yes";
	
	while (play_again == "yes")
	{
		int answer; 
		cout << "Please enter a combination to try for or enter 0 for a random number" << endl;
		cin >> answer;
		
		if (answer == 0)
		{
		answer = generateAnswer();
		}

		cout << "Guessing at ...." << answer << '\n';
		cout << " " << endl;

		methodicalEliminate(answer);
		guessAndEliminate(answer);
		guessThreeandEliminate(answer);

		cout << "Play again? Enter yes or no" << endl;
		cin >> play_again;

	}

}



int main() {

	srand(time(NULL));

	playMastermind();
	


	



	return 0;
}




