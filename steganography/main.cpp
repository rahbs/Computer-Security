#include <iostream>
#include "steganography.h"

#define BMP_HEADER_SIZE 54

using namespace std;

int main(int argc, char* argv[])
{
	char input_bmp_file[] = "origin.bmp";
	char output_bmp_file[] = "stego.bmp";

	if (argc == 2) {
		if (*(argv[1]) == 'e') 
			encode(input_bmp_file, output_bmp_file);
		else if (*(argv[1]) == 'd') 
			decode(output_bmp_file);
	}
	else {
		cout << "please select proper program option ['e':encode, 'd':decode]\n";
	}
}
