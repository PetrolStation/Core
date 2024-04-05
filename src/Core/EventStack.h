#pragma once

#include "Event.h"
#include <entt/entt.hpp>
#include <Core/Aliases.h>

#include <list>
#include <mutex>

namespace PetrolEngine {

    // Event manager
    class EventStack {
    public:
        template<class T>
        static bool checkEvents() {
            return events.find(entt::type_index<T>::value()) != events.end();
        }
        
        static void callCallbacks() {
            for(auto& eventList : events){
                auto x = callbacks.find(eventList.first);
                if(x == callbacks.end()) continue;
                for(auto& event : eventList.second){
                    for(auto callback : x->second) if(callback != nullptr) callback(event);
                }
            }
        }

        template<class T>
        static Vector<T*>& getEvents() {
            auto eventList = events.find(entt::type_index<T>::value());

            if (eventList == events.end())
                return *reinterpret_cast<Vector<T*>*>(const_cast<Vector<Event*>*>(&emptyEventList));

            return *reinterpret_cast<Vector<T*>*>(&eventList->second);
        }

        template<class T>
        static void popFront() {
            auto eventList = events.find(entt::type_index<T>::value());

            if (eventList == events.end()) return;

            eventList->second.erase(eventList->second.begin());
        }

        static void clear() {
            for (auto& event : events) event.second.clear();
        }

        template<class T>
        static void removeCallback(void(*_callback)(T*)) {
            auto eventCallbacks = callbacks.find(entt::type_index<T>::value());

            for(auto& callback : eventCallbacks->second)
                if(callback == _callback) callback = nullptr;
        }
        
        template<class T>
        static void addCallback(void(*callback)(T*)) {
            auto eventCallbacks = callbacks.find(entt::type_index<T>::value());
            
            if (eventCallbacks == callbacks.end())
                callbacks.emplace<entt::id_type, Vector<void(*)(Event*)>>(entt::type_index<T>::value(), { callback });
            else
                eventCallbacks->second.push_back(reinterpret_cast<Event*>(callback));
        }

        template<class T>
        static T* addEvent(T* _event) {
            auto eventClassEvents = events.find(entt::type_index<T>::value());

            std::lock_guard<std::mutex> guard(eventLock);
            if (eventClassEvents == events.end())
                events.emplace<entt::id_type, Vector<Event*>>(entt::type_index<T>::value(), { _event });
            else
                eventClassEvents->second.push_back(reinterpret_cast<Event*>(_event));
            
            return _event;
        }
    private:
        static UnorderedMap<entt::id_type, Vector<void(*)(Event*)>> callbacks;
        static UnorderedMap<entt::id_type, Vector<Event*>> events;
        static std::mutex eventLock;
        static const Vector<Event*> emptyEventList;
    };
}
