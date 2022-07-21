/*
    bitStream 
         - implementa operaçoes de manipulação de de bits em arquivos

    Implementado por: Jose J. Camata
    Data: 21/07/2022
    Disciplina: Estrutura de Dados II

 */

#ifndef BITSTREAM_H__
#define BITSTREAM_H__

#include <cstdint>
#include <cstring>
#include <cassert>
#include <fstream>

using namespace std;

class bitStream{

    public:
        bitStream();      
        void    setBit(uint8_t pos, uint8_t bit); // seta o bit na posição pos com o valor bit.
        uint8_t getBit(uint8_t k);                // retorna o bit na posição k da palavra.
    protected:
        uint8_t  buffer;     // palavra de 8 bits
        uint8_t  bitPos;     // posição do bit no buffer
        uint8_t buffer_size; // numero de bits da palavra.
};


class outPutBitStream : public bitStream { 
    public:
        outPutBitStream(const char* filename); // construtor: abre o arquivo para escrita.
        void writeBit(uint8_t bit);            // escreve o bit no arquivo.
        void close();                          // fecha o arquivo.
        ~outPutBitStream();                    // destrutor: fecha o arquivo.
    private:
        uint64_t bitCount;                     // numero total de bits escritos.
        ofstream outFile;                      // arquivo de escrita.
};

class inPutBitStream : public bitStream { 
    public:
        inPutBitStream(const char* filename); // construtor: abre o arquivo para leitura.
        uint8_t readBit();                    // lê o bit do arquivo.
        bool    eof();                        // retorna true se o arquivo estiver no fim.
        void close();                         // fecha o arquivo.
        ~inPutBitStream();                    // destrutor: fecha o arquivo.
    private:
        uint64_t bitCount;                    // numero total de bits lidos.
        ifstream inFile;                      // arquivo de leitura.
};


#endif /* BITSTREAM_H__ */
