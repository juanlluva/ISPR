#include "xparameters.h"
#include "xgpio.h"
#include "xil_io.h"
#include "xgpiops.h"

static XGpioPs psGpioInstancePtr;
static int iPinNumber = 7; /*Led LD9 on ZedBoard and LD4 on Zybo is connected to MIO pin 7*/

//====================================================

int main (void) 
{

      XGpio sw, led;
	  int i, pshb_check, sw_check;
	  XGpioPs_Config*GpioConfigPtr;
	  int xStatus;
	  int iPinNumberEMIO = 54;
	  u32 uPinDirectionEMIO = 0x0;
	  u32 uPinDirection = 0x1;
	
	  xil_printf("-- Start of the Program --\r\n");

	  // AXI GPIO switches Intialization
	  XGpio_Initialize(&sw, XPAR_SWITCHES_DEVICE_ID);

	  // AXI GPIO leds Intialization
	  XGpio_Initialize(&led, XPAR_LEDS_DEVICE_ID);

	  // PS GPIO Intialization
	  GpioConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	  if(GpioConfigPtr == NULL)
	    return XST_FAILURE;
	  xStatus = XGpioPs_CfgInitialize(&psGpioInstancePtr,
	      GpioConfigPtr,
	      GpioConfigPtr->BaseAddr);
	  if(XST_SUCCESS != xStatus)
	    print(" PS GPIO INIT FAILED \n\r");
	  //PS GPIO pin setting to Output
	  XGpioPs_SetDirectionPin(&psGpioInstancePtr, iPinNumber,uPinDirection);
	  XGpioPs_SetOutputEnablePin(&psGpioInstancePtr, iPinNumber,1);
	  //EMIO PIN Setting to Input port
	  XGpioPs_SetDirectionPin(&psGpioInstancePtr,
	      iPinNumberEMIO,uPinDirectionEMIO);
	  XGpioPs_SetOutputEnablePin(&psGpioInstancePtr, iPinNumberEMIO,0);

	  xil_printf("-- Press BTNR (Zedboard) or BTN3 (Zybo) to see the LED light --\r\n");
	  xil_printf("-- Change slide switches to see corresponding output on LEDs --\r\n");
	  xil_printf("-- Set slide switches to 0x0F to exit the program --\r\n");
	  
	  Xil_Out32(XPAR_MATH_IP_0_BASEADDR, 0x12);
	  Xil_Out32(XPAR_MATH_IP_0_BASEADDR+4, 0x34);
	  i=Xil_In32(XPAR_MATH_IP_0_BASEADDR);
	  xil_printf("result=%x\r\n",i);

	  while (1)
	  {
		  sw_check = XGpio_DiscreteRead(&sw, 1);
		  XGpio_DiscreteWrite(&led, 1, sw_check);
		  if ((sw_check & 0x0f) == 0xf)
			break;
	      pshb_check = XGpioPs_ReadPin(&psGpioInstancePtr,iPinNumberEMIO);
          XGpioPs_WritePin(&psGpioInstancePtr,iPinNumber,pshb_check);
		  for (i=0; i<9999999; i++); // delay loop
	   }
	
	return 0;
}
 
