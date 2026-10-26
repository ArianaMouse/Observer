#pragma once

#include <algorithm>
#include <string>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

//Наблюдаемый класс.
class Observable {
public:
    //Методы для подписки и отписки.
    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);

    //Методы, генерирующие события.
    void warning(const std::string& message) const;
    void error(const std::string& message) const;
    void fatalError(const std::string& message) const;

private:
    //Хранение указателей.
    std::vector<Observer*> observers_;
};