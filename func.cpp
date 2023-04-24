
#include "Header.h"



void circle(HDC hdc,planet& obj) {
	
	HBRUSH hBrush = CreateSolidBrush(RGB(obj.getcol().r, obj.getcol().g, obj.getcol().b));
	// Сохраняем старую кисть
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	
	Ellipse(hdc, obj.getx() - R, obj.gety() - R, obj.getx() + R, obj.gety() + R);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	

}
void plan(HDC hdc) {
	RECT size = { 0,0,1600,1000 };
	HBRUSH bruh = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hdc, &size, bruh);
	DeleteObject(bruh);
}
void paint(HDC hdc,planet& obj) {
	
	circle(hdc, obj);
	int size = obj.mas.size();
	
	color col = obj.getcol();
	
	for (int i = 0; i < size; ++i) {
		
		SetPixel(hdc, obj.mas[i].x,obj.mas[i].y,RGB(col.r,col.g,col.b) );
	}
}