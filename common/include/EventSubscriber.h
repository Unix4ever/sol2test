/*
-----------------------------------------------------------------------------
This file is a part of Gsage engine

Copyright (c) 2014-2016 Artem Chernyshev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef _EventHandler_H_
#define _EventHandler_H_

#include "EventDispatcher.h"


namespace Gsage {
  /**
   * Class that can listen to the events, distpached by the eventDispatcher
   */
  template<class C>
  class EventSubscriber
  {
    public:
      class HandlerDescriptor;
      // ----------------------------------------------------------------------
      // Definitions
      //
      // Identification pair for each subscribed event -- EventDispatcher instance + event type string
      typedef std::pair<EventDispatcher*, Event::Type> EventSubscription;
      // List of handler descriptors for subscription
      typedef std::vector<HandlerDescriptor> Handlers;
      // Iterator for handlers vector
      typedef typename Handlers::iterator HandlerIterator;
      // Map of subscriptions
      typedef std::map<EventSubscription, Handlers> EventConnections;
      // Event callback format
      typedef bool (C::*CallbackMemFn)(EventDispatcher*, const Event&);

      class HandlerDescriptor
      {
        public:
          HandlerDescriptor(CallbackMemFn callback, EventConnection connection) : mCallback(callback), mConnection(connection) {};

          void disconnect()
          {
            mConnection.disconnect();
          }

          bool operator==(const CallbackMemFn& callback)
          {
            return callback == mCallback;
          }

          bool operator!=(const CallbackMemFn& callback)
          {
            return callback != mCallback;
          }
        private:
          CallbackMemFn mCallback;
          EventConnection mConnection;
      };

      EventSubscriber() {};
      virtual ~EventSubscriber()
      {
        for(auto pair : mConnections)
        {
          for(auto handler : pair.second)
          {
            handler.disconnect();
          }
        }
        mConnections.clear();
      }

      /**
       * Adds event listener function to the event dispatcher
       *
       * @param dispatcher EventDispatcher
       * @param eventType Unique event id
       * @param callback The function that accepts EventDispatcher pointer as the first param and const Event& as the second param.
       *   It should return bool value. Returning false, will stop event propagation.
       * @param priority Adjusts callback call order
       *
       * @returns true if added, false if already exists
       */
      bool addEventListener(EventDispatcher* dispatcher, Event::ConstType eventType, CallbackMemFn callback, const int priority = 0)
      {
        EventSubscription subscription(dispatcher, eventType);
        // if there is the same listener, there is no need to add another
        if(hasEventListener(dispatcher, eventType))
        {
          Handlers &h = mConnections[subscription];
          HandlerIterator iterator = getDescriptor(h, callback);
          if(iterator != h.end())
            return false;
        }

        if(!hasEventListener(dispatcher, DispatcherEvent::FORCE_UNSUBSCRIBE) && eventType != DispatcherEvent::FORCE_UNSUBSCRIBE)
        {
          addEventListener(dispatcher, DispatcherEvent::FORCE_UNSUBSCRIBE, &EventSubscriber<C>::onForceUnsubscribe);
        }

        mConnections[subscription].push_back(HandlerDescriptor(callback, dispatcher->addEventListener(eventType, std::bind(callback, (C*)this, std::placeholders::_1, std::placeholders::_2), priority)));
        return true;
      }

      /**
       * Remove event listener from the event dispatcher
       *
       * @param dispatcher EventDispatcher
       * @param eventType Unique event id
       * @param callback Pointer to the previosly defined function
       *
       * @returns true if successful
       */
      bool removeEventListener(EventDispatcher* dispatcher, Event::ConstType eventType, CallbackMemFn callback)
      {
        EventSubscription subscription(dispatcher, eventType);
        if(!hasEventListener(dispatcher, eventType))
          return false;

        Handlers &h = mConnections[subscription];
        HandlerIterator iterator = getDescriptor(h, callback);
        if(iterator == h.end())
        {
          return false;
        }

        (*iterator).disconnect();
        h.erase(iterator);

        if(h.size() == 0)
        {
          mConnections.erase(subscription);
        }

        if(hasEventListener(dispatcher, DispatcherEvent::FORCE_UNSUBSCRIBE) && eventType != DispatcherEvent::FORCE_UNSUBSCRIBE){
          int subscriptions = 0;
          for(auto pair : mConnections)
          {
            if(pair.first.first == dispatcher && pair.first.second != DispatcherEvent::FORCE_UNSUBSCRIBE && pair.second.size() > 0)
            {
              subscriptions++;
            }
          }

          if(subscriptions == 0)
          {
            removeEventListener(dispatcher, DispatcherEvent::FORCE_UNSUBSCRIBE, &EventSubscriber<C>::onForceUnsubscribe);
          }
        }
        return true;
      }

      bool hasEventListener(EventDispatcher* dispatcher, Event::ConstType eventType)
      {
        EventSubscription subscription(dispatcher, eventType);
        return mConnections.count(subscription) > 0;
      }

      virtual bool onForceUnsubscribe(EventDispatcher* sender, const Event& event)
      {
        typename EventConnections::iterator iter = mConnections.begin();
        while(iter != mConnections.end())
        {
          if((*iter).first.first == sender)
          {
            typename EventConnections::iterator tmp = iter++;
            mConnections.erase(tmp);
          }
          else
          {
            iter++;
          }
        }
        return true;
      }

    protected:
      HandlerIterator getDescriptor(Handlers& h, const CallbackMemFn& callback)
      {
        return std::find(h.begin(), h.end(), callback);
      }

      EventConnections mConnections;
  };
}
#endif
