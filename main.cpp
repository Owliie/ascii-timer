#include <iostream>
#include <string>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"

using namespace std;

int const MIN_SECONDS = 0;
int const MAX_SECONDS = 9999;
int const SECONDS_IN_MINUTE = 60;

string convertToMinutes(int seconds){
	int minutes = seconds/SECONDS_IN_MINUTE;
	seconds %= SECONDS_IN_MINUTE;

	string time = to_string(minutes) + ':' + to_string(seconds);

	return time;
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
			cout << RED << "Invalid seconds format!" << endl << endl;
		}
	} while (seconds < 0 || seconds > 9999);

	cout << convertToMinutes(seconds) << endl;

	return 0;
}
