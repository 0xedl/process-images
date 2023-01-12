
#pragma once

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Image
        {

public:

    struct Header
            {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;

        bool operator==(Header h2) const; // COMPARE OPERATOR
    };

    struct Pixel
            {
        unsigned char blue, green, red;

        // ****************************** OVERLOADED OPERATORS ****************************** //
        Pixel operator*(Pixel pixel2) const; // MULTIPLY TWO PIXELS
        Pixel operator-(Pixel pixel2) const; // SUBTRACT TOP LAYER FROM BOTTOM LAYER
        Pixel operator+(Pixel pixel2) const; // ADD CHANNEL
        bool operator==(Pixel pixel2) const; // COMPARE OPERATOR

    };

    static const int MAXPIXELS = 255.0f; // MAXIMUM NUMBER OF PIXELS
    Header header;
    vector<Pixel> pixels;

    // ****************************** FUNCTIONS ****************************** //
    Image operator*(const Image &img1) const; // MULTIPLY TWO PIXELS VECTORS
    Image operator+(const Image &img1) const; // ADD IMAGE HORIZONTAL TO OTHER
    Image operator-(const Image &img1) const;
    void serialize(ofstream &out); // WRITE DATA TO FILE
    void deSerialize(ifstream &file); // READ DATA FROM FILE
    void screen(Image &text, Image &img); // SCREEN IMAGES
    static unsigned char
    overlayHelper(unsigned char &rgbValue1, unsigned char &rgbValue2); // HELPER, RETURNS OVERLAY CHAR

    void overlay(Image &img1, Image &img2); // OVERLAY PIXELS
    void addOneChannel(const Image &img, const unsigned char &c); // ADDS ONE CHANNEL TO EACH PIXEL IN IMAGE
    void scale(Image &img, int &blueScale, int &greenScale, int &redScale); // SCALE IMAGE BASED ON GIVEN VALUES
    static void separateChannels(Image &img, Image &b, Image &g, Image &r); // SEPARATE THREE CHANNELS INTO DIFF IMAGES
    void combineThreeLayers(Image &b, Image &g, Image &r); // COMBINE THREE LAYERS
    void flip(Image &img); // FLIP IMAGE 180 DEGREES
    static void combineVertical(Image &img1, Image &img2); // ADD IMAGE VERTICALLY
    void test(const string &exampleName); // TEST TWO FILES, RETURN # OF ERRORS

};


