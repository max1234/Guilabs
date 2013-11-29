#ifndef MD5_H
#define MD5_H

#include <QFile>
#include <stdio.h>
#include <string.h>
#include <math.h>

static unsigned char MD5PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static unsigned char S[16] = {7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21};

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

class MD5
{
public:

    MD5();
    char* digestFile(QFile *file);

private:

    struct __context_t {
      __UINT32_TYPE__ state[4];
      __UINT32_TYPE__ count[2]; //number of bits, mod 2^64
      __UINT8_TYPE__ buffer[64]; //input
    } context ;



    __UINT32_TYPE__ K[64];
    __UINT8_TYPE__ digestRaw[16];
    char digestChars[33];

    void MD5Transform(__UINT32_TYPE__ state[4], __UINT8_TYPE__ block[64]);
    void Update(__UINT8_TYPE__ *input, __UINT16_TYPE__ inputLen);
    void Final();
    void Init();
    void Encode(__UINT8_TYPE__ *output, __UINT32_TYPE__ *input, __UINT16_TYPE__ len);
    void Decode(__UINT32_TYPE__ *output, __UINT8_TYPE__ *input, __UINT16_TYPE__ len);

};

#endif
