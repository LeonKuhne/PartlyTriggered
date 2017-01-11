#include "mediaGamepad.h"

using namespace std;

void emulateMediaGamepad(int gamepadID)
{
	Gamepad g(gamepadID);
	int inputDelay = 150;

	while (TRUE)

	{
		if (!g.Connected())
		{
			cout << "Waiting for xbox 360 gamepad to be connected... ";
			while (!g.Connected()) {}
			cout << "found." << endl;
		}

		cout << "Using gamepad " << gamepadID << " as media controller." << endl;
		g.Rumble(0.5, 0.5);
		Sleep(500);
		g.Rumble();

		BOOL videoMode = FALSE;

		while (g.Connected() && !g.GetButtonPressed(XINPUT_GAMEPAD_BACK))
		{
			g.Update();

			if (g.GetButtonPressed(XINPUT_GAMEPAD_DPAD_UP))
			{
				cout << "Volume increased." << endl;
				simulateKeyPress(175, 0.05);
			}
			else if (g.GetButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN))
			{
				cout << "Volume decreased." << endl;
				simulateKeyPress(174, 0.05);
			}
			else if (g.GetButtonPressed(XINPUT_GAMEPAD_B))
			{
				cout << "Volume mute/unmute." << endl;
				simulateKeyPress(173, 0.5);
			}
			else if (g.GetButtonPressed(XINPUT_GAMEPAD_Y))
			{
				videoMode = !videoMode;
				cout << "Video mode ";
				if (videoMode)
				{
					cout << "enabled." << endl;
					g.Rumble(1, 1);
					Sleep(200);
					g.Rumble();
					Sleep(100);
					g.Rumble(1, 1);
					Sleep(200);
					g.Rumble();
				}
				else
				{
					cout << "disabled." << endl;
					g.Rumble(1, 1);
					Sleep(200);
					g.Rumble();
				}
				Sleep(inputDelay);
			}
			else
			{
				if (videoMode)
				{
					if (g.GetButtonPressed(XINPUT_GAMEPAD_A))
					{
						simulateKeyPress(32, 0.5);
					}
					else if (g.GetButtonPressed(XINPUT_GAMEPAD_START))
					{
						cout << "Video Paused/Played." << endl;

						POINT mPos = getMousePos();
						clickAt(0.5, 0.5, 20);
						SetMousePosition(mPos.x, mPos.y);

						Sleep(inputDelay);
					}
					else if (g.GetButtonPressed(XINPUT_GAMEPAD_X))
					{
						cout << "Video Toggle Fullscreen." << endl;

						POINT mPos = getMousePos();
						clickAt(0.5, 0.5, 20);
						Sleep(50);
						clickAt(0.5, 0.5, 20);
						SetMousePosition(mPos.x, mPos.y);

						Sleep(inputDelay);
					}
					else if (g.GetButtonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER))
					{
						cout << "Next Tab." << endl;
						simulateKeyDown(17);	// ctrl
						simulateKeyDown(9);		// tab
						simulateKeyUp(9);		// tab
						simulateKeyUp(17);		// ctrl
						Sleep(inputDelay);
					}
					else if (g.GetButtonPressed(XINPUT_GAMEPAD_LEFT_SHOULDER))
					{
						cout << "Prevous Tab." << endl;
						simulateKeyDown(17);	// ctrl
						simulateKeyDown(16);	// shift
						simulateKeyDown(9);		// tab
						simulateKeyUp(9);		// tab
						simulateKeyUp(16);		// shift
						simulateKeyUp(17);		// ctrl
						Sleep(inputDelay);
					}
					else if (g.RightTrigger() > 0.5)
					{
						cout << "Next Window." << endl;
						simulateKeyDown(18);			// alt
						simulateKeyDown(9);				// tab
						simulateKeyUp(9);				// tab
						while (g.RightTrigger() > 0)
						{
							g.Update();
							if (g.GetButtonPressed(XINPUT_GAMEPAD_A))
							{
								simulateKeyDown(9);		// tab
								simulateKeyUp(9);		// tab
								Sleep(inputDelay);
							}
							Sleep(50);
						}
						simulateKeyUp(18);				// alt
					}
					else if (g.LeftTrigger() > 0.5)
					{
						cout << "Prevous Window." << endl;
						simulateKeyDown(18);			// alt
						simulateKeyDown(16);			// shift
						simulateKeyDown(9);				// tab
						simulateKeyUp(9);				// tab
						while (g.LeftTrigger() > 0)
						{
							g.Update();
							if (g.GetButtonPressed(XINPUT_GAMEPAD_A))
							{
								simulateKeyDown(9);		// tab
								simulateKeyUp(9);		// tab
								Sleep(inputDelay);
							}
							Sleep(50);
						}
						simulateKeyUp(16);				// shift
						simulateKeyUp(18);				// alt
					}
				}
				else
				{
					if (g.GetButtonPressed(XINPUT_GAMEPAD_A))
					{
						cout << "Music Paused/Playing." << endl;
						simulateKeyPress(179, 0.5);
					}
					else if (g.GetButtonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER))
					{
						cout << "Song Skipped." << endl;
						simulateKeyPress(176, 0.5);
					}
					else if (g.GetButtonPressed(XINPUT_GAMEPAD_LEFT_SHOULDER))
					{
						cout << "Prevous Song." << endl;
						simulateKeyPress(177, 0.5);
					}
					else if (g.GetButtonPressed(XINPUT_GAMEPAD_X))
					{
						cout << "Opening Pandora." << endl;
						system("start pandora:");
						Sleep(500);
					}
				}
			}

			Sleep(50); // decrease cpu usage

		}
	}
}