#include <stdlib.h>
#include "RLEList.h"
#include "AsciiArtTool.h"
#define BUFFER_SIZE 100



RLEList asciiArtRead(FILE* in_stream){
    RLEList list = RLEListCreate();
    char content[BUFFER_SIZE+1];
    bool scan_success = true;
    while (scan_success)
    {
        scan_success = fgets(content, BUFFER_SIZE, in_stream); //fscanf(in_stream, &content); //TODO: fix syntax
        for (int i = 0; (scan_success && content[i]); ++i) {
            RLEListAppend(list, content[i]);
        }
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
    char* ExportedString = RLEListExportToString(list, &print_result);
    if (print_result != RLE_LIST_SUCCESS)
        return print_result;

    fprintf(out_stream, ExportedString);

    fclose(out_stream);
    free_export(ExportedString);
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