/*
 *	This source code is free and open source.  You may use it as you
 *  see fit so long as this header comment stays put!
 *
 * Author MatCat
 */
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

long map(float x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void printHelp(char *argv[])
{
	printf("Usage: %s <input> <output>\n",argv[0]);
}

int main(int argc, char *argv[])
{
	printf("CSV to ARB Converter\n\nThis program is free and open source.\n\nWritten by MatCat\n");
	if (argc < 3)
	{
		printf("\nPlease specify an input and output file.\n");
		printHelp(argv);
	} else {
		printf("\nInput File: %s\n",argv[1]);
		FILE *ifp, *ofp;
		char *mode = "r";
		char *oMode = "wb";

		ifp = fopen(argv[1], mode);
		ofp = fopen(argv[2], oMode);

		if (ifp == NULL) {
			fprintf(stderr, "Error opening %s\n",argv[1]);
			exit(1);
		}
		if (ofp == NULL) {
			fprintf(stderr, "Error opening %s\n", argv[2]);
			exit(1);
		}

		char line[1000];
		int lineCount = 0;
		int charCount = 0;
		while (fgets(line, sizeof line, ifp) != NULL) /* read a line from a file */ {
			if (line[0] == '#')
			{
				; // Ignore Comments
			}
			else {
				lineCount++;
					char * pEnd;
					float iValue;
					long oValue;

					iValue = strtof(line, &pEnd, 10);
					oValue = map(iValue, -1, 1, 0, 16383) % 16384 + 32768;

					charCount++;
					putc(oValue & 0xFF, ofp);
					charCount++;
					putc(oValue >> 8, ofp);
			}
		}
		printf("%d points, wrote %d bytes\n",lineCount,charCount);
		fclose(ifp);
		fclose(ofp);
	}
	return 1;
}