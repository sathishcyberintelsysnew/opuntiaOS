#pragma once
#include <std/Vector.h>
#include <sys/types.h>

typedef Vector<uint8_t> EncodedMessage;
typedef int message_key_t;

class Message {
public:
    Message() { }
    virtual ~Message() = default;

    virtual int decoder_magic() const { return 0; }
    virtual int id() const { return 0; }
    virtual message_key_t key() const { return -1; }
    virtual int reply_id() const { return -1; } // -1 means that there is no reply.
    virtual EncodedMessage encode() const { return Vector<uint8_t>(); }
};