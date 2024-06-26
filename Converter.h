
bool TryConvertToIntegerFromString(const char* inputString, int* value) {
    char* endPointer;
    *value = strtol(inputString, &endPointer, 10);
    return endPointer != inputString && *endPointer == '\0';
}

bool TryConvertToDoubleFromString(const char* inputString, double* value) {
    char* endPointer;
    *value = strtod(inputString, &endPointer);
    return endPointer != inputString && *endPointer == '\0';
}
