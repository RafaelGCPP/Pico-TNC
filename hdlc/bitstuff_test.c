// hdlc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdint.h>

int main()
{

	size_t nbytes = 54;
	char inputdata[54] = "~PU1OWL-?/{Rafael Gustavo da Cunha Pereira Pinto\xf8}~_Z";

	size_t max_output_bytes = ((nbytes * 48) / 40)+1;
	size_t max_words = max_output_bytes/4;

	uint32_t *current=(uint32_t *)inputdata;
	for (int i=0; i<54 ; i+=4) {
		uint32_t data=*current++;
		printf("%08x ",data);
		for (int j=0;j<4;j++) {
			printf("%c ", data>>(j*8));
		}
		puts("");
		for (int j=0;j<32;j++) {
			putchar((data & 1)?'1':'0');
			if ((j>0)&& !((j+1)%8)) putchar(' ');
			data>>=1;
		}	
		puts("");
	}	


}

