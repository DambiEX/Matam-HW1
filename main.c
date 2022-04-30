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
RLEListResult OpenFile(char* source, FILE *destination, char *flag);
RLEListResult ParseFlag (FLAG* destination, FLAG* source);
RLEListResult UnpackInput(int argc, char **argv, FLAG *flag, FILE *source, FILE *destination);

int main(int argc, char** argv){
    FLAG flag;
    FILE *source, *destination; //TODO: make sure pointer syntax is correct.
    RLEListResult unpacked_success = UnpackInput(argc, argv, &flag, source, destination);
    if (unpacked_success != RLE_LIST_SUCCESS)
        return -1;

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


RLEListResult ParseFlag(FLAG *destination, FLAG *source) {
    if (source[0] == FLAGGED)
    {
        if (source[1] == ENCODED || source[1] == INVERTED)
        {
            *destination = source[1];
            return RLE_LIST_SUCCESS;
        }
        else
            return RLE_LIST_ERROR;
    }
    else if (source[0]) // != NULL and != FLAGGED
        return RLE_LIST_ERROR;
    return RLE_LIST_ERROR; //TODO: return error if (source[0] == NULL)?
}

RLEListResult UnpackInput(int argc, char **argv, FLAG *flag, FILE *source, FILE *destination) {
    if (argc != 4) // 3 args + 1 default
        return RLE_LIST_NULL_ARGUMENT; // invalid amount of args
    RLEListResult valid_input = ParseFlag(flag, argv[1]);
    if (valid_input != RLE_LIST_SUCCESS)
        return valid_input;
    valid_input = OpenFile(argv[2], source, READ);
    if (valid_input != RLE_LIST_SUCCESS)
        return valid_input;
    valid_input = OpenFile(argv[3], destination, WRITE);
    return valid_input;
}

RLEListResult OpenFile(char *source, FILE *destination, char *flag) {
    if (!source)
        return RLE_LIST_NULL_ARGUMENT;
    FILE *file = fopen(source, flag); //TODO: close the file in case of error? is it needed?
    if (!file) //failed opening the file
        return RLE_LIST_ERROR; //TODO: return the right errors.
    destination = file; //TODO: make sure destination is really changed outside the function.
    return RLE_LIST_SUCCESS;
}




