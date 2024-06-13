
char** SplitString(const char* inputString, char delimiter) {
    int delimiterCount = 0;
    const char* pointer = inputString;
    while (*pointer != '\0') {
        if (*pointer++ == delimiter) {
            delimiterCount++;
        }
    }

    char** referenceOfStringReference = (char**)malloc(sizeof(char*) * (delimiterCount + 2));
    int delimiterIndex = 0;
    pointer = inputString;
    char* stringReference = (char*)malloc(strlen(inputString) + 1);
    int inputStringIndex = 0;
    while (*pointer != '\0') {
        if (*pointer == delimiter) {
            stringReference[inputStringIndex] = '\0';
            referenceOfStringReference[delimiterIndex++] = strdup(stringReference);
            inputStringIndex = 0;
        } else {
            stringReference[inputStringIndex++] = *pointer;
        }
        pointer++;
    }
    stringReference[inputStringIndex] = '\0';
    referenceOfStringReference[delimiterIndex++] = strdup(stringReference);
    referenceOfStringReference[delimiterIndex] = NULL;
    free(stringReference);
    return referenceOfStringReference;
}
