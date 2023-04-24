#pragma once
#include "framework.h"
#include "Gravity.h"
#include <deque>
#include <cmath>
#define TIME 10
#define R 5
#define K 50/100
#define MAX 500
#define OGR
struct pos {
	int x;
	int y;
	bool operator==(pos& sec) {
		return (sec.x == x && sec.y == y);
	}
};
struct color {
	int r;
	int g;
	int b;
};
class planet {
private:
	double mass;
	double ux;
	double uy;
	double ax;
	double ay;
	color col;
	pos posit;
	double copx;
	double copy;
	
public:
	std::deque<pos> mas;
	planet() :mass(1.), ux(0), uy(0), ax(0), ay(0), col({ 255,255,255 }), posit({ 100,100 }), mas(),copx(posit.x),copy(posit.y) {
	}
	planet(int x, int y) :planet() {
		posit.x = x;
		posit.y = y;
		copx = x;
		copy = y;
	}
	planet(int r, int g, int b, int x, int y) :planet(x, y) {
		col.r = r;
		col.g = g;
		col.b = b;
	}
	planet(int r, int g, int b, int x, int y, double ux, double uy) :planet(r, g, b, x, y) {
		this->ux = ux;
		this->uy = uy;
	}
	planet(int r, int g, int b, int x, int y, double ux, double uy, double mass) :planet(r, g, b, x, y, ux, uy) {
		this->mass = mass;
	}
	void move() {

		if (mas.size() > MAX) {
			for (int i = 0; i < 50; ++i) {
				mas.pop_front();
			}
		}
		if (mas.size() == 0 || !(mas[mas.size() - 1] == posit)) {
			mas.push_back(posit);
		}
		copx += TIME * ux;
		copy += TIME * uy;
		ux += ax * TIME;
		uy += ay * TIME;
		ax = 0;
		ay = 0;
		posit.x = copx;
		posit.y = copy;
#ifdef OGR
		if (posit.x < 0) {
			posit.x = 1;
			ux = abs(ux) * K;
		}
		if (posit.y < 0) {
			posit.y = 1;
			uy = abs(uy) * K;
		}
		if (posit.x >= 1500) {
			posit.x = 1499;
			ux = -abs(ux) * K;
		}
		if (posit.y >= 780) {
			posit.y = 779;
			uy = -abs(uy)*K;
		}
#endif
	}
	void chmass(double k) {
		
		mass += k;
		if (mass == 0) {
			mass += k;
		}
	}
	double getmass() {
		return mass;
	}
	int massize() {
		return mas.size();
	}
	color getcol() {
		return col;
	}
	void force(planet& second, int k = 1) {
		double lenth = ((posit.x - second.posit.x) * (posit.x - second.posit.x)) + ((posit.y - second.posit.y) * (posit.y - second.posit.y));
		
		double f = k * mass * second.mass / (lenth);
		if (lenth < 50) {
			f =0;
		}
		int dx = second.posit.x - posit.x;
		int dy = second.posit.y - posit.y;
		ax += f * dx / (sqrt(lenth) * abs(mass));
		second.ax += -f*dx/(sqrt(lenth)*abs(second.mass));  ////Для 3 тел не работает
		ay += f * dy / (sqrt(lenth) * abs(mass));
		second.ay += -f * dy/ (sqrt(lenth) * abs(second.mass));
	}

	~planet() {

	}
	int getx() {
		return posit.x;
	}
	int gety() {
		return posit.y;
	}

};
void paint(HDC hdc, planet& obj);
void plan(HDC hdc);