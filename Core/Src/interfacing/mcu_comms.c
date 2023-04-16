#include "interfacing/mcu_comms.h"

#include "stm32f0xx_ll_usart.h"

#include "hardware/STM32.h"

#include "settings.h"


void handle_ack_message(void);
void handle_options_message(void);
void handle_player_ready_message(void);
void handle_player_score_message(void);
void handle_player_lives_message(void);

CommState __commState;
CommState* commState = &__commState;

// the message length of the associate message type (not including the initial message type message)
uint8_t message_lengths[] = {0, 1, 0, 4, 1};
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

#if DEVICE_ID == PLAYER1
void send_game_options(GameState* gs) {
	commState->send_buffer[1] = ((uint8_t)gs->is_multiplayer) << 4;
	commState->send_buffer[1] |= (uint8_t)gs->lives_option;
	start_send(COMM_OPTIONS);
}
#endif

void handle_ack_message(void) {
	// msg not used
}
void handle_options_message(void) {
	// only p2 should recv this message
#if DEVICE_ID == PLAYER2
	// update gameState
	uint8_t is_multiplayer = commState->recv_buffer[1] >> 4;
	uint32_t lives_option = commState->recv_buffer[1] & 0xF;
	gameState->is_multiplayer = is_multiplayer;
	gameState->lives_option = lives_option;
	gameState->lives_left = lives[lives_option];
#endif
}
void handle_player_ready_message(void) {
	// update gameState
	gameState->other_ready = 1;
}
void handle_player_score_message(void) {
	// update gameState
	// fill send buffer to send lives
}
void handle_player_lives_message(void) {
	// update gameState
	// fill send buffer to send score
}

