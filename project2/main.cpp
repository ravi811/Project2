
#include <iostream>
#include <vector>
#include <fstream>
#include "imageStuff.h"

using namespace std;
int main() {
    ifstream layer1,pattern1,pattern12,pattern2,car,layer_red,layer_green,layer_blue;
    ifstream layer12,layer13,layer14,layer2, text, text2,circles,car2, example;
    imageHeader Head1,Head2,Head3,temp, Example;
    imageHeader part1,part2,part3,part4,part5,part6,part7,part9,part10;
    ofstream outFile1("output/part1.tga",ios_base::out|ios_base::binary);
    ofstream outFile2("output/part2.tga",ios_base::out|ios_base::binary);
    ofstream outFile3("output/part3.tga",ios_base::out|ios_base::binary);
    ofstream outFile4("output/part4.tga",ios_base::out|ios_base::binary);
    ofstream outFile5("output/part5.tga",ios_base::out|ios_base::binary);
    ofstream outFile6("output/part6.tga",ios_base::out|ios_base::binary);
    ofstream outFile7("output/part7.tga",ios_base::out|ios_base::binary);
    ofstream outFile81("output/part8_r.tga",ios_base::out|ios_base::binary);
    ofstream outFile82("output/part8_g.tga",ios_base::out|ios_base::binary);
    ofstream outFile83("output/part8_b.tga",ios_base::out|ios_base::binary);
    ofstream outFile9("output/part9.tga",ios_base::out|ios_base::binary);
    ofstream outFile10("output/part10.tga",ios_base::out|ios_base::binary);
////CASE 1

            layer1.open("input/layer1.tga", ios_base::in | ios_base::binary);
            pattern1.open("input/pattern1.tga", ios_base::in | ios_base::binary);
            example.open("examples/EXAMPLE_part1.tga",ios_base::in|ios_base::binary);
            Head1.readIn(layer1);
            Head2.readIn(pattern1);
            Example.readIn(example);
            part1.insertHeader(Head1);
            part1.MultBlend(Head1, Head2);
            part1.Write(outFile1);
            QuickCompare(1,part1,Example);
            layer1.close();
            pattern1.close();
            example.close();

////CASE 2

            layer12.open("input/layer2.tga", ios_base::in | ios_base::binary);
            car.open("input/car.tga", ios_base::in | ios_base::binary);
            example.open("examples/EXAMPLE_part2.tga", ios_base::in|ios_base::binary);
            Head1.readIn(layer12);
            Head2.readIn(car);
            Example.readIn(example);
            part2.insertHeader(Head1);
            part2.SubBlend(Head2,Head1);
            part2.Write(outFile2);
            QuickCompare(2,part2,Example);
            layer12.close();
            car.close();
            example.close();


////CASE 3
            layer13.open("input/layer1.tga", ios_base::in | ios_base::binary);
            pattern2.open("input/pattern2.tga", ios_base::in | ios_base::binary);
            text.open("input/text.tga", ios_base::in| ios_base::binary);
            example.open("examples/EXAMPLE_part3.tga", ios_base::in|ios_base::binary);
            Head1.readIn(layer13);
            Head2.readIn(pattern2);
            Head3.readIn(text);
            Example.readIn(example);
            temp.insertHeader(Head1);
            temp.MultBlend(Head1,Head2);
            part3.insertHeader(Head1);
            part3.Screen(temp,Head3);
            part3.Write(outFile3);
            QuickCompare(3,part3,Example);
            layer13.close();
            pattern2.close();
            text.close();
            example.close();
////CASE 4
            layer2.open("input/layer2.tga", ios_base::in | ios_base::binary);
            circles.open("input/circles.tga", ios_base::in | ios_base::binary);
            pattern2.open("input/pattern2.tga", ios_base::in | ios_base::binary);
                example.open("examples/EXAMPLE_part4.tga", ios_base::in|ios_base::binary);
            Head1.readIn(layer2);
            Head2.readIn(circles);
            Head3.readIn(pattern2);
                Example.readIn(example);
            temp.insertHeader(Head1);
            temp.MultBlend(Head1,Head2);
            part4.insertHeader(Head1);
            part4.SubBlend(temp,Head3);
            part4.Write(outFile4);
                QuickCompare(4,part4,Example);
            layer2.close();
            circles.close();
            pattern2.close();
                example.close();
////CASE 5
            layer1.open("input/layer1.tga", ios_base::in | ios_base::binary);
            pattern12.open("input/pattern1.tga", ios_base::in | ios_base::binary);
                example.open("examples/EXAMPLE_part5.tga", ios_base::in|ios_base::binary);
            Head1.readIn(layer1);
            Head2.readIn(pattern12);
                Example.readIn(example);
            part5.insertHeader(Head1);
            part5.Overlay(Head1,Head2);
            part5.Write(outFile5);
                QuickCompare(5,part5,Example);
            layer1.close();
            pattern12.close();
                example.close();
////CASE 6
            car.open("input/car.tga", ios_base::in | ios_base::binary);
                example.open("examples/EXAMPLE_part6.tga", ios_base::in|ios_base::binary);
            Head1.readIn(car);
                Example.readIn(example);
            part6.insertHeader(Head1);
            part6.AddGreen(Head1);
            part6.Write(outFile6);
                QuickCompare(6,part6,Example);
            car.close();
                example.close();
////CASE 7
            car.open("input/car.tga", ios_base::in | ios_base::binary);
            example.open("examples/EXAMPLE_part7.tga", ios_base::in|ios_base::binary);
            Head1.readIn(car);
                Example.readIn(example);
            part7.insertHeader(Head1);
            part7.ScaleRedBlue(Head1);
            part7.Write(outFile7);
                QuickCompare(7,part7,Example);
            car.close();
                example.close();
////CASE 8
            car.open("input/car.tga", ios_base::in | ios_base::binary);
                example.open("examples/EXAMPLE_part8_r.tga", ios_base::in|ios_base::binary);
            Head1.readIn(car);
                Example.readIn(example);
            imageHeader Red, Green, Blue;
            Red.insertHeader(Head1);
            Blue.insertHeader(Head1);
            Green.insertHeader(Head1);
            Red.SplitRed(Head1);
            Green.SplitGreen(Head1);
            Blue.SplitBlue(Head1);
            Red.Write(outFile81);
                QuickCompare(81, Red,Example);
                example.close();
                example.open("examples/EXAMPLE_part8_g.tga", ios_base::in|ios_base::binary);
                Example.readIn(example);
            Green.Write(outFile82);
                QuickCompare(82,Green,Example);
                example.close();
                example.open("examples/EXAMPLE_part8_b.tga", ios_base::in|ios_base::binary);
                Example.readIn(example);
            Blue.Write(outFile83);
                QuickCompare(83, Blue,Example);
            car.close();
                example.close();
////CASE 9
            layer_red.open("input/layer_red.tga", ios_base::in | ios_base::binary);
            layer_green.open("input/layer_green.tga", ios_base::in | ios_base::binary);
            layer_blue.open("input/layer_blue.tga", ios_base::in | ios_base::binary);
            example.open("examples/EXAMPLE_part9.tga", ios_base::in|ios_base::binary);
            Head1.readIn(layer_red);
            Head2.readIn(layer_green);
            Head3.readIn(layer_blue);
            Example.readIn(example);
            part9.insertHeader(Head1);
            part9.combine(Head1,Head2,Head3);
            part9.Write(outFile9);
            QuickCompare(9,part9,Example);
            layer_blue.close();
            layer_green.close();
            layer_red.close();
            example.close();
////CASE 10
        text2.open("input/text2.tga", ios_base::in | ios_base::binary);
        example.open("examples/EXAMPLE_part10.tga", ios_base::in|ios_base::binary);
            Head1.readIn(text2);
            Example.readIn(example);
            part10.insertHeader(Head1);
            part10.imageFlip(Head1);
            part10.Write(outFile10);
            QuickCompare(10,part10,Example);
            example.close();
            text2.close();



    return 0;
}





