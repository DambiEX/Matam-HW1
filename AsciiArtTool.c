#include "RLEList.c"
#define READ "r"
#define NULL_CHAR '\0'
RLEList asciiArtRead(FILE* in_stream){
    RLEList list = RLEListCreate();
    FILE *file = fopen(in_stream, READ);
    if (!file) //failed opening the file
        return NULL;
    char content = NULL_CHAR;
    bool scan_success = true;
    while (scan_success)
    {
        scan_success = fgets(content, 1, file); //fscanf(file, &content); //TODO: fix syntax
        RLEListAppend(list, content);
    }

    if (RLEListSize(list) == 0)
        return NULL; //received an empty file
    fclose(in_stream);
    return list;
}
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){

}
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){

}