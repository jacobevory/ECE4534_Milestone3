
#include "uart_thread.h"

void uart_buffer_create (void){
	 uart.utQueue = xQueueCreate( 256, sizeof(char));
     uart.urQueue = xQueueCreate( 1024, sizeof(char));
}

void uart_send(char data){
    uart.transmit_char = data;
	xQueueSendToBack( uart.utQueue, ( void * ) &uart.transmit_char, (BaseType_t) 0);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
}

char uart_receive(void){
    
    if(uxQueueMessagesWaiting( uart.urQueue )){
        if( xQueueReceive( uart.urQueue, &uart.receive_char, portMAX_DELAY ) ){
            return uart.receive_char;
        }
    }
    return 0;
}

char uart_receive_from_transmit_queue(void){
    if( xQueueReceiveFromISR( uart.utQueue, &uart.transmit_char, pdFALSE ) );
    return uart.transmit_char;
}

void uart_send_to_receive_queue(char data){
	xQueueSendToBackFromISR( uart.urQueue, ( void * ) &data, (TickType_t) 0);
}

void initializeUART(void){
    uart_buffer_create();
}

void transmitUARTstring(char *string){
    char *stringPointer;
    stringPointer = string;
    while(*stringPointer != '\0'){
            uart.transmit_char = *stringPointer;
            xQueueSend( uart.utQueue, ( void * ) &uart.transmit_char, (TickType_t) 0);
            stringPointer++;
           
    }
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
}

//Depricated, use uart_send(char);
void transmitUARTchar(char data){
    uart_send(data);
    return;
}



void UART_Tasks(void){
    /*
    uart.ptr = "Test#4 yes please: ";
    transmitUARTstring(uart.ptr);
    itoa(uart.itoa, 912, 10);
    transmitUARTstring(uart.itoa);
    */
    uart.ready = true;
    for(;;){
        //uart_send(temp++);
    }
}
/*******************************************************************************
 End of File
 */