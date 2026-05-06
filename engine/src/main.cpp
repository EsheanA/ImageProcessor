#include "Image.h"

#include <cstdlib>
#include <cmath>
#include <chrono>

int main(int argc, char** argv){

	//invert
	// Image invert_test("test1.jpg");
	// invert_test.invert();
	// invert_test.write("invert.png");

	//blur 
	// Image blur_test("test1.jpg");
	// blur_test.blur(3);
	// blur_test.write("blur.png");

	//sepia
	Image sepia_test("test1.jpg");
	sepia_test.sepia();
	sepia_test.write("sepia.png");
	

	//traverse image data array	
	// Image test("test1.jpg");
	// Image copy = test;
	// for(int i = 0; i < copy.w; ++i){
	// 	for(int j = 0; j < copy.h; ++j){
	// 		int index = (j * copy.w + i) * copy.channels;
	// 		copy.data[index + 0] = 255;
	// 		copy.data[index + 1] = 255;
	// 		copy.data[index + 2] = 255;
	// 	}
	// }
	// copy.write("copy.png");
	//color
    // Image img("test1.jpg");

	// img.colorMask(0, 0, 1);

	// img.write("blue.png");
	
	// grayscale
	// img.grayscale_avg();
	// int img_size = img.w*img.h;

	// Image gray_img(img.w, img.h, 1);
	// for(uint64_t k=0; k<img_size; ++k) {
	// 	gray_img.data[k] = img.data[img.channels*k];
	// }
	// gray_img.write("grayscale.jpg");


    // Image gray_lum = img;
    // gray_lum.grayscale_lum();
    // gray_lum.write("gray_lum.png");

    return 0;
}