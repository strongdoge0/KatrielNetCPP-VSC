#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <mutex>

class ActionDispatcher{
    public:
    bool IsActive();
    void Add(std::function<void()> action);
    void ExecuteOnce();
    void Execute();
    void Clear();
    
    private:
    std::vector<std::function<void()>> _actions;
    std::mutex _actionsLock;
    
};