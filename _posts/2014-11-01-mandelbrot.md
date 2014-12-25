---
layout: post
title: Mandelbrot Set renderer in C
date: 2014-11-01 14:49:04
summary: An obfuscated ASCII Mandelbrot set renderer in 228 bytes of C code.
categories: blog dev
---
Playing around with minified C I wrote a renderer for the Mandelbrot set in 228 bytes, using some abuse of boolean logic.

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

And here's the expanded version so you can see how it works:

    #include <stdio.h>

    void main()
    {
        int i = 4095, j;
        while(i-- >= 0)
        {
            if(i % 64 > 0) /* give us newlines every 64 chars */
            {
                float p = 0, /* re(z) */
                      q = 0, /* im(z) */
                      a = -(float)(i % 64 - 14) / 30, /* re(c) */
                      b = (float)(i / 64 - 32) / 30;  /* im(c) */

                j = 99; /* 99 iterations computed */
                while(j-- > 0 && /* iterate */
                      p * p + q * q < 9) /* check for divergence */
                {
                    float s = p * p - q * q, t = 2 * p * q; /* z^2 */
                    p = a + s; /* z = z^2 + c */
                    q = b + t; /* ........... */
                }
                putchar(')' - j / 10); /* print different character
                                          depending on iteration count */
            }
            else
            {
                putchar('\n');
            }
        }
    }

Of course, there would be little point showing you if I didn't show you the output, too. Here it is, looking slightly out of proportion due to the non-square characters in my terminal emulator:

<div style="text-align: center">
  <img alt="The Mandelbrot set rendered as ASCII art in a terminal emulator." src="{{ site.base_url }}/images/mandelbrot.png" /><br/>
  <span class="post-meta small">The different 'levels' of iterations required for the sequence to diverge are shown using different characters.</span>
</div>

Not only was this a fun little challenge to write, but it also taught me what the Mandelbrot set actually is - prior to this point, my knowledge of the fractal was limited to what it looked like.
