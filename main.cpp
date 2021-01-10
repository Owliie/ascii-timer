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
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>
#include <ctype.h>
#include "constants.h"
#include "arrayHelper.h"
#include "printDigitLines.h"

using namespace std;

// produce beep sound
void beep_sound()
{
	cout << BEEP_CHAR;
}

void start_timer(int *time)
{
	int *minutes = &time[0];
	int *seconds = &time[1];

	while (true)
	{
		// clear console so that prints wouldn't stack
		system("clear");

		print_digit_per_line(time);

		// wait 1s before update
		sleep(1);

		if (*minutes == MIN_SECONDS && *seconds == MIN_SECONDS)
		{
			break;
		}

		(*seconds)--;

		if (*seconds < MIN_SECONDS)
		{
			(*minutes)--;
			(*seconds) = SECONDS_IN_MINUTE - 1;
		}
	}

	beep_sound();
}

int main(int argc, char const *argv[])
{
	int seconds = -1;
	string input;

	do
	{
		cout << CYN << "Enter seconds: ";
		cin >> input;

		try
		{
			seconds = stoi(input);
		}catch (const invalid_argument & e) {
            cout << RED << "Invalid seconds format!" << endl << endl;
			continue;
        }

		if (seconds < MIN_SECONDS || seconds > MAX_SECONDS)
		{
			cout << RED << "Invalid seconds format!" << endl
				 << endl;
		}
	} while (seconds < MIN_SECONDS || seconds > MAX_SECONDS);

	cout << seconds << endl;

	int *time = convert_to_seconds(seconds);

	start_timer(time);

	delete[](time);
	return 0;
}
