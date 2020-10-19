#include <iostream>
#include <string>
#include "steganography.h"

#define BMP_HEADER_SIZE 54

using namespace std;

void encode(char* input_bmp_file, char* output_bmp_file) {

	int c;
	int text_idx = 0;
	int img_idx = 0;
	int bit_idx = 0;
	char pixel_value;
	char bit_mask;
	FILE* input_img = NULL;
	FILE* output_img = NULL;
	input_img = NULL;
	output_img = NULL;

	string text;
	getline(cin, text);

	fopen_s(&input_img, input_bmp_file, "rb");
	if (input_img == NULL) {
		printf("Can not open the input image file.\n");
		return;
	}

	fopen_s(&output_img, output_bmp_file, "wb");
	if (output_img == NULL) {
		printf("Can not open the output image file.\n");
		return;
	}
	
	// encode
	while ((c = fgetc(input_img)) != EOF) {
		//original pixel value
		pixel_value = (char)c;
		
		// Skip bmp header 
		if (img_idx >= BMP_HEADER_SIZE && text_idx <= text.length()) {
			// bit_mask for processing bit in the lowest order
			// ex) 00000001 -> 00000010 -> 00000100 -> ...
			bit_mask = 1 << bit_idx;
			bit_idx++;
			
			if ((text[text_idx] & bit_mask) == 0)
				// if the bit was 0, save 0 to the LSB of the image pixel 
				pixel_value &= 254; //AND operation and allacation
			else
				// if the bit was 1, save 1 to the LSB of the image pixel
				pixel_value |= 1; //OR operation and allacation
			
			// Move to the next byte, start from the lowest bit
			if (bit_idx >= 8) {
				bit_idx = 0;
				text_idx++;
			}
		}

		// Copy
		fputc(pixel_value, output_img);
		img_idx++;
	}

	printf("\nThe text was successfully hidden into the image. \n");
	fclose(input_img);
	fclose(output_img);
}

void decode(char* input_bmp_file) {

	int c;
	int text_idx = 0;
	int img_idx = 0;
	int bit_idx = 0;
	int bit_mask;
	int max_txt_size = 10000;
	string text;
	FILE* input_img = NULL;

	fopen_s(&input_img, input_bmp_file, "rb");

	if (input_img == NULL) {
		printf("Can not open the input image file.\n");
		return;
	}

	//preset text to 0. 
	for (int i = 0; i < max_txt_size; i++)
		text.push_back(0);

	// decode
	while ((c = fgetc(input_img)) != EOF) {
		
		// Skip bmp header
		if (img_idx >= BMP_HEADER_SIZE) {
			
			// bit_mask for processing bit in the lowest order
			// ex) 00000001 -> 00000010 -> 00000100 -> ...
			bit_mask = 1 << bit_idx;
			bit_idx++;

			// Check the LSB
			if ((c & 1) == 1)
				// If the LSB was 1, change the bit of text 
				text[text_idx] |= bit_mask;

			// Move to the next byte, start from the lowest bit
			if (bit_idx >= 8) {
				if (text[text_idx] == NULL)
					break;
				bit_idx = 0;
				text_idx++;
			}
		}
		img_idx++;
	}

	//print the extracted text
	cout << text << "\n";
	fclose(input_img);
}