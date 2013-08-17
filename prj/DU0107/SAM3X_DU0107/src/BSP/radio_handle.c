
#include <asf.h>
#include <string.h>

// From module: FreeRTOS mini Real-Time Kernel
#include <FreeRTOS.h>
#include "task.h"
#include "status_codes.h"

#include "radio_handle.h"
#include "cc1101_radio.h"


uint8_t rPHY_Buf[64] = {0};

/**
 * \brief 
 * 
 * \param 
 * \param 
 * 
 * \return 
 */
portTASK_FUNCTION(vAppSpiTask, pvParameters)
{
	uint8_t frm[10];
	
	(void)pvParameters;
	
	Radio_Init();
	
	for(;;)
	{
		memcpy(frm, "dooya", 5);
//		Radio_Transmit(frm, 5);
		
		vTaskDelay(1000);
	}
}

/*-------------------------------------------------------------------------------------------------
 * @fn          radio_init
 *
 * @brief       Initialize radio.
 *
 * @param       none
 *
 * @return      none
 *
 */
void vStartRadioTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vAppSpiTask, (const signed portCHAR *)"SPILAUNCH",
				configMINIMAL_STACK_SIZE, NULL, uxPriority,
				(xTaskHandle *)NULL );
}

/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
void Radio_RcvHandler(void)
{
	Radio_ReadFifo();
	
	Mrfi_SpiCmdStrobe(SFRX);
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(SRX);
}
