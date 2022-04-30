#include "RLEList.h"
#include "Node.h"
#include "AsciiArtTool.h"



RLEList asciiArtRead(FILE* in_stream){
    RLEList list = RLEListCreate();
    char content = NULL_CHAR;
    bool scan_success = true;
    while (scan_success)
    {
        scan_success = fgets(&content, 1, in_stream); //fscanf(in_stream, &content); //TODO: fix syntax
        RLEListAppend(list, content);
    }

    if (RLEListSize(list) == 0) //received an empty in_stream
        return NULL;
    fclose(in_stream);
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){


    for (int i = 0; i < RLEListSize(list); ++i) {
        fprintf(out_stream, "%c", RLEListGet(list, i, NULL)); //TODO: nicer syntax to write all the repetitions at once?
    }

    fclose(out_stream);
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){

    RLEListResult print_result;
    fprintf(out_stream, "%s", RLEListExportToString(list, &print_result));

    fclose(out_stream);
    return print_result;
}

char InvertChar(char symbol) {
    if (symbol == AT_SIGN)
        return SPACE;
    else if (symbol == SPACE)
        return AT_SIGN;
    else
        return symbol;
}