
#include "bitstream.h"

#include <iostream>
using namespace std;

bitStream::bitStream():
    buffer(0),
    bitPos(0),
    buffer_size(8)
{
}

// TODO: implementar o método setBit.
// Exemplo de uso: setar o 4 bit para 1     
// Status do buffer:  00001001
// pos=4                 ^
// bit=1
// Etapas: criar mascara deslocando bit em pos posicoes: bit << pos
//  mask              00010000
// Aplicar OR entre buffer e mask
//       00001001   OR
//       00010000   
//       --------
//       00011001
// Armazendar resultado final em buffer
void bitStream::setBit(uint8_t pos, uint8_t bit)
{

    
}

// TODO: Implementar a extração de bit
// Exemplo de uso:  retornar o bit na quarta posição do buffer      
// Status do buffer:  00011001
// pos=4                 ^
// Etapas: criar mascara deslocando 1 em pos posicoes: 1 << pos
//  mask              00010000
// Aplicar AND entre buffer e mask
//       00011001   AND
//       00010000   
//       --------
//       00010000
// Deslocar 4 (pos) bits a direira e retorna o resultado
//       00000001
uint8_t bitStream::getBit(uint8_t k)
{


}


outPutBitStream::outPutBitStream(const char* filename):
    bitStream(),  bitCount(0),
    outFile(filename, ios::out | ios::binary)
{
    if(!outFile.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        exit(1);
    }
    // deixamos um espaço para o bitCount no inicio do arquivo binário.
    outFile.write((char*)&bitCount, sizeof(uint64_t));
}

void outPutBitStream::writeBit(uint8_t bit)
{
    // Se o bitPos for igual  o tamanho do buffer, precisamos escrever o buffer no arquivo
    // e reiniciar o bitPos e o buffer
    if(bitPos == buffer_size)
    {
        outFile.write((char*)&buffer, sizeof(uint8_t));
        bitPos = 0;
        buffer   = 0;
    }

    // Caso contrário, escrevemos o bit no buffer e incrementamos os contadores.
    setBit(bitPos, bit);
    bitPos++;
    bitCount++;
}


void outPutBitStream::close()
{
    // escrevemos o buffer no arquivo.
    if(bitPos > 0)
    {
        outFile.write((char*)&buffer, sizeof(uint8_t));
    }
    // Escrevemos o bitCount no espaco reservado no inicio do arquivo.
    outFile.seekp(0, ios::beg);
    outFile.write((char*)&bitCount, sizeof(uint64_t));
    outFile.seekp(0, ios::end);
    // fechamos o arquivo.
    outFile.close();
}

outPutBitStream::~outPutBitStream()
{
    close();
}

inPutBitStream::inPutBitStream(const char* filename):
    bitStream(),  bitCount(0),
    inFile(filename, ios::in | ios::binary)
{
    if(!inFile.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        exit(1);
    }
    // lêmos o bitCount do inicio do arquivo.
    inFile.read((char*)&bitCount, sizeof(uint64_t));
}

uint8_t inPutBitStream::readBit()
{
    // se bitpos for zero, precisamos ler um nova palavra do arquivo.
   if(bitPos == 0)
    {
        inFile.read((char*)&buffer, sizeof(uint8_t));
        
    }
    // retornamos o bit na posição bitPos do buffer.
    uint8_t bit =  getBit(bitPos);
    bitPos++;
    bitCount--;

    // se o bitPos for o tamanho do buffer, precisamos zera-lo para que 
    // na proxima chamada o buffer seja lido.
    if(bitPos == buffer_size)
    {
        bitPos = 0;
    }
  
    return bit;
}

// Verifica se o arquivo está no fim
// ou seja, se todos os bits foram lidos.
bool inPutBitStream::eof()
{
    return bitCount == 0;
}

void inPutBitStream::close()
{
    inFile.close();
}

inPutBitStream::~inPutBitStream()
{
    close();
}
