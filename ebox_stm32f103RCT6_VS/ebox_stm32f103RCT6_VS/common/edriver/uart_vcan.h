#pragma once
#include "ebox.h"
int cmd;
class UartVscan
{
	Uart *uart;	
public:
	UartVscan(Uart *uartX) :
 uart(uartX)	
	{ 

	}
	//初始化
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
	void sendCCD(uint8_t  *ccdaddr,int ccdsize)
	{
	     	cmd = 2;
			uart->write(cmd);
			uart->write(~cmd);
			for(int i = 0; i < ccdsize;i++)
			 uart->write(ccdaddr[i]);
			uart->write(~cmd);
			uart->write(cmd);
	}
	void sendCCD(uint8_t  *ccdaddr, uint8_t *ccdaddr2,int ccdsize)
	{
		cmd = 2;
		uart->write(cmd);
		uart->write(~cmd);
		for (int i = 0; i < ccdsize; i++)
			uart->write(ccdaddr[i]);
		for (int i = 0; i < ccdsize; i++)
			uart->write(ccdaddr2[i]);
		uart->write(~cmd);
		uart->write(cmd);
	}


	//虚拟示波器
	template<typename T>
	T sendOscilloscope(T x)
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

	template<typename T>
	T sendOscilloscope(T *y,int n)
	{
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		union
		{
			T f;
			uint8_t c[sizeof(f)];
		}dataBuf;
		for (int m = 0; m < n; m++)
		{
			dataBuf.f = y[m];
			for (int i = 0; i < sizeof(dataBuf.f); i++)
				uart->write(dataBuf.c[i]);
		}
		uart->write(~cmd);
		uart->write(cmd);
	}
};