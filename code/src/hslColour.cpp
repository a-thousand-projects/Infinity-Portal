#include <arduino.h>

// Fast hsl2rgb algorithm: https://stackoverflow.com/questions/13105185/fast-algorithm-for-rgb-hsl-conversion
uint32_t hsl_to_rgb2(uint8_t h, uint8_t s, uint8_t l) {
	if(l == 0) return 0;

	volatile uint8_t  r, g, b, lo, c, x, m;
	volatile uint16_t h1, l1, H;
	l1 = l + 1;
	if (l < 128)    c = ((l1 << 1) * s) >> 8;
	else            c = (512 - (l1 << 1)) * s >> 8;

	H = h * 6;              // 0 to 1535 (actually 1530)
	lo = H & 255;           // Low byte  = primary/secondary color mix
	h1 = lo + 1;

	if ((H & 256) == 0)   x = h1 * c >> 8;          // even sextant, like red to yellow
	else                  x = (256 - h1) * c >> 8;  // odd sextant, like yellow to green

	m = l - (c >> 1);
	switch(H >> 8) {       // High byte = sextant of colorwheel
	 case 0 : r = c; g = x; b = 0; break; // R to Y
	 case 1 : r = x; g = c; b = 0; break; // Y to G
	 case 2 : r = 0; g = c; b = x; break; // G to C
	 case 3 : r = 0; g = x; b = c; break; // C to B
	 case 4 : r = x; g = 0; b = c; break; // B to M
	 default: r = c; g = 0; b = x; break; // M to R
	}

	return (((uint32_t)r + m) << 16) | (((uint32_t)g + m) << 8) | ((uint32_t)b + m);
}

uint32_t hsl_to_rgb(uint8_t h, uint8_t s, uint8_t l) {
	if(l == 0) return 0;

	volatile uint8_t  r, g, b, lo, c, x, m;
	volatile uint16_t h1, l1, H;
	l1 = l + 1;
	if (l < 128)    c = ((l1 << 1) * s) >> 8;
	else            c = (512 - (l1 << 1)) * s >> 8;

	H = h * 6;              // 0 to 1535 (actually 1530)
	lo = H & 255;           // Low byte  = primary/secondary color mix
	h1 = lo + 1;

	if ((H & 256) == 0)   x = h1 * c >> 8;          // even sextant, like red to yellow
	else                  x = (256 - h1) * c >> 8;  // odd sextant, like yellow to green

	m = l - (c >> 1);
	switch(H >> 8) {       // High byte = sextant of colorwheel
	 case 0 : r = c; g = x; b = 0; break; // R to Y
	 case 1 : r = x; g = c; b = 0; break; // Y to G
	 case 2 : r = 0; g = c; b = x; break; // G to C
	 case 3 : r = 0; g = x; b = c; break; // C to B
	 case 4 : r = x; g = 0; b = c; break; // B to M
	 default: r = c; g = 0; b = x; break; // M to R
	}

	return (((uint32_t)(r + m)*255) << 16) | (((uint32_t)(g + m)*255) << 8) | ((uint32_t)(b + m)*255);
}

uint32_t hsl_to_rgb2(float h, float s, float l) {
	if(l == 0) return 0;
	float r,g,b;
	float S = (float)s/100;
	float L = (float)l/100;
	float c = S*L;
	
	float x = (c * (1-abs(fmod(h/60, 2)-1)));

	//float m = (float)(L - (c /2));
	float m = L-c;

	if (h>= 0 && h < 60)   
		{r = c; g = x; b = 0;}
	else if (h>=60 && h < 120 ) 
		{r = x; g = c; b = 0;}
	else if (h>=120 && h < 180) 
		{r = 0; g = c; b = x;}
	else if (h>=180 && h < 240) 
		{r = 0; g = x; b = c;}
	else if (h>=240 && h < 300) 
		{r = x; g = 0; b = c;}
	else if (h>=300 && h < 360) 
		{r = c; g = 0; b = x;}


	uint8_t R = (r+m)*255;
    uint8_t G = (g+m)*255;
    uint8_t B = (b+m)*255;

	Serial.print("A=");Serial.print(h);

	Serial.print("\tc=");Serial.print(c,4);
	Serial.print("\tx=");Serial.print(x,4);
	Serial.print("\tm=");Serial.print(m,4);


	Serial.print("\tR=");Serial.print(R);
	Serial.print("\tG=");Serial.print(G);
	Serial.print("\tB=");Serial.println(B);

	return ((R << 16) | (G << 8) | B);
}