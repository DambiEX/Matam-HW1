#include "RLEList.c"
#define READ "r"
#define WRITE "w"
#define AT_SIGN '@'
#define SPACE ' '
#define NULL_CHAR '\0'

RLEListResult OpenFile(FILE *source, FILE *destination, char *flag) {
    if (!source)
        return RLE_LIST_NULL_ARGUMENT;
    FILE *file = fopen(source, flag); //TODO: close the file in case of error? is it needed?
    if (!file) //failed opening the file
        return RLE_LIST_ERROR; //TODO: return the right errors
    destination = file;
    return RLE_LIST_SUCCESS;
}

RLEList asciiArtRead(FILE* in_stream){
    FILE *file;
    RLEListResult result = OpenFile(in_stream, file, READ);
    if (result != RLE_LIST_SUCCESS)
        return NULL;

    RLEList list = RLEListCreate();
    char content = NULL_CHAR;
    bool scan_success = true;
    while (scan_success)
    {
        scan_success = fgets(&content, 1, file); //fscanf(file, &content); //TODO: fix syntax
        RLEListAppend(list, content);
    }

    if (RLEListSize(list) == 0) //received an empty file
        return NULL;
    fclose(file);
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    FILE *file;
    RLEListResult result = OpenFile(out_stream, file, WRITE);
    if (result != RLE_LIST_SUCCESS)
        return result;

    Node node = list->first_node;
    while (node->next){
        for (int i = 0; i < node->next->repetitions; ++i) {
            fprintf(file, &node->next->symbol); //TODO: nicer syntax to write all the repitions at once?
        }
    }
    fclose(file);
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
    FILE *file;
    RLEListResult result = OpenFile(out_stream, file, WRITE);
    if (result != RLE_LIST_SUCCESS)
        return result;

    RLEListResult print_result;
    fprintf(RLEListExportToString(list, print_result), file);
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