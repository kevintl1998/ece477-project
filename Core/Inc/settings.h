#ifndef SETTINGS_H
#define SETTINGS_H

// UNCOMMENT TO ENABLE DEBUGGING
#define DEBUG_MODE

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


// i2c 7-bit address
#define P1_I2C_ADDRESS 0
#define P2_I2C_ADDRESS 3

#endif
