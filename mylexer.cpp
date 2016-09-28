// John Padgett
// CS 3500 - Programming Languages and Translators
// Homework 1 - Lexical Analyzer
// main_func.cpp

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

string stringType(char lex);
bool isDigit(char c);
bool isAlpha(char c);
bool isHex(char c);
char lexAnalyzer(string S);

int main ()
{
	int user_num; // specified by the user to determine how many strings are to be read
	int lp_count = 1; // tracks the number of loop iterations
	char lexeme; // changes what string will be output by stringType()
	string S; // string to be read by the analyzer
	
	cin >> user_num;
	cout << user_num <<endl;
	while(lp_count <= user_num)
	{
		cin >> S;
		cout << lp_count << ": ";
		lexeme = lexAnalyzer(S);
		cout << stringType(lexeme) <<endl;
		lp_count++;
	};
	
	return 0;
}
