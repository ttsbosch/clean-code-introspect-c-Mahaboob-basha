#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char SourceCurrency[256];
    char DestinationCurrency[256];
    float Lots;
    double Price;
} TradeRecord;


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

void CovertCSVToXML(FILE* stream) {
    char line[1024];
    TradeRecord tradeObjects[1024];
    int lineCount = 0;
    int objectCount = 0;

    while (fgets(line, sizeof(line), stream)) {
        char* fields[3];
        int fieldCount = 0;
        char* stringReference = strtok(line, ",");
        while (stringReference != NULL) {
            fields[fieldCount++] = stringReference;
            stringReference = strtok(NULL, ",");
        }

        if (fieldCount != 3) {
            fprintf(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, fieldCount);
            continue;
        }

        if (strlen(fields[0]) != 6) {
            fprintf(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, fields[0]);
            continue;
        }

        int tradeAmount;
        if (!TryConvertToIntegerFromString(fields[1], &tradeAmount)) {
            fprintf(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, fields[1]);
        }

        double tradePrice;
        if (!TryConvertTDoubleFromString(fields[2], &tradePrice)) {
            fprintf(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, fields[2]);
        }

        strncpy(tradeObjects[objectCount].SourceCurrency, fields[0], 3);
        strncpy(tradeObjects[objectCount].DestinationCurrency, fields[0] + 3, 3);
        tradeObjects[objectCount].Lots = tradeAmount / LotSize;
        tradeObjects[objectCount].Price = tradePrice;
        objectCount++;
        lineCount++;
    }

    FILE* outFile = fopen("output.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int i = 0; i < objectCount; i++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", tradeObjects[i].SourceCurrency);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", tradeObjects[i].DestinationCurrency);
        fprintf(outFile, "\t\t<Lots>%d</Lots>\n", tradeObjects[i].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", tradeObjects[i].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    fclose(outFile);
    printf("INFO: %d trades processed\n", objectCount);
}

