#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

#pragma pack(push, 1)
struct bitmap_header
{
	uint16_t FileType;
	uint32_t FileSize;
	uint16_t Reserved1;
	uint16_t Reserved2;
	uint32_t BitmapOffset;
	uint32_t Size;
	uint16_t Planes;
	uint16_t BitsPerPixel;
	uint32_t Compression;
	uint32_t SizeOfBitmap;
	uint32_t ColorsUsed;
	uint32_t ColorsImportant;
	int32_t Width;
	int32_t Height;
	int32_t HorzResolution;
	int32_t VertResolution;


}; 


#pragma pack(pop)
int main(int ArgCount, char **Args)
{
	uint32_t OutputWidth = 1280;
	uint32_t OutputHeight = 720;

	uint32_t OutputPixelSize = sizeof(uint32_t)*OutputWidth*OutputHeight;
	uint32_t *OutputPixels = (uint32_t *)malloc(OutputPixelSize);

	uint32_t *Out = OutputPixels;

	for (uint32_t Y = 0 ;Y < OutputHeight; ++Y)
	{
		for (uint32_t X = 0; X < OutputWidth; ++X)
		{
			*Out++ = 0xFF0000FF;
		}
	}

	bitmap_header Header = {};

	Header.FileType = 0x4D42;
	Header.FileSize = sizeof(Header) + OutputPixelSize;
	Header.BitmapOffset = sizeof(Header);
	Header.Size = sizeof(Header) - 14;
	Header.Width = OutputWidth;
	Header.Height = OutputHeight;
	Header.Planes = 1;
	Header.BitsPerPixel = 32;
	Header.Compression = 0;
	Header.SizeOfBitmap = OutputPixelSize;
	Header.HorzResolution = 0;
	Header.VertResolution = 0;
	Header.ColorsUsed = 0;
	Header.ColorsImportant = 0;






	FILE*InFile = fopen("ref.bmp", "rb");
	bitmap_header RefHeader = {};
	fread(&RefHeader, sizeof(RefHeader), 1, InFile);
	fclose(InFile);

	const char *OutputFileName = "test.bmp";
	FILE *OutFile = fopen(OutputFileName, "wb");
	if (OutFile)
	{
		fwrite(&Header, sizeof(Header), 1, OutFile);
		fwrite(OutputPixels, OutputPixelSize, 1, OutFile);
		fclose(OutFile);
	}
	else
	{
		fprintf(stderr, "Error, unable to write output file", OutputFileName);
	}



	return 0;
}