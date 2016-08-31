#include <iostream>
#include <cctype>  // For toupper

using namespace std;

//function prototypes
void downSizePtr(int inputLength, char *inputPtr, char *adjustedInputPtr);
void getVowelCount(char *adjustedInputPtr, int inputLength, char vowels[], int vowelCount[], bool &littleVowelsPresent, bool &bigVowelsPresent);
void sortVowels(int vowelCount[], char vowels[], bool &littleShareCount, bool &bigShareCount);
void showVowels(int vowelCount[], char vowels[], bool littleVowelsPresent, bool bigVowelsPresent, bool littleShareCount, bool bigShareCount);
void goAgain();

const int SIZE = 10000;

int main()
{
	char *inputPtr = nullptr;
	inputPtr = new char[SIZE];  //pointing to dynamic char array
	int inputLength = 0;
	char *adjustedInputPtr = nullptr;
	int i = 0; //counter

	char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
	//holds number of each vowel found (in parallel with vowels[] array)
	//[spot] vowel   
	//[0]a, [1]e, [2]i, [3]o, [4]u, [5]A, [6]E, [7]I, [8]U
	int vowelCount[] = { 0,0,0,0,0,0,0,0,0,0 };

	bool littleVowelsPresent = false;
	bool bigVowelsPresent = false;
	bool littleShareCount = false;
	bool bigShareCount = false;
	system("cls");

	cout << "Enter some stuff and I'll show you the vowels you typed the most." << endl;
	cin.getline(inputPtr, SIZE - 1); //input up to 9,999 chars

	//set length of user input
	for (i = 0; i < SIZE; i++)
	{
		if (inputPtr[i] == '\0') //when i gets to null char, inputLength equal to i val of last printable char
		{
			inputLength = i - 1;
		}
	}

	adjustedInputPtr = new char[inputLength + 1]; //allocate just enough memory to hold user input and '\0'
 
	//move input from 10,000 size memory to memory space just large enough for input
	downSizePtr(inputLength, inputPtr, adjustedInputPtr); 


	delete[] inputPtr; //delete original 10,000 space to free up memory
	inputPtr = nullptr; //null inputPtr

	cout << endl;

	//count vowels in input, update numbers and whether little or big vowels are present
	getVowelCount(adjustedInputPtr, inputLength, vowels, vowelCount, littleVowelsPresent, bigVowelsPresent);

	cout << endl;

	//sort vowels based on highest count 
	sortVowels(vowelCount, vowels, littleShareCount, bigShareCount);

	//show results, highest count upper and lower case vowels
	showVowels(vowelCount, vowels, littleVowelsPresent, bigVowelsPresent, littleShareCount, bigShareCount);

	cout << endl; 

	//Ask user to quit or go again
	goAgain();

	return 0;
}// end main

//Moves actual user input in to memory space just large enough to hold it
void downSizePtr(int inputLength, char *inputPtr, char *adjustedInputPtr)
{
	int i;//counter

	//moving user input to right size array in preparation to delete unused memory space
	for (i = 0; i <= inputLength; i++)
	{
		*(adjustedInputPtr + i) = *(inputPtr + i);
	}

	*(adjustedInputPtr + i) = '\0'; //append null char

}//end downSizeInput

//Searches user input for vowels
//add count for each vowel
//toggles display if vowels are or are not found
void getVowelCount(char *adjustedInputPtr, int inputLength, char vowels[], int vowelCount[], bool &littleVowelsPresent, bool &bigVowelsPresent)
{
	int i; //counter for outer loop

	cout << "The vowels you entered are: ";
	//iterate across user input
	for (i = 0; i <= inputLength; i++)
	{
		//iterate across vowelCount and vowels array
		for (int x = 0; x < 10; x++)
		{
			//if current input char is same as a vowel,
			//vowel count for found vowel, 1+
			if (adjustedInputPtr[i] == vowels[x])
			{
				vowelCount[x] = vowelCount[x] + 1;
				cout << adjustedInputPtr[i] << " ";//displays the vowels in user input

				//True if little vowels in 0-4, or big vowels in 5 - 9 are found
				if (x <= 4)
				{
					littleVowelsPresent = true;
				}
				if (x >= 5)
				{
					bigVowelsPresent = true;
				}
			}
		}
	}
} //end get vowels

//Puts little vowel with highest count in spot 4 of vowels array for display
//Puts big vowel with highest count in spot 9 of vowels array for display
//If 2 vowels have equally highest count, toggle bool
void sortVowels(int vowelCount[], char vowels[], bool &littleShareCount, bool &bigShareCount)
{
	int start;
	int end;
	int i;//counter for outer loop

	//outer loop
	//first time i loops through 0-4 little vowels
	//second time i loops throgh 5-9 big vowels
	for (i = 0; i < 2; i++)
	{
		if (i == 0)//first time i, sort 0-4
		{
			start = 0;
			end = 4;
		}

		if (i == 1)//second time i, sort 5-9
		{
			start = 5;
			end = 9;
		}
		for (start; start < end; start++)
		{
			//if vowel has more count than next in array
			//swap positions
			if (vowelCount[start] > vowelCount[start + 1])
			{
				int tempInt;
				char tempChar;

				tempInt = vowelCount[start + 1];
				tempChar = vowels[start + 1];

				vowelCount[start + 1] = vowelCount[start];
				vowels[start + 1] = vowels[start];

				vowelCount[start] = tempInt;
				vowels[start] = tempChar;
			}

			//test if 2 or more vowels share the same number of repitition/highest count
			if (vowelCount[start + 1] == vowelCount[start] || vowelCount[start+1] == vowelCount[start - 1] || vowelCount[start+1] == vowelCount[start - 2] || vowelCount[start+1] == vowelCount[start - 3])
			{
				//will only switch to true when considering the litte and big vowel with highest count
				if (start == 3) 
				{
					littleShareCount = true;
				}
				if (start == 8)
				{
					bigShareCount = true;
				}
			}
		}
	}
} // end sort vowels

//Displays upper and lower case vowels with highest count each
//Or, displays that no vowels (upper or lower) are present
void showVowels(int vowelCount[], char vowels[], bool littleVowelsPresent, bool bigVowelsPresent, bool littleShareCount, bool bigShareCount)
{
	//if no vowels are entered
	if (!littleVowelsPresent && !bigVowelsPresent)
	{
		cout << "Actually, you didn't enter any upper or lower case vowels to display.\n";
	}
	else
	{
		//if there is only one lower case vowel with highest count, display
		if (littleVowelsPresent && !littleShareCount)
		{
			cout << "The little vowel that is repeated most is \"" << vowels[4] << "\" with a count of " << vowelCount[4] << "." << endl;
		}
		else //no lower case vowels present or 2 vowels with equal highest count
		{
			cout << "There are no lower case vowels most repeated to display.\n";
		}
		
		//if there is only one upper case vowel with highest count, display
		if (bigVowelsPresent && !bigShareCount)
		{
			cout << "The big vowel that is repeated most is \"" << vowels[9] << "\" with a count of " << vowelCount[9] << "." << endl;
		}
		else //no upper case vowels present or 2 vowels with equal highest count
		{
			cout << "There are no upper case vowels most repeated to display.\n";
		}
	}
} //end showVowels

//ask user if they will run program again
//Y to continue, anything else will quit 
void goAgain()
{
	char go;

	cout << "Would you like to go again? Y/y to continue\n"
		<< "Anything else to quit" << endl;
	cin >> go;
	cin.ignore();

	if (toupper(go) == 'Y')
	{
		main();
	}
	else
	{
		exit(0);
	}
}
