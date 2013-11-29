#include "rsa.h"

RSA::RSA()
{
}

void RSA::GenerateKeys(QFile *PublicKey, QFile *PrivateKey, QFile *Randomize, unsigned int numBits)
{
    //printf("Start\n");
    mpz_t p, q, phi, pDec, qDec;

    Algorithms algo;

    char e_str[100];
    char *n_str = new char[numBits / 4 + 2];
    char *d_str = new char[numBits / 4 + 2];
    char *p_str = new char[numBits / 8 + 2];
    char *q_str = new char[numBits / 8 + 2];

    unsigned int initRandom = 0;
    unsigned int bufIO;

    mpz_init(p);
    mpz_init(q);
    mpz_init(phi);

    mpz_init(pDec);
    mpz_init(qDec);


    mpz_init(d);
    mpz_init(e);
    mpz_init(n);

    //generate p, q
    Randomize->getChar((char *)&initRandom);
    initRandom <<= 8;
    Randomize->getChar((char *)&bufIO);
    initRandom |= bufIO;

    algo.GeneratePrime(p, numBits / 2, initRandom);
    mpz_get_str(p_str,16,p);

    Randomize->getChar((char *)&bufIO);
    initRandom ^= (bufIO << 8);
    Randomize->getChar((char *)&bufIO);
    initRandom ^= bufIO;

    algo.GeneratePrime(q, numBits / 2, initRandom);
    mpz_get_str(q_str,16,q);

    //n=p*q
    mpz_mul(n,p,q);
    mpz_get_str(n_str,16,n);

    //pDec=(p-1); qDec=(q-1)
    mpz_sub_ui(pDec,p,(unsigned long)1);
    mpz_sub_ui(qDec,q,(unsigned long)1);

    //phi=(p-1)*(q-1)
    mpz_mul(phi,qDec,pDec);

    Randomize->getChar((char *)&bufIO);
    initRandom ^= (bufIO << 8);
    Randomize->getChar((char *)&bufIO);
    initRandom ^= bufIO;

    srand(initRandom);

    // generate e
    mpz_t gcd;
    mpz_init(gcd);

    unsigned long e_int;
    while(true)
    {
        e_int = 1;
        e_int <<= (int)((numBits < 30 ? numBits : 30) * rand() / (RAND_MAX + 1.0));
        e_int++;

        while(true)
        {
            if((e_int >> (numBits < 30 ? numBits : 30)))
            {
                e_int = 1;
                e_int <<= (int)((numBits < 30 ? numBits : 30) * rand() / (RAND_MAX + 1.0));
                e_int++;
            }
            else
            {
                e_int <<= 1;
                e_int--;
            }

            mpz_gcd_ui(gcd,phi,e_int);
            if((mpz_cmp_ui(gcd,(unsigned long)1) == 0) && (mpz_cmp_ui(phi, e_int) == 1))
            {
                mpz_set_ui(e,e_int);
                break;
            }
        }


        if(mpz_invert(d, e, phi) != 0)
            break;

    }

    mpz_get_str(e_str,16,e);
    mpz_get_str(d_str,16,d);

    char *stringBufIO = new char[2 * numBits + 8];
    memset(stringBufIO, 0, 2 * numBits + 8);
    sprintf(stringBufIO ,"%x\n%s\n%s", numBits, n_str, e_str);
    PublicKey->write(stringBufIO);
    memset(stringBufIO, 0, 2 * numBits + 8);
    sprintf(stringBufIO, "%x\n%s\n%s\n%s\n%s", numBits, n_str, p_str, q_str, d_str);
    PrivateKey->write(stringBufIO);

    free(stringBufIO);

    mpz_clear(gcd);

    mpz_clear(pDec);
    mpz_clear(qDec);

    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi);

    mpz_clear(d);
    mpz_clear(e);
    mpz_clear(n);
}

