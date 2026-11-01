#include "common.h"

typedef struct {
    u32 magic;
    u32 length;
} Header;

typedef struct {
    s32 active;
    u32 length;
    u8 *start;
    u8 *end;
    u8 *cursor;
} Stream;

extern Stream D_80092914[];

Stream *func_8001D428(Header *header, u32 suppliedLength) {
    Stream *stream;
    u32 length;
    s32 index;
    s32 hasHeader;
    u8 *start;
    u8 *end;

    hasHeader = 1;
    if (header->magic != 0x4D524F46) {
        if (suppliedLength != 0) {
            hasHeader = 0;
            length = suppliedLength;
        } else {
            length = 0;
        }
    } else {
        length = header->length;
    }
    stream = D_80092914;
    for (index = 0; index < 4; index++, stream++) {
        if (stream->active == 0) {
            break;
        }
    }
    stream->active = 1;
    if (hasHeader != 0) {
        stream->start = (u8 *)(header + 1);
    } else {
        stream->start = (u8 *)header;
    }
    end = stream->start;
    stream->length = length;
    start = end;
    end += length;
    stream->end = end;
    stream->cursor = start;
    return &D_80092914[index];
}
