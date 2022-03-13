#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#define N 1024
#define NUMBER_0 0  
#define NUMBER_9 9
#define LOWERCASE 32
#define CONJUNCTIONS_SIZE 18 
#define SHINGLE_SIZE 3

using namespace std;

bool isSeparator(char);
bool isNumber(char);
char lowerCase(char);
bool isConjuction(char[]);
int editingTextDatabase(string);
int editingUserText(string);
int calculateUniqueness(int, int);
bool isShingleUnique(string[], int);
string editedTextDatabase[N];
string editedUserText[N];
double antiPlagiarism(string text, string fragment);

double antiPlagiarism(string text, string fragment)
{
	string text;
	string fragment;
	int textDatabaseLength = 0;
	int userTextLength = 0;
	double uniqueness = 0.0;
	
	textDatabaseLength = editingTextDatabase(text);
	userTextLength = editingUserText(fragment);
	uniqueness = 100 - calculateUniqueness(textDatabaseLength, userTextLength);
	
	
	cout << "Uniqueness is: " << uniqueness << "%" << endl;
	
	return 0;
}

bool isSeparator(char text)
{
	char separators[] = " !@#$%^&*():;,.[]{}/*-+_=<>`~?\\\'\"";
	
	for (int i = 0; separators[i] != '\0'; i++)
	{
		if (separators[i] == text)
		{
			return true;
		}
	}
	
	return false;
}

bool isNumber(char text)
{
	char number[] = "0123456789";
	
	for (int i = 0; number[i] != '\0'; i++)
	{
		if (number[i] == text)
		{
			return true;
		}
	}
	
	return false;
}

bool isConjuction(char word[])
{
	string conjunctions[CONJUNCTIONS_SIZE] = {"and", "or", "for", "nor", "at", "by", "till", "to", "from", "in", "of", "about", "a", "an", "the", "on", "but", "as"};
	
	for (int i = 0; i < CONJUNCTIONS_SIZE; i++)
	{
		if (word == conjunctions[i])
		{
			return true;
		}
	}
	
	return false;
}

char lowerCase(char text)
{
	if (text >= 'A' and text <= 'Z')
	{
		text += LOWERCASE;
	}
	
	return text;
}

int editingTextDatabase(string text)
{
	char word[N];
	int iw = 0;//indexWord
	int counter = 0;
	
	for(int i = 0; text[i] != '\0'; i++)
	{
		if (!isSeparator(text[i]) and  !isNumber(text[i]))
		{
			word[iw++] = text[i];
			if (isSeparator(text[i + 1]) or text[i + 1] == '\0' or isNumber(text[i + 1])) 
			{
				word[iw] = '\0';
				iw = 0;
				for(int k = 0; word[k] != '\0'; k++){
					word[k] = lowerCase(word[k]);
				}	
				if(!isConjuction(word) and (counter == 0 or word != editedTextDatabase[counter - 1]))
				{
					editedTextDatabase[counter] = word;
					counter++;
				}
			}
		}
	}
		
	return counter;
}
	
int editingUserText(string text)
{
	char word[N];
	int iw = 0;
	int counter = 0;
	
	for(int i = 0; text[i] != '\0'; i++)
	{
		if (!isSeparator(text[i]) and  !isNumber(text[i]))
		{
			word[iw++] = text[i];			
			if (isSeparator(text[i + 1]) or text[i + 1] == '\0' or isNumber(text[i+1])) 
			{
				word[iw] = '\0';
				iw = 0;
				for(int k = 0; word[k] != '\0'; k++){
					word[k] = lowerCase(word[k]);
				}	
				if(!isConjuction(word) and (counter == 0 or word != editedUserText[counter - 1]))  
				{
					editedUserText[counter] = word;
					counter++;
				}
			}
		}
	}
	cout << "Counter" << counter << endl;	
	return counter;
}

int calculateUniqueness(int textDatabaseLength, int userTextLength)
{
	string shingle[SHINGLE_SIZE];
	int allShingle = 0;
	int uniqueShingles = 0;
	int uniqueness = 0;
	
	if (textDatabaseLength < SHINGLE_SIZE or userTextLength < SHINGLE_SIZE)
	{
		uniqueness = 100;
		
		return uniqueness;
	}
	allShingle = userTextLength - SHINGLE_SIZE + 1;
	for (int shingleCount = 0; shingleCount < allShingle; shingleCount++)
	{
		for (int i = 0; i < SHINGLE_SIZE; i++)
		{
			shingle[i] = editedUserText[i + shingleCount];
		}
		if (isShingleUnique(shingle, textDatabaseLength))
		{
			uniqueShingles++;
		}
	}
	uniqueness = (100.0 * uniqueShingles / allShingle);
	
	return uniqueness;
}

bool isShingleUnique(string shingle[], int textDatabaseLength)
{
	int allShingless=0;
	int allShingles = textDatabaseLength - SHINGLE_SIZE + 1;
	int matchedWords = 0;
	
	for (int i = 0; i < allShingles; i++)
	{
		matchedWords = 0;
		for (int j = 0; j < SHINGLE_SIZE; j++)
		{
			if (shingle[j] == editedTextDatabase[i + j])
			{
				matchedWords++;
			}
		}
		if (matchedWords == SHINGLE_SIZE)
		{
			return false;
		}
	}
	return true;
}

