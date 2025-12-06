uint8_t arrImages[1][buffersize];

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