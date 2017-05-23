#pragma once
#include "ebox.h"
uint8_t cmd;
class UartVscan
{
	Uart *uart;;
	union
	{
		float f;
		uint8_t c[4];
	}floatBuf;
	union
	{
		uint16_t j;
		uint8_t a[2];
	}uint16_tBuf;
	union
	{
		uint32_t j;
		uint8_t a[4];
	}uint32_tBuf;
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

	//·¢ËÍÍ¼ÏñÊý¾Ý
	void sendImage(uint8_t *imgaddr, uint32_t imgsize)
	{
		cmd = 1;
		uart->write(cmd);
		uart->write(~cmd);
		uart->write(imgaddr,imgsize);
		uart->write(~cmd);
		uart->write(cmd);
	}

	//·¢ËÍccd
	void sendCCD(uint8_t *ccdaddr,uint32_t ccdsize)
	{
	     	cmd = 2;
			uart->write(cmd);
			uart->write(~cmd);
			uart->write(ccdaddr, ccdsize);
			uart->write(~cmd);
			uart->write(cmd);
	}

	//ÐéÄâÊ¾²¨Æ÷
	void sendOscilloscope(float f)
	{
		floatBuf.f = f;
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		uart->write(floatBuf.c[0]);
		uart->write(floatBuf.c[1]);
		uart->write(floatBuf.c[2]);
		uart->write(floatBuf.c[3]);
		uart->write(~cmd);
		uart->write(cmd);
	}
	void sendOscilloscope(uint8_t data1)
	{
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		uart->write(data1);
		uart->write(~cmd);
		uart->write(cmd);
	}
	void sendOscilloscope(uint8_t data1,uint8_t data2)
	{
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		uart->write(data1);
		uart->write(data2);
		uart->write(~cmd);
		uart->write(cmd);
	}
	void sendOscilloscope(uint16_t data)
	{
		uint16_tBuf.j = data;
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		uart->write(uint16_tBuf.a[0]);
		uart->write(uint16_tBuf.a[1]);
		uart->write(~cmd);
		uart->write(cmd);
	}
	void sendOscilloscope(uint32_t data)
	{
		uint32_tBuf.j = data;
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		uart->write(uint32_tBuf.a[0]);
		uart->write(uint32_tBuf.a[1]);
		uart->write(uint32_tBuf.a[2]);
		uart->write(uint32_tBuf.a[3]);
		uart->write(~cmd);
		uart->write(cmd);
	}
};