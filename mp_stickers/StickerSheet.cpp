#include <iostream>
#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    this->max = max; 
    this->lowest = 0; //lowest always is lowest AVAILABLE layer
    
    stickers = new Image*[max];
    x = new unsigned[max];
    y = new unsigned[max];

    base = new Image(picture);

    for (unsigned i = 0; i < max; i++) 
        stickers[i] = NULL;
}

StickerSheet::~StickerSheet() {
    clear();
}

StickerSheet::StickerSheet(const StickerSheet& other) {
    copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (this->max == max)
        return;
    else {
        Image** temp = new Image*[max];
        unsigned* x_temp = new unsigned[max];
        unsigned* y_temp = new unsigned[max];

        if (max < lowest) lowest = max;

        for (unsigned i = 0; i < lowest; i++) {
            temp[i] = stickers[i];
            x_temp[i] = x[i];
            y_temp[i] = y[i];
        }

        delete[] stickers;
        delete[] x;
        delete[] y;
        
        this->max = max;
        stickers = temp;
        x = x_temp;
        y = y_temp;
    }
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
    if (lowest >= max) 
        return -1;
    else {
        stickers[lowest] = &sticker; 
        this->x[lowest] = x;
        this->y[lowest] = y;
        lowest++;
    }
    return lowest - 1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if(!valid_index(index))
        return false;

    this->x[index] = x;
    this->y[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (!valid_index(index))
        return;
    lowest--;
    for (unsigned i = index; i < max - 1; i++) {
        stickers[i] = stickers[i + 1];
        x[i] = x[i+1];
        y[i] = y[i+1];
    }
}

Image* StickerSheet::getSticker(unsigned index) {
    if(!valid_index(index))
        return NULL;
    return stickers[index];
}

Image StickerSheet::render() const {
    unsigned maxH = base->height();
    unsigned maxW = base->width();
    for (unsigned i = 0; i < lowest; i++) {
        if (y[i] + stickers[i]->height() > maxH)
            maxH = y[i] + stickers[i]->height();
        if (x[i] + stickers[i]->width() > maxW)
            maxW = x[i] + stickers[i]->width();
    }

    Image result(maxW, maxH);

    //draw base image first, fill anything out of bounds with white pixels

    for (unsigned x = 0; x < maxW; x++) {
        for (unsigned y = 0; y < maxH; y++) {
            cs225::HSLAPixel& curr = result.getPixel(x, y);
            if (x >= base->width() || y >= base->height()) curr.l = 1;
            else curr = base->getPixel(x, y);
        }
    }

    for (unsigned i = 0; i < lowest; i++) {
        for (unsigned x = 0; x < maxW; x++) {
            for(unsigned y = 0; y < maxH; y++) {
                cs225::HSLAPixel& curr = result.getPixel(x, y);
                
                //check if pixel should be drawn from element in stickers array or not
                
                if (x >= this->x[i] && y >= this->y[i]) { 
                    if (x < (this->x[i] + stickers[i]->width()) && y < (this->y[i] + stickers[i]->height())) {
                        cs225::HSLAPixel& source = stickers[i]->getPixel(x - this->x[i], y - this->y[i]);
                        if (source.a != 0) curr = source;
                    }
                }
            }
        }
    }
    return result;
}
void StickerSheet::clear() {
    delete base;
    delete[] stickers;
    delete[] x;
    delete[] y;
}

void StickerSheet::copy(const StickerSheet& other) {
    max = other.max;
    lowest = other.lowest;

    base = new Image(*other.base);
    stickers = new Image*[max];
    x = new unsigned[max];
    y = new unsigned[max];
    
    for (unsigned i = 0; i < max; i++) {
        stickers[i] = other.stickers[i];
        if (i < lowest) {
            x[i] = other.x[i];
            y[i] = other.y[i];
        }
    }
}

bool StickerSheet::valid_index(unsigned index) {
    if (index >= 0 && index < lowest)
        return true;
    return false;
}
