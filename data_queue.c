#include "data_queue.h"

void initializeDataQueue(void){
    data_queue_create();
}

void data_queue_create(void){
     data.dataQueue = xQueueCreate( 32, 22);
}
void encoder_data_send(uint32_t L, uint32_t R){
    struct data_message *pdataMessage;
    dataMessage.messageType = Encoder;
    dataMessage.left  = L;
	dataMessage.right = R;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}

void distance_data_send(uint32_t d){
    struct data_message *pdataMessage;
    dataMessage.messageType = Distance;
    dataMessage.distance = d;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void color_data_send(int8_t c){
    struct data_message *pdataMessage;
    dataMessage.messageType = Color;
    dataMessage.color = c;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}

void line_data_send(uint8_t l){
    struct data_message *pdataMessage;
    dataMessage.messageType = Line;
    dataMessage.line = l;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void motor_data_send(uint32_t speed_left, uint32_t speed_right, bool direction_left, bool direction_right){
    struct data_message *pdataMessage;
    dataMessage.messageType = Motor;
    dataMessage.speed_left = speed_left;
    dataMessage.speed_right = speed_right;
    dataMessage.direction_left = direction_left;
    dataMessage.direction_right = direction_right;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void uart_data_send_send(char * c){
    struct data_message *pdataMessage;
    dataMessage.messageType = Uart_send;
    dataMessage.uart = c;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}
void uart_data_receive_send(char * c){
    struct data_message *pdataMessage;
    dataMessage.messageType = Uart_receive;
    dataMessage.uart = c;
    pdataMessage = &dataMessage;
	xQueueSendToBack( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}

void encoder_counter_rollover_error(void){
    struct data_message *pdataMessage;
    dataMessage.messageType = Rollover_error;
    pdataMessage = &dataMessage;
	xQueueSendToBackFromISR( data.dataQueue, ( void * ) &pdataMessage, (BaseType_t) 0);
}

struct data_message * data_receive( void ){
    struct data_message *inMessage;
	if(xQueueReceive( data.dataQueue, &inMessage, portMAX_DELAY )){
        return inMessage;
    }
}

void Data_Tasks(void){
    while(!uart.ready);
    //transmitUARTstring("TaskSwitch-Success,this is proof the string can be really long\0");
    /*itoa(uart.itoa, 91, 10);
    uart.itoa[3] = '~';
    transmitUARTstring(uart.itoa);
    */
    //encoder_sensor_send(56, 98);
    
    
    uint32_t dataLeft;
    uint32_t dataRight;
    for(;;){
        struct encoder_message inDataMessage;
        if(xQueueReceive( encoder.eQueue, ( void * ) &(inDataMessage), (TickType_t) 0)){
            dataLeft = inDataMessage.left;
            dataRight = inDataMessage.right;
            char *etemp0 = "{left: \0";
            char etemp1[4];
            itoa(etemp1, dataLeft, 10);
            etemp1[3] = '\0';
            char *etemp2 = ",right: \0";
            char etemp3[4];
            itoa(etemp3, dataRight, 10);
            etemp3[3] = '\0';
            transmitUARTstring(etemp0);
            transmitUARTstring(etemp1);
            transmitUARTstring(etemp2);
            transmitUARTstring(etemp3);
            uart_send('}');
        }
    }
}
/*******************************************************************************
 End of File
 */