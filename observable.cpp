#include "observer.h"

void Observable::AddObserver(Observer* observer) {
    if (observer) {
        observers_.push_back(observer);
    }
}

void Observable::RemoveObserver(Observer* observer) {
    //Используем erase-remove idiom для удаления указателя из вектора.
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}

void Observable::warning(const std::string& message) const {
    for (Observer* observer : observers_) {
        observer->onWarning(message);
    }
}

void Observable::error(const std::string& message) const {
    for (Observer* observer : observers_) {
        observer->onError(message);
    }
}

void Observable::fatalError(const std::string& message) const {
    for (Observer* observer : observers_) {
        observer->onFatalError(message);
    }
}