#ifndef __SELEKWA__GLOBAL__INFO__HPP__
#define __SELEKWA__GLOBAL__INFO__HPP__

typedef struct {
	uint32_t PORTA_PINS;
	uint32_t PORTB_PINS;
	uint32_t PORTC_PINS;
	uint32_t PORTD_PINS;
	uint32_t PORTE_PINS;
} globalInfo;

globalInfo getGInfo(void) {
	globalInfo ginfo;
	ginfo.PORTA_PINS = 0x00000000;
	ginfo.PORTB_PINS = 0x00000000;
	ginfo.PORTC_PINS = 0x00000000;
	ginfo.PORTD_PINS = 0x00000000;
	ginfo.PORTE_PINS = 0x00000000;
	return ginfo;
}

#endif // __SELEKWA__GLOBAL__INFO__HPP__
