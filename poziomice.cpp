#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
int n = 25; /*liczba poziomic*/
float minx = 0;
float maxx = 6.29;
float miny = 0;
float maxy = 6.29; /*jaki przedzial x, y*/
float funkcja(float x1, float y1){ /*bedziemy rysowac warstwice tej funkcji, przeskalowanie współrzędnych*/
	float x = x1;
	float y = y1;
	if(maxy - miny > maxx - minx){
		x = (maxy - miny)/400.00000 *x1 + minx; /*(maxy - miny) a nie (maxx - minx) bo chcemy Ox i Oy przeskalowac tak samo*/
		y = (maxy - miny)/400.00000 *y1 + miny;
	}
	else {
		x = (maxx - minx)/400.00000 *x1 + minx;
		y = (maxx - minx)/400.00000 *y1 + miny;
	}
	return sin(x)*sin(y); /*jakafunkcja*/
}

float minimum(void){  /*przedzal x: [0, 400], znajdowanie minimum funkcji*/
	float mini = 10000;
	int x;
	for(x=0; x<400; x++){
		int y;
		for(y=0; y<400; y++){
			float a = funkcja(x, y);

			if(a < mini)
				mini = a;
		}
	}
	return mini;
}
float mini = minimum();
float maximum(void){ /*przedzal x: [0, 400], znajdowanie maksimum funkcji*/
	float maxi = -10000;
	int x;
	for(x=0; x<400; x++){
		int y;
		for(y=0; y<400; y++){
			float a = funkcja(x, y);
			if(a > maxi)
				maxi = a;
		}
	}
	return maxi;
}
float maxi = maximum();


int main()
{

	/*int n= 100;   ile poziomic*/
	float wartosci[n]; /*przedzial y*/
	int ij;
	for(ij = 0; ij<n; ij++){
		wartosci[ij] = mini + (ij+1)*(maxi - mini)/n;
	}

	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");

	int i;
	for(i=0; i<401; i++){ /*ramka*/
		putpixel(i+20, -1+20, WHITE);
		putpixel(400+20, i+20, WHITE);
		putpixel(i+20, 400+20, WHITE);
		putpixel(19, i+20, WHITE);
	}

	if(maxx- minx > maxy - miny){
		int x;
		for(x = 0; x<400; x++){/*rysowanie*/
			/*ustalone x*/
			int y;
			for(y=0; y < 400*(maxy - miny)/(maxx - minx); y++){
	
				if(funkcja(x, y) <= wartosci[0])
					putpixel(x+20, 399 - y + 20 , RGB(0, 255, 0));
	
				int ni;
				for(ni=0; ni<n/2; ni++){ /*w jakim przedziale f(x);*/
					if(wartosci[ni] < funkcja(x, y) && funkcja(x, y) <= wartosci[ni+1]){
						int a = (ni+1)*255/(n/2);
						putpixel(x+20, 399 - y +20 , RGB( a, 255, 0));
					}
				}
				int ni1;
				for( ni1=n/2; ni1 < n; ni1++){
					if(wartosci[ni1] < funkcja(x, y) && funkcja(x, y)<= wartosci[ni1+1]){
						int a1 = 255 - (ni1 - (n/2-1))*255/(n/2);
						putpixel(x+20, 399 - y +20, RGB(255, a1, 0));
					}
				}
			}
		}/*rysowanie*/
	}
	else {
		int x;
		for(x = 0; x<400*(maxx - minx)/(maxy - miny); x++){/*rysowanie
			ustalone x */
			int y;
			for(y=0; y < 400; y++){
				if(funkcja(x, y) <= wartosci[0])
					putpixel(x+20, 399 - y +20 , RGB(0, 255, 0));
					
				int ni;
				for(ni=0; ni<n/2; ni++){ /*w jakim przedziale f(x);*/
					if(wartosci[ni] < funkcja(x, y) && funkcja(x, y) <= wartosci[ni+1]){
						int a = (ni+1)*255/(n/2);
						putpixel(x+20, 399 - y +20, RGB( a, 255, 0));
					}
				}
				int ni1;
				for(ni1=n/2; ni1 < n; ni1++){
					if(wartosci[ni1] < funkcja(x, y) && funkcja(x, y)<= wartosci[ni1+1]){
						int a1 = 255 - (ni1 - (n/2-1))*255/(n/2);
						putpixel(x+20, 399 - y +20 , RGB(255, a1, 0));
					}
				}
			}
		}/*rysowanie*/
	}
	
	getch();
	closegraph();

	return 0;
}
