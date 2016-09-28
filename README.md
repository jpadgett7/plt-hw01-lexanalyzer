# Lexical Analyzer
This project is a lexical analyzer created in C++. It receives a given number of strings and identifies what type of lexeme they are from a specified list of token types.

##Token Types
The following are the types of lexemes that the program can identify.

* **Integer:** Non-empty sequence of digits optionally preceded with '+' or '-'
* **Decimal:** Integer followed by a '.' then followed by a non-empty sequence of digits
* **Scientific:** Decimal followed by character 'E' then followed by a non-zero integer
* **Hexadecimal:** Non-empty sequence of digits or characters 'A' through 'F' followed by character 'H'
* **Binary:** Non-empty sequence of digits '1' or '0' followed by character 'B'
* **Keyword:** Specific strings `while`, `else`, `end`, and `print`
* **Identifier:** String that consists of a letter followed by zero or more letters, digits, or the underscore that are **not** hexadecimal type

##Input
First input is an integer **N**. The program will then accept **N** lines of input. Strings must be input line by line for program to function correctly.

