/*
 * Sensor: HC-SR04 Ultrasonic sensor
 * Dev kit: Arduino Uno
 */

#define echoPin 8 // Echo pin on sensor wired to Pin D8 on dev kit
#define trigPin 9 // Echo pin on sensor wired to Pin D9 on dev kit

// defines variables
long duration;  // Variable for the duration of sound wave travel
int distance;   // Variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  Serial.begin(9600);       // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor Data Capture Start"); // Text to note start of data collection
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds, as required by sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  // Displays the distance on the Serial Monitor
  // Serial.print("Distance: ");
  Serial.print(distance);
  // Serial.println(" cm");
}
