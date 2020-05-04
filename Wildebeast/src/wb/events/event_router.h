#pragma once

#include "wbpch.h"
#include "wb/events/events.h"

namespace wb {
    class EventRouter {
        public:
            EventRouter(Event& e) : event(e) {}

            using EventCallbackFn = std::function<void(Event& e)>;

            template<u32 ET>
            bool ProcessEvent(const EventCallbackFn func) {
                if (event.Type == ET) {
                    func(event);
                    return true;
                }
                return false;
            }

        private:
            Event& event;
    };
}