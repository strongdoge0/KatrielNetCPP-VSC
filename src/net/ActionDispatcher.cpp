#include "ActionDispatcher.hpp"

bool ActionDispatcher::IsActive() {
  if (_actions.size() > 0) {
    return true;
  }
  return false;
}

void ActionDispatcher::Add(std::function<void()> action) {
  std::lock_guard<std::mutex> guard(_actionsLock);
  _actions.push_back(action);
}

void ActionDispatcher::ExecuteOnce() {
  // std::lock_guard<std::mutex> guard(_actionsLock);
  if (_actions.size() > 0) {
    _actions[0]();
    _actions.erase(_actions.begin() + 0);
  }
}

void ActionDispatcher::Execute() {
  std::lock_guard<std::mutex> guard(_actionsLock);
  for (int i = 0; i < _actions.size(); i++) {
    _actions[i]();
  }
  _actions.clear();
}

void ActionDispatcher::Clear() { _actions.clear(); }