#include "ControllerInput.h"


ControllerInput::ControllerInput()
{
	cExit = "";
	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
		cExit = "SDL Failed To Initialize Controller";
    cJoyStick = NULL;
    cController = NULL;
    lStickX = 0;
    lStickY = 0;
    rStickX = 0;
    rStickY = 0;
    lTrigger = false;
    rTrigger = false;
    for (int i = 0; i < 15; i++)
        buttons[i] = false;
}

void ControllerInput::update(SDL_Event rEvent)
{
    switch (rEvent.type)
    {
    case SDL_JOYAXISMOTION:
        if (rEvent.jaxis.axis == 0)
        {
            if (rEvent.jaxis.value < -8000)
            {
                lStickX = -1;
            }
            else if (rEvent.jaxis.value > 8000)
            {
                lStickX = 1;
            }
            else
            {
                lStickX = 0;
            }
        }
        else if (rEvent.jaxis.axis == 1)
        {
            if (rEvent.jaxis.value < -8000)
            {
                lStickY = -1;
            }
            else if (rEvent.jaxis.value > 8000)
            {
                lStickY = 1;
            }
            else
            {
                lStickY = 0;
            }
        }

        if (rEvent.jaxis.axis == 3)
        {
            if (rEvent.jaxis.value < -8000)
            {
                rStickX = -1;
            }
            else if (rEvent.jaxis.value > 8000)
            {
                rStickX = 1;
            }
            else
            {
                rStickX = 0;
            }
        }
        else if (rEvent.jaxis.axis == 4)
        {
            if (rEvent.jaxis.value < -8000)
            {
                rStickY = -1;
            }
            else if (rEvent.jaxis.value > 8000)
            {
                rStickY = 1;
            }
            else
            {
                rStickY = 0;
            }
        }
        else if (rEvent.jaxis.axis == 2)
        {
            if (rEvent.jaxis.value > 8000)
                lTrigger = true;
            else
                lTrigger = false;
        }
        else if (rEvent.jaxis.axis == 5)
        {
            if (rEvent.jaxis.value > 8000)
                rTrigger = true;
            else
                rTrigger = false;
        }
        break;
    default:
        break;
    }
}

void ControllerInput::controllerUpdate()
{
    if (SDL_NumJoysticks() > 0)
    {
        if (!cJoyStick)
        {
            cJoyStick = SDL_JoystickOpen(0);
            cController = SDL_GameControllerOpen(0);
        }
    }
    else
        destroy();

    for (int i = 0; i < 15; i++)
        if (SDL_GameControllerGetButton(cController, (SDL_GameControllerButton)i))
            buttons[i] = true;
        else
            buttons[i] = false;
}

void ControllerInput::destroy()
{
    if (cJoyStick)
    {
        SDL_JoystickClose(0);
        cJoyStick = NULL;
        SDL_GameControllerClose(0);
        cController = NULL;
        lStickX = 0;
        lStickY = 0;
        rStickX = 0;
        rStickY = 0;
    }
}