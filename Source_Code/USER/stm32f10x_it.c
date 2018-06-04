/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "gps.h"
#include "oled.h"
#include <stdio.h>

extern void TimingDelay_Decrement(void);

char   rev_buf[80];        //���ջ���
u8  rev_start = 0;         //���տ�ʼ��־
u8  rev_stop  = 0;         //���ս�����־
u8  gps_flag = 0;          //GPS�����־
u8  change_page = 0;       //��ҳ��ʾ��־
u8  num = 0;               //
int numtx=0;

GPS_INFO   GPS;

int txd_buf[50];
u8 test[4]={1,2,3,4};
u8 error_num = 0;
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */

/******************************************************************************/
/*                ����1�����ж��ӳ���                                         */
/******************************************************************************/
void USART1_IRQHandler(void)
{
  u8 ch;
	
	
	
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)    //�жϽ������ݼĴ�������־  
  {     
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);         //���жϱ�־λ
    ch = USART_ReceiveData(USART1);   
        
    if ((ch == '$') && (gps_flag == 0))                    //������յ�����'$'�ַ����㿪ʼ����
    {
      rev_start = 1;
      rev_stop  = 0;
    }
    
    if (rev_start == 1)                                    //���տ�ʼ��־λ1����ʼ����
    {
      rev_buf[num++] = ch;                                 //�ַ��浽����������
      if (ch == '\n')                                      //������յ������ַ�
      {
        USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);      //�ر�USART1�����ж�
        rev_buf[num] = '\0';
        rev_start = 0;
        rev_stop  = 1;
        gps_flag = 1;
        num = 0;
        
        if (rev_stop)                                      //���������һ��
        {
   
          if (GPS_RMC_Parse(rev_buf, &GPS))                 //����GPRMC
          {
            error_num = 0;
            gps_flag = 0;
            rev_stop  = 0;
          }
          else
          {
            error_num++;
            if (error_num >= 20)                            //�����Ч���ݳ���20��
            {
              error_num = 20;
							
            }
            gps_flag = 0;
            rev_stop  = 0;
          }
					/*
					
					if (GPS_GSV_Parse(rev_buf, &GPS))                 //����GPGSV
          {
            error_num = 0;
            gps_flag = 0;
            rev_stop  = 0;
          }
          else
          {
            error_num++;
            if (error_num >= 20)                            //�����Ч���ݳ���20��
            {
              error_num = 20;
							
            }
            gps_flag = 0;
            rev_stop  = 0;
          }
					
					if (GPS_GGA_Parse(rev_buf, &GPS))                //����GPGGA
          {
            error_num = 0;
            gps_flag = 0;
            rev_stop = 0;
          }
          else
          {
            error_num++;
            if (error_num >= 20)                           //�����Ч���ݳ���20��
            {
              error_num = 20;
							
            }
            gps_flag = 0;
            rev_stop = 0;
          }*/
					
					
        }

				USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
        }
      }
    }                              			   
  }



void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
