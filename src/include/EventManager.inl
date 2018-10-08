template<typename EventType>
void EventManager::subscribe(callType<EventType> callable) {
    size_t type = Event<EventType>::type();

    mSubscribers[type].push_back(CallbackWrapper<EventType>(callable));
}

template <typename EventType>
void EventManager::emit(const EventType& evt) {
    size_t type = Event<EventType>::type();

    Event<EventType> eventWrapper(evt);

    for (auto& receiver : mSubscribers[type]) {
        receiver(eventWrapper);
    }
}