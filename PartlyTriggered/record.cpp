#include "record.h"

using namespace std;

void recordInputs(string filename, float waitTime, double startTime)
{
	clock_t start = clock();
	double time;

	Sleep(waitTime);

	// Open the log file to save data in.
	ofstream file;
	file.open(filename, ios_base::app);

	vector<int> keysPressed;

	cout << "Recording keypresses to file \"" << filename << "\"." << endl;

	while (true)
	{
		for (int keyId = 0; keyId <= 256; keyId++)
		{
			// test if the keyId is "new" (not contained in keysPressed) and down
			if ((GetAsyncKeyState(keyId) & 0x8000) && (find(keysPressed.begin(), keysPressed.end(), keyId) == keysPressed.end()))
			{
				time = (clock() - start) / (double)CLOCKS_PER_SEC + startTime;

				if (keyId <= 6)
				{
					// get mouse coordinates
					POINT coord = getMousePos();
					writeMouseToFile(file, time, keyId, 1, coord.x, coord.y);
				}
				else {
					writeKeyToFile(file, time, keyId, 1);
				}
				// Add the value to the pressed list
				keysPressed.push_back(keyId);
			}
		}

		vector<int> removalQueue;

		// Test for released keys
		for (int i = 0; i < keysPressed.size(); i++)
		{
			if (!(GetAsyncKeyState(keysPressed.at(i)) & 0x8000))
			{
				time = (clock() - start) / (double)CLOCKS_PER_SEC + startTime;

				if (keysPressed.at(i) <= 6)
				{
					POINT coord = getMousePos();
					writeMouseToFile(file, time, keysPressed.at(i), 0, coord.x, coord.y);
				}
				else
				{
					writeKeyToFile(file, time, keysPressed.at(i), 0);
				}

				removalQueue.push_back(keysPressed.at(i));
			}
		}

		// Remove the value from the pressed list
		for (int i = 0; i < removalQueue.size(); i++)
			keysPressed.erase(remove(keysPressed.begin(), keysPressed.end(), removalQueue.at(i)), keysPressed.end());

		// Test for escape key
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			// exit if the escape key is pressed
			// release all of the keys that are still currently pressed

			time = (clock() - start) / (double)CLOCKS_PER_SEC + startTime;

			for (int i = 0; i < keysPressed.size(); i++)
				if (keysPressed.at(i) <= 6)
				{
					POINT coord = getMousePos();
					writeMouseToFile(file, time, keysPressed.at(i), 0, coord.x, coord.y);
				}
				else
				{
					writeKeyToFile(file, time, keysPressed.at(i), 0);
				}

			return;
		}
	}
}

void writeKeyToFile(ostream & file, double time, int key, int state)
{
	cout << time << " " << char(key) << " " << state << endl;
	file << time << " " << key << " " << state << endl;
}

void writeMouseToFile(ostream & file, double time, int key, int state, float x, float y)
{
	cout << time << " " << char(key) << " " << state << " " << x << " " << y << endl;
	file << time << " " << key << " " << state << " " << x << " " << y << endl;
}

POINT getMousePos()
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	m.x = mouse.x;
	m.y = mouse.y;
	return m;
}