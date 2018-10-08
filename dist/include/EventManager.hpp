#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <vector>
#include <unordered_map>

#include <Event.hpp>

class EventManager {
public:
    template <class EventType>
    using callType = std::function<void(const EventType&)>;

    template <typename EventType>
    void subscribe(callType<EventType> callable);

    template <typename EventType>
    void emit(const EventType& event);

    template <typename EventType>
    struct CallbackWrapper {
        CallbackWrapper(callType<EventType> callable) : mCallable(callable) {};
        void operator() (const BaseEvent& event) {
            mCallable(static_cast<const Event<EventType>&>(event).event_);
        };

        callType<EventType> mCallable;
    };

    std::unordered_map<size_t, std::vector<callType<BaseEvent>>> mSubscribers;
};

#include <EventManager.inl>

#endif // !EVENT_MANAGER_HPP
