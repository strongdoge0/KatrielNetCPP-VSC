#include "ActionDispatcher.hpp"

bool ActionDispatcher::IsActive() {
  if (_actions.size() > 0) {
    return true;
  }
  return false;
}

void ActionDispatcher::Add(std::function<void()> action) {
  std::unique_lock<std::mutex> guard(_actionsLock, std::try_to_lock);
  _actions.push_back(action);
}

void ActionDispatcher::ExecuteOnce() {
  std::unique_lock<std::mutex> guard(_actionsLock, std::try_to_lock);
  if (_actions.size() > 0) {
    _actions[0]();
    _actions.erase(_actions.begin() + 0);
  }
}

void ActionDispatcher::Execute() {
  std::unique_lock<std::mutex> guard(_actionsLock, std::try_to_lock);
  for (int i = 0; i < _actions.size(); i++) {
    _actions[i]();
  }
  _actions.clear();
}

void ActionDispatcher::Clear() {
  std::unique_lock<std::mutex> guard(_actionsLock, std::try_to_lock);
  _actions.clear();
}