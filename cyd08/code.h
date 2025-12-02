void InitializeSerialCommunication(void)
{
    loglevel++;  // would normally be part of the call to enterfunction for InitializeSerialCommunication()

    Serial.begin(115200);

    // Wait for the serial port to connect so the Serial Monitor printouts work consistently
    // This may not be necessary on Windows or Linux but with my Macbook Air M3 (2024) it is.
    delay(2000);

    // Set all chip selects high to avoid bus contention during initialisation of each peripheral
    digitalWrite(22, HIGH);  // Touch controller chip select (if used)
    digitalWrite(15, HIGH);  // TFT screen chip select
    digitalWrite(5, HIGH);   // SD card chips select, must use GPIO 5 (ESP32 SS)

    logit("");  // insert a newline after the random garbage that gets printed on connection/powerup
    logit("####### Done initializing serial communication. ################################");
    exitfunction("InitializeSerialCommunication");
}