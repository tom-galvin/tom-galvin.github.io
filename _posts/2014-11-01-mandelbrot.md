---
layout: post
title: Mandelbrot Set Renderer in C
date: 2014-11-01 14:49:04
summary: A Mandelbrot set renderer in 228 bytes of C code.
categories: programming c
---
Playing around with minified C I wrote a renderer for the Mandelbrot set in 228 bytes, using some abuse of boolean logic.
```c
#include<stdio.h>
#define F float
void main(){int i
=4095,j;while(i--
>=0){F p=0,q=0,a=
-(F)(i%64-14)/30,
b=(F)(i/64-32)/30
;j=99;while(j-->0
&&p*p+q*q<9){F s=
p*p-q*q,t=2*p*q;p
=a+s,q=b+t;}j=~i&
63?')'-j/10:'\n';
putchar(j);}}
```
And here's the expanded version so you can see how it works:
```c
#include <stdio.h>

void main()
{
    int i = 4095, j;
    while(i-- >= 0)
    {
        if(i % 64 > 0) /* give us newlines every 64 chars, so it's not rendered as one line */
        {
						float p = 0, /* re(z) */
								  q = 0, /* im(z) */
									a = -(float)(i % 64 - 14) / 30, /* re(c) */
									b = (float)(i / 64 - 32) / 30;  /* im(c) */

						j = 99; /* 99 iterations computed */
						while(j-- > 0 && /* iterate */
									p * p + q * q < 9) /* check for divergence - z not too large */
						{
								float s = p * p - q * q, t = 2 * p * q; /* square z */
								p = a + s; /* z = z^2 + c */
								q = b + t; /* ........... */
						}
						putchar(')' - j / 10); /* use ASCII to print different character
																			depending on iterations until divergence */
				}
				else
				{
						putchar('\n');
				}
		}
}
```
Not only was this a fun little challenge to write, but it also taught me what the Mandelbrot set actually is - prior to this point, my knowledge of the fractal was limited to what it looked like.
