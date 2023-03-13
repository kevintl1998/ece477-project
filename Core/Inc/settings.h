#ifndef SETTINGS_H
#define SETTINGS_H

/*
 * SPECIFY THE RELEASE TYPE
 */
#define RELEASE 0       // ./releases/release.c
#define DEBUG 1         // ./releases/debug.c
#define UNIT_TEST 2     // ./releases/unit_test.c
#define OTHER 3         // For misc purposes

#define RELEASE_TYPE UNIT_TEST

/*
 * SPECIFY THE DEVICE
 */
#define PLAYER1 0x02
#define PLAYER2 0x03

#define DEVICE_ID PLAYER2


// i2c 7-bit address
#define P1_I2C_ADDRESS 0
#define P2_I2C_ADDRESS 3

#endif
