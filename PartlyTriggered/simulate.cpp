#include "simulate.h"

using namespace std;

void simulateInputs(string filename)
{
	// Simulate keys contained within a log file
	cout << "Simulating keypresses from file \"" << filename << "\"." << endl;

	ifstream file(filename);
	file.unsetf(ios_base::skipws);

	clock_t start = clock();
	string line;

	while (!file.eof()) {
		getline(file, line);
		// fetch line data
		vector<string> data = split(line);
		if (data.size() >= 3)
		{
			double time = stof(data.at(0));

			int key = stof(data.at(1));
			int state = stof(data.at(2));

			// Calculate the time to sleep, make sure sleep time isn't negative
			double timeToSleep = max((time - ((clock() - start) / (double)CLOCKS_PER_SEC)), 0);

			// Simulate key presses
			Sleep(timeToSleep * 1000);

			// if 'key' is on mouse (ie. 0,1,2,4,5,6). I'm assuming that inputs 3 and 4 are also reserved for the mouse
			if (key <= 6)
			{
				double x = stof(data.at(3));
				double y = stof(data.at(4));
				if (state == 1)
					clickDown(x, y, key);
				else
					clickUp(x, y, key);
			}
			else {
				if (state == 1)
					simulateKeyDown(key);
				else
					simulateKeyUp(key);
			}
		}
		else
		{
			return;
		}

	}
}

INPUT click(int key)
{
	INPUT ip = { 0 };
	ip.type = INPUT_MOUSE;
	return ip;
}

void SetMousePosition(double x, double y)
{
	INPUT ip = { 0 };
	ip.type = INPUT_MOUSE;

	ip.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	long fScreenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
	long fScreenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;

	ip.mi.dx = (x / fScreenWidth)*65535.0f;
	ip.mi.dy = (y / fScreenHeight)*65535.0f;

	SendInput(1, &ip, sizeof(INPUT));
}

void clickDown(double x, double y, int key)
{
	INPUT ip = click(key);

	SetMousePosition(x, y);
	Sleep(0);

	ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &ip, sizeof(INPUT));
}

void clickUp(double x, double y, int key)
{
	INPUT ip = click(key);

	SetMousePosition(x, y);
	Sleep(0);

	ZeroMemory(&ip, sizeof(INPUT));
	ip.type = INPUT_MOUSE;
	ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &ip, sizeof(INPUT));
}

INPUT getKey(char key)
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = key;

	return ip;
}

void simulateKeyDown(char key)
{
	// Simulate key down
	INPUT ip = getKey(key);

	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));
}

void simulateKeyUp(char key)
{
	// Simulate key up
	INPUT ip = getKey(key);

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void simulateKeyPress(char key, float time)
{
	simulateKeyDown(key);
	Sleep(float(time * 1000));
	simulateKeyUp(key);
}