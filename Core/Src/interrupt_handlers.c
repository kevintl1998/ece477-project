


// timer 14 interrupt handler code
/*
void TIM14_IRQHandler(void) {
    TIM14->SR &= ~TIM_SR_UIF;
    uint32_t v = poll_pc12(); // poll value of pc12(button) in input data register
    if (v == 1) {
        update_pc9(0);
    } else {
        update_pc9(1);
    }
}
*/
