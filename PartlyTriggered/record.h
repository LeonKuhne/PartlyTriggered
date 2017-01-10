#pragma once

#include "helper.h"

using namespace std;

void recordInputs(string, float waitTime = 500, double startTime = 0);
void writeKeyToFile(ostream &, double, int, int);
void writeMouseToFile(ostream &, double, int, int, float, float);
POINT getMousePos();