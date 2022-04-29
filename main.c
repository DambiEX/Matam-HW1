#include "AsciiArtTool.c"
#define ENCODED 'e'
#define INVERTED 'i'
#define FLAGGED '-'
typedef char FLAG;

RLEListResult ParseFlag (FLAG* destination, FLAG* source){
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

RLEListResult UnpackInput(int argc, char **argv,
                          FLAG* flag, FILE *source, FILE *destination){
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

int main(int argc, char** argv){
    FLAG flag;
    FILE *source, *destination; //TODO: make sure pointer syntax is correct.
    RLEListResult unpacked_success = UnpackInput(argc, argv, &flag, source, destination);
    if (unpacked_success != RLE_LIST_SUCCESS)
        return NULL;

    RLEList list = asciiArtRead(source);

    if (flag == ENCODED){
        asciiArtPrintEncoded(list, destination);
    }
    else if (flag == INVERTED){
        RLEListMap(list, InvertNode);
    }

}