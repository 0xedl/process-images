#include <iostream>
#include <vector>
#include "Image.h"
using namespace std;

int main(){

    // ****************************** IMAGE VARIABLES ****************************** //
    Image layer1Image, pattern1Image, layer2Image, carImage, pattern2Image, circlesImage, textImage,
            layerBlueImage, layerGreenImage, layerRedImage, text2Image;

    // ****************************** OPEN FILES ****************************** //
    ifstream layer1File("input/layer1.tga", ios::binary);
    ifstream pattern1File("input/pattern1.tga", ios::binary);
    ifstream layer2File("input/layer2.tga", ios::binary);
    ifstream carFile("input/car.tga", ios::binary);
    ifstream pattern2File("input/pattern2.tga", ios::binary);
    ifstream circlesFile("input/circles.tga", ios::binary);
    ifstream textFile("input/text.tga", ios::binary);
    ifstream layerBlueFile("input/layer_blue.tga", ios::binary);
    ifstream layerGreenFile("input/layer_green.tga", ios::binary);
    ifstream layerRedFile("input/layer_red.tga", ios::binary);
    ifstream text2File("input/text2.tga", ios::binary);

    // CHECK IF ALL FILES OPENED CORRECTLY & CREATE IMAGE OBJECTS FROM EACH FILE
    if (layer1File.is_open() && pattern1File.is_open() && layer2File.is_open() && carFile.is_open()
        && pattern2File.is_open() && circlesFile && textFile.is_open() && layerBlueFile
        && layerGreenFile && layerRedFile && text2File) {

        // READ DATA FROM FILE
        layer1Image.deSerialize(layer1File);
        pattern1Image.deSerialize(pattern1File);
        layer2Image.deSerialize(layer2File);
        carImage.deSerialize(carFile);
        pattern2Image.deSerialize(pattern2File);
        circlesImage.deSerialize(circlesFile);
        textImage.deSerialize(textFile);
        layerBlueImage.deSerialize(layerBlueFile);
        layerGreenImage.deSerialize(layerGreenFile);
        layerRedImage.deSerialize(layerRedFile);
        text2Image.deSerialize(text2File);

    } else {
        cout << "Error reading in files.";
    }


    // ******************************                                   ****************************** //
    // ****************************** PT1. MULTIPLY LAYER 1 & PATTERN 1 ****************************** //
    // ******************************                                   ****************************** //
    Image part1 = layer1Image * pattern1Image;

    // WRITE FILE
    ofstream out1("output/part1.tga");
    part1.serialize(out1);
    
    // TEST
    cout << "\n****************************** PART 1 TEST ***********************************************\n";
    part1.test("examples/EXAMPLE_part1.tga");


    // ******************************                               ****************************** //
    // ****************************** PT2. SUBTRACT LAYER 2 & CAR  ****************************** //
    // ******************************                               ****************************** //
    Image part2 = carImage - layer2Image;

    // WRITE FILE
    ofstream out2("output/part2.tga");
    part2.serialize(out2);

    // TEST
    cout << "\n****************************** PART 2 TEST ***********************************************\n";
    part2.test("examples/EXAMPLE_part2.tga");


    // ******************************                                   ****************************** //
    // ****************************** PT3. MULTIPLY LAYER 1 & PATTERN 2 ****************************** //
    // ******************************                                   ****************************** //
    Image part3;
    Image temp = layer1Image * pattern2Image;

    // SCREEN PIXELS
    part3.screen(textImage, temp);

    // WRITE FILE
    ofstream out3("output/part3.tga");
    part3.serialize(out3);

    // TEST
    cout << "\n****************************** PART 3 TEST ***********************************************\n";
    part3.test("examples/EXAMPLE_part3.tga");


    // ******************************                                 ****************************** //
    // ****************************** PT4. MULTIPLY LAYER 2 & CIRCLES ****************************** //
    // ******************************                                 ****************************** //
    Image part4 = layer2Image * circlesImage - pattern2Image;

    // WRITE FILE
    ofstream out4("output/part4.tga");
    part4.serialize(out4); // WRITE MULTIPLIED DATA TO FILE

    // TEST
    cout << "\n****************************** PART 4 TEST ***********************************************\n";
    part4.test("examples/EXAMPLE_part4.tga");


    // ******************************                                  ****************************** //
    // ****************************** PT5. OVERLAY LAYER 1 & PATTERN 1 ****************************** //
    // ******************************                                  ****************************** //
    Image part5;
    part5.overlay(layer1Image, pattern1Image);

    // WRITE FILE
    ofstream out5("output/part5.tga");
    part5.serialize(out5); // WRITE OVERLAY DATA TO FILE

    // TEST
    cout << "\n****************************** PART 5 TEST ***********************************************\n";
    part5.test("examples/EXAMPLE_part5.tga");


    // ******************************                                   ****************************** //
    // ****************************** PT6. CAR ADD 200 TO GREEN CHANNEL ****************************** //
    // ******************************                                   ****************************** //
    Image part6;
    unsigned char c = 200;
    part6.addOneChannel(carImage, c);

    // WRITE FILE
    ofstream out6("output/part6.tga");
    part6.serialize(out6); // WRITE MULTIPLIED DATA TO FILE

    // TEST
    cout << "\n****************************** PART 6 TEST ***********************************************\n";
    part6.test("examples/EXAMPLE_part6.tga");


    // ******************************                                ****************************** //
    // ****************************** PT7. SCALE RED BY 4, BLUE BY 0 ****************************** //
    // ******************************                                ****************************** //
    Image part7;
    int blueScale = 0;
    int greenScale = 1;
    int redScale = 4;

    part7.scale(carImage, blueScale, greenScale, redScale);

    // WRITE FILE
    ofstream out7("output/part7.tga");
    part7.serialize(out7); // WRITE MULTIPLIED DATA TO FILE

    // TEST
    cout << "\n****************************** PART 7 TEST ***********************************************\n";
    part7.test("examples/EXAMPLE_part7.tga");


    // ******************************                                     ****************************** //
    // ****************************** PT8. WRITE EACH CHANNEL TO SEP FILE ****************************** //
    // ******************************                                     ****************************** //
    Image part8_r, part8_g, part8_b;
    Image::separateChannels(carImage, part8_b, part8_g, part8_r);

    // WRITE FILE
    ofstream outB("output/part8_b.tga");
    part8_b.serialize(outB); // WRITE MULTIPLIED DATA TO FILE
    ofstream outG("output/part8_g.tga");
    part8_g.serialize(outG); // WRITE MULTIPLIED DATA TO FILE
    ofstream outR("output/part8_r.tga");
    part8_r.serialize(outR); // WRITE MULTIPLIED DATA TO FILE

    // TEST
    cout << "\n****************************** PART 8 TEST ***********************************************\n";
    part8_b.test("examples/EXAMPLE_part8_b.tga");
    part8_g.test("examples/EXAMPLE_part8_g.tga");
    part8_r.test("examples/EXAMPLE_part8_r.tga");


    // ******************************                           ****************************** //
    // ****************************** PT9. COMBINE THREE LAYERS ****************************** //
    // ******************************                           ****************************** //
    Image part9;
    part9.combineThreeLayers(layerBlueImage, layerGreenImage, layerRedImage);

    // WRITE FILE
    ofstream out9("output/part9.tga");
    part9.serialize(out9); // WRITE MULTIPLIED DATA TO FILE

    // TEST
    cout << "\n****************************** PART 9 TEST ***********************************************\n";
    part9.test("examples/EXAMPLE_part9.tga");


    // ******************************                       ****************************** //
    // ****************************** PT10. FLIP IMAGE 180  ****************************** //
    // ******************************                       ****************************** //
    Image part10;
    part10.flip(text2Image);

    // WRITE FILE
    ofstream out10("output/part10.tga");
    part10.serialize(out10); // WRITE MULTIPLIED DATA TO FILE

    // TEST
    cout << "\n****************************** PART 10 TEST **********************************************\n";
    part10.test("examples/EXAMPLE_part10.tga");


    // ******************************                                                   ****************************** //
    // ****************************** EXTRA CREDIT COMBINE CAR, CIRCLES, PATTERN1, TEXT ****************************** //
    // ******************************                                                   ****************************** //
    Image ec1;
    Image ec2;
    ec1 = carImage + circlesImage;
    ec2 = textImage + pattern1Image;
    Image::combineVertical(ec1, ec2);

    // WRITE FILE
    ofstream outEC("output/extracredit.tga");
    ec1.serialize(outEC); // WRITE MULTIPLIED DATA TO FILE

    // TEST
    cout << "\n****************************** EXTRA CREDIT TEST *****************************************\n";
    ec1.test("examples/EXAMPLE_extracredit.tga");

    return 0;
}

