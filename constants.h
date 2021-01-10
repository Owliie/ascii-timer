/**
*  
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Aneta Tsvetkova
* @idnumber 62634
* @compiler GCC
*
* <file with constants>
*
*/

#ifndef CONSTANTS
#define CONSTANTS

#define GRN "\e[0;32m"
#define NC "\e[0m"
#define RED "\e[0;31m"
#define CYN "\e[0;36m"

using namespace std;

const int MIN_SECONDS = 0;
const int MAX_SECONDS = 9999;
const char BEEP_CHAR = '\7';
const int SECONDS_IN_MINUTE = 60;
const int TIMER_DIGIT_WIDTH = 10;
const int TIMER_DIGIT_HEIGHT = 11;
const int WINDOW_WIDTH = 80;
const string BLACK_BLOCK_ASCII_CODE = "\u2593";

#endif