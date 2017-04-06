#include <msp430.h>
#include "timer.h"
#include "state_machine.h"
#include "buzzer.h"
#include "led.h"
#include "switches.h"

#define REACTION_TIME 40

// State transitions
static enum {START, MENU_0, MENU_1, GAME_PIANO, GAME_LED_0, GAME_LED_1, GAME_LED_2,  GAME_LED_WIN, GAME_LED_LOSE} current_state = START;
// The delay for the LED game
static short random_delay = 0;

// External buzzer state
char buzzer_state;

void state_update(){
  switch (current_state){
  case START:
    // Turn off the start-up lights
    led_set(0,0);
    // Begin playing music
    buzzer_play();

    // Change state when are are done playing music
    if(buzzer_state == STATE_BUZZER_READY)
      current_state = MENU_0;

    // Or if the user wants to skip the intro by pressing a button
    if(top_s1_state_down || top_s2_state_down || top_s3_state_down || top_s4_state_down || bottom_s1_state_down){
      // Set the next state
      current_state = MENU_0;
      // Set a delay in case they are holding down a button
      timer_set_state_transition(20);
      // Reset the buzzer to its default state
      buzzer_state = STATE_BUZZER_READY;
      buzzer_set_period(0);
    }
    
    break;
  case MENU_0:
    // Set a delay between flashes
    timer_set_state_transition(15);
    // Flash green
    led_set(0, 1);
    current_state = MENU_1;
    break;
  case MENU_1:
    // Flash red
    led_set(1, 0);

    // Check for a selected game
    if(top_s1_state_down)
      current_state = GAME_PIANO;
    else if(top_s2_state_down)
      current_state = GAME_LED_0;
    else
      current_state = MENU_0;

    break;
  case GAME_PIANO:
    // Reset the timer
    timer_set_state_transition(0);
    // Turn off the lights
    led_set(0,0);
    // Check if we want to go back to the game menu
    if(bottom_s1_state_down){
      current_state = MENU_0;
      break;
    }
    
    /* ---=== Piano Game ===--- */
    short period = 0;
    if(top_s1_state_down)
      period = 1000;
    
    if(top_s2_state_down)
      period = 1200;
    
    if(top_s3_state_down)
      period = 1400;
      
    if(top_s4_state_down)
      period = 1600;
    
    buzzer_set_period(period);
    led_set(period != 0, period == 0);
    
    break;
  
  case GAME_LED_0:
    // Start the game by clearing the LED and the buzzer
    led_set(0,0);
    buzzer_set_period(0);

    // Select a random delay for pressing
    random_delay = (short)(prand () % 400) + 50;

    // Begin the timer
    timer_start();

    // Set the next state
    current_state = GAME_LED_1;

    // Give the user a bit of time before starting the game
    // This is in case they are still holding the button
    timer_set_state_transition(25);
    break;
  case GAME_LED_1:
    // Set the state timer back to 0
    timer_set_state_transition(0);

    // Check if the random delay has passed
    if(timer_elapsed() - random_delay <= 2){
      // Set off the alarm
      led_set(1, 1);
      buzzer_set_period(1000);
      // This is where we set the reaction time
      timer_set_state_transition(REACTION_TIME);
      // Set the next state
      current_state = GAME_LED_2;
    }
    // Check if they pressed too early
    else if(top_s2_state_down)
      current_state = GAME_LED_LOSE;
    
    break;
  case GAME_LED_2:
    // Stop the alarm
    led_set(0, 0);
    buzzer_set_period(0);
    
    // Check input
    if(top_s2_state_down)
      current_state = GAME_LED_WIN;
    else
      current_state = GAME_LED_LOSE;
    
    break;
  case GAME_LED_WIN:
    // Set the green LED
    led_set(0, 1);

    // Check if we want to go back to the game menu
    if(bottom_s1_state_down)
      current_state = MENU_0;

    // Check if they want to try again
    else if(top_s4_state_down)
      current_state = GAME_LED_0;
    
    break;
  case GAME_LED_LOSE:
    // Set the red LED
    led_set(1, 0);
    
    // Check if we want to go back to the game menu
    if(bottom_s1_state_down)
      current_state = MENU_0;

    // Check if they want to try again
    else if(top_s4_state_down)
      current_state = GAME_LED_0;
    
    
    break;
  }
}
