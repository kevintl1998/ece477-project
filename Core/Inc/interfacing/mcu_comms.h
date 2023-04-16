#ifndef MCU_COMMS_H
#define MCU_COMMS_H

#include <stdint.h>

#include "game.h"

#define COMM_FINISHED 2
#define COMM_SUCCESS 1
#define COMM_FAIL 0
#define COMM_BUFFER_NONE (uint8_t)(0-1)

#define COMM_BUFFER_SIZE 5

// message types
#define COMM_ACK		  0x00
#define COMM_OPTIONS 	  0x01
#define COMM_PLAYER_READY 0x02
#define COMM_PLAYER_SCORE 0x03
#define COMM_PLAYER_LIVES 0x04

#define COMM_MESSAGE_TYPE_COUNT 5
#define COMM_MESSAGE_TYPE_NONE (uint8_t)(0-1)

typedef struct CommState {
	uint8_t current_recv_message_type;

	uint8_t recv_buffer[COMM_BUFFER_SIZE];
	// if 0:  next uint8_t sent is the message type
	// if == (message_lengths[recv_type] + 1): message is sent. update respective gameState var
	uint8_t recv_buff_next;
	uint8_t recv_type;

	uint8_t send_buffer[COMM_BUFFER_SIZE];
	uint8_t send_buff_next;
	uint8_t send_type;
} CommState;

extern uint8_t message_lengths[];

void init_comms(void);

uint8_t recv_data(void);
uint8_t send_data(void);
void start_send(uint8_t msg_type);

void send_player_ready(void);

#if DEVICE_ID == PLAYER1
void send_game_options(GameState* gs);
#endif

#endif
