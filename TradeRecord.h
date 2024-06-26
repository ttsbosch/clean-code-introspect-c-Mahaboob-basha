#define SOURCE_CURRENCY_LENGTH 255
#define DESTINATION_CURRENCY_LENGTH 255

typedef struct {
    char SourceCurrency[SOURCE_CURRENCY_LENGTH + 1];
    char DestinationCurrency[DESTINATION_CURRENCY_LENGTH + 1];
    float Lots;
    double Price;
} TradeRecord;

