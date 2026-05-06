#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <cstring>
#include <algorithm>

enum ImageType{
    PNG, JPG, BMP, TGA
};

ImageType getFileType(const char* filename);

Image::Image(const char* filename){
    if(read(filename)){
        printf("Read %s\n", filename);
        size = w*h*channels;
    }else{
        printf("Read failed %s\n", filename);
    }
}

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels){
    size = w*h*channels;
    data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels){
    data = new uint8_t[size];
    memcpy(data, img.data, img.size);
}

Image::~Image(){
    stbi_image_free(data);
}

bool Image::read(const char* filename){
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
}

bool Image::write(const char* filename){
    ImageType type = getFileType(filename);
    int success;
    switch(type){
        case PNG:
            success = stbi_write_png(filename, w, h, channels, data, w*channels);
            break;
        case BMP:
            success = stbi_write_bmp(filename, w, h, channels, data);
            break;
        case JPG:
            success = stbi_write_jpg(filename, w, h, channels, data, 100);
            break;
        case TGA:
            success = stbi_write_tga(filename, w, h, channels, data);
            break;
    }
    return success != 0;
}

ImageType getFileType(const char* filename){
    const char* ext = strrchr(filename, '.');
    if(ext != nullptr){
        if(strcmp(ext, ".png") == 0){
            return PNG;
        }else if(strcmp(ext, ".jpg") == 0){
            return JPG;
        }else if(strcmp(ext, ".bmp") == 0){
            return BMP;
        }else if(strcmp(ext, ".tga") == 0){
            return TGA;
        }
    }
    return PNG;
}

Image& Image::grayscale_avg(){
    if(channels < 3){
        printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
    }else{
        for(int i = 0; i < size; i+=channels){
            // (r+g+b)/3
            int gray = (data[i] + data[i+1] + data[i+2])/3;
            memset(data+i, gray, 3);
        }
    }
    return *this;
}

Image& Image::grayscale_lum(){
    if(channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
	}
	else {
		for(int i = 0; i < size; i+=channels) {
			int gray = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
			memset(data+i, gray, 3);
		}
	}
	return *this;
}


Image& Image::sepia(){
    if(channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
	}
	else {
	    for(int i = 0; i < w; ++i){
            for(int j = 0; j < h; ++j){
                int index = (j * w + i) * channels;

                int inputRed = data[index+0];
                int inputGreen = data[index+1];
                int inputBlue = data[index+2];

                int outputRed = (inputRed * .393) + (inputGreen *.769) + (inputBlue * .189);
                int outputGreen = (inputRed * .349) + (inputGreen *.686) + (inputBlue * .168);
                int outputBlue = (inputRed * .272) + (inputGreen *.534) + (inputBlue * .131);

                data[index + 0] = static_cast<unsigned char>(std::clamp(outputRed, 0, 255));
                data[index + 1] = static_cast<unsigned char>(std::clamp(outputGreen, 0, 255));
                data[index + 2] = static_cast<unsigned char>(std::clamp(outputBlue, 0, 255));
            }
	    }

	}
    return *this;
}


Image& Image::blur(int box){
    if(channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
	}
	else {
        double avg_red, avg_green, avg_blue;
        int count;
	    for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                int index = (j * w + i) * channels;
                
                avg_red = 0;
                avg_green = 0;
                avg_blue = 0;
                count = 0;
               for(int li = i-box; li <= i+box; ++li){
                    if(li < 0){
                        li = 0;
                    }
                    if(li == h) break;

                    for(int col = j-box; col < j+box; col++){
                        if(col == w) break;
                        if(col < 0){
                            col = 0;
                        }
                        int curr_index = (col*w + li) * channels;
                        avg_red += data[curr_index + 0];
                        avg_green += data[curr_index + 1];
                        avg_blue += data[curr_index + 2];

                        count+=1;
                    }
               }

                data[index + 0] = static_cast<unsigned char>(std::clamp((int)(avg_red/count), 0, 255));
                data[index + 1] = static_cast<unsigned char>(std::clamp((int)(avg_green/count), 0, 255));
                data[index + 2] = static_cast<unsigned char>(std::clamp((int)(avg_blue/count), 0, 255));

               
            }
	    }
	}
    return *this;
}

Image& Image::invert(){
    if(channels < 3){
        printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
    }else{
        for(int i = 0; i < h; ++i){
            for(int j = 0; j < w; ++j){
                int index = (i * w + j) * channels;

                int inputRed = data[index + 0];
                int inputGreen = data[index + 1];
                int inputBlue = data[index + 2];

                int outputRed = 255 - inputRed;
                int outputGreen = 255 - inputGreen;
                int outputBlue = 255 - inputBlue;

                data[index + 0] = static_cast<unsigned char>(outputRed);
                data[index + 1] = static_cast<unsigned char>(outputGreen);
                data[index + 2] = static_cast<unsigned char>(outputBlue);
            }
        }
    }
    return *this;
}


Image& Image::colorMask(float r, float g, float b){
    if(channels < 3){
        printf("\e[31m[ERROR] Color mask requires at least 3 channels");
    }else{
        for(int i =0; i < size; i+=channels){
            data[i] *= r;
            data[i+1] *= g;
            data[i+2] *= b;
        }
    }
    return *this;
}