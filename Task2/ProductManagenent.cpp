#include <iostream>
#include <string>
#include <vector>
#include "Task2.h"

Book *AddToExistingArray(Book *existingBooks, int &currentCount, int newCount)
{
    std::cout << "Введите новое количество продукций (не меньше текущего " << currentCount << "): ";
    newCount = ifValidNewCount(currentCount);

    Book *newBooks = new Book[currentCount + newCount];
    for (int i = 0; i < currentCount; i++)
    {
        newBooks[i] = existingBooks[i];
    }

    delete[] existingBooks;
    existingBooks = nullptr;

    for (int i = 0; i < newCount; i++)
    {
        std::cout << "Введите данные для новой книги #" << (currentCount + i + 1) << ":\n";
        newBooks[currentCount + i] = AllocationFor1();
    }

    currentCount += newCount;
    return newBooks;
}

void PrintBooks(Book *books, int count)
{
    if (books == nullptr || count == 0)
    {
        std::cout << "Книги не введены.\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        std::cout << "Книга #" << i + 1 << ":\n";
        std::cout << "  Регистрационный номер: " << books[i].RegisterNumber << "\n";
        std::cout << "  Автор: " << books[i].AuthorName << "\n";
        std::cout << "  Название: " << books[i].BookName << "\n";
        std::cout << "  Год издания: " << books[i].Year << "\n";
        if (books[i].isPublishmentName)
        {
            std::cout << "  Название издательства: " << books[i].PublishmentInfo.PublishmentName << "\n";
        }
        else
        {
            std::cout << "  Адрес издательства: " << books[i].PublishmentInfo.PublishmentAddress << "\n";
        }
        std::cout << "  Количество страниц: " << books[i].NumberofPages << "\n";
    }
}

void FindSmth(Book *p, int BookCount, bool found, std::vector<int> &foundIndices)
{
    if (p == nullptr || BookCount == 0)
    {
        std::cout << "Нет данных для поиска.\n";
        return;
    }
    std::cout << "Выберите поле для поиска:\n"
              << "1. Регистрационный номер\n"
              << "2. Имя автора\n"
              << "3. Название книги\n"
              << "4. Год издания\n"
              << "5. Название или адрес издательства\n"
              << "6. Количество страниц\n"
              << "Ваш выбор: ";
    int choice = ifInt();
    while (choice < 1 || choice > 6)
    {
        std::cout << "Введите число от 1 до 6" << std::endl;
        choice = ifInt();
    }
    char SearchString[100];
    int searchInt;
    foundIndices.clear();
    switch (choice)
    {
    case 1:
        std::cout << "Введите регистрационный номер: ";
        searchInt = ifPositiveInt();
        break;
    case 2:
        std::cout << "Введите имя автора: ";
        if (std::cin.peek() == '\n')
        {
            std::cin.ignore();
        }
        inputString(SearchString, 50);
        break;
    case 3:
        std::cout << "Введите название книги: ";
        if (std::cin.peek() == '\n')
        {
            std::cin.ignore();
        }
        inputString(SearchString, 50);
        break;
    case 4:
        std::cout << "Введите год издания: ";
        searchInt = ifPositiveInt();
        break;
    case 5:
        std::cout << "Введите название или адрес издательства: ";
        if (std::cin.peek() == '\n')
        {
            std::cin.ignore();
        }
        inputString(SearchString, 50);
        break;
    case 6:
        std::cout << "Введите количество страниц: ";
        searchInt = ifPositiveInt();
        break;
    default:
        std::cout << "Некорректный выбор.\n";
        return;
    }

    for (int i = 0; i < BookCount; i++)
    {
        bool match = false;

        switch (choice)
        {
        case 1:
            if (p[i].RegisterNumber == searchInt)
            {
                match = true;
            }
            break;
        case 2:
            if (strcmp(p[i].AuthorName, SearchString) == 0)
            {
                match = true;
            }
            break;
        case 3:
            if (strcmp(p[i].BookName, SearchString) == 0)
            {
                match = true;
            }
            break;
        case 4:
            if (p[i].Year == searchInt)
            {
                match = true;
            }
            break;
        case 5:
            if (p[i].isPublishmentName && strcmp(p[i].PublishmentInfo.PublishmentName, SearchString) == 0)
            {
                match = true;
            }
            else if (!p[i].isPublishmentName && strcmp(p[i].PublishmentInfo.PublishmentAddress, SearchString) == 0)
            {
                match = true;
            }
            break;
        case 6:
            if (p[i].NumberofPages == searchInt)
            {
                match = true;
            }
            break;
        }

        if (match)
        {
            foundIndices.push_back(i);
        }
    }

    if (!foundIndices.empty())
    {
        std::cout << "\nНайденные книги:\n";
        for (int index : foundIndices)
        {
            std::cout << "Книга #" << index + 1 << ":\n"
                      << "  Регистрационный номер: " << p[index].RegisterNumber << "\n"
                      << "  Автор: " << p[index].AuthorName << "\n"
                      << "  Название: " << p[index].BookName << "\n"
                      << "  Год издания: " << p[index].Year << "\n";
            if (p[index].isPublishmentName)
            {
                std::cout << "  Название издательства: " << p[index].PublishmentInfo.PublishmentName << "\n";
            }
            else
            {
                std::cout << "  Адрес издательства: " << p[index].PublishmentInfo.PublishmentAddress << "\n";
            }
            std::cout << "  Количество страниц: " << p[index].NumberofPages << "\n\n";
        }
    }
    else
    {
        std::cout << "Совпадений не найдено.\n";
    }
}


