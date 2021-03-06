#include "coding.h"

bool decode(const BinarySequence* source, CharVector* dest, const CodingTree* tree, unsigned char eof){

  Decoded tmp;
  tmp.character = -1;
  tmp.nextBit = 0;

  while(tmp.nextBit < biseGetNumberOfBits(source)){ //traduit une séquance de bit
    tmp = ctDecode(tree, source, tmp.nextBit); // traduit une sequence de bit jusqu'à ce quand la suite de bit mène à un character

    if(tmp.character == eof)
      return 1;

    cvAdd(dest, tmp.character);
  }
    return 0;
}
