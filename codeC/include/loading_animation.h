#ifndef LOADING_ANIMATION_H
#define LOADING_ANIMATION_H

// Function to draw the lightbulb (on or off)
void draw_bulb(int on);

// Function to draw the "Loading..." animation with dots
void draw_loading(int step);

// Constants for animation steps (number of dots to display)
#define DELAY 300000 // 300ms delay for the blinking effect

#endif // LOADING_ANIMATION_H
