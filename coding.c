#include "coding.h"

bool encode(const CharVector* source, BinarySequence* dest, const CodingTree* tree, unsigned char eof) {
    BinarySequence** table = ctCodingTable(tree);
    if(!table){
        printf("hehon\n");
        return false;
      }

    bool success = true;
    char c;
    for (size_t i = 0; i < cvSize(source); i++) {
        c = cvGet(source, i);
        if(c < 0 || c >= 127) // Filtering out non-ascii
            continue;
        success &= biseAddSequence(dest, table[(size_t)c]);
    }
    //ctPrint(tree, 0, "test");
    // add end of file code
    success &= biseAddSequence(dest, table[eof]);

    for(size_t i = 0; i < 127; i++)
        biseFree(table[i]);
    free(table);

    return success;
}

/* ------------------------------------------------------------------------- *
 * Decode an encoded text using the given coding tree.
 *
 * PARAMETERS
 * source     The binary sequence to decode.
 * dest       A vector where to write the decoded characters.
 * tree       The coding tree to use for encoding. All codes found in
 *            source should have a corresponding decoding path in this tree.
 * eof        The character indicating the end of the encoded content. When
 *            reached, the decode function should ignore the remaining bits
 *            in source.
 *
 * RETURN
 * success    True on success, false on error
 * ------------------------------------------------------------------------- */
// bool decode(const BinarySequence* source, CharVector* dest, const CodingTree* tree, unsigned char eof){
//
// }
