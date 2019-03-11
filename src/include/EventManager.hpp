#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <vector>
#include <unordered_map>

#include <Event.hpp>

class EventManager {
private:
    unsigned long idCounter = 0;

public:
    template <class EventType>
    using callType = std::function<void(const EventType&)>;

    template <typename EventType>
    unsigned long subscribe(callType<EventType> callable);

    template <typename EventType>
    void emit(const EventType& event);

    template <typename EventType>
    void removeSubscription(const unsigned int& id);

    template <typename EventType>
    struct CallbackWrapper {
        CallbackWrapper(callType<EventType> callable) : mCallable(callable) {};
        void operator() (const BaseEvent& event) {
            mCallable(static_cast<const Event<EventType>&>(event).event_);
        };

        callType<EventType> mCallable;
    };

    std::unordered_map<size_t, std::unordered_map<unsigned long, callType<BaseEvent>>> mSubscribers;
};

#include <EventManager.inl>

#endif // !EVENT_MANAGER_HPP
