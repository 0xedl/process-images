//
// Created by Ed Lang on 11/11/22.
//

#include "Image.h"

// ****************************** OVERLOADED OPERATORS ****************************** //

bool Image::Header::operator==(Header h2) const // COMPARE OPERATOR
{
        return
                idLength == h2.idLength &&
                colorMapType == h2.colorMapType &&
                dataTypeCode == h2.dataTypeCode &&
                colorMapOrigin == h2.colorMapOrigin &&
                colorMapLength == h2.colorMapLength &&
                colorMapDepth == h2.colorMapDepth &&
                xOrigin == h2.xOrigin &&
                yOrigin == h2.yOrigin &&
                width == h2.width &&
                height == h2.height &&
                bitsPerPixel == h2.bitsPerPixel &&
                imageDescriptor == h2.imageDescriptor;
}

Image::Pixel Image::Pixel::operator*(Pixel pixel2) const // MULTIPLY TWO PIXELS
{
    Pixel pixel{};
    double temp;
    temp = (((double) this->blue / MAXPIXELS) * ((double) pixel2.blue / MAXPIXELS) * MAXPIXELS) + 0.5f;
    pixel.blue = (unsigned char) temp;
    temp = (((double) this->green / MAXPIXELS) * ((double) pixel2.green / MAXPIXELS) * MAXPIXELS) + 0.5f;
    pixel.green = (unsigned char) temp;
    temp = (((double) this->red / MAXPIXELS) * ((double) pixel2.red / MAXPIXELS) * MAXPIXELS) + 0.5f;
    pixel.red = (unsigned char) temp;
    return pixel;
}

Image::Pixel Image::Pixel::operator-(Pixel pixel2) const // SUBTRACT TOP LAYER FROM BOTTOM LAYER
{
    Pixel pixel{};
    double temp;
    temp = (double) this->blue - (double) pixel2.blue;
    pixel.blue = (unsigned char) temp;
    temp = (double) this->green - (double) pixel2.green;
    pixel.green = (unsigned char) temp;
    temp = (double) this->red - (double) pixel2.red;
    pixel.red = (unsigned char) temp;
    return pixel;
}

Image::Pixel Image::Pixel::operator+(Pixel pixel2) const // ADD CHANNEL
{
    Pixel pixel{};
    if (this->blue + pixel2.blue > 255)
        pixel.blue = 255;
    else
        pixel.blue = this->blue + pixel2.blue;
    if (this->green + pixel2.green > 255)
        pixel.green = 255;
    else
        pixel.green = this->green + pixel2.green;
    if (this->red + pixel2.red > 255)
        pixel.red = 255;
    else
        pixel.red = this->red + pixel2.red;
    return pixel;
}

bool Image::Pixel::operator==(Pixel pixel2) const // COMPARE OPERATOR
{
    return
            this->blue == pixel2.blue &&
            this->green == pixel2.green &&
            this->red == pixel2.red;
}


// ******************************  IMAGE FUNCTIONS ****************************** //
// ******************************  IMAGE FUNCTIONS ****************************** //
// ******************************  OVERLOADED OPERATORS ****************************** //
Image Image::operator*(const Image &img1) const {
    Image img;
    img.header = header;
    for (int i = 0; i < pixels.size(); i++)
        img.pixels.push_back(pixels[i] * img1.pixels[i]);
    return img;
}

Image Image::operator+(const Image &img1) const
{
    // ADD IMAGE HORIZONTALLY
    Image img;
    img.header = img1.header;
    img.header.width = (short) ((int) header.width + (int) img1.header.width);

    for (unsigned int row = 0; row < img.header.height; row++)
    {
        int p1Counter = 0;
        int p2Counter = 0;
        for (unsigned int col = 0; col < img.header.width; col++)
        {
            if (p1Counter < header.width)
            {
                img.pixels.push_back(pixels[row * header.height + p1Counter]);
                p1Counter++;
            }
            else
            {
                img.pixels.push_back(img1.pixels[row * header.height + p2Counter]);
                p2Counter++;
            }
        }
    }
    return img;
}

