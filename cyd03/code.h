uint8_t cardType;
uint64_t cardSize;

int ledPins[] = { 4, 16, 17 };

void BlinkOnboardLEDs(void)
{
    for (int p : ledPins)
    {
        Serial.printf("Blinking GPIO %d\n", p);
        digitalWrite(p, HIGH);
        delay(300);
        digitalWrite(p, LOW);
        delay(300);
    }
}