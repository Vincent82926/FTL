typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long long u64;

#define SECTOR_SIZE 512

	void lbaWrite(u32 lba, u8 len, u8* writeBuf);
	void lbaRead(u32 lba, u8 len, u8* writeBuf);

