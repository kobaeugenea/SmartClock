#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "service/kea_sc_ErrorS.h"
#include "util/collection/kes_sc_QueueU.h"

#define MAX_ERRORS_COUNT 16

kea_sc_QueueData(MAX_ERRORS_COUNT) kea_sc_QueueData;

void kea_sc_ErrorS_put(char errorFormat[MAX_ERROR_LENGTH], ...) {
    char *errorMessage = malloc(MAX_ERROR_LENGTH * sizeof(char));

    va_list argList;
    va_start(argList, errorFormat);

    vsnprintf(errorMessage, MAX_ERROR_LENGTH, errorFormat, argList);
    kea_sc_Qeueu_push(kea_sc_QueueData, errorMessage);

    va_end(argList);
}