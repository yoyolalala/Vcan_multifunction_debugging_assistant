#pragma once
#include "ebox.h"
#include <stdarg.h>
uint8_t cmd;
class UartVscan
{
	Uart *uart;;
public:
	UartVscan(Uart *uartX) :
		uart(uartX)
	{

	}
	void begin(uint32_t baud_rate, uint8_t data_bit, uint8_t parity, float stop_bit, uint8_t _use_dma)
	{
		uart->begin(baud_rate, data_bit, parity, stop_bit, _use_dma);
	}
	void begin(uint32_t baud_rate, uint8_t _use_dma /*= 1*/)
	{
		uart->begin(baud_rate, _use_dma);
	}

	//发送图像数据
	void sendImage(uint8_t *imgaddr, uint32_t imgsize)
	{
		cmd = 1;
		uart->write(cmd);
		uart->write(~cmd);
		uart->write(imgaddr,imgsize);
		uart->write(~cmd);
		uart->write(cmd);
	}

	//发送ccd
	void sendCCD(uint8_t *ccdaddr,uint32_t ccdsize)
	{
	     	cmd = 2;
			uart->write(cmd);
			uart->write(~cmd);
			uart->write(ccdaddr, ccdsize);
			uart->write(~cmd);
			uart->write(cmd);
	}
	//虚拟示波器
	template<typename T>
	T sendOscilloscope(T x, ...)
	{
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		union
		{
			T f;
			uint8_t c[sizeof(f)];
		}dataBuf;
		dataBuf.f = x;
		for (int i = 0; i < sizeof(x); i++)
			uart->write(dataBuf.c[i]);
		uart->write(~cmd);
		uart->write(cmd);
	}

	//虚拟示波器
	//template<typename T>
	//T sendOscilloscope(T x, ...)
	//{
	//	T next = 0;
	//	va_list ap;
	//	va_start(ap, x);
	//	cmd = 3;
	//	uart->write(cmd);
	//	uart->write(~cmd);
	//	for (int i = 0; i < x; i++)
	//	{   
	//		next=va_arg(ap, T);
	//		union
	//		{
	//			T f;
	//			uint8_t c[sizeof(f)];
	//		}dataBuf;
	//		dataBuf.f = next;
	//		for (int i = 0; i < sizeof(next); i++)
	//			uart->write(dataBuf.c[i]);
	//	}
	//	uart->write(~cmd);
	//	uart->write(cmd);
	//	va_end(ap);
	//}
};