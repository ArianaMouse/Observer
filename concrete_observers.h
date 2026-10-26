#pragma once

#include "observer.h"
#include <fstream>
#include <iostream>

//Для предупреждений.
class WarningObserver : public Observer {
public:
    explicit WarningObserver(Observable& observable) : observable_(observable) {
        observable_.AddObserver(this);
    }

    ~WarningObserver() override {
        observable_.RemoveObserver(this);
    }

    void onWarning(const std::string& message) override {
        std::cout << "[WARNING] " << message << std::endl;
    }

private:
    Observable& observable_;
};

//Для ошибок.
class ErrorObserver : public Observer {
public:
    ErrorObserver(Observable& observable, std::string file_path)
        : observable_(observable), file_path_(std::move(file_path)) {
        observable_.AddObserver(this);
    }

    ~ErrorObserver() override {
        observable_.RemoveObserver(this);
    }

    void onError(const std::string& message) override {
        std::ofstream file(file_path_, std::ios::app);
        if (file.is_open()) {
            file << "[ERROR] " << message << std::endl;
        }
    }

private:
    Observable& observable_;
    std::string file_path_;
};

//Для фатальных ошибок.
class FatalErrorObserver : public Observer {
public:
    FatalErrorObserver(Observable& observable, std::string file_path)
        : observable_(observable), file_path_(std::move(file_path)) {
        observable_.AddObserver(this);
    }

    ~FatalErrorObserver() override {
        observable_.RemoveObserver(this);
    }

    void onFatalError(const std::string& message) override {
        std::cout << "[FATAL] " << message << std::endl;

        std::ofstream file(file_path_, std::ios::app);
        if (file.is_open()) {
            file << "[FATAL] " << message << std::endl;
        }
    }

private:
    Observable& observable_;
    std::string file_path_;
};