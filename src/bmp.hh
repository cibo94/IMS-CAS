/**
 * @file bmp.cpp
 * @author Miroslav Cibulka
 * @created 12/6/15
 * @copyright Copyright (c) 2015 XXX
 * @brief BMP class
 * @detail
 *
 */


#pragma once


#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <math.h>


class BMP :
    public ::std::ofstream
  {
  typedef ::std::ofstream _BaseT;
public:
    BMP(::std::string input, int w, int h) :
        _BaseT(input, ::std::ofstream::binary),
        _width(w), _height(h)
    {
        padSize = (4 - (w * 3) % 4) % 4;
        int sizeData = w * h * 3 + h * padSize;
        size_t sizeAll = sizeData + sizeof(file) + sizeof(info);

        file[2] = (unsigned char) (sizeAll);
        file[3] = (unsigned char) (sizeAll >> 8);
        file[4] = (unsigned char) (sizeAll >> 16);
        file[5] = (unsigned char) (sizeAll >> 24);

        info[4] = (unsigned char) (w);
        info[5] = (unsigned char) (w >> 8);
        info[6] = (unsigned char) (w >> 16);
        info[7] = (unsigned char) (w >> 24);

        info[8] = (unsigned char) (h);
        info[9] = (unsigned char) (h >> 8);
        info[10] = (unsigned char) (h >> 16);
        info[11] = (unsigned char) (h >> 24);

        info[20] = (unsigned char) (sizeData);
        info[21] = (unsigned char) (sizeData >> 8);
        info[22] = (unsigned char) (sizeData >> 16);
        info[23] = (unsigned char) (sizeData >> 24);

        this->write((char *) file, sizeof(file));
        this->write((char *) info, sizeof(info));
      }

    ::std::ofstream &operator<<(::std::vector<unsigned> data)
      {
        unsigned char pad[3] = {0, 0, 0};

        for (int y = 0;
             y < _height;
             ++y)
          {
            for (int x = 0;
                 x < _width;
                 ++x)
              {
                unsigned p = data[y * _width + x];
                unsigned char pixel[3];
                pixel[0] = (unsigned char) (p & 0x000000FF);
                pixel[1] = (unsigned char) ((p >> 8) & 0x000000FF);
                pixel[2] = (unsigned char) ((p >> 16) & 0x000000FF);
                this->write((char *) pixel, 3);
              }
            this->write((char *) pad, padSize);
          }
        return *this;
      }

    virtual ~BMP()
      { }

private:
    int padSize, _width, _height;

    unsigned char file[14] = {
        'B', 'M', // magic
        0, 0, 0, 0, // size in bytes
        0, 0, // app data
        0, 0, // app data
        40 + 14, 0, 0, 0 // start of data offset
    };
    unsigned char info[40] = {
        40, 0, 0, 0, // info hd size
        0, 0, 0, 0, // width
        0, 0, 0, 0, // heigth
        1, 0, // number color planes
        24, 0, // bits per pixel
        0, 0, 0, 0, // compression is none
        0, 0, 0, 0, // image bits size
        0x13, 0x0B, 0, 0, // horz resoluition in pixel / m
        0x13, 0x0B, 0, 0, // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
        0, 0, 0, 0, // #colors in pallete
        0, 0, 0, 0, // #important colors
    };
  };
