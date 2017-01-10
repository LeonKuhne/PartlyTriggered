#pragma once

#include "helper.h"

using namespace std;

void simulateInputs(string);
INPUT click(int);
void SetMousePosition(double, double);
void clickDown(double, double, int);
void clickUp(double, double, int);
INPUT getKey(char);
void simulateKeyDown(char);
void simulateKeyUp(char);
void simulateKeyPress(char, float time = 0);