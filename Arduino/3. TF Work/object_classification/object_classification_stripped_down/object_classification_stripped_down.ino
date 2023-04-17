/*
This code is used to run the generated model from my object detection project

Python code:  X_train.shape, X_test.shape, y_train.shape, y_test.shape
Generates:    ((134000, 2), (66000, 2), (134000,), (66000,))



https://www.programiz.com/c-programming/online-compiler/
#include <stdio.h>

int main() {
    int array[10][2];   
    // Fill the array with values
    
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 2; j++) {
        printf("%d ", array[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    return 0;
}


*/

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h> // Had to add "tflite_bridge"
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "model.h"


// defines variables
const int numSamples = 5000;
int samplesRead = numSamples;
// float durationCh1, durationCh2;  // Variable for the duration of sound wave travel
// long distanceCh1, distanceCh2;                   // Variable for the distance measurement
long cm;
int j, i;
long k;

// const int NUM_SAMPLES = 10000;
// int samplesRead = numSamples;

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
constexpr int tensorArenaSize = 60 * 1024;
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
  Serial.begin(9600);
  while(!Serial);
  Serial.print("Starting..."); // Text to note start of data collection

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

void loop() 
{
  float durationCh1, durationCh2;  // Variable for the duration of sound wave travel

  while(samplesRead ==  numSamples) // SAMPLES_LIMIT = 10000
  {
    samplesRead = 0;
    break;
  }
  // for(i=0; i<5000; i++)  
  while(samplesRead < numSamples)
  {  

    tflInputTensor->data.f[samplesRead*2+0] = 4512.00;
    tflInputTensor->data.f[samplesRead*2+1] = 4428.00;

    samplesRead++;    
    Serial.println(samplesRead);

    if(samplesRead == numSamples)
    { 
 
      TfLiteStatus invokeStatus = tflInterpreter->Invoke();
      Serial.println("Invoke");      
      if (invokeStatus != kTfLiteOk) 
      {
        Serial.println("Invoke failed!");
        while (1);
        return;
      }

      // Loop through the output tensor values from the model
      for (int i = 0; i < NUM_GRIDS; i++) 
      {
        Serial.print(GRIDS[i]);
        Serial.print(": ");
        Serial.println(tflOutputTensor->data.f[i],9); // The int here gives the decimal places
      }
      //======================================================= */ 
      Serial.println();
      delay(2000);
    }
  }
}
 
