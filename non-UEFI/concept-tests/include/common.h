#ifndef COMMON_H
#define COMMON_H

#define HEIGHT 900
#define WIDTH 1440

typedef union {
    struct {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    };
    uint32_t value;
} pixel;
typedef enum {
    RESULT_SUCCESS=0,
    RESULT_GENERIC_FAILURE=-1,
    RESULT_BUFFER_TOO_SMALL=-2,
    RESULT_INVALID_PARAMETER=-3
} execution_result;
#endif
