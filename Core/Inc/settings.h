#ifndef SETTINGS_H
#define SETTINGS_H

// UNCOMMENT TO ENABLE DEBUGGING
//#define DEBUG_MODE

/*
 * SPECIFY THE RELEASE TYPE
 */
#define RELEASE 0       // located in ./releases/release.c
#define DEBUG 1         // located in ./releases/debug.c
#define UNIT_TEST 2     // located in ./releases/unit_test.c
#define OTHER 3         // For misc purposes. located in ./releases/entry.c

#define RELEASE_TYPE RELEASE

/*
 * SPECIFY THE DEVICE
 */
#define PLAYER1 0x02
#define PLAYER2 0x03


#define DEVICE_ID PLAYER1

// PLAYER 1 (red light)
#define WORKING_SERVO 1
// PLAYER 2 (green light)
#define BROKE_SERVO 2

#if DEVICE_ID == PLAYER2
#define SERVO_TYPE WORKING_SERVO
#endif
#if DEVICE_ID == PLAYER1
#define SERVO_TYPE BROKE_SERVO
#endif

#endif
