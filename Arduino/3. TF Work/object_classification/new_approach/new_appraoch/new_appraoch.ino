#include <TensorFlowLite.h>

#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h> // Had to add "tflite_bridge"
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "model.h"

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

// Define the pins that will be used for the input and output tensors.
const int INPUT_PIN = 0;
const int OUTPUT_PIN = 1;

// Generate an interpretor to run the model
tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize);  

// Assign memory for the model's input and output tensors
tflInterpreter->AllocateTensors();

// Pointers for the model input and output tensors
tflInputTensor = tflInterpreter->input(0);
tflOutputTensor = tflInterpreter->output(0);

// The TensorFlow Lite model.
// TFL_Model* model;

// The input and output tensors.
// TFL_Tensor* input_tensor;
// TFL_Tensor* output_tensor;

// The 2D array of 5000 rows and 2 columns.
float** data = malloc(5000 * sizeof(float*));
for (int i = 0; i < 5000; i++) {
  data[i] = malloc(2 * sizeof(float));
}

// The float array.
float* floatData = malloc(5000 * 2 * sizeof(float));

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

  // Get the input and output tensors.
  // input_tensor = tfl_model_get_input_tensor(model, 0);
  // output_tensor = tfl_model_get_output_tensor(model, 0);

  // Create a 2D array of 5000 rows and 2 columns.
  for (int i = 0; i < 5000; i++) {
    for (int j = 0; j < 2; j++) {
      data[i][j] = i * 2 + j;
    }
  }

  // Convert the 2D array to a float array.
  for (int i = 0; i < 5000; i++) {
    for (int j = 0; j < 2; j++) {
      floatData[i * 2 + j] = data[i][j];
    }
  }
}

void loop() {
  // Write the float array to the input tensor.
  tfl_write_tensor(tflInputTensor, floatData, 5000 * 2 * sizeof(float));
  /*
  if (status != TFL_OK) {
    Serial.println("Failed to write to input tensor: %s", tfl_status_str(status));
    while (true) {}
  }
  */

  // Run the inference.
  tfl_invoke_model(model);
  /*
  if (status != TFL_OK) {
    Serial.println("Failed to run inference: %s", tfl_status_str(status));
    while (true) {}
  }
  */

  // Get the output tensor data.
  float* outputData = malloc(5000 * sizeof(float));
  tfl_read_tensor(tflOutputTensor, outputData, 5000 * sizeof(float));
  /*
  if (status != TFL_OK) {
    Serial.println("Failed to read from output tensor: %s", tfl_status_str(status));
    while (true) {}
  }
  */

  // Print the output tensor data.
  for (int i = 0; i < 5000; i++) {
    Serial.println(outputData[i]);
  }
}