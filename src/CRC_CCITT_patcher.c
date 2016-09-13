// Copyright Thomas Herpoel 2016
//
// This file is part of BaseI6_updater
//
// BaseI6_updater is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FSi6_updater is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../inc/crctester.h"

#define BEGIN_OFFSET 0x0

//int     crc_ok = 0x470F;
bool verbose = false;
bool bootloader = false;

int main(int argc,char *argv[])
{
	
		unsigned short crc_offset=0;
		unsigned short payload_size=0;
		FILE* file = NULL;
		//char filename[] = "test.bin";
		//char filename[] = "fsi6_patch2_lock.bin";
		char* filename = argv[1];
		for(int i = 2; i< argc ; i++) {
			if(strcmp(argv[i],"-v")==0) {
				verbose=true;
			}
			if(strcmp(argv[i],"-b")==0) {
				bootloader=true;
			}
		}
	if(verbose) {
		printf("_____BaseI6 CRC patcher_____\r\n");
		printf("Opening file:\t%s\t",filename);
	}
	
	file = fopen(filename, "rb+"); //read and write
	if(file==NULL) {
		if(verbose) printf("[ERROR] File not found\r\n");
		return -1;
	}
	if(verbose) printf("[OK]\r\n");
	
	int beginOffset = 0;
	
	if(bootloader) beginOffset = 0x1800;
		
	fseek(file,0x0F88+beginOffset,0);
	payload_size = fgetc(file);
	payload_size = payload_size + (fgetc(file)<<8);
	crc_offset = payload_size + beginOffset;
	if(verbose) printf("Payload size:\t[0x%X]\r\n",payload_size);
	if(verbose) printf("CRC offset:\t[0x%X]\r\n",crc_offset);
		
	unsigned char payload[payload_size];
	
	fseek(file,beginOffset,SEEK_SET);
	fread(payload,payload_size,1,file);


	if(verbose) printf("CRC:\t\t");
	//unsigned short CRC = crc16(payload,sizeof(payload));
	//printf("sizeof:0x%X _size:0x%X",sizeof(payload),payload_size);
	unsigned short CRC = crc_ccitt(payload,sizeof(payload));
	if(verbose) printf("[0x%X]\r\n",CRC);
	if(verbose) printf("Patching:\t");
	fseek(file,crc_offset,0);
	
	fputc((unsigned char)(CRC&0x00FF),file);
	fputc((unsigned char)((CRC&0xFF00)>>8),file);
	if(verbose) printf("[OK]\r\n");
	
	fclose(file);
	
	if(verbose) puts("Press ENTER to quit...\r\n");
	if(verbose) getchar();
		
	return 0;	
}