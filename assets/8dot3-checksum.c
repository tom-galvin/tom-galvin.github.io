/* A checksum calculator for Windows 8.3 filenames.
 * The relevant post can be found at http://usn.pw/blog/cs/2015/06/09/filenames/
 * Written by Thomas Galvin. */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint16_t chksum(wchar_t * name)
{
	int i;
	uint16_t checksum = 0;

	for (i = 0; name[i]; i++) {
		checksum = checksum * 0x25 + name[i];
	}

	int32_t temp = checksum * 314159269;
	if (temp < 0) temp = -temp;
	temp -= ((uint64_t)((int64_t)temp * 1152921497) >> 60) * 1000000007;
	checksum = temp;

	// reverse nibble order
	checksum =
		((checksum & 0xf000) >> 12) |
		((checksum & 0x0f00) >> 4) |
		((checksum & 0x00f0) << 4) |
		((checksum & 0x000f) << 12);

	return checksum;
}

int main(int argc, char * argv[]) {
	int length = strlen(argv[1]); 
	wchar_t * wide_filename = malloc(sizeof(wchar_t) * (length + 1));
	mbstowcs(wide_filename, argv[1], length);
	printf("%x\n", chksum(wide_filename));
	free(wide_filename);
	return 0;
}
