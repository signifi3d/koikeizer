#include "types.h"
#include <string>
#include <iostream>

#include "../include/CImg.h"


using namespace cimg_library;

static void 	help_output();
void 		split_image(std::string, long int, long int);
void 		inline_image(std::string, long int, long int);
int 		split_x_values(int,int,int);
int 		split_y_values(int,int,int);
int 		inline_x_values(int,int);
int 		inline_y_values(int,int);

int main(int argc, char* argv[]) {

	std::string	input_filepath;
	std::string	output_filepath;
	long int	vertical_strip_count = 10;
	long int	horizontal_strip_count = 10;
	processType	process_option = SPLIT;

	for (int i = 1; i < argc; ++i) {
		std::string opt = argv[i];
		if ( opt == "-h" || opt == "--help" ) {
			help_output();
			return 0;
		} else if ( opt == "-v" ) {
			if ( i + 1 == argc ) {
				vertical_strip_count = 10;
			} else {
				char *digit_check;
				long int opt_val = strtol(argv[i+1], &digit_check, 10);
				if (*digit_check) {
					vertical_strip_count = 10;
				} else {
					if ( opt_val == 0 ) {
						std::cerr << "Vertical strip count can't be 0. Defaulting to 10." << std::endl;
					} else {
						vertical_strip_count = opt_val%2==0 ? opt_val : opt_val+1;
						++i;
					}
				}
				
			}
		} else if ( opt == "-r" ) {
			if ( i + 1 == argc ) {
				horizontal_strip_count = 10;
			} else {
				char *digit_check;
				long int opt_val = strtol(argv[i+1], &digit_check, 10);
				if (*digit_check) {
					horizontal_strip_count = 10;
				} else {
					if ( opt_val == 0 ) {
						std::cerr << "Horizontal strip count can't be 0. Defaulting to 10." << std::endl;
					} else {
						horizontal_strip_count = opt_val%2==0 ? opt_val : opt_val+1;
						++i;
					}
				}
			}
		} else if ( opt == "-o" ) {
			if ( i + 1 == argc ) {
				std::cerr << "Invalid output argument. Proper usage: koikeizer in_filename -o out_filename" << std::endl;
				return 1;
			} else {
				output_filepath = argv[i+1];
				++i;
			}
		} else if ( opt == "-i" ) {
			process_option = INLINE;
		} else if ( opt == "-s" ) {
			process_option = SPLIT;
		} else {
			input_filepath = opt;	
		}
	}

	if ( input_filepath.length() == 0 ) {
		std::cerr << "No input filepath. Proper usage: koikeizer [-v [n]][-r [n]][-o out_filename][-i][-s] in_filepath" << std::endl;
		return 1;
	}
	
	if ( process_option == SPLIT ) 
		split_image(input_filepath, vertical_strip_count, horizontal_strip_count);
	else if ( process_option == INLINE ) 
		inline_image(input_filepath, vertical_strip_count, horizontal_strip_count);	
	
	return 0;
}

static void help_output() {
	std::cout << "koikeizer is a command line tool that recompiles strips of images inspired by the art of Kensuke Koike." << std::endl;
	std::cout << "	Usage: koikeizer [-v [n]][-r [n]][-o out_filename][-i][-s] in_filepath" << std::endl;
}

void split_image(std::string filepath, long int vert_strips, long int hor_strips) {

	CImg<unsigned char> 	image(filepath.c_str());
	CImg<unsigned char> 	new_image(image.width(), image.height(), image.depth(), image.spectrum(), 0);
	
	long int 		strip_width = image.width() / vert_strips;
	long int 		strip_height = image.height() / hor_strips;


	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			for (int chan = 0; chan < image.spectrum(); ++chan)
				new_image.atXY(split_x_values(x,strip_width,image.width()), split_y_values(y,strip_height,image.height()),0,chan) = image.atXY(x, y, 0, chan);
		} 
	}


	new_image.display();
}

void inline_image(std::string filepath, long int vert_strips, long int hor_strips) {
	CImg<unsigned char>	image(filepath.c_str());
	CImg<unsigned char> 	new_image(image.width(), image.height(), image.depth(), image.spectrum(), 0);

	long int		strip_width = image.width() / vert_strips;
	long int		strip_height = image.height() / hor_strips;

	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			for (int chan = 0; chan < image.spectrum(); ++chan)
				new_image.atXY(inline_x_values(x, strip_width), inline_y_values(y, strip_height), 0, chan) = image.atXY(x, y, 0, chan);
		}
	}

	new_image.display();
}

int inline_x_values(int x, int strip_width) {
	if ( (x/strip_width) % 2 == 0) {
		return x + strip_width;
	} else {
		return x - strip_width;
	}
}

int inline_y_values(int y, int strip_height) {
	if ( (y/strip_height) % 2 == 0 ) 
		return y + strip_height;
	else
		return y - strip_height;
}

int split_x_values(int x, int strip_width, int image_width) {
	if ( (x / strip_width) % 2 == 0 )
		return (strip_width * ((x/strip_width)/2)) + (x%strip_width);
	else 
		return image_width/2 + (strip_width * ((x/strip_width)/2)) + (x%strip_width);
}

int split_y_values(int y, int strip_height, int image_height) {
	if ( ( y / strip_height ) % 2 == 0 ) 
		return (strip_height * (( y / strip_height )/2)) + ( y % strip_height );
	else
		return image_height/2 + (strip_height * (( y / strip_height)/2)) + ( y % strip_height );
}
