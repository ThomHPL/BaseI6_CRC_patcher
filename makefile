CC := gcc

all:
	@$(CC) -std=c99 src/CRC_CCITT_patcher.c src/crctester.c inc/crctester.h -o bin/BaseI6_CRC_patcher.exe