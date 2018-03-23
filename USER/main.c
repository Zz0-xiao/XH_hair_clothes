#include "delay.h"
#include "timer.h"
#include "rs232.h"
#include "utility.h"
#include "motor.h"
#include "sensor.h"
#include "rs3485.h"

#include "communication.h"

// TIM14,TIM16 PWM 频率设定
#define INIHz 1000

HAL_StatusTypeDef Protocol_Process(uint8_t* pbuff);

HAL_StatusTypeDef processResult = HAL_INI;


void ResultSend(uint8_t* pbuff, HAL_StatusTypeDef result);
void Main_Process(void);
void Reset(void);
void MotorTime(void);

uint8_t rs485buf[5]  ;
//uint8_t rs485buf3[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

static void IWDG_Config(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    IWDG_SetReload(2000 * 40 / 256); //2s
    IWDG_ReloadCounter();
    IWDG_Enable();
}

int main(void)
{

//    uint16_t cmdr;
    Delay_init();

    TIM3_Initial();
    TIM14_Initial(INIHz);
    TIM16_Initial(INIHz);
//    UART_TransmitData_API(USART1, "XH-Wardrobe-V2.5", 0, SENDNOPROTOCOL);
//    IWDG_Config();

    SENSOR_Init();
    Motor_Init();

    RS232_Init(UART1BUAD);
    RS485_Init(UART2BUAD);

    RS485_Send_Data("XH-Wardrobe-V2.5", 0);

    while (1)
    {
//        if(UART2Time_1ms > 30)
//        {
//            UART2Time_1ms = 1;
            Protocol_Process(UART2RevData);
//            UART2RXDataLenth = 0;
//        }
			
			
//#ifdef USE_UART2
//        if(UART2Time_1ms > 30)
//        {
//            UART2Time_1ms = 1;
////            RS485_Send_Data("XH-Wardrobe-V2.5", 0);
//            processResult = CheckProtocol(RS485, UART2RevData);

//            if(processResult == HAL_OK)
//            {
//                processResult = Protocol_Process(UART2RevData);//协议处理函数
//            }
//            else
//                processResult = HAL_BUSY;
//            UART2RXDataLenth = 0;

//            BuffReset_API(UART2RevData, MAXCOMSIZE);
//        }
//#endif
    }
}

/*******************************
名称：Protocol_Process(uint8_t* pbuff,);
功能：协议处理函数
参数：协议数据缓存区pbuff
返回：处理结果，可以在communication.h中添加
*******************************/
//const uint32_t DEV_ID = 0xffffffff;//初始必须为ffffffff,否则写入不成功
//53 44 73 45 73 00 00 00 09 21 01 ff ff 04 00 2a 82 da
HAL_StatusTypeDef Protocol_Process(uint8_t* pbuff)
{
    HAL_StatusTypeDef processResult;
    uint16_t cmdr;

//    cmdr = ((uint16_t)pbuff[9] << 8) + pbuff[10];
    cmdr = pbuff[1];
    switch(cmdr)
    {
    case 0x01:
        RS485_Send_Data("111", 0);
        break;
    case 0x02:
        RS485_Send_Data("222", 0);
        break;
    case 0x03:
        RS485_Send_Data("333", 0);
        break;
    case 0x2011:
        RS485_Send_Data("444", 0);
        break;
    case 0x2018:
        RS485_Send_Data("555", 0);
        break;
    default:
        break;
    }
    return processResult;
}


/*******************************
名称：ResultSend(uint8_t* pbuff, uint16_t buffSize)
功能：流程结果上传
参数：pbuff 接收缓冲区，用于非神思协议上传回复命令，result 结果
返回：null
*******************************/
//void ResultSend(uint8_t* pbuff, HAL_StatusTypeDef result)
//{
//		uint8_t dataSDSES[10];
//	  if(motorErrorFlag != MOTOR_OK)
//		{
//			UART_TransmitData_API(USART1,"57MOTOR ERROR",0,SENDNOPROTOCOL);
//			MotorDrive57(MOTORV,MOTOR_STOP);
//			MotorDrive57(MOTORH,MOTOR_STOP);
//			return;
//		}
//		if(result == HAL_ERROR)
//		{
//			UART_TransmitData_SDSES(USART1,0,0xA100,OPFAILED,"");
//		}
//		if(result == HAL_OK)
//		{
//			UART_TransmitData_SDSES(USART1,0,0xA100,OPSUCCESS,"");
//		}
//		if(result == HAL_TIMEOUT)//电机运作超时
//		{
//			motorErrorFlag = MOTOR_OK;
//			MotorDrive57(MOTORV,MOTOR_STOP);
//			MotorDrive57(MOTORH,MOTOR_STOP);
//			dataSDSES[0]=0x02;
//			UART_TransmitData_SDSES(USART1,1,0xA100,OPFAILED,dataSDSES);
//		}
//		if(result == HAL_DCTIMEOUT)
//		{
//			dataSDSES[0] = 0x01;//无货
//			UART_TransmitData_SDSES(USART1,1,0xA100,OPFAILED,dataSDSES);
//		}
//		if(result == HAL_CRCERROR)
//			UART_TransmitData_API(USART1,"CRC ERROR",0,SENDNOPROTOCOL);
//		if(result == HAL_BUSY)
//			UART_TransmitData_API(USART1,"ERROR BUSY",0,SENDNOPROTOCOL);
//
//		cV = 0;
//}


