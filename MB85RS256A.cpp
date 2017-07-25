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
 
#include "MB85RS256A.h"
  
/**  MB85RS256A FRAM class creator function
 *
 *   Parameters:
 *   DSPI &spi             SPI object
 *
 */
FRAM::FRAM(DSPI &spi): line(spi)
{
}

/**  Initialise FRAM
 *	 Both memory blocks and status register are initialise to be unprotected
 *
 */
void FRAM::init()
{	
	write_Disable();	
}

/**  Enable data writing in FRAM memory space
 *
 */
void FRAM::write_Enable()
{
	line.transfer(WREN); 
}

/**  Disable data writing in FRAM memory space
 *
 */
void FRAM::write_Disable()
{
	line.transfer(WRDI); 
}

/**  Returns content of FRAM status register
 *
 *	 Returns
 * 	 unsigned char         status register value
 */
unsigned char FRAM::read_Status()
{
  line.transfer(RDSR);  
  return line.transfer(0x00);
}

/**  writes in FRAM status register
 *
 *	 Parameter
 * 	 char val         status register value
 */
void FRAM::write_Status(char val)
{
  line.transfer(WRSR);
  line.transfer(val);
}

/**  reads sequential memory locations to buffer
 *
 *	 Parameters
 * 	 unsigned int address       start address
 *   char *buffer				buffer
 *   unsigned int size			total number of bytes
 *
 */
void FRAM::read(unsigned int address, char *buffer, unsigned int size)
{  
  line.transfer(READ);
  line.transfer((char)(address >> 8));
  line.transfer((char)address);
  
  for (unsigned int i = 0; i < size; i++)
    *(buffer + i) = line.transfer(0x00);
}

/**  writes to sequential memory locations from buffer
 *
 *	 Parameters
 * 	 unsigned int address       start address
 *   char *buffer				buffer
 *   unsigned int size			total number of bytes
 *
 */
void FRAM::write(unsigned int address, char *buffer, unsigned int size)
{
  line.transfer(WRITE);
  line.transfer((char)(address >> 8));
  line.transfer((char)address);

  for (unsigned int i = 0; i < size; i++)
    line.transfer(*(buffer + i));
}


/**  flush whole data memory and resets status reg
 *
 */
void FRAM::erase_All()
{  
  write_Status(0x00);
  write_Enable();
  
  line.transfer(WRITE);
  line.transfer(0x00);
  line.transfer(0x00);
  
  for(unsigned int i = 0; i <= MEM_SIZE; i++)
    line.transfer(0x00);
}
