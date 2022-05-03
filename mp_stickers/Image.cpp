#include <iostream>
#include <cmath>
#include <algorithm>
#include "Image.h"

using namespace cs225;

void Image::lighten() {
    //increase luminance of every pixel by 0.1, maintain below 1
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.l += 0.1;
            if (p.l > 1)
                p.l = 1;
        }
    }
}

void Image::lighten(double amount) {
    //increase luminance of every pixel by amount, maintain below 1
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.l += amount;
            if (p.l > 1)
                p.l = 1;
        }
    }
}
        
void Image::darken() {
    //decrease luminance of every pixel by 0.1, maintain above 0 
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.l -= 0.1;
            if (p.l < 0)
                p.l = 0;
        }
    }
}
        
void Image::darken(double amount) {
    //decrease luminance of every pixel by amount, maintain above 0 
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.l -= amount;
            if (p.l < 0)
                p.l = 0;
        }
    }
}
        
void Image::saturate() {
    //increase saturation of every pixel by 0.1, maintain below 1 
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.s += 0.1;
            if (p.s > 1)
                p.s = 1;
        }
    }
}

void Image::saturate(double amount) {
    //increase saturation of every pixel by amount, maintain below 1
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.s += amount;
            if (p.s > 1)
                p.s = 1;
        }
    } 
}
     
void Image::desaturate() {
    //decrease saturation of every pixel by 0.1, maintain above 0 
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.s -= 0.1;
            if (p.s < 0)
                p.s = 0;
        }
    }
}
   
void Image::desaturate(double amount) {
    //decrease saturation of every pixel by amount, maintain above 0 
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.s -= amount;
            if (p.s < 0)
                p.s = 0;
        }
    }
}
        
void Image::grayscale() {
    //set saturation of every pixel to 0 
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.s = 0;
        }
    }
}
        
void Image::rotateColor(double degrees) {
    //rotate the hue of every pixel by degrees. Wrap around if exceed/below 360/0 respectively. 
    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);
            p.h += degrees;
            
            if (p.h < 0) 
                p.h = 360 + p.h;
            else 
                p.h = std::fmod(p.h, 360);
            
        }
    }
}
        
void Image::illinify() {
    //decrease saturation of every pixel by 0.1, maintain above 0 
    for(unsigned int x = 0; x < width(); x++) {
        for(unsigned int y = 0; y < height(); y++) {
            HSLAPixel& p = getPixel(x, y);

            double bDist = std::abs(p.h - 216);
            double oDist = std::abs(p.h - 11);

            if(bDist < oDist)
                p.h = 216;
            else if(oDist < bDist)
                p.h = 11;
            //do nothing if equally close.
        }
    }
}
        
void Image::scale(double factor) {
    if (factor == 1)
        return;
    else {
        Image orig(*this);
        resize(width() * factor, height() * factor);
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel& curr = getPixel(x, y);
                HSLAPixel& source = orig.getPixel((int)(x / factor), (int)(y / factor));
                curr = source;
            }
        }
    }
}
        
void Image::scale(unsigned w, unsigned h) {
    double r1 = (double) width() / (double) height(); //ratio of original width to height
    double r2 = (double) w / (double) h; //ratios of desired width to height;
    double factor = 1; //factor to scale by

    if (r1 < r2) factor = (double) h / (double) height();
    else if (r1 > r2) factor = (double) w / (double) width();

    scale(factor);
}
