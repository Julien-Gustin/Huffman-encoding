#include "coding.h"

bool decode(const BinarySequence* source, CharVector* dest, const CodingTree* tree, unsigned char eof){
  BinarySequence** table = ctCodingTable(tree);
  Decoded tmp;
  tmp.character = -1;
  tmp.nextBit = 0;

  while(tmp.nextBit < biseGetNumberOfBits(source)){
    tmp = ctDecode(tree, source, tmp.nextBit);
    if(tmp.character == eof){
      for(size_t i = 0; i < 127; i++)
          biseFree(table[i]);

      free(table);

      printf("yo");
      return 1;
    }
    cvAdd(dest, tmp.character);
  }

    return 0;
}
