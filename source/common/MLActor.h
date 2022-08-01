
// mlvg: GUI library for madronalib apps and plugins
// Copyright (C) 2019-2022 Madrona Labs LLC
// This software is provided 'as-is', without any express or implied warranty.
// See LICENSE.txt for details.

#pragma once

#include "MLMessage.h"
#include "MLQueue.h"
#include "MLTimer.h"

// An Actor is a MessageReceiver that handles incoming messages
// using its own queue and timer. Combining Actors is a simple and scalable way
// to make distributed systems.

namespace ml
{

class Actor;
class ActorRegistry
{
  Tree< Actor* > _actors;
  std::mutex _listMutex;
  
public:
  ActorRegistry() = default;
  ~ActorRegistry() = default;
  
  Actor* getActor(Path actorName)
  {
    return _actors[actorName];
  }
  
  void doRegister(Path actorName, Actor* a)
  {
    _actors[actorName] = a;
  }
  
  void doRemove(Actor* actorToRemove)
  {
    // get exclusive access to the Tree
    std::unique_lock<std::mutex> lock(_listMutex);
    
    // remove the Actor
    for (auto it = _actors.begin(); it != _actors.end(); ++it)
    {
      Actor* pa = *it;
      if(pa == actorToRemove)
      {
        const Path p = it.getCurrentNodePath();
        _actors[p] = nullptr;
      }
    }
  }
};


// TODO actor can have state machine functions using PropertyTree as storage.

class Actor
{
  friend ActorRegistry;

  static constexpr size_t kMessageQueueSize{128};
  static constexpr size_t kDefaultMessageInterval{1000/60};
  
  Queue< Message > _messageQueue{kMessageQueueSize};
  Timer _queueTimer;

protected:
  Path _actorName;
  size_t _maxQueueSize{0};
  size_t getMessagesAvailable() { return _messageQueue.elementsAvailable(); }

  // handle all the messages in the queue immediately.
  inline void handleMessagesInQueue()
  {
    while(Message m = _messageQueue.pop())
    {
      handleMessage(m);
    }
  }
  
  virtual void handleFullQueue() {}

 public:
  
  // TODO Actor is not a subclass of MessageReceiver, change that or make this clearer!
  
  virtual void handleMessage(Message m) = 0;

  Actor()
  {
  }
  
  virtual ~Actor() = 0;
  
  Actor (const Actor&) = delete;
  Actor& operator= (const Actor&) = delete;
  
  void setName(Path n)
  {
    _actorName = n;
  }

  void start(size_t interval = kDefaultMessageInterval)
  {
    // we currently attempt to handle all the messages in the queue.
    // in the future we may want to do just a few at a time instead.
    _queueTimer.start([=]() { handleMessagesInQueue(); }, milliseconds(interval));
  }

  void stop()
  {
    _queueTimer.stop();
  }

  // enqueueMessage just pushes the message onto the queue.
  inline void enqueueMessage(Message m)
  {
    // queue returns true unless full.
    if(!(_messageQueue.push(m)))
    {
      handleFullQueue();
    }
    
    // DEBUG
    _maxQueueSize = std::max(_maxQueueSize, getMessagesAvailable());
  }
  
  inline void enqueueMessageList(const MessageList& ml)
  {
    for (auto m : ml)
    {
      enqueueMessage(m);
    }
  }

};


// send message to an Actor.
//
// TODO handle situations where sender is not able to use a pointer
// to the receiver, as when it is on a different computer on the network.
// to start we will need a "main" host with the registry.
// - if receiver is on same host?
//    then send directly as below.
// -- else
//      serialize the message
//      transmit serialized message to the receiver's host (UDP)
inline void sendMessageToActor(Path actorName, Message m)
{
  SharedResourcePointer< ActorRegistry > registry;
  if(Actor* pActor = registry->getActor(actorName))
  {
    pActor->enqueueMessage(m);
  }
}

inline void registerActor(Path actorName, Actor* actorToRegister)
{
  SharedResourcePointer< ActorRegistry > registry;
  registry->doRegister(actorName, actorToRegister);
  actorToRegister->setName(actorName);
}

inline void removeActor(Actor* actorToRemove)
{
  SharedResourcePointer< ActorRegistry > registry;
  registry->doRemove(actorToRemove);
}


}  // namespace ml
