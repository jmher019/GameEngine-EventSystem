#ifndef EVENT_HPP
#define EVENT_HPP

#include <BaseEvent.hpp>

template <typename EventType>
class Event : public BaseEvent {
public:
    Event(const EventType& event) : event_(event) {};

    static size_t type() noexcept {
        static size_t tType = BaseEvent::getNextType();
        return tType;
    };

    const EventType& event_;
};

#endif // !EVENT_HPP
