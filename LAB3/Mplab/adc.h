#ifndef __adc_h_
#define	__adc_h_
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
void configura_adc();
uint8_t LecturaADC(uint8_t x);
#endif
