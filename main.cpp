#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"

using namespace std;

int const MIN_SECONDS = 0;
int const MAX_SECONDS = 9999;
int const SECONDS_IN_MINUTE = 60;

int *convertToMinutes(int seconds)
{
	int minutes = seconds / SECONDS_IN_MINUTE;
	seconds %= SECONDS_IN_MINUTE;

	int *time = new int[2]{minutes, seconds};

	return time;
}

void display_clock();

void beep_sound()
{
	cout << '\7';
}

void start_timer(int *time)
{
	int minutes = time[0];
	int seconds = time[1];

	while (true)
	{
		system("clear");
		cout << NC << setfill('0')
			 << setw(2) << minutes << ':' << setw(2) << seconds << endl;
		sleep(1);

		if (minutes == MIN_SECONDS && seconds == MIN_SECONDS)
		{
			break;
		}

		seconds--;

		if (seconds < MIN_SECONDS)
		{
			minutes--;
			seconds = SECONDS_IN_MINUTE - 1;
		}
	}

	beep_sound();
}

int main(int argc, char const *argv[])
{
	int seconds = 0;

	do
	{
		cout << CYN << "Enter seconds: ";
		cin >> seconds;

		if (seconds < 0 || seconds > 9999)
		{
			cout << RED << "Invalid seconds format!" << endl
				 << endl;
		}
	} while (seconds < 0 || seconds > 9999);

	int *time = convertToMinutes(seconds);
	start_timer(time);

	return 0;
}
