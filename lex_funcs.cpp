// John Padgett
// CS 3500 - Programming Languages and Translators
// Homework 1 - Lexical Analyzer
// lex_funcs.cpp

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

string stringType(char lex)
{
	string lexeme;
	
	switch(lex)
	{
		case 'n':
			lexeme = "Integer.";
			break;
		case 'd':
			lexeme = "Decimal.";
			break;
		case 's':
			lexeme = "Scientific.";
			break;
		case 'h':
			lexeme = "Hexadecimal.";
			break;
		case 'b':
			lexeme = "Binary.";
			break;
		case 'k':
			lexeme = "Keyword.";
			break;
		case 'i':
			lexeme = "Identifier.";
			break;
		case 'v':
			lexeme = "Invalid!";
			break;
		default:
			lexeme = "Error!!";
			break;
	}
		
	return lexeme;
}

bool isDigit(char c)
{
	return('0' <= c && c <= '9');
}

bool isAlpha(char c)
{
	char alph[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	return(strchr(alph, c) != NULL);
}

bool isHex(char c)
{
	char hex[] = "0123456789ABCDEF";
	
	return(strchr(hex, c) != NULL);
}

char lexAnalyzer(string S)
{
	char lex = 'v';
	int state = 0;
	int i = 0;
	
	if(S=="while"||S=="else"||S=="end"||S=="print")
		lex = 'k';
	else
	{
		while(i < S.size())
		{
			switch(state)
			{
				case 0: // start state
					if(isDigit(S[i]))
					{
						if(S[i] == '0' || S[i] == '1')
							state = 1;
						else
							state = 2;
					}
					else if(isAlpha(S[i]))
					{
						if (isHex(S[i]))
						{
							state = 14; // char is A,B,C,D,E,F; could be hex
						}
						else
						{
							state = 4; // char is definitely not hex
						}
					}
					else if(S[i] == '+' || S[i] == '-')
					{
						state = 3;
					}
					else
					{
						state = -1;
					}
					break;
				case 1: // final state for integers (halfway for binary)
					if(isDigit(S[i]))
					{
						if(S[i] == '0' || S[i] == '1')
							state = 1;
						else
							state = 2;
					}
					else if(isHex(S[i]))
					{
						if(S[i] == 'B') //can now be considered binary, but possibly hex
							state = 5;
						else
							state = 6;
					}
					else if(S[i] == '.')
					{
						state = 7;
					}
					else if(S[i] == 'H')
					{
						state = 8;
					}
					else
					{
						state = -1;
					}
					break;
				case 2: // alternate final state for integers (no longer binary)
					if(isDigit(S[i]))
					{
						state = 2;
					}
					else if(isHex(S[i]))
					{
						state = 6;
					}
					else if(S[i] == '.')
					{
						state = 7;
					}
					else if(S[i] == 'H')
					{
						state = 8;
					}
					else
					{
						state = -1;
					}
					break;
				case 3: //+ or - detected
					if(isDigit(S[i]))
					{
						state = 9; // now has + or -, cannot be hex or binary
					}
					else
					{
						state = -1;
					}
					break;
				case 4: // final state for identifier
					if(isAlpha(S[i]) || isDigit(S[i]) || S[i] == '_')
					{
						state = 4;
					}
					else
					{
						state = -1;
					}
					break;
				case 5: // final binary state
					if(isHex(S[i]))
					{
						state = 6;
					}
					else if(S[i] == 'H')
					{
						state = 8;
					}
					else
						state = -1;
					break;
				case 6: // intermediate step for hex
					if(isHex(S[i]))
					{
						state = 6;
					}
					else if(S[i] == 'H')
					{
						state = 8;
					}
					else
					{
						state = -1;
					}
					break;
				case 7: // decimal detected, intermediate step for decimals and scientific
					if(isDigit(S[i]))
					{
						state = 10;
					}
					else
					{
						state = -1;
					}
					break;
				case 8: // final state for hex
					state = -1; //any input would invalidate string
					break;
				case 9: // alternate final state for integers (when + or - is present)
					if(isDigit(S[i]))
					{
						state = 9;
					}
					else if(S[i] == '.')
					{
						state = 7;
					}
					else
					{
						state = -1;
					}
					break;
				case 10: // final state for decimal, intermediate step for scientific 
					if(isDigit(S[i]))
					{
						state = 10;
					}
					else if(S[i] == 'E')
					{
						state = 11;
					}
					else
					{
						state = -1;
					}
					break;
				case 11: // intermediate step for scientific string
					if(S[i] == '+' || S[i] == '-')
					{
						state = 12;
					}
					else if(isDigit(S[i]) && S[i] != '0')
					{
						state = 13;
					}
					else
					{
						state = -1;
					}
					break;
				case 12: // + or - in scientific string detection
					if(isDigit(S[i]) && S[i] != '0')
					{
						state = 13;
					}
					else
					{
						state = -1;
					}
					break;
				case 13: // final state of scientific recognition
					if(isDigit(S[i]))
					{
						state = 13;
					}
					else
					{
						state = -1;
					}
					break;
				case 14: // alternate final for identifier, intermediate for hex
					if(isDigit(S[i]))
					{
						state = 14;
					}
					else if(isHex(S[i]))
					{
						state = 14;
					}
					else if(S[i] == 'H')
					{
						state = 8;
					}
					else if(isAlpha(S[i]))
					{
						state = 4;
					}
					else
					{
						state = -1;
					}
					break;
				default:
					i = S.size();
					break;
			}//end switch-case
			
			i++;
		}//end while
		
		if(i == S.size())
		{
			if(state == 1 || state == 2 || state == 9)
				lex = 'n';
			else if(state == 10)
				lex = 'd';
			else if(state == 8)
				lex = 'h';
			else if(state == 13)
				lex = 's';
			else if(state == 5)
				lex = 'b';
			else if(state == 4 || state == 14)
				lex = 'i';
		}
		else
			lex = 'v';
		
	} //end else
	
	return lex;
}


