#include "observer.h"
#include "concrete_observers.h"
#include <iostream>

int main() {
    Observable logger;

    //Создание наблюдателей. Они автоматически подписываются в конструкторе.
    WarningObserver warning_obs(logger);
    ErrorObserver error_obs(logger, "errors.txt");
    FatalErrorObserver fatal_obs(logger, "fatal.txt");

    //Генерирация события.
    std::cout << "--- Generating events ---\n";
    logger.warning("Low disk space"); //Выведет только WarningObserver.
    logger.error("Connection timeout"); //Запишет в файл только ErrorObserver.
    logger.fatalError("Database crashed"); //Выведет в консоль И запишет в файл FatalErrorObserver.

    //Проверка корректного удаления наблюдателя.
    std::cout << "\n--- Destroying WarningObserver ---\n";
    {
        //Создание во вложенной области видимости.
        WarningObserver temp_obs(logger);
    } //temp_obs уничтожается здесь, вызывается RemoveObserver.

    logger.warning("This warning should not crash the program");

    return 0;
}