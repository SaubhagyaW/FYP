#include <iostream>
#include "SideBySidePersonFollowing.h"
#include "BackPersonFollowing.h"

using namespace std;

void main()
{
	int mode = 0;

	do
	{
		cout << "Navigation mode"
			<< "\n\t<1> Side-by-side accompaniment"
			<< "\t<2> Follow person from behind" << endl;
		cin >> mode;

		switch (mode)
		{
		case 1: {
			SideBySidePersonFollowing sideBySide;
			sideBySide.follow();
		}
				break;
		case 2: {
			BackPersonFollowing behind;
			behind.follow();
		}
				break;
		default:
			cout << "Please enter a valid person-following mode" << endl;
		}
	} while (mode != 1 && mode != 2);
}