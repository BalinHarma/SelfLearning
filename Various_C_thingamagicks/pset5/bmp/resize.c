/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, and while at it, resizes the image by a factor of n.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage, also remember factor in n
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        printf("factor needs to be in [1;100].\n");
        return 5;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding in input
    int paddingi =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // determine padding in output
    int paddingo =  (4 - (n * bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine scanline width in bits
    int slw = n * bi.biWidth * sizeof(RGBTRIPLE);
    
    // Cook up the modified headers    
    BITMAPINFOHEADER bim = bi;
    bim.biWidth = bi.biWidth * n;
    bim.biHeight = bi.biHeight * n;
    bim.biSizeImage =  abs(bim.biWidth * bim.biHeight) * 3 + abs(bim.biHeight * paddingo);
    
    BITMAPFILEHEADER bfm = bf;
    bfm.bfSize = bim.biSizeImage + 54;
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfm, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER 
    fwrite(&bim, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // read entire scanline, pixel by pixel
        RGBTRIPLE* temp = malloc(slw);
        for (int j = 0; j < bi.biWidth; j++)
        {
            fread(&temp[j], sizeof(RGBTRIPLE), 1, inptr);
        }
        // write n times the same scanline
        for (int m = 0; m < n; m++)
        {
            // write pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // n times each
                for (int l = 0; l < n; l++)
                {
                    fwrite(&temp[k], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add padding to new file
            for (int k = 0; k < paddingo; k++)
            {
                fputc(0x00, outptr);
            }
        }
        // free temporary scanline
        free(temp);
        // Skip padding from reading if any
        fseek(inptr, paddingi, SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
