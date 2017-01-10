#include "helper.h"

using namespace std;

vector<string> split(string str, char delimiter) {
	// split a string into parts using space as a delimiter
	istringstream ss(str);
	vector<string> tokens;
	string buf;

	while (getline(ss, buf, delimiter)) {
		tokens.push_back(buf.c_str());
	}

	return tokens;
}

string requestParam(int index, string textToPrint, vector<string> parameters)
{
	string param;
	if (parameters.size() > index)
	{
		param = parameters.at(index);
	}
	else
	{
		// Get a parameter from a user manualy
		cout << textToPrint;
		cin >> param;
	}

	return param;
}

void readFile(string filename)
{
	// Read the contents of a file
	ifstream file(filename);
	string line;
	while (!file.eof())
	{
		getline(file, line);
		if (!line.empty())
			cout << line << endl;
	}
}

void emptyFile(string filename)
{
	// Empties a given file
	ofstream ofs;
	ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}