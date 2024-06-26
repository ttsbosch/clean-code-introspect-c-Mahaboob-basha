#define MAX_CURRENCY_LENGTH 255

typedef struct {
    char SourceCurrency[MAX_CURRENCY_LENGTH + 1];
    char DestinationCurrency[MAX_CURRENCY_LENGTH + 1];
    float Lots;
    double Price;
} TradeRecord;

