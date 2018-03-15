#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>
#include "stdint.h"

typedef struct
{
    QueueHandle_t eQueue;
    QueueHandle_t encoderReady;
    uint32_t int_right;
    uint32_t int_left;
} ENCODER_QUEUE_DATA;

ENCODER_QUEUE_DATA encoder;

struct encoder_message
    {
        uint32_t left;
		uint32_t right;
    } eMessage;


void encoder_queue_create(void);
void encoder_sensor_send(uint32_t L, uint32_t R); 
void calculate_encoder_val(void);
struct encoder_message * encoder_sensor_receive( void );
void initializeEncoder(void);
void Encoder_Tasks(void);