Image Image::operator-(const Image &img1) const
{
    Image img;
    img.header = header;
    // SUBTRACT PIXELS
    for (int i = 0; i < pixels.size(); i++)
        img.pixels.push_back(pixels[i] - img1.pixels[i]);
    return img;
}


// ******************************  FUNCTIONS ****************************** //
void Image::serialize(ofstream &out) {
    // ******************************  WRITING HEADER TO FILE ****************************** //
    out.write(&header.idLength, sizeof(header.idLength));
    out.write(&header.colorMapType, sizeof(header.colorMapType));
    out.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
    out.write(reinterpret_cast<char *>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    out.write(reinterpret_cast<char *>(&header.colorMapLength), sizeof(header.colorMapLength));
    out.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
    out.write(reinterpret_cast<char *>(&header.xOrigin), sizeof(header.xOrigin));
    out.write(reinterpret_cast<char *>(&header.yOrigin), sizeof(header.yOrigin));
    out.write(reinterpret_cast<char *>(&header.width), sizeof(header.width));
    out.write(reinterpret_cast<char *>(&header.height), sizeof(header.height));
    out.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    out.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

    // ******************************  WRITING DATA TO FILE ****************************** //
    for (auto &p: pixels) {
        out.write(reinterpret_cast<char *>(&p.blue), sizeof(p.blue));
        out.write(reinterpret_cast<char *>(&p.green), sizeof(p.green));
        out.write(reinterpret_cast<char *>(&p.red), sizeof(p.red));
    }
}

void Image::deSerialize(ifstream &file) {
    // ******************************  READ HEADER DATA ****************************** //
    file.read(&header.idLength, sizeof(header.idLength));
    file.read(&header.colorMapType, sizeof(header.colorMapType));
    file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.read(reinterpret_cast<char *>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    file.read(reinterpret_cast<char *>(&header.colorMapLength), sizeof(header.colorMapLength));
    file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.read(reinterpret_cast<char *>(&header.xOrigin), sizeof(header.xOrigin));
    file.read(reinterpret_cast<char *>(&header.yOrigin), sizeof(header.yOrigin));
    file.read(reinterpret_cast<char *>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char *>(&header.height), sizeof(header.height));
    file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

    // ******************************  READ IMAGE DATA ****************************** //
    Pixel p{};
    for (int i = 0; i < (header.width * header.height); i++) {
        file.read(reinterpret_cast<char *>(&p.blue), sizeof(p.blue));
        file.read(reinterpret_cast<char *>(&p.green), sizeof(p.green));
        file.read(reinterpret_cast<char *>(&p.red), sizeof(p.red));
        pixels.push_back(p);
    }
}

void Image::screen(Image &img1, Image &img2)
{
    header = img1.header;
    Pixel p{};
    double temp;

    for (int i = 0; i < img1.pixels.size(); i++)
    {
        temp = MAXPIXELS -
               (((MAXPIXELS - (double) img1.pixels[i].blue) * (MAXPIXELS - (double) img2.pixels[i].blue)) / MAXPIXELS) +
               0.5f;
        p.blue = (unsigned char) temp;
        temp = MAXPIXELS -
               (((MAXPIXELS - (double) img1.pixels[i].green) * (MAXPIXELS - (double) img2.pixels[i].green)) / MAXPIXELS) +
               0.5f;
        p.green = (unsigned char) temp;
        temp = MAXPIXELS - (((MAXPIXELS - (double) img1.pixels[i].red) * (MAXPIXELS - (double) img2.pixels[i].red)) / MAXPIXELS) +
               0.5f;
        p.red = (unsigned char) temp;
        pixels.push_back(p);
    }
}

unsigned char Image::overlayHelper(unsigned char &rgbValue1, unsigned char &rgbValue2) {

    double res;
    double val1 = (double) rgbValue1 / MAXPIXELS;
    double val2 = (double) rgbValue2 / MAXPIXELS;

    if (val2 <= 0.5)
        res = ((2 * val1 * val2) * MAXPIXELS) + 0.5f;
    else
        res = ((1 - (2 * (1 - val1) * (1 - val2))) * MAXPIXELS) + 0.5f;

    return (unsigned char) res;
}

void Image::overlay(Image &img1, Image &img2)
{
    header = img1.header;
    Pixel p{};

    for (int i = 0; i < img1.pixels.size(); i++) {
        p.blue = overlayHelper(img1.pixels[i].blue, img2.pixels[i].blue);
        p.green = overlayHelper(img1.pixels[i].green, img2.pixels[i].green);
        p.red = overlayHelper(img1.pixels[i].red, img2.pixels[i].red);
        pixels.push_back(p);
    }
}

void Image::addOneChannel(const Image &img, const unsigned char &c)
{
    header = img.header;
    Pixel ch{};
    ch.green = c;
    for (auto &pixel: img.pixels)
        pixels.push_back(pixel + ch);
}

void Image::scale(Image &img, int &blueScale, int &greenScale, int &redScale)
{
    header = img.header;
    Pixel pixel{};

    for (auto p: img.pixels) {
        if (p.blue * blueScale > MAXPIXELS)
            pixel.blue = MAXPIXELS;
        else
            pixel.blue = p.blue * blueScale;

        if (p.green * greenScale > MAXPIXELS)
            pixel.green = MAXPIXELS;
        else
            pixel.green = p.green * greenScale;

        if (p.red * redScale > MAXPIXELS)
            pixel.red = MAXPIXELS;
        else
            pixel.red = p.red * redScale;
        pixels.push_back(pixel);
    }
}

void Image::separateChannels(Image &img, Image &b, Image &g, Image &r)
{
    b.header = g.header = r.header = img.header;
    Pixel pixel{};

    for (auto &p: img.pixels)
    {
        pixel.red = pixel.blue = pixel.green = p.blue;
        b.pixels.push_back(pixel);

        pixel.red = pixel.blue = pixel.green = p.green;
        g.pixels.push_back(pixel);

        pixel.red = pixel.blue = pixel.green = p.red;
        r.pixels.push_back(pixel);
    }


}

void Image::combineThreeLayers(Image &b, Image &g, Image &r)
{
    header = b.header;
    Pixel p{};
    for (int i = 0; i < b.pixels.size(); i++)
    {
        p.blue = b.pixels[i].blue;
        p.green = g.pixels[i].green;
        p.red = r.pixels[i].red;
        pixels.push_back(p);
    }
}

void Image::flip(Image &img)
{
    header = img.header;
    for (auto it = img.pixels.crbegin(); it != img.pixels.crend(); it++)
        pixels.push_back(*it);
}

void Image::combineVertical(Image &img1, Image &img2)
{
    img1.header.height = (short) ((int) img1.header.height + (int) img2.header.height);
    vector<Image::Pixel> p;

    for (auto pixel: img2.pixels)
        p.push_back(pixel);

    for (auto pixel: img1.pixels)
        p.push_back(pixel);
    img1.pixels = p;
}

void Image::test(const string &exampleName)
{
    ifstream file(exampleName, ios::binary);
    if (file.is_open())
    {
        int count = 0;
        Image img2;
        img2.deSerialize(file); // READ DATA FROM FILE

        // Test Header
        if (!(header == img2.header))
            cout << "TESTS FAILED. ISSUES FOUND IN HEADER FILE: " << exampleName << endl;

        // Test Data
        for (int i = 0; i < img2.pixels.size(); i++)
        {
            if (!(pixels[i] == img2.pixels[i]))
                count++;
        }

        if (count == 0)
            cout << exampleName << " HAS PASSED ALL TESTS!\n";
        else
            cout << "TESTS FAILED. TOTAL NUMBER OF ISSUES FOUND IN DATA TERMINATION IN " << exampleName << ": " << count
                 << endl;

    } else
        cout << "FILE NOT OPENED, terminating test for this part.\n";
}

