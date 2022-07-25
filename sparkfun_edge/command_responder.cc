/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#if defined(ARDUINO) && !defined(ARDUINO_SFE_EDGE)
#define ARDUINO_EXCLUDE_CODE
#endif  // defined(ARDUINO) && !defined(ARDUINO_SFE_EDGE)

#ifndef ARDUINO_EXCLUDE_CODE

#include "tensorflow/lite/micro/examples/micro_speech/command_responder.h"

#include "am_bsp.h"  // NOLINT


void ledBinary(tflite::ErrorReporter* error_reporter,const char* binary){
  if(binary[0] == '1'){
    am_devices_led_on(am_bsp_psLEDs, AM_BSP_LED_RED);
  }
  if(binary[1] == '1'){
    am_devices_led_on(am_bsp_psLEDs, AM_BSP_LED_BLUE);
  }
  if(binary[2] == '1'){
    am_devices_led_on(am_bsp_psLEDs, AM_BSP_LED_GREEN);
  }
  if(binary[3] == '1'){
    am_devices_led_on(am_bsp_psLEDs, AM_BSP_LED_YELLOW);
  }
}
// This implementation will light up the LEDs on the board in response to
// different commands.
void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {
  static bool is_initialized = false;
  if (!is_initialized) {
    // Setup LED's as outputs
#ifdef AM_BSP_NUM_LEDS
    am_devices_led_array_init(am_bsp_psLEDs, AM_BSP_NUM_LEDS);
    am_devices_led_array_out(am_bsp_psLEDs, AM_BSP_NUM_LEDS, 0x00000000);
#endif
    is_initialized = true;
  }


  // Turn on LEDs corresponding to the detection for the cycle
  am_devices_led_off(am_bsp_psLEDs, AM_BSP_LED_RED);
  am_devices_led_off(am_bsp_psLEDs, AM_BSP_LED_BLUE);
  am_devices_led_off(am_bsp_psLEDs, AM_BSP_LED_YELLOW);
  am_devices_led_off(am_bsp_psLEDs, AM_BSP_LED_GREEN);

  if (is_new_command) {
    TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) @%dms", found_command,
        score, current_time);
    // one
    if(found_command[0] =='o' && found_command[1] == 'n' && found_command[2] == 'e') {
      ledBinary(error_reporter,"0001"); 
    }
    // on
    else if (found_command[0] =='o' && found_command[1] =='n') {
      ledBinary(error_reporter,"1111");
    }
    // zero & off
    if (found_command[0] =='z' || (found_command[0] =='o' && found_command[1] =='f')) {
      ledBinary(error_reporter,"0000");
    }
    // two
    if (found_command[0] == 't' && found_command[1] == 'w') {
      ledBinary(error_reporter,"0010");
    }
    //three
    if (found_command[0] == 't' && found_command[1] == 'h') {
      ledBinary(error_reporter,"0011");
    }
    //four
    if (found_command[0] == 'f' && found_command[1] == 'o') {
      ledBinary(error_reporter,"0100");
    }
    //five 
    if (found_command[0] == 'f' && found_command[1] == 'i') {
      ledBinary(error_reporter,"0101");
    }
    //six
    if (found_command[0] == 's' && found_command[1] == 'i') {
      ledBinary(error_reporter,"0110");
    }
    //seven
    if (found_command[0] == 's' && found_command[1] == 'e') {
      ledBinary(error_reporter,"0111");
    }
    //eight
    if (found_command[0] == 'e' && found_command[1] == 'i') {
      ledBinary(error_reporter,"1000");
    }
    //nine
    if (found_command[0] == 'n') {
      ledBinary(error_reporter,"1001");
    }
  }
}

#endif  // ARDUINO_EXCLUDE_CODE
