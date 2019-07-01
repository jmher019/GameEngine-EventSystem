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
	unsigned long subscribe(callType<EventType> callable) {
		size_t type = Event<EventType>::type();
		unsigned long id = idCounter++;

		if (mSubscribers.count(type) == 0) {
			mSubscribers[type] = std::unordered_map<unsigned long, callType<BaseEvent>>();
		}

		mSubscribers[type].insert(std::make_pair(id, CallbackWrapper<EventType>(callable)));

		return id;
	}

    template <typename EventType>
	void emit(const EventType& event) {
		size_t type = Event<EventType>::type();

		Event<EventType> eventWrapper(event);

		for (auto& receiver : mSubscribers[type]) {
			receiver.second(eventWrapper);
		}
	}

    template <typename EventType>
	void removeSubscription(const unsigned int& id) {
		size_t type = Event<EventType>::type();

		if (mSubscribers.count(type) > 0 && mSubscribers[type].count(id) > 0) {
			mSubscribers[type].erase(id);
		}
	}

	void removeSubscription(const unsigned int& id) {
		for (auto it = mSubscribers.begin(); it != mSubscribers.end(); ++it) {
			(*it).second.erase(id);
		}
	}

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

#endif // !EVENT_MANAGER_HPP
