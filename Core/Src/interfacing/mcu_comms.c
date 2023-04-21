#include "interfacing/mcu_comms.h"

#include "stm32f0xx_ll_usart.h"

#include "hardware/STM32.h"

#include "settings.h"


void handle_ack_message(void);
void handle_options_message(void);
void handle_player_ready_message(void);
void handle_player_score_message(void);
void handle_player_lives_message(void);

volatile CommState __commState;
CommState* commState = &__commState;


// arrays to provide easy relation of message type to various data about them (message number is the index)
// the message length of the associate message type (not including the initial message type message)
uint8_t message_lengths[] = {0, 1, 0, 4, 1};
// message handler functions for the associated message type
void (*message_handler[])() = { handle_ack_message, handle_options_message, handle_player_ready_message, handle_player_score_message, handle_player_lives_message };


void init_comms(void) {
	init_tim17();
}

uint8_t recv_data(void) {
	if(USART1->ISR & USART_ISR_RXNE) { // if there is data to recv
		commState->recv_buffer[commState->recv_buff_next++] = LL_USART_ReceiveData8(USART1);
		if(commState->recv_buff_next == 1) { // if this is new data being sent
			commState->recv_type = commState->recv_buffer[0];
		}
		if(commState->recv_buff_next == (message_lengths[commState->recv_type] + 1)) {	// check if current data is done being received
			// if current data is done being received
			// update the respective gameState variable(s)
			(message_handler[commState->recv_buffer[0]])();
			// reset recv type
			commState->recv_type = COMM_MESSAGE_TYPE_NONE;
			// reset recv buffer
			commState->recv_buff_next = 0;
			return COMM_FINISHED;
		}
		return COMM_SUCCESS;
	}
	return COMM_FAIL;
}

uint8_t send_data(void) {
	if(commState->send_type != COMM_MESSAGE_TYPE_NONE) { // if buffer has data to send
		if(USART1->ISR & USART_ISR_TXE) { // if can send data
			LL_USART_TransmitData8(USART1, commState->send_buffer[commState->send_buff_next++]);
			if(commState->send_buff_next == (message_lengths[commState->send_type] + 1)) { // if current data is done being sent
				// reset send type
				commState->send_type = COMM_MESSAGE_TYPE_NONE;
				// reset send buffer
				commState->send_buff_next = 0;
				return COMM_FINISHED;
			}
			return COMM_SUCCESS;
		}
	}
	return COMM_FAIL;
}

void start_send(uint8_t msg_type) {
	commState->send_buffer[0] = msg_type;
	commState->send_type = msg_type; // must be filled last because the interrupt checks this var to start sending data
}

void send_player_ready(void) {
	start_send(COMM_PLAYER_READY);
}

void send_game_options(GameState* gs) {
	commState->send_buffer[1] = ((uint8_t)gs->gameMode) << 4;
	commState->send_buffer[1] |= (uint8_t)gs->lives_option;
	start_send(COMM_OPTIONS);
}

void send_score(GameState* gs) {
	commState->send_buffer[1] = (gs->score >> (8 * 3)) & 0xFF;
	commState->send_buffer[2] |= (gs->score >> (8 * 2)) & 0xFF;
	commState->send_buffer[3] |= (gs->score >> (8 * 1)) & 0xFF;
	commState->send_buffer[4] |= (gs->score >> (8 * 0)) & 0xFF;
	start_send(COMM_PLAYER_SCORE);
}

void send_lives(GameState* gs) {
	commState->send_buffer[1] = gs->lives_left;
	start_send(COMM_PLAYER_LIVES);
}

void handle_ack_message(void) {
	// msg not used
}
void handle_options_message(void) {
	// only p2 should receive this message
#if DEVICE_ID == PLAYER2
	// update gameState
	uint8_t gameMode = commState->recv_buffer[1] >> 4;
	uint32_t lives_option = commState->recv_buffer[1] & 0xF;
	gameState->gameMode = gameMode;
	gameState->lives_option = gameState->gameMode ? lives_option : 0;
	gameState->lives_left = lives[lives_option];
#endif
}
void handle_player_ready_message(void) {
	// update gameState
	gameState->other_ready = 1;
}
void handle_player_score_message(void) {
	// update gameState
	uint32_t score = 0;
	score |= commState->recv_buffer[1] << (8 * 3);
	score |= commState->recv_buffer[2] << (8 * 2);
	score |= commState->recv_buffer[3] << (8 * 1);
	score |= commState->recv_buffer[4] << (8 * 0);
	gameState->other_score = score;
#if DEVICE_ID == PLAYER2
	// player 2 responds to player 1 with their score
	send_score(gameState);
#endif

}
void handle_player_lives_message(void) {
	// update gameState
	gameState->other_lives = commState->recv_buffer[1];
#if DEVICE_ID == PLAYER2
	// player 2 responds to player 1 with their life count
	send_lives(gameState);
#endif
}

