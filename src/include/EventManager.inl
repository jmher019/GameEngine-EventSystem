
unsigned long EventManager::idCounter = 0;

template<typename EventType>
unsigned long EventManager::subscribe(callType<EventType> callable) {
    size_t type = Event<EventType>::type();
    unsigned long id = idCounter++;

    if (mSubscribers.count(type) == 0) {
        mSubscribers[type] = std::unordered_map<unsigned long, callType<BaseEvent>>();
    }

    mSubscribers[type].insert(std::make_pair(id, CallbackWrapper<EventType>(callable)));
    
    return id;
}

template <typename EventType>
void EventManager::emit(const EventType& evt) {
    size_t type = Event<EventType>::type();

    Event<EventType> eventWrapper(evt);

    for (auto& receiver : mSubscribers[type]) {
        receiver.second(eventWrapper);
    }
}

template <typename EventType>
void EventManager::removeSubscription(const unsigned int& id) {
    size_t type = Event<EventType>::type();

    if (mSubscribers.count(type) > 0 && mSubscribers[type].count(id) > 0) {
        mSubscribers[type].erase(id);
    }
}