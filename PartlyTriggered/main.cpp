#include "main.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Setup
	if (argc > 1)
	{
		ostringstream buffer;
		for (int i = 0; i < argc; ++i)
			buffer << argv[i] << " ";
		string cmdString = buffer.str();
		processCommand(cmdString);
	}
	else
	{
		// Start the cmd input proccess
		requestCommand();
	}
	
	return 0;
}

void requestCommand()
{
	string cmdString;
	cout << "Enter command: ";
	
	getline(std::cin, cmdString);
	processCommand(cmdString);
}

void processCommand(string cmdString)
{
	vector<string> cmdParameters = split(cmdString);
	string cmd = cmdParameters.front();
	
	if (cmd == "quit")
	{
		exit(0);
	}
	else if (cmd == "help")
	{
		displayHelp();
	}
	else if (cmd == "clr")
	{
		system("CLS");
	}
	else if (cmd == "record")
	{
		string filename = requestParam(1, "Enter filename: ", cmdParameters);
		emptyFile(filename);
		recordInputs(filename);
	}
	else if (cmd == "run")
	{
		string filename = requestParam(1, "Enter filename: ", cmdParameters);
		simulateInputs(filename);
	}
	else if (cmd == "continue")
	{
		string filename = requestParam(1, "Enter filename: ", cmdParameters);
		string shortenTime = requestParam(2, "Enter time: ", cmdParameters);
		continueRecording(filename, stof(shortenTime));
	}
	else if (cmd == "shorten")
	{
		string filename = requestParam(1, "Enter filename: ", cmdParameters);
		string shortenTime = requestParam(2, "Enter time: ", cmdParameters);
		deleteSeconds(filename, stof(shortenTime));
	}
	else if (cmd == "read")
	{
		string filename = requestParam(1, "Enter filename: ", cmdParameters);
		readFile(filename);
	}
	else if (cmd == "clear")
	{
		string filename = requestParam(1, "Enter filename: ", cmdParameters);
		emptyFile(filename);
	}
	else if (cmd == "360media")
	{
		emulateMediaGamepad(1);
	}
	else
	{
		cout << "I didn't understand that. Ask me for help if you need it." << endl;
	}

	requestCommand();
}

void continueRecording(string filename, double secondsToDelete)
{
	// continue recording
	if (secondsToDelete > 0)
	{
		deleteSeconds(filename, secondsToDelete);
	}
	clock_t start = clock();
	simulateInputs(filename);
	recordInputs(filename, 0, (clock() - start) / (double)CLOCKS_PER_SEC);
}

void deleteSeconds(string filename, double secondsToDelete)
{
	// remove the last seconds of a file
	
	// get the last line in a file
	ifstream readFile(filename);
	
	vector<string> lines;
	string line;
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			getline(readFile, line);
			if (!line.empty())
				lines.push_back(line);
		}
	}
	readFile.close();

	// calculate the time
	vector<string> data = split(lines.back());
	double timeToStartDeleting = stof(data.at(0)) - secondsToDelete;

	// clear contents of file
	emptyFile(filename);

	// write to file
	ofstream writeFile;
	writeFile.open(filename, ios_base::app);

	for (int i = 0; i < lines.size(); i++)
	{
		vector<string> data = split(lines.at(i));
		if (stof(data.at(0)) < timeToStartDeleting)
		{
			writeFile << lines.at(i) << endl;
		}
	}
	writeFile.close();
}

void displayHelp()
{
	cout << "	quit - exit the program" << endl;
	cout << "	help - display this information" << endl;
	cout << "	record (filename) - record keypresses and mouse inputs from a text file" << endl;
	cout << "	run (filename) - simulate keypresses and mouse inputs from a text file" << endl;
	cout << "	continue (filename) - continue recording from the end of another file" << endl;
	cout << "	shorten (filename) - remove the last few seconds of a file" << endl;
	cout << "	read (filename) - display the contents of a text file" << endl;
	cout << "	clear (filename) - empty a text file" << endl;
	cout << "	clr - clear the screen" << endl;
	cout << "	360media - use an XBOX 360 controller as a media controller" << endl;
	cout << "	*WIP* 360midi - use an XBOX 360 controller as a midi controller" << endl;
}

void emulateMediaGamepad(int gamepadID)
{
	Gamepad g(gamepadID);

	if (!g.Connected())
	{
		cout << "Waiting for xbox 360 gamepad to be connected... ";
		while (!g.Connected()) {}
		cout << "found." << endl;
	}
	
	cout << "Using gamepad " << gamepadID << " as media controller." << endl;

	while (g.Connected() && !g.GetButtonPressed(XINPUT_GAMEPAD_BACK))
	{
		g.Update();

		if (g.GetButtonPressed(XINPUT_GAMEPAD_A))
		{
			cout << "Music Paused/Playing." << endl;
			simulateKeyPress(179, 0.5);
		}
		if (g.GetButtonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER))
		{
			cout << "Song Skipped." << endl;
			simulateKeyPress(176, 0.5);
		}
		if (g.GetButtonPressed(XINPUT_GAMEPAD_LEFT_SHOULDER))
		{
			cout << "Prevous Song." << endl;
			simulateKeyPress(177, 0.5);
		}
		if (g.GetButtonPressed(XINPUT_GAMEPAD_DPAD_UP))
		{
			cout << "Volume increased." << endl;
			simulateKeyPress(175, 0.05);
		}
		if (g.GetButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN))
		{
			cout << "Volume decreased." << endl;
			simulateKeyPress(174, 0.05);
		}
		if (g.GetButtonPressed(XINPUT_GAMEPAD_B))
		{
			cout << "Volume mute/unmute." << endl;
			simulateKeyPress(173, 0.5);
		}
	}
}