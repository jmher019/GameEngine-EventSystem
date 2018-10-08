#ifndef BASE_EVENT_HPP
#define BASE_EVENT_HPP

class BaseEvent {
public:
    virtual ~BaseEvent(void) noexcept {};
protected:
    static size_t getNextType(void) noexcept {
        static size_t typeCount = 0;
        return typeCount++;
    };
};

#endif // !BASE_EVENT_HPP
