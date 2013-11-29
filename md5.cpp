#include "md5.h"

MD5::MD5()
{
 Init() ;
}

void MD5::MD5Transform(__UINT32_TYPE__ state[4], __UINT8_TYPE__ block[64])
{
 __UINT32_TYPE__ a = state[0], b = state[1], c = state[2], d = state[3], temp, x[16];
 Decode (x, block, 64);
 for(int i = 0; i < 64; i++)
 {
  if (i < 16)
  {
   a += F(b, c, d) + x[i] + K[i];
   a = ROTATE_LEFT (a, S[i % 4]);
  }
  else if (i < 32)
  {
   a += G(b, c, d) + x[(int)fmod((5 * i + 1), 16)] + K[i];
   a = ROTATE_LEFT (a, S[i % 4 + 4]);
  }
  else if (i < 48)
  {
   a += H(b, c, d) + x[(int)fmod((3 * i + 5), 16)] + K[i];
   a = ROTATE_LEFT (a, S[i % 4 + 8]);
  }
  else
  {
   a += I(b, c, d) + x[(int)fmod((7 * i), 16)] + K[i];
   a = ROTATE_LEFT (a, S[i % 4 + 12]);
  }
   temp = d;
   d = c;
   c = b;
   b += a;
   a = temp;
  }
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void MD5::Update(__UINT8_TYPE__ *input, __UINT16_TYPE__ inputlength)
{
    int i, index, partlength;
    //Number of bytes mod 64
    index = (__UINT16_TYPE__)((context.count[0] >> 3) & 0x3F);

    if ((context.count[0] += ((__UINT32_TYPE__)inputlength << 3)) < ((__UINT32_TYPE__)inputlength << 3))
        context.count[1]++;
    context.count[1] += ((__UINT32_TYPE__)inputlength >> 29);

    partlength = 64 - index;

    if (inputlength >= partlength)
    {
        memcpy((__UINT16_TYPE__ *) & context.buffer[index], (__UINT16_TYPE__ *)input, partlength);
        MD5Transform (context.state, context.buffer);

        for (i = partlength; i + 63 < inputlength; i += 64)
            MD5Transform (context.state, &input[i]);
        index = 0;
    }
    else
        i = 0;

     memcpy((__UINT16_TYPE__ *) & context.buffer[index], (__UINT16_TYPE__ *)&input[i], inputlength - i);
}

void MD5::Final()
{
    __UINT8_TYPE__ bits[8];
    __UINT16_TYPE__ index, padlength;
     Encode(bits, context.count, 8);
    index = (__UINT16_TYPE__)((context.count[0] >> 3) & 0x3f);
    padlength = (index < 56) ? (56 - index) : (120 - index);
    Update(MD5PADDING, padlength);

    Update(bits, 8);

      Encode(digestRaw, context.state, 16);

    for(int pos = 0; pos < 16; pos++)
        sprintf(digestChars + (pos * 2), "%02x", digestRaw[pos]);
}

char* MD5::digestFile(QFile *file)
{
    int length;
    __UINT8_TYPE__ buffer[1024];

    while(length = file->read((char *)buffer, 1024))
        Update(buffer, length);
    Final();

    return digestChars;
}

void MD5::Init()
{
    context.count[0] = context.count[1] = 0;
    context.state[0] = 0x67452301; //A0
    context.state[1] = 0xefcdab89; //B0
    context.state[2] = 0x98badcfe; //C0
    context.state[3] = 0x10325476; //D0

    for(int counter = 0; counter < 64; counter++)
    {
        K[counter] = (__UINT32_TYPE__)floor(fabs(sin(counter + 1) * pow(2, 32)));
    }    
}

void MD5::Encode(__UINT8_TYPE__ *output, __UINT32_TYPE__ *input, __UINT16_TYPE__ length)
{
    for (int i = 0; i < length / 4; i++)
    {
        output[4 * i] = (__UINT8_TYPE__)(input[i] & 0xFF);
        output[4 * i + 1] = (__UINT8_TYPE__)((input[i] >> 8) & 0xFF);
        output[4 * i + 2] = (__UINT8_TYPE__)((input[i] >> 16) & 0xFF);
        output[4 * i + 3] = (__UINT8_TYPE__)((input[i] >> 24) & 0xFF);
    }
}

void MD5::Decode(__UINT32_TYPE__ *output, __UINT8_TYPE__ *input, __UINT16_TYPE__ length)
{
    for (int i = 0; i < length / 4; i++)
        output[i] = ((__UINT32_TYPE__)input[4 * i]) |\
                (((__UINT32_TYPE__)input[4 * i + 1]) << 8) |\
                (((__UINT32_TYPE__)input[4 * i + 2]) << 16) |\
                (((__UINT32_TYPE__)input[4 * i + 3]) << 24);
}
