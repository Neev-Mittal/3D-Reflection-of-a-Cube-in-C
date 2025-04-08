#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

// Function to Reflect along the Z axis
void Reflect(int mat1[3], int result[3]) {
	
	result[0] = -mat1[0];
	result[1] = -mat1[1];
	result[2] = mat1[2];
       
}


//Bresenham Line Drawing Algorithm
void drawLine(int x1, int y1, int x2, int y2, int color) {
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	
	int sx = (x2 >= x1) ? 1 : -1;
    int sy = (y2 >= y1) ? 1 : -1;
	
	putpixel(x1, y1, color);
	if(dx < dy) 
	{
		int G = (2 * dx) - dy;
		do
		{
			if(G >= 0)
			{
				x1 = x1 + sx;
				y1 = y1 + sy;
				G = G + (2 * dx) - (2 * dy);
			}
			else
			{
				y1 = y1 + sy;
				G = G + (2 * dx);
			}
			putpixel(x1, y1, color);
		} while(y1 != y2);
	}
	else
	{
		int G = (2 * dy) - dx;
		do
		{
			if(G >= 0)
			{
				x1 = x1 + sx;
				y1 = y1 + sy;
				G = G + (2 * dy) - (2 * dx);
			}
			else
			{
				x1 = x1 + sx;
				G = G + (2 * dy);
			}
			putpixel(x1, y1, color);
		}while(x1 != x2);
	}
}


//drawing the Cube
void drawCube(int mat1[3], int color) {
	drawLine(320, 240, mat1[0] + 320, 240, color);
	drawLine(320, 240, 320, 240 - mat1[1], color);
	drawLine(mat1[0] + 320, 240, mat1[0] + 320, 240 - mat1[1], color);
	drawLine(320, 240 - mat1[1], mat1[0] + 320, 240 - mat1[1], color);
	
	drawLine(320 - mat1[2], mat1[2] + 240, 320 - mat1[2], mat1[2] + 240 - mat1[1], color);
	drawLine(320 - mat1[2], mat1[2] + 240, 320 - mat1[2] + mat1[0], mat1[2] + 240, color);
	drawLine(320 - mat1[2], mat1[2] + 240 - mat1[1], 320 - mat1[2] + mat1[0], mat1[2] + 240 - mat1[1], color);
	drawLine(320 - mat1[2] + mat1[0], mat1[2] + 240, 320 - mat1[2] + mat1[0], mat1[2] + 240 - mat1[1], color);
	
	drawLine(320 - mat1[2], mat1[2] + 240, 320, 240, color);
	drawLine(320, 240, 320 + mat1[0], 240 - mat1[1], color);
	drawLine(320 + mat1[0], 240, 320 - mat1[2] + mat1[0], mat1[2] + 240, color);
	drawLine(320, 240 - mat1[1], 320 - mat1[2], mat1[2] + 240 - mat1[1], color);
}


void drawAxes() {
	drawLine(320, 240, 600, 240, 15);
	drawLine(600, 240, 590, 230, 15);
	drawLine(600, 240, 590, 250, 15);
	outtextxy(610, 230, (char*)"+X");
	
	drawLine(320, 240, 320, 40, 15);
	drawLine(320, 40, 310, 50, 15);
	drawLine(320, 40, 330, 50, 15);
	outtextxy(310, 10, (char*)"+Y");
	
	drawLine(320, 240, 120, 440, 15);
	drawLine(120, 440, 120, 430, 15);
	drawLine(120, 440, 130, 440, 15);
	outtextxy(95, 450, (char*)"+Z");
	
	int k=1;
	for(int i=360; i<600; i = i+40){
		drawLine(i, 235, i, 245, 15);
		char num[2];
		sprintf(num, "%d", k); 
		outtextxy(i, 246, (char*)num);
		k++;
	}
	
	k=1;
	for(int i=200; i>40; i = i-40){
		drawLine(315, i, 325, i, 15);
		char num[2];
		sprintf(num, "%d", k);
		outtextxy(290, i-5, (char*)num);
		k++;
	}
	
	k=1;
	int j=280;
	for(int i=280; i>120; i = i-40){
		drawLine(i-5, j-5, i+5, j+5, 15);
		char num[2];
		sprintf(num, "%d", k);
		outtextxy(i-15, j-15, (char*)num);
		j = j + 40;
		k++;
	}
	
}

void getNumberInput(int *num, int x, int y) {
    char input[10];
    int index = 0;
    char ch;
    int isNegative = 0;

    while (1) {
        ch = getch();

        if (ch == '\r') {  // Enter key
            input[index] = '\0';
            *num = atoi(input);
            break;
        }
        else if (ch == '\b') {  // Backspace
            if (index > 0) {
                index--;
                input[index] = '\0';
                outtextxy(x + (index * 10), y, (char*)" ");
            }
            else if (index == 0 && isNegative) {
                isNegative = 0;
                input[0] = '\0';
                outtextxy(x, y, (char*)" ");
            }
        }
        else if (ch == '-' && index == 0 && !isNegative) {
            isNegative = 1;
            input[index] = ch;
            input[index + 1] = '\0';
            outtextxy(x, y, input + index);
            index++;
        }
        else if (ch >= '0' && ch <= '9' && index < 9) {
            input[index] = ch;
            input[index + 1] = '\0';
            outtextxy(x + (index * 10), y, input + index);
            index++;
        }
    }
}



int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, (char*)"");
	
	int x1len, y1len, z1len;
	
	outtextxy(200, 240, (char*)"Enter X1 Length:");
	getNumberInput(&x1len, 315, 240);
	cleardevice();
	
	outtextxy(200, 240, (char*)"Enter Y1 Length:");
	getNumberInput(&y1len, 315, 240);
	cleardevice();
	
	outtextxy(200, 240, (char*)"Enter Z1 Length:");
	getNumberInput(&z1len, 315, 240);
	cleardevice();
	
	x1len *= 40;
	y1len *= 40;
	z1len *= 40;
	
	int mat1[3] = {x1len, y1len, z1len};
	drawAxes();
	drawCube(mat1, 1);
	
	getch();
	int mat2[3];
	Reflect(mat1, mat2);
	cleardevice();
	drawAxes();
	drawCube(mat2, 2);
	
	getch();
	closegraph();
	return 0;
}