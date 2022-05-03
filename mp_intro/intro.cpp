#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    // TODO: Part 2
    PNG input;
    input.readFromFile(inputFile);
    
    unsigned int width = input.width();
    unsigned int height = input.height(); 
    
    PNG output(width, height);

    for(unsigned int x = 0; x < width; x++){
        for(unsigned int y = 0; y < height; y++){
            HSLAPixel & inPixel = input.getPixel(width - x - 1, height - y - 1);
            HSLAPixel & outPixel = output.getPixel(x, y);

            outPixel.h = inPixel.h;
            outPixel.s = inPixel.s;
            outPixel.l = inPixel.l;
            outPixel.a = inPixel.a;
        }
    }
    output.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
    cs225::PNG png(width, height);
    // TODO: Part 3
    for(unsigned int x = 0; x < width; x++){
        for(unsigned int y = 0; y < height; y++){
            HSLAPixel & pixel = png.getPixel(x, y);
            //draw base 
            if(x < width/2 && y < height/2)
                pixel.h = 216;
            else
                pixel.h = 11;
            pixel.l = 0.5;
            pixel.s = 1;
            pixel.a = 1;

            double sunCenterX = width/4;
            double sunCenterY = height/4;
            double yDist = (double)abs(y - sunCenterY);
            double xDist = (double)abs(x - sunCenterX);
            double dist = pow(xDist, 2) + pow(yDist, 2);
            dist = sqrt(dist);

            if(dist <= width/10)
                pixel.l = 1;
            else if(dist <= width/9.5)
                pixel.l = 0.5;
            else if(dist <= width/4.5 && dist >= width/9){
                pixel.l = 0.5;
                double thickness = width/4.5 - width/9;
                pixel.h = (dist-width/9)/thickness*360;
            }
        }
    }
    return png;
}
