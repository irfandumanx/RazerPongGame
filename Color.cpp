#include "Color.h"

Color::Color(unsigned char R, unsigned char G, unsigned char B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

void Color::changeColor(unsigned char R, unsigned char G, unsigned char B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

