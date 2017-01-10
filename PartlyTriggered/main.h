#pragma once

#include "helper.h"
#include "simulate.h"
#include "record.h"

#include "gamepad.h"
#include <xinput.h>	// 360 controller

using namespace std;

void requestCommand();
void processCommand(string);
void displayHelp();

void continueRecording(string, double);
void deleteSeconds(string, double);

void emulateMediaGamepad(int);