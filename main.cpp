#include <iostream>
#include <string>
using namespace std;

int const MIN_SECONDS = 0;
int const MAX_SECONDS = 9999;
int const SECONDS_IN_MINUTE = 60;

string convertToMinutes(int seconds){
	int minutes = seconds/SECONDS_IN_MINUTE;
	seconds %= SECONDS_IN_MINUTE;

	string time = to_string(minutes);
	time.push_back(':');
	time.append(to_string(seconds));

	return time;
}

int main(int argc, char const *argv[])
{
	int seconds = 0;

	do
	{
		cout << "Enter seconds: ";
		cin >> seconds;

		if (seconds < 0 || seconds > 9999)
		{
			cout << "Invalid seconds format!" << endl;
		}
	} while (seconds < 0 || seconds > 9999);

	cout << convertToMinutes(seconds) << endl;

	return 0;
}