void DeleteBooks(Book *&p, int &BookCount)
{
    if (p == nullptr || BookCount == 0)
    {
        std::cout << "Нет данных для удаления.\n";
        return;
    }
    std::vector<int> foundIndices = {0};
    bool found = true;
    FindSmth(p, BookCount, found, foundIndices);
    if (!found)
    {
        std::cout << "Нет найдено данных для удаления." << std::endl;
    }
    int last = foundIndices.size();
    std::cout << "Введите номер книги для удаления (" << foundIndices[0] + 1 << "-" << last << "): ";
    int index = ifPositiveInt();

    while (index > last)
    {
        std::cout << "Неверный номер. Введите число от " << foundIndices[0] + 1 << " до " << last << ": ";
        index = ifPositiveInt();
    }

    index--;

    for (int i = index; i < BookCount - 1; i++)
    {
        p[i] = p[i + 1];
    }

    BookCount--;
    if (BookCount > 0)
    {
        Book *newBooks = new Book[BookCount];
        for (int i = 0; i < BookCount; i++)
        {
            newBooks[i] = p[i];
        }
        delete[] p;
        p = newBooks;
    }
    else
    {
        delete[] p;
        p = nullptr;
    }

    std::cout << "Книга успешно удалена.\n";
    return;
}

void ModifyBook(Book* p, int BookCount)
{
    if (p == nullptr || BookCount == 0)
    {
        std::cout << "Нет данных для изменения.\n";
        return;
    }

    bool found = true;
    std::vector<int> foundIndices;
    FindSmth(p, BookCount, found, foundIndices);

    if (foundIndices.empty())
    {
        std::cout << "Нет подходящих книг для изменения.\n";
        return;
    }

    int last = foundIndices.size();
    std::cout << "Введите номер книги для изменения (1-" << last << "): ";
    int choiceIndex = ifPositiveInt();

    while (choiceIndex < 1 || choiceIndex > last)
    {
        std::cout << "Неверный номер. Введите число от 1 до " << last << ": ";
        choiceIndex = ifPositiveInt();
    }

    int index = foundIndices[choiceIndex - 1];

    std::cout << "\nВыберите поле для изменения:\n"
              << "1. Регистрационный номер\n"
              << "2. Имя автора\n"
              << "3. Название книги\n"
              << "4. Год издания\n"
              << "5. Издательство (Название)\n"
              << "6. Издательство (Адрес)\n"
              << "7. Количество страниц\n"
              << "Ваш выбор: ";

    int choice = ifPositiveInt();
    while (choice < 1 || choice > 7)
    {
        std::cout << "Введите число от 1 до 7: ";
        choice = ifPositiveInt();
    }

    switch (choice)
    {
    case 1:
        std::cout << "Введите новый регистрационный номер: ";
        p[index].RegisterNumber = ifPositiveInt();
        break;
    case 2:
        std::cout << "Введите новое имя автора: ";
        std::cin.ignore();
        inputString(p[index].AuthorName, 50);
        break;
    case 3:
        std::cout << "Введите новое название книги: ";
        std::cin.ignore();
        inputString(p[index].BookName, 50);
        break;
    case 4:
        std::cout << "Введите новый год издания: ";
        p[index].Year = ifPositiveInt();
        break;
    case 5:
        std::cout << "Введите новое название издательства: ";
        std::cin.ignore();
        inputString(p[index].PublishmentInfo.PublishmentName, 50);
        p[index].isPublishmentName = true; 
        break;
    case 6:
        std::cout << "Введите новый адрес издательства: ";
        std::cin.ignore();
        inputString(p[index].PublishmentInfo.PublishmentAddress, 50);
        p[index].isPublishmentName = false; 
        break;
    case 7:
        std::cout << "Введите новое количество страниц: ";
        p[index].NumberofPages = ifPositiveInt();
        break;
    }

    std::cout << "Данные книги успешно обновлены.\n";
}

void Alphabetical(Book *p, int BookCount)
{
    int possibleYear;
    int count = 0;
    if (p == nullptr || BookCount == 0)
    {
        std::cout << "Нет данных для изменения.\n";
        return;
    }
    std::cout << "Введите год: " << std::endl;
    possibleYear = ifPositiveInt();
    Book *SortedBooks = new Book[BookCount];

    for (int i = 0; i < BookCount; i++)
    {
        if (p[i].Year > possibleYear)
        {
            SortedBooks[count++] = p[i];
        }
    }

    if (count == 0)
    {
        std::cout << "Книг, изданных после " << possibleYear << ", не найдено.\n";
        return;
    }
    std::string new_array[count];
    for (int i = 0; i < count; i++)
    {
        new_array[i] = p[i].AuthorName;
    }

    insertionSort(new_array, count);

    bool *used = new bool[count];

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (!used[j] && new_array[i] == SortedBooks[j].AuthorName)
            {
                p[i] = SortedBooks[j];
                used[j] = true;
                break;
            }
        }
    }

    delete[] used;

    for (int i = 0; i < count; i++)
    {
        p[i] = SortedBooks[i];
    }

    PrintBooks(p, count);
    delete[] SortedBooks;
}

void insertionSort(std::string *array, int arrayLength)
{
    for (int i = 1; i < arrayLength; i++)
    {
        int j = i - 1;
        while (j >= 0 && array[j] > array[j + 1])
        {
            std::swap(array[j], array[j + 1]);
            j--;
        }
    }
}
