#include "event.h"
#include <safe_c.h>

#ifndef CONFIG_EVENT_C_MAX_HANDLERS
#define CONFIG_EVENT_C_MAX_HANDLERS EVENT_C__DEFAULT_MAX_HANDLERS
#endif

typedef struct EventHandlerRecord {
    uint32_t id;
    EventHandlerFunc func;
} EventHandlerRecord;

typedef struct EventManager {
    EventHandlerRecord handlers[CONFIG_EVENT_C_MAX_HANDLERS];
} EventManager;

static EventManager g_event_manager = {0};

void event__init(void) {
    int i = 0;
    
    for (i = 0; i < CONFIG_EVENT_C_MAX_HANDLERS; i++) {
        g_event_manager.handlers[i].func = NULL;
    }
}

int event__subscribe(uint32_t const event_id, EventHandlerFunc const func) {
    int i = 0;
    int rc = ER_NO_ENT;
    
    for (i = 0; i < CONFIG_EVENT_C_MAX_HANDLERS; i++) {
        if (NULL == g_event_manager.handlers[i].func) {
            g_event_manager.handlers[i].func = func;
            g_event_manager.handlers[i].id = event_id;
            rc = 0;
            break;
        }
    }

    return rc;
}

int event__unsubscribe(EventHandlerFunc const func) {
    int i = 0;
    int rc = ER_NO_ENT;
    
    for (i = 0; i < CONFIG_EVENT_C_MAX_HANDLERS; i++) {
        if (func == g_event_manager.handlers[i].func) {
            g_event_manager.handlers[i].func = NULL;
            rc = 0;
            break;
        }
    }

    return rc;
}

int event__pub(uint32_t const event_id, void const* const data) {
    int i = 0;
    int cnt = 0;
    
    for (i = 0; i < CONFIG_EVENT_C_MAX_HANDLERS; i++) {
        if (event_id == g_event_manager.handlers[i].id && NULL != g_event_manager.handlers[i].func) {
            g_event_manager.handlers[i].func(data);
            cnt++;
        }
    }

    return cnt;
}
