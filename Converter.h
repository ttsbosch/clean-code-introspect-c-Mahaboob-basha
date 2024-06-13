
bool TryConvertToIntegerFromString(const char* inputString, int* value) {
    char* endPointer;
    *value = strtol(inputString, &endPointer, 10);
    if (endPointer == inputString) {
        return 0;
    }
    return 1;
}

bool TryConvertTDoubleFromString(const char* inputString, double* value) {
    char* endPointer;
    *value = strtod(inputString, &endPointer);
    if (endPointer == inputString) {
        return 0;
    }
    return 1;
}

