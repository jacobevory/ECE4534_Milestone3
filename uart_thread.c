
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
    BaseType_t pxHigerPriorityTaskWoken=pdFalse;
    if( xQueueReceiveFromISR( uart.utQueue, &uart.transmit_char, &pxHigerPriorityTaskWoken ) );
    return uart.transmit_char;
}

void uart_send_to_receive_queue(char data){
	xQueueSendToBackFromISR( uart.urQueue, ( void * ) &data, (BaseType_t) 0);
}

void initializeUART(void){
    uart_buffer_create();
}

void transmitUARTstring(const char *string){
    const char *stringPointer;
    stringPointer = string;
    while(*stringPointer == '\0'){
        uart_send(*stringPointer);
        stringPointer++;
            if(*stringPointer == '\0'){
                stringPointer = string;
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
    //PLIB_USART_TransmitterByteSend(USART_ID_1, 'G');
    char temp;
    for(;;){
        uart_send(temp++);
        //uart_send('A');
        //SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
        //uart.transmit_char = UART_TRANSMIT_MESSAGE->data;
        
    }
}
/*******************************************************************************
 End of File
 */