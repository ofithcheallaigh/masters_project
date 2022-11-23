/*
 * Sensor: HC-SR04 Ultrasonic sensor
 * Dev kit: Arduino Uno
 */


#define echoPin 8 // Echo pin on sensor wired to Pin D8 on dev kit
#define trigPin 9 // Echo pin on sensor wired to Pin D9 on dev kit

long myArray[400];
int j, i, k;
int arraySize;



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

  j = j+1;
  for ( i = 0; i < 400; i = i + 1) {
  
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
    // Serial.print(distance);
    // Serial.println(" cm");
    // myArray = duration;

    /*
    Serial.print("Pulse duration ");
    Serial.print(duration);
    Serial.println("");
    */

     myArray[i] = duration;

     arraySize = sizeof(myArray) / sizeof(myArray[0]); // Size of the array is 10 bytes

    delay(20);
    
    // Serial.println("The size of the array is: ");
    // Serial.println(arraySize);
    
  }
  for(int k = 0; k < arraySize; k++)
  {
    // Serial.println(sizeof(myArray));
    Serial.println(myArray[k]);
  }
  Serial.println("Array End");
  
} // End of void loop
