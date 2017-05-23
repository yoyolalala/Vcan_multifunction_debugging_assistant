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
		for (float x = 1; x < 100; x += 0.01)
		{
			float y = sin(x);
			uart.sendOscilloscope(y);
			delay_ms(1);
		}
	}
}


