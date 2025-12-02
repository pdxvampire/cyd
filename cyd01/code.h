int blinkctr = 0;
int ledPins[] = { 4, 16, 17 };

bool blinkflag = true;

void InitializeSerialCommunication(void)
{
    loglevel++;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()

    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    logit("");  // insert a newline after the random garbage that gets printed on connection/powerup
    logit("####### Done initializing serial communication. ################################");
    exitfunction("InitializeSerialCommunication");
}

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