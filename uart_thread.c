
#include "uart_thread.h"

void uart_buffer_create (void){
	 uart.utQueue = xQueueCreate( 1024, sizeof(char));
     if(!uart.utQueue) PLIB_USART_TransmitterByteSend(USART_ID_1, 'E');
     uart.urQueue = xQueueCreate( 1024, sizeof(char));
     if(!uart.urQueue) PLIB_USART_TransmitterByteSend(USART_ID_1, 'F');
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
	xQueueSendToBackFromISR( uart.urQueue, ( void * ) &data, (BaseType_t) 0);
}

void initializeUART(void){
    uart_buffer_create();
}

void transmitUARTstring(char *string){
    char *stringPointer;
    stringPointer = string;
    while(*stringPointer != '\0'){
            uart.transmit_char = *stringPointer;
            xQueueSendToBack( uart.utQueue, ( void * ) &uart.transmit_char, (BaseType_t) 0);
            stringPointer++;
            if(*stringPointer == '\0'){
                stringPointer = string;
                SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
                return;
            }
    }
}

//Depricated, use uart_send(char);
void transmitUARTchar(char data){
    uart_send(data);
    return;
}

void UART_Tasks(void){
    initializeUART();
    //char *temp = "Hello, this is a test. My name is Jacob and I'm a baller ass bitch." + 0;
    //transmitUARTstring(temp);
    for(;;){
        //uart_send(temp++);
        
    }
}
/*******************************************************************************
 End of File
 */