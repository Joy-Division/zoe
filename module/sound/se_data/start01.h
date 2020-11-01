#ifndef INCLUDED_START01_H
#define INCLUDED_START01_H

u_char start0100[] = {
#if defined(BORMAN_DEMO) || defined(DENGEKI_DEMO)
	0x00,0x01,0x7E,0xD0,0x00,0x00,0xC8,0xD5,
	0x00,0x00,0x2B,0xF6,0x00,0x00,0x14,0xD2,
	0x05,0x04,0x7F,0xD7,0x00,0x00,0x00,0xD8,
	0x00,0x00,0x12,0xD9,0x30,0x63,0x02,0x38,
	0x50,0x63,0x01,0x3C,0x05,0x04,0x5A,0xD7,
	0x00,0x00,0x50,0xD8,0x00,0x00,0x12,0xD9,
	0x48,0x32,0x0B,0x3E,0x18,0x32,0x07,0xF2,
	0x10,0x32,0x0B,0x3E,0x18,0x32,0x07,0xF2,
	0x08,0x32,0x0B,0x3E,0x00,0x00,0xFE,0xFF
#else
	0x00,0x01,0x7E,0xD0,0x00,0x00,0xB4,0xD5,
	0x00,0x00,0x2B,0xF6,0x00,0x00,0x14,0xD2,
	0x05,0x04,0x7F,0xD7,0x00,0x00,0x00,0xD8,
	0x00,0x00,0x12,0xD9,0x24,0x63,0x00,0xDF,
	0x24,0x63,0x02,0x38,0x3C,0x63,0x01,0x3C,
	0x05,0x04,0x5A,0xD7,0x00,0x00,0x50,0xD8,
	0x00,0x00,0x12,0xD9,0x36,0x32,0x0B,0x3E,
	0x18,0x32,0x07,0xF2,0x0C,0x32,0x0B,0x3E,
	0x18,0x32,0x07,0xF2,0x06,0x32,0x0B,0x3E,
	0x00,0x00,0xFE,0xFF
#endif
};

u_char start0101[] = {
#if defined(BORMAN_DEMO) || defined(DENGEKI_DEMO)
	0x00,0x01,0x7E,0xD0,0x00,0x00,0xC8,0xD5,
	0x00,0x00,0x2B,0xF6,0x00,0x00,0x13,0xD2,
	0x05,0x04,0x7F,0xD7,0x00,0x00,0x00,0xD8,
	0x00,0x00,0x12,0xD9,0x40,0x63,0x02,0x2C,
	0x58,0x63,0x01,0x3C,0x05,0x04,0x5A,0xD7,
	0x00,0x00,0x50,0xD8,0x00,0x00,0x12,0xD9,
	0x48,0x32,0x0B,0x3E,0x18,0x32,0x07,0xF2,
	0x10,0x32,0x0B,0x3E,0x18,0x32,0x07,0xF2,
	0x08,0x32,0x0B,0x3E,0x00,0x00,0xFE,0xFF
#else
	0x00,0x01,0x7E,0xD0,0x00,0x00,0xB4,0xD5,
	0x00,0x00,0x2B,0xF6,0x00,0x00,0x13,0xD2,
	0x05,0x04,0x7F,0xD7,0x00,0x00,0x00,0xD8,
	0x00,0x00,0x12,0xD9,0x40,0x63,0x02,0x2C,
	0x58,0x63,0x01,0x3C,0x05,0x04,0x5A,0xD7,
	0x00,0x00,0x50,0xD8,0x00,0x00,0x12,0xD9,
	0x48,0x32,0x0B,0x3E,0x18,0x32,0x07,0xF2,
	0x10,0x32,0x0B,0x3E,0x18,0x32,0x07,0xF2,
	0x08,0x32,0x0B,0x3E,0x00,0x00,0xFE,0xFF
#endif
};

#endif /* END OF FILE */
