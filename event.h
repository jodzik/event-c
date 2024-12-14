#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>

enum EventConf {
    EVENT_C__DEFAULT_MAX_HANDLERS = 64,	// subscribers
};

typedef void (*EventHandlerFunc)(void const*);

void event__init(void);
int event__subscribe(uint32_t event_id, EventHandlerFunc func);
int event__unsubscribe(EventHandlerFunc func);
int event__pub(uint32_t event_id, void const* data);

#endif
