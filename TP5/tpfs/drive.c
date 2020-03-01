#include "drive.h"

/** Permet de deplacer la tete de lecture vers un secteur **/
void seek(unsigned int cyl, unsigned int sect)
{
	_out(HDA_DATAREGS, cyl>>8);
	_out(HDA_DATAREGS + 1, cyl&0xFF);
	_out(HDA_DATAREGS + 2, sect>>8);
	_out(HDA_DATAREGS + 3, sect&0xFF);
	_out(HDA_CMDREG, CMD_SEEK);
	_sleep(HDA_IRQ);
}


/** Permet la lecture d'un secteur **/
void read_sector(unsigned int cylinder, unsigned int sector,
                 unsigned char *buffer)
{
	int i;
	seek(cylinder,sector);
	_out(HDA_DATAREGS,0);
	_out(HDA_DATAREGS + 1,1);
	_out(HDA_CMDREG, CMD_READ);
	_sleep(HDA_IRQ);
	for(i=0;i<HDA_SECTORSIZE;i++)
	{
		buffer[i]=MASTERBUFFER[i];
	}	

}

/** Permet l'ecriture du contenu d'un secteur **/
void write_sector(unsigned int cylinder, unsigned int sector,
                  const unsigned char *buffer)
{
	int i;
	seek(cylinder,sector);
	_out(HDA_DATAREGS,0);
	_out(HDA_DATAREGS + 1,1);
	for(i=0;i<HDA_SECTORSIZE;i++)
	{
		MASTERBUFFER[i]=buffer[i];
		putchar(MASTERBUFFER[i]);
	}
	_out(HDA_CMDREG, CMD_WRITE);
	_sleep(HDA_IRQ);
}

/** Permet de formater un secteur **/
void format_sector(unsigned int cylinder, unsigned int sector,
                   unsigned int nsector,
                   unsigned int value)

{
	seek(cylinder,sector);
	_out(HDA_DATAREGS, (nsector>>8)&0xFF);
	_out(HDA_DATAREGS + 1, nsector&0xFF);

	_out(HDA_DATAREGS + 2, (value>>24)&0xFF);
	_out(HDA_DATAREGS + 3, (value>>16)&0xFF);
	_out(HDA_DATAREGS + 4, (value>>8)&0xFF);
	_out(HDA_DATAREGS + 5, value&0xFF);
	_out(HDA_CMDREG, CMD_FORMAT);
	_sleep(HDA_IRQ);
}

/** Permet de formater tt le disque
void format_sector(unsigned int nbcylinder, unsigned int nbsector)
{
	int i,j;
	for(i=0;i<nbcylinder;i++)
		for(j=0;j<nbsector;j++)
			format_onesSector(i,j,nbsector,0);
}
 **/

/** Permet d'afficher le contenu d'un secteur **/
void dump_sector(unsigned int cylinder, unsigned int sector)
{
	int i;
	seek(cylinder,sector);
	_out(HDA_DATAREGS,0);
	_out(HDA_DATAREGS + 1,1);
	_out(HDA_CMDREG, CMD_READ);
	_sleep(HDA_IRQ);
	for(i=0;i<HDA_SECTORSIZE;i++)
	{
		putchar(MASTERBUFFER[i]);
	}	
}








