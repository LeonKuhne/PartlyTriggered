#pragma once

#include "helper.h"
#include "simulate.h"
#include "record.h"
#include "mediaGamepad.h"

using namespace std;

void requestCommand();
void processCommand(string);
void displayHelp();

void continueRecording(string, double);
void deleteSeconds(string, double);