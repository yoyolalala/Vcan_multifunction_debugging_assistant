#include "ebox.h"
#include "uart_vcan.h"
#include "math.h"
UartVscan uart(&uart1);
void setup()
{
    ebox_init();
    uart.begin(9600,1);
}
int main(void)
{
	setup();
	uint8_t x[128],y[128];
	for (int i = 0; i < 128; i++)
		 x[i]= 255*sin(float(i)/5);
	for (int i = 0; i < 128; i++)
		y[i] = 255 * sin(float(i));
	while (1)
	{
		uart.sendCCD(x, y,256);
	}
}


