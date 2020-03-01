#ifndef DRIVE
#define DRIVE

#include "hardware_ini.h"
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void seek(unsigned int cyl, unsigned int sect);
void read_sector(unsigned int cylinder, unsigned int sector,
                 unsigned char *buffer);

void write_sector(unsigned int cylinder, unsigned int sector,
                  const unsigned char *buffer);


void format_sector(unsigned int cylinder, unsigned int sector,
                   unsigned int nsector,
                   unsigned int value);

/* void format_sector(unsigned int nbcylinder, unsigned int nbsector); */

void dump_sector(unsigned int cylinder, unsigned int sector);

#endif
