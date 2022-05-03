#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

#include <vector>

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG& png) {
	/** @todo [Part 2] */
	png_ = new PNG(png);
}

FloodFilledImage::~FloodFilledImage() {
    delete png_;
    // for (std::vector<ImageTraversal*>::iterator it = traversals_.begin(); it != traversals_.end(); ++it) {
    //     delete *it;
    // }
    traversals_.clear();
    colorPickers_.clear();
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal& traversal, ColorPicker& colorPicker) {
	/** @todo [Part 2] */
	traversals_.push_back(&traversal);
	colorPickers_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
	Animation animation;

	/** @todo [Part 2] */
	//size of traversals should equal size of colorPickers
	//each traversal should correspond to a colorPicker, vice versa
    int frame = 0;
    animation.addFrame(*png_);
    frame++;
	for (unsigned i = 0; i < traversals_.size(); ++i) {
		for (ImageTraversal::Iterator it = traversals_.at(i)->begin(); it != traversals_.at(i)->end(); ++it) {
			HSLAPixel& pixel = png_->getPixel((*it).x, (*it).y);
            HSLAPixel color = colorPickers_.at(i)->getColor((*it).x, (*it).y);

            pixel = color;

            if (frame % frameInterval == 0) {
                animation.addFrame(*png_);
            }
            frame++;
		}
	}
    animation.addFrame(*png_);
	return animation;
}
