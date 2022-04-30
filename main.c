#include "RLEList.h"
#include "AsciiArtTool.h"
#define ENCODED 'e'
#define INVERTED 'i'
#define FLAGGED '-'
typedef char FLAG;

// --------------- Functions to help parse the input -------------------- //
/**
 * Handles opening a file and errors that can happen while opening.
 *
 * @param source - The original file to be opened.
 * @param destination - The file pointer where the opened file will be.
 * @param flag - READ or WRITE.
 * @return
 *  RLE_LIST_NULL_ARGUMENT if one of the parameters is NULL.
 *  RLE_LIST_ERROR if failed opening the file.
 *  RLE_LIST_SUCCESS if opened the file successfully.
 */
RLEListResult ParseFlag (FLAG* destination, const FLAG* source);
RLEListResult UnpackInput(int argc, char **argv, FLAG *flag, FILE **source, FILE **destination);

int main(int argc, char** argv){
    FLAG flag;
    FILE *source = NULL;
    FILE *destination = NULL;
    RLEListResult unpacked_success = UnpackInput(argc, argv, &flag, &source, &destination);
    if (unpacked_success != RLE_LIST_SUCCESS)
    {
        return -1;
    }

    RLEList list = asciiArtRead(source);

    if (flag == ENCODED){
        asciiArtPrintEncoded(list, destination);
    }
    else if (flag == INVERTED){
        RLEListMap(list, InvertChar);
        asciiArtPrint(list, destination);
    }

    RLEListDestroy(list);
    return 0;

}

RLEListResult ParseFlag(FLAG *destination, const FLAG *source) {
    if (source[0] == FLAGGED)
    {
        if (source[1] == ENCODED || source[1] == INVERTED)
        {
            *destination = source[1];
            return RLE_LIST_SUCCESS;
        }
        else
        {
            return RLE_LIST_ERROR;
        }
    }
    else if (source[0]) // != NULL and != FLAGGED
    {
        return RLE_LIST_ERROR;
    }
    return RLE_LIST_ERROR; //TODO: return error if (source[0] == NULL)?
}

RLEListResult UnpackInput(int argc, char **argv, FLAG *flag, FILE **source, FILE **destination) {
    if (argc != 4) // 3 args + 1 default
    {
        return RLE_LIST_NULL_ARGUMENT; // invalid amount of args
    }
    RLEListResult valid_input = ParseFlag(flag, argv[1]);
    if (valid_input != RLE_LIST_SUCCESS)
    {
        return valid_input;
    }
    *source = fopen(argv[2], READ);
    if (!*source)
    {
        return RLE_LIST_ERROR;
    }
    *destination = fopen(argv[3], WRITE);
    if (!*destination)
    {
        return RLE_LIST_ERROR;
    }

    return valid_input;
}





