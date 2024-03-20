#ifndef DISPLAY_H    /* Guard against multiple inclusion */
#define DISPLAY_H


/*uint8_t cnt = 0;
uint8_t xdyd[6]={32, 120, 160, 24, 32, 24}; 
uint16_t xtyt[2];
uint16_t xt[1], yt[1];
uint8_t brojac = 0;
uint8_t ukucana_sifra[4] = {0,0,0,0};
uint8_t prava_sifra[4] = {4, 2, 3, 7};
*/


//static STATUS_t status;

void GPIO_RB15_IntHandler(GPIO_PIN pin, uintptr_t context);

void sort(uint16_t* arr, int n);

void readXY(uint16_t* x, uint16_t* y);

void kalibracija(void);

void tacka(int brojac);

void reset(void);

bool sifra( void );

#endif /* DISPLAY_H */