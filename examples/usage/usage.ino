// Copyright (c) 2018 Jidesh Veeramachaneni
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).

#include <LoopWaiter.h>

LoopWaiter<unsigned long> red_waiter(millis);
LoopWaiter<unsigned long> green_waiter(millis);
LoopWaiter<unsigned long> blue_waiter(millis);

bool red_state, green_state, blue_state = false;
uint8_t red, green, blue = 0;

void setup() {
  RGB.control(true);
  // Starts the red timer
  red_waiter.Start(1313);
  // Starts the green timer
  green_waiter.Start(1414);
  // Starts the blue timer
  blue_waiter.Start(1314);
}

void loop() {
  // Check each waiter for Expired() to return true.
  if (red_waiter.Expired()) {
    red = red_state ? 255 : 75;
    red_state = !red_state;
  }
  if (green_waiter.Expired()) {
    green = green_state ? 255 : 75;
    green_state = !green_state;
  }
  if (blue_waiter.Expired()) {
    blue = blue_state ? 255 : 75;
    blue_state = !blue_state;
  }
  RGB.color(red,green,blue);
}
