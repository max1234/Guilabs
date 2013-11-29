#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <QFile>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <gmp.h>
#include "algorithms.h"

class ElGamal
{
public:
    ElGamal();
    void GenerateKeys(QFile *PublicKey, QFile *PrivateKey, QFile *Randomize, unsigned int numBits);
    void Encrypt(QFile *Input, QFile *Output, QFile *PublicKey);
    void Decrypt(QFile *Input, QFile *Output, QFile *PrivateKey);
private:
    mpz_t p, g, x, y;
    void PrintStr(char *str, QFile *file, unsigned int numBytes);
    void ConvertStr(char *inputStr, char *outputStr, unsigned int length);
};
#endif
