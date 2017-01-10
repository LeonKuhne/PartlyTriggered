#pragma once

#define WINVER 0x0500
#include <windows.h>
#include <winuser.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

#include <stdio.h>
#include <algorithm>
#include <tuple>
#include <cstdlib>
#include <thread>
#include <future>

using namespace std;

vector<string> split(string, char delimiter = ' ');
string requestParam(int, string, vector<string> parameters = {});
void readFile(string);
void emptyFile(string);