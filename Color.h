#pragma once

class Color {
private:
	unsigned char R;
	unsigned char G;
	unsigned char B;
public:
	Color(unsigned char R, unsigned char G, unsigned char B);
	unsigned char getR() { return this->R; }
	unsigned char getG() { return this->G; }
	unsigned char getB() { return this->B; }
	void changeColor(unsigned char R, unsigned char G, unsigned char B);
};