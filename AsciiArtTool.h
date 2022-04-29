//
// Created by PC on 25/4/2022.
//

#ifndef RLELIST_C_ASCIIARTTOOL_H
#define RLELIST_C_ASCIIARTTOOL_H

RLEList asciiArtRead(FILE* in_stream);
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //RLELIST_C_ASCIIARTTOOL_H
