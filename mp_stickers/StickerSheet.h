/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <cmath>

class StickerSheet {
    public:
        StickerSheet(const Image& picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet& other);
        const StickerSheet& operator=(const StickerSheet& other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image& sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        Image render() const;
        void clear();
        void copy(const StickerSheet& other);
        bool valid_index(unsigned index);
    private:
        unsigned max; //max number of layers available
        unsigned lowest; //lowest layer possible
        Image* base; //base image of StickerSheet
        Image** stickers; //array of all stickers, ordered by layer, bottom to top
        unsigned* x; //x positions of each image's top left
        unsigned* y; //y positions of each image's top left
};
