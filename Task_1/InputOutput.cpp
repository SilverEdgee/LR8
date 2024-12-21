#include <iostream>
#include <limits>
#include <string>
#include "header.h"

int ifInt()
{
    int num;
    char after;
    while (true)
    {
        if (std::cin >> num && ((after = std::cin.peek()) == ' ' || after == '\n'))
        {
            std::cin.get(after);
            return num;
        }
        std::cout << "Error! Please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int ifPositiveInt()
{
    int num = ifInt();
    while (num <= 0)
    {
        std::cout << "Error! The number must be greater than 0: ";
        num = ifInt();
    }
    return num;
}

double ifPositive()
{
    double num;
    char after;
    while (true)
    {
        if (std::cin >> num && num > 0 && ((after = std::cin.peek()) == ' ' || after == '\n'))
        {
            std::cin.get(after);
            return num;
        }
        std::cout << "Error! Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

int ifChoice1or2()
{
    int choice = ifInt();
    while (choice != 1 && choice != 2)
    {
        std::cout << "Error! Please select 1 or 2: ";
        choice = ifInt();
    }
    return choice;
}

int ifValidNewCount(int currentCount)
{
    int newCount = ifPositiveInt();
    while (newCount < currentCount)
    {
        std::cout << "Error! The new count cannot be less than the current count ("
                  << currentCount << "): ";
        newCount = ifPositiveInt();
    }
    return newCount;
}

void inputString(char *buffer, int maxLength)
{
    int i = 0;
    char ch;
    while ((ch = getchar()) != '\n' && i < maxLength - 1)
    {
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
}

