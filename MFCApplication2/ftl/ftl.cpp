
#include "pch.h"
#include "ftl.h"



u8 storage_1m[ 2 * SECTOR_SIZE * 1024] = { 0 };



void lbaWrite(u32 lba, u8 secLen, u8* writeBuf) {
	//assert(lba < 2048);
	for (u32 i = 0; i < secLen * SECTOR_SIZE; i++) {
		storage_1m[i + lba] = writeBuf[i];
	}
}

void lbaRead(u32 lba, u8 secLen, u8* readBuf) {
	//assert(lba < 2048);
	for (u32 i = 0; i < secLen * SECTOR_SIZE; i++) {
		readBuf[i] = storage_1m[i + lba];
	}
}