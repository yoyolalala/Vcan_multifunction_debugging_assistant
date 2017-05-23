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
	while (1)
	{      
		for (float i = 1; i < 100; i += 0.01)
		{
			float y = sin(i);
			uart.sendOscilloscope(y);
			delay_ms(1);
		}
	}
}


