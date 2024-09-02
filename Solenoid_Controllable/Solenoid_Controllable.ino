int frequency = 8; // Frequency in Hz (Adjust as needed)
const int maxHighTime = 35; // Decreased maximum duration of HIGH signal in milliseconds

void setup() {
  pinMode(2, OUTPUT);    // Set pin D2 as an output
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED as an output
}

void loop() {
  // Calculate interval in milliseconds
  int interval = 1000 / frequency;

  // Calculate highTime (minimum of maxHighTime and calculated interval)
  int highTime = min(maxHighTime, interval / 2);

  // Calculate lowTime to complete the full cycle
  int lowTime = interval - highTime;

  if (lowTime < 0) {
    lowTime = 0; // Ensure lowTime is not negative
  }

  digitalWrite(2, HIGH);         // Send a HIGH signal to pin D2
  digitalWrite(LED_BUILTIN, HIGH); // Turn on the built-in LED
  delay(highTime);               // Wait for the highTime duration
  
  digitalWrite(2, LOW);          // Send a LOW signal to pin D2
  digitalWrite(LED_BUILTIN, LOW);  // Turn off the built-in LED
  delay(lowTime);                // Wait for the lowTime duration
}