void RSA::Encrypt(QFile *Input, QFile *Output, QFile *PublicKey)
{
    //printf("Start\n");
    unsigned int i, j;
    unsigned int numBits, inputBytes, outputBytes;

    char *stringBufIO = new char[10];
    //bzero(stringBufIO, 10);
    memset(stringBufIO, 0, 10);

    PublicKey->read(stringBufIO, 10);
    PublicKey->reset();
    sscanf(stringBufIO, "%x\n", &numBits);
    free(stringBufIO);

    stringBufIO = new char[numBits + 8];
    //bzero(stringBufIO, numBits + 8);
    memset(stringBufIO, 0, numBits + 8);

    PublicKey->read(stringBufIO, numBits + 8);

    outputBytes = (numBits % 8 ? numBits / 8 - 1 : numBits / 8);

    inputBytes = (numBits % 8 ? numBits / 8 :  numBits / 8 - 1);

    char *n_str = new char[numBits / 4 + 2];

    char *c_str = new char[inputBytes + 1];
    char *IOstring = new char[outputBytes + 1];
    char e_str[100];

    sscanf(stringBufIO, "%*x\n%s\n%s\n", n_str, e_str);
    free(stringBufIO);

    mpz_init(M);
    mpz_init(C);
    mpz_init(e);
    mpz_init(n);

    mpz_set_str(n,n_str,16);
    mpz_set_str(e,e_str,16);

    bool isEOF = false;

    while(!isEOF)
    {
        for(i = 0, j = 0; i < inputBytes && !isEOF; i++, j++)
            if(!Input->getChar((char *)&IOstring[i]))
                isEOF = true;
        if(i)
        {
            if(!isEOF)
                IOstring[j] = '\0';
            else if (j - 1)
                IOstring[--j] = '\0';
            else
                break;
        }
        else
            break;

        char* m_str = new char[j * 2 + 1];
        ConvertStr(IOstring, m_str, j);

        mpz_set_str(M,m_str,16);

        //C=M^e(mod e)
        mpz_powm(C,M,e,n);
        mpz_get_str(c_str,16,C);

        PrintStr(c_str, Output, outputBytes);

        free(m_str);
    }

    //printf("Stop\n");

    mpz_clear(e);
    mpz_clear(n);
    mpz_clear(M);
    mpz_clear(C);
}


void RSA::Decrypt(QFile *Input, QFile *Output, QFile *PrivateKey)
{
    //printf("Start\n");

    unsigned int i, j;
    unsigned int numBits, inputBytes, outputBytes;

    char *stringBufIO = new char[10];
    //bzero(stringBufIO, 10);
    memset(stringBufIO, 0, 10);

    PrivateKey->read(stringBufIO, 10);
    PrivateKey->reset();
    sscanf(stringBufIO, "%x\n", &numBits);
    free(stringBufIO);

    stringBufIO = new char[numBits + 8];
    //bzero(stringBufIO, numBits + 8);
    memset(stringBufIO, 0, numBits + 8);

    PrivateKey->read(stringBufIO, numBits + 8);

    inputBytes = (numBits % 8 ? numBits / 8 - 1 : numBits / 8);
    outputBytes = (numBits % 8 ? numBits / 8 :  numBits / 8 - 1);

    char *n_str = new char[numBits / 4 + 2];
    char *d_str = new char[numBits / 4 + 2];

    char *m_str = new char[outputBytes + 1];
    char *IOstring = new char[inputBytes + 1];

    sscanf(stringBufIO, "%*x\n%s\n%*s\n%*s\n%s\n", n_str, d_str);
    free(stringBufIO);

    mpz_init(M);
    mpz_init(C);
    mpz_init(d);
    mpz_init(n);

    mpz_set_str(n,n_str,16);
    mpz_set_str(d,d_str,16);

    bool isEOF = false;

    while(!isEOF)
    {
        for(i = j = 0; i < inputBytes && !isEOF; i++, j++)
            if(!Input->getChar((char *)&IOstring[j]))
                isEOF = true;
        if(i)
        {
            if(!isEOF)
                IOstring[j] = '\0';
            else if (j - 1)
                IOstring[--j] = '\0';
            else
                break;
        }
        else
            break;

        char* c_str = new char[j * 2 + 1];
        ConvertStr(IOstring, c_str, j);

        mpz_set_str(C,c_str,16);

        //M=C^d(mod e)
        mpz_powm(M,C,d,n);

        mpz_get_str(m_str,16,M);

        PrintStr(m_str, Output, outputBytes);
        free(c_str);
    }

    //printf("Stop\n");

    mpz_clear(d);
    mpz_clear(n);
    mpz_clear(M);
    mpz_clear(C);
}


void RSA::PrintStr(char *str, QFile *file, unsigned int numBytes)
{
    unsigned int i, tmp = numBytes * 2 - strlen(str);
    tmp -= ((numBytes * 2 - strlen(str)) % 2);
    tmp /= 2;
    for(i = 0; i < tmp; i++)
        file->putChar(0);
    for(i = 0; i < strlen(str);)
    {
        if(((numBytes * 2 - strlen(str)) % 2) && !i)
            tmp = 0;
        else
            tmp = str[i] - (str[i++] >= 'a' ? 'a' - 10 : '0');
        tmp <<= 4;
        tmp |= str[i] - (str[i++] >= 'a' ? 'a' - 10 : '0');
        file->putChar(tmp);
    }
}

void RSA::ConvertStr(char *inputStr, char *outputStr, unsigned int length)
{
    char tmps[2];
    strcpy(outputStr,"");

    for(unsigned int i = 0, tmp; i < length; i++)
    {
        tmp = ((inputStr[i] >> 4) & 0xF);
        sprintf(tmps,"%01x",tmp);
        strcat(outputStr,tmps);

        tmp = (inputStr[i]  & 0xF);
        sprintf(tmps,"%01x",tmp);
        strcat(outputStr,tmps);
    }
}
