
unsigned long reflect (unsigned long crc, int bitnum);
void generate_crc_table();
unsigned long crctablefast (unsigned char* p, unsigned long len);
unsigned long crctable (unsigned char* p, unsigned long len);
unsigned long crcbitbybit(unsigned char* p, unsigned long len);
unsigned long crcbitbybitfast(unsigned char* p, unsigned long len);
unsigned long crc_ccitt(unsigned char* p, unsigned long len);