#include <iostream>
#include <limits>
#include <string>
#include "Task2.h"
#include <fstream>
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

int ifChoice1or2()
{
    int choice = ifInt();
    while (choice != 1 && choice != 2)
    {
        std::cout << "Error! Please choose 1 or 2: ";
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

bool writeToFile(const std::string filename, Book* products, int productCount)
{
    std::ofstream file(filename);
    if (!file)
    {
        return false;
    }

    for (int i = 0; i < productCount; i++)
    {
        file << "Номер: " << products[i].RegisterNumber << '\n';
        file << "Имя автора: " << products[i].AuthorName << '\n';
        file << "Имя книги: " << products[i].BookName << '\n';
        file << "Год написания: " << products[i].Year << '\n';

        if (products[i].isPublishmentName)
        {
            file << "Название: " << products[i].PublishmentInfo.PublishmentName << '\n';
        }
        else
        {
            file << "Адрес: " << products[i].PublishmentInfo.PublishmentAddress << '\n';
        }

        file << products[i].NumberofPages << '\n';
        file << "===\n"; // Разделитель между записями
    }

    file.close();
    return true;
}

void editRecord(const std::string filename)
{
    std::fstream file(filename, std::ios::in);
    if (!file)
    {
        std::cout << "Ошибка открытия файла\n";
        return;
    }

    int record_number;
    std::cout << "Введите номер записи для редактирования: ";
    std::cin >> record_number;

    long record_offset = record_number * sizeof(Book);

    Book book;
    file.seekg(record_offset, std::ios::beg);
    file.read(reinterpret_cast<char*>(&book), sizeof(Book));
    if (file.fail())
    {
        std::cout << "Ошибка чтения записи\n";
        file.close();
        return;
    }

    std::cout << "\nВыберите поле для редактирования:\n"
              << "1. Регистрационный номер\n"
              << "2. Имя автора\n"
              << "3. Название книги\n"
              << "4. Год издания\n"
              << "5. Издательство (название или адрес)\n"
              << "6. Количество страниц\n"
              << "Ваш выбор: ";

    int choice;
    std::cin >> choice;

    switch (choice)
    {
        case 1:
            std::cout << "Новый регистрационный номер: ";
            std::cin >> book.RegisterNumber;
            break;
        case 2:
            std::cout << "Новое имя автора: ";
            std::cin.ignore();
            inputString(book.AuthorName, 50);
            break;
        case 3:
            std::cout << "Новое название книги: ";
            std::cin.ignore();
            inputString(book.BookName, 50);
            break;
        case 4:
            std::cout << "Новый год издания: ";
            std::cin >> book.Year;
            break;
        case 5:
            std::cout << "Выберите тип издательства:\n"
                      << "1. Название\n"
                      << "2. Адрес\n";
            int pub_choice;
            std::cin >> pub_choice;
            std::cin.ignore();

            if (pub_choice == 1)
            {
                std::cout << "Введите новое название издательства: ";
                inputString(book.PublishmentInfo.PublishmentName, 50);
                book.isPublishmentName = true;
            }
            else if (pub_choice == 2)
            {
                std::cout << "Введите новый адрес издательства: ";
                inputString(book.PublishmentInfo.PublishmentAddress, 50);
                book.isPublishmentName = false;
            }
            else
            {
                std::cout << "Неверный выбор.\n";
            }
            break;
        case 6:
            std::cout << "Новое количество страниц: ";
            std::cin >> book.NumberofPages;
            break;
        default:
            std::cout << "Неверный выбор\n";
            file.close();
            return;
    }

    fil
    
    <char*>(&book), sizeof(Book));

    if (file.fail())
    {
        std::cout << "Ошибка записи в файл\n";
    }
    else
    {
        std::cout << "Запись успешно обновлена\n";
    }

    file.close();
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
