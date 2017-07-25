/* Code written by Chia Jiun Wei @ 24 Jul 2017
 * <J.W.Chia@tudelft.nl>
 
 * MB85RS256A: a library to provide high level APIs to interface  
 * with the Fujitsu FRAM. It is possible to use this library in
 * Energia (the Arduino port for MSP microcontrollers) or in 
 * other toolchains.
 
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License 
 * version 3, both as published by the Free Software Foundation.
  
 */
 
#ifndef MB85RS256A_H
#define MB85RS256A_H

#include <Energia.h>
#include <driverlib.h>
#include <DSPI.h>

// Status register
#define WPEN       0x80
#define BP1        0x08
#define BP0        0x04
#define WEL        0x02

// OP-CODE
#define WREN       0x06
#define WRDI       0x04
#define RDSR       0x05
#define WRSR       0x01
#define READ       0x03
#define WRITE      0x02

#define MEM_SIZE   0x8000	//Memory size

class FRAM

{
protected:
	DSPI &line;
	unsigned char CSpin;
	
public:
	FRAM(DSPI &spi, unsigned char pin);
	virtual ~FRAM( ) {};
		
	void init();
	void write_Enable();
	void write_Disable();
	unsigned char read_Status();
	void write_Status(char val);
	void read(unsigned int address, char *buffer, unsigned int size);
	void write(unsigned int address, char *buffer, unsigned int size);
	void erase_All();
	
private:

};

#endif	// MB85RS256A_H