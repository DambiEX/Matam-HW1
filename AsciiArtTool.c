#include <stdlib.h>
#include "RLEList.h"
#include "Node.h" //TODO: remove node.h and find a solution that uses the minimal number of external modules
#include "AsciiArtTool.h"
#define BUFFER_SIZE 100



RLEList asciiArtRead(FILE* in_stream){
    RLEList list = RLEListCreate();
    char content[BUFFER_SIZE+1];
    bool scan_success = true;
    while (scan_success)
    {
        scan_success = fgets(content, BUFFER_SIZE, in_stream);
        for (int i = 0; (scan_success && content[i]); ++i) {
            RLEListAppend(list, content[i]);
        }
    }

    if (RLEListSize(list) == 0) //received an empty in_stream
    {
        return NULL;
    }
    fclose(in_stream);
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){

    RLEListResult result = RLEListPrintContent(list, out_stream);
    fclose(out_stream);
    return result;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){

    RLEListResult print_result;
    char* ExportedString = RLEListExportToString(list, &print_result);
    if (print_result != RLE_LIST_SUCCESS)
    {
        return print_result;
    }
    fputs(ExportedString, out_stream);

    fclose(out_stream);
    free(ExportedString);

    return print_result;
}

char InvertChar(char symbol) {
    if (symbol == AT_SIGN)
    {
        return SPACE;
    }
    else if (symbol == SPACE)
    {
        return AT_SIGN;
    }
    else
    {
        return symbol;
    }
}