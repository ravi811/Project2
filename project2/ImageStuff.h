//
// Created by ravip on 8/6/2018.
//
#include <fstream>
#include<stdio.h>
#include <string.h>
#include <iostream>
#include<cmath>
#ifndef PROJECT2_IMAGESTUFF_H
#define PROJECT2_IMAGESTUFF_H

class Pixel{
public:
    unsigned char R;
    unsigned char G;
    unsigned char B;

    Pixel & operator =(const Pixel &p){
        R=p.R;
        G=p.G;
        B=p.B;
        return *this;
    }
    Pixel & operator *(const Pixel &p){
        float tempR1, tempR2, tempG1, tempG2, tempB1, tempB2;

        tempR1=R/255.0f;
        tempR2=p.R/255.0f;
        tempG1=G/255.0f;
        tempG2=p.G/255.0f;
        tempB1=B/255.0f;
        tempB2=p.B/255.0f;

        R= (unsigned char)(tempR1*tempR2*255 +0.5);
        G=(unsigned char)(tempG1*tempG2*255+0.5);
        B= (unsigned char)(tempB1*tempB2*255+0.5);
        return *this;
    }
    Pixel & operator +(const Pixel &p){
        R+=p.R;
        G+=p.G;
        B+=p.B;
        if(R>255){
            R=255;
        }
        if(G>255){
            G=255;
        }
        if(B>255){
            B=255;
        }
        return *this;
    }
    Pixel & operator -(const Pixel &p){

        R-=p.R;
        G-=p.G;
        B-=p.B;
        if(R<0){
            R=0;
        }
        if(G<0){
            G=0;
        }
        if(B<0){
            B=0;
        }
        return *this;
    }
    Pixel pixRead(std::ifstream &myFile){

            myFile.read((char*)&B,1);
            myFile.read((char*)&G,1);
            myFile.read((char*)&R,1);

        return *this;
    }

};
struct imageHeader{
    char idLength;
    char colourMapType;
    char dataTypeCode;
    short colourMapOrigin;
    short colourMapLength;
    char colourMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    Pixel * image;

    void readIn( std::ifstream &myFile){
    myFile.read(&idLength,1);
    myFile.read(&colourMapType,1);
    myFile.read(&dataTypeCode,1);
    myFile.read((char*)&colourMapOrigin,2);
    myFile.read((char*)&colourMapLength,2);
    myFile.read(&colourMapDepth,1);
    myFile.read((char*)&xOrigin,2);
    myFile.read((char*)&yOrigin,2);
    myFile.read((char*)&width, 2);
    myFile.read((char*)&height,2);
    myFile.read(&bitsPerPixel,1);
    myFile.read(&imageDescriptor,1);
    image = new Pixel[width*height];
    for(int i =0; i < width*height;i++){
        image[i].pixRead(myFile);
    }
    }

    void Write(std::ofstream &outFile){
        outFile.write(&idLength, 1);
        outFile.write(&colourMapType, 1);
        outFile.write(&dataTypeCode, 1);
        outFile.write((char*)&colourMapOrigin, 2);
        outFile.write((char*)&colourMapLength, 2);
        outFile.write(&colourMapDepth, 1);
        outFile.write((char*)&xOrigin, 2);
        outFile.write((char*)&yOrigin, 2);
        outFile.write((char*)&width, 2);
        outFile.write((char*)&height, 2);
        outFile.write(&bitsPerPixel, 1);
        outFile.write(&imageDescriptor, 1);
        for(int i = 0; i < width*height; i++){
            outFile.write(( char*)&image[i].B,1);
            outFile.write(( char*)&image[i].G,1);
            outFile.write((char*)&image[i].R,1);
        }
    }
    void insertHeader(imageHeader Head){
        this->idLength=Head.idLength;
        this->colourMapType=Head.colourMapType;
        this->dataTypeCode=Head.dataTypeCode;
        this->colourMapOrigin=Head.colourMapOrigin;
        this->colourMapLength=Head.colourMapLength;
        this->colourMapDepth=Head.colourMapDepth;
        this->xOrigin=Head.xOrigin;
        this->yOrigin=Head.yOrigin;
        this->width=Head.width;
        this->height=Head.height;
        this->bitsPerPixel=Head.bitsPerPixel;
        this->imageDescriptor=Head.imageDescriptor;
    }

    void MultBlend( imageHeader Head1, imageHeader Head2){
        int size=Head1.width*Head1.height;
        image=new Pixel[size];
        for(int i =0; i < size; i++){
            image[i]=(Head1.image[i]*Head2.image[i]);
        }
    }
    void SubBlend(imageHeader Head1, imageHeader Head2){
        int size=Head1.height*Head1.width;
        image=new Pixel[size];
        for(int i =0; i < size; i++){
            if(Head1.image[i].R > Head2.image[i].R){
                image[i].R=Head1.image[i].R-Head2.image[i].R;
            }
            else{
                image[i].R=0;
            }
            if(Head1.image[i].G > Head2.image[i].G){
                image[i].G=Head1.image[i].G-Head2.image[i].G;
            }
            else{
                image[i].G=0;
            }
            if(Head1.image[i].B > Head2.image[i].B){
                image[i].B=Head1.image[i].B-Head2.image[i].B;
            }
            else{
                image[i].B=0;
            }
        }
    }
    void AddGreen(imageHeader Head){
        image=new Pixel[Head.width*Head.height];
        for(int i = 0 ; i < Head.width*Head.height;i++) {
            image[i]=Head.image[i];
        }
        for(int i = 0; i < Head.width*Head.height;i++){
            if(image[i].G>55){
                image[i].G=255;
            }else {
                image[i].G += 200;
            }
        }
    }
    void Screen(imageHeader Head1, imageHeader Head2){
        int size=Head1.width*Head1.height;
        image=new Pixel[size];
        for(int i=0; i < size; i++){
            float R = Head1.image[i].R/255.0f;
            float G = Head1.image[i].G/255.0f;
            float B = Head1.image[i].B/255.0f;

            float R2 = Head2.image[i].R/255.0f;
            float G2 = Head2.image[i].G/255.0f;
            float B2 = Head2.image[i].B/255.0f;

            image[i].R=(1-(1-R)*(1-R2))*255 +0.5;
            image[i].G=(1-(1-G)*(1-G2))*255+0.5;
            image[i].B=(1-(1-B)*(1-B2))*255+0.5;

        }
    }
    void Overlay(imageHeader Head1, imageHeader Head2){
        int size= Head1.width*Head1.height;
        image=new Pixel[size];
        for(int i=0; i<size;i++){
            float R = Head1.image[i].R/255.0f;
            float G = Head1.image[i].G/255.0f;
            float B = Head1.image[i].B/255.0f;

            float R2 = Head2.image[i].R/255.0f;
            float G2 = Head2.image[i].G/255.0f;
            float B2 = Head2.image[i].B/255.0f;

            if(R2<=0.5f){
                image[i].R=std::round((2*R*R2)*255);
            }
            else{
                image[i].R=std::round((1-(2*(1-R)*(1-R2)))*255);
            }
            if(G2<=0.5f){
                image[i].G=std::round((2*G*G2)*255);
            }
            else{
                image[i].G=std::round((1-(2*(1-G)*(1-G2)))*255);
            }
            if(B2<=0.5f){
                image[i].B=std::round((2*B*B2)*255);
            }
            else{
                image[i].B=std::round((1-(2*(1-B)*(1-B2)))*255);
            }
        }
    }
    void ScaleRedBlue(imageHeader Head){
        int size=Head.width*Head.height;
        image=new Pixel[size];
        for(int i=0; i < Head.width*Head.height;i++){
            image[i]=Head.image[i];
        }
        for(int i =0; i<Head.width*Head.height;i++){
            image[i].B=0;
            if(image[i].R*4>255){
                image[i].R=255;
            }
            else {
                image[i].R *= 4;
            }
        }
    }
    void SplitRed(imageHeader Head){
        image= new Pixel[Head.width*Head.height];
        for(int i = 0; i < Head.width*Head.height;i++){
            image[i]=Head.image[i];
        }
        for(int i =0; i < Head.width*Head.height;i++){
            image[i].G=image[i].R;
            image[i].B=image[i].R;
        }
    }
    void SplitGreen(imageHeader Head){
        image=new Pixel[Head.width*Head.height];
        for(int i = 0; i < Head.width*Head.height;i++){
            image[i]=Head.image[i];
        }
        for(int i =0; i < Head.width*Head.height;i++){
            image[i].R=image[i].G;
            image[i].B=image[i].G;
        }
    }
    void SplitBlue(imageHeader Head){
        image=new Pixel[Head.height*Head.width];
        for(int i = 0; i < Head.width*Head.height;i++){
            image[i]=Head.image[i];
        }
        for(int i =0; i < Head.width*Head.height;i++){
            image[i].G=image[i].B;
            image[i].R=image[i].B;
        }
    }
    void combine(imageHeader Head1, imageHeader Head2, imageHeader Head3){
        image=new Pixel[Head1.width*Head1.height];
        for(int i =0; i < Head1.width*Head1.height;i++){
            image[i].R=Head1.image[i].R;
        }
        for(int i =0; i < Head1.width*Head1.height;i++){
            image[i].G=Head2.image[i].G;
        }
        for(int i =0; i < Head1.width*Head1.height;i++){
            image[i].B=Head3.image[i].B;
        }
    }
   void imageFlip(imageHeader Head){
    int size = Head.width*Head.height;
        image=new Pixel[size];
        for(int i = 0; i < size;i++){
            image[i]=Head.image[size-i-1];
        }
    }
};

    void QuickCompare(int testnum, imageHeader head1, imageHeader head2){
        int n;
        n= memcmp(head1.image, head2.image, head1.width*head1.height*3);
        if(n==0){
            std::cout<<"Test" <<testnum<<" successful!"<<std::endl;
        }
        else{
            std::cout<<"Test "<<testnum<<" failed"<<std::endl;
        }
    }



#endif //PROJECT2_IMAGESTUFF_H

