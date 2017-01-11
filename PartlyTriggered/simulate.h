#pragma once

#include "helper.h"

using namespace std;

void simulateInputs(string);
INPUT click();
void SetMousePosition(double, double);
void clickDown(double, double, int);
void clickUp(double, double, int);
void clickAt(double, double, double time = 0);

INPUT getKey(char);
void simulateKeyDown(char);
void simulateKeyUp(char);
void simulateKeyPress(char, float time = 0);