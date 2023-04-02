/*
This code is used to run the generated model from my object detection project
*/

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h> // Had to add "tflite_bridge"
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "object_model_50_128_sdg.h"

/**********************************************************************************************/
// *** Taken from: https://forum.arduino.cc/t/nano-ble-sense-and-ultrasonic-sensor/626958/3 ***/
/**********************************************************************************************/
// function prototype to define default timeout value
static unsigned int pulseInFun(const byte pin, const byte state, const unsigned long timeout = 1000000L);

// using a macro to avoid function call overhead
#define WAIT_FOR_PIN_STATE(state) \
  while (digitalRead(pin) != (state)) { \
    if (micros() - timestamp > timeout) { \
      return 0; \
    } \
  }

static unsigned int pulseInFun(const byte pin, const byte state, const unsigned long timeout) {
  unsigned long timestamp = micros();
  WAIT_FOR_PIN_STATE(!state);
  WAIT_FOR_PIN_STATE(state);
  timestamp = micros();
  WAIT_FOR_PIN_STATE(!state);
  return micros() - timestamp;
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/


const int numSamples = 10000;
int samplesRead = numSamples;

// Global variable used for TF Lite Micro
tflite::MicroErrorReporter tflErrorReporter;

// Import all the TF Lite Micro ops. I could pull in just the ones I need.
// For the minute I will take everything in. But this may change.
tflite::AllOpsResolver tflOpsResolver;

// Used to declare a variable that will be used to store a reference to a TF Lite model
const tflite::Model* tflModel = nullptr;

tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Create a memory buffer in the micro:
// byte define the type of the array and `tensorArena` is the name of the array.
// [tensorArenaSize] is the size of the array. In this case, the array has a size of tensorArenaSize bytes.
// __attribute__((aligned(16))) is an attribute that tells the compiler to align the memory for 
// the array on a 16-byte boundary.
constexpr int tensorArenaSize = 8 * 1024;
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));

// Array to map grids
const char* GRIDS[] = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine"          
};

#define NUM_GRIDS (sizeof(GRIDS) / sizeof(GRIDS[0]))

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  // Get the TFL repsentation of the model byte array
  tflModel = tflite::GetModel(model);
    if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);
  }
  
  // Generate an interpretor to run the model
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize);  

  // Assign memory for the model's input and output tensors
  tflInterpreter->AllocateTensors();

  // Pointers for the model input and output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);
}

void loop() {
  // Here I need to get my data samples, invoke the model and generate an output

}
