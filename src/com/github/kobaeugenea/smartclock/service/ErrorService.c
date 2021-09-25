#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "com/github/kobaeugenea/smartclock/service/ErrorService.h"
#include "com/github/kobaeugenea/smartclock/util/collection/Queue.h"
#include "com/github/kobaeugenea/smartclock/util/MemoryUtils.h"

#define MAX_ERRORS_COUNT 16

static QueueData* queueData;

static void init() {
    queueData = Queue.init(MAX_ERRORS_COUNT);
}

static void put(char errorFormat[MAX_ERROR_LENGTH], ...) {
    char *errorMessage = MemoryUtils.malloc(MAX_ERROR_LENGTH * sizeof(char));

    va_list argList;
    va_start(argList, errorFormat);

    vsnprintf(errorMessage, MAX_ERROR_LENGTH, errorFormat, argList);
    Queue.push(queueData, errorMessage);

    va_end(argList);
}

kea_sc_ErrorService_n const kea_sc_ErrorService = {
    .init = init,
    .put = put
};