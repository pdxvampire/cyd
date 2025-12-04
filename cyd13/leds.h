// This is strictly the LEDs built into the CYD board,
// useful for making sure sketches are running, that
// the board works, etc.

int blinkctr = 0;
int ledPins[] = { 4, 16, 17 };

bool blinkflag = true;

void InitializeOnboardLEDs(void)
{
    enterfunction("InitializeOnboardLEDs");

    // set up onboard LED pins so we can get visual feedback that at least that much is working
    for (int p : ledPins)
    {
        pinMode(p, OUTPUT);
    }

    exitfunction("InitializeOnboardLEDs");
}

void TurnOnOnboardLEDs(void)
{
    enterfunction("TurnOnOnboardLEDs");

    for (int p : ledPins)
    {
        logit("Turning on GPIO %d", p);
        digitalWrite(p, LOW);
    }

    exitfunction("TurnOnOnboardLEDs");
}

void TurnOffOnboardLEDs(void)
{
    enterfunction("TurnOffOnboardLEDs");

    for (int p : ledPins)
    {
        logit("Turning off GPIO %d", p);
        digitalWrite(p, HIGH);
    }

    exitfunction("TurnOffOnboardLEDs");
}

void BlinkOnboardLEDs(void)
{
    enterfunction("BlinkOnboardLEDs");

    TurnOnOnboardLEDs();
    delay(300);
    TurnOffOnboardLEDs();

    exitfunction("BlinkOnboardLEDs");
}