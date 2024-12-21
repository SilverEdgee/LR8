#include <iostream>
#include <string>
#include <vector>
#include "Task2.h"

Book AllocationFor1()
{
    Book b;

    std::cout << "Введите регистрационный номер книги: ";
    b.RegisterNumber = ifPositiveInt();

    std::cout << "Введите имя автора: ";
    inputString(b.AuthorName, 50);

    std::cout << "Введите название книги: ";
    inputString(b.BookName, 50);

    std::cout << "Введите год издания: ";
    b.Year = ifPositiveInt();

    std::cout << "Введите 1, чтобы ввести название издательства, или 2 для ввода адреса издательства: ";
    int choice = ifPositiveInt();
    while (choice < 1 || choice > 2)
    {
        std::cout << "Неверный выбор. Введите 1 или 2: ";
        choice = ifPositiveInt();
    }

    if (choice == 1)
    {
        std::cout << "Введите название издательства: ";
        inputString(b.PublishmentInfo.PublishmentName, 50);
        b.isPublishmentName = true; 
    }
    else
    {
        std::cout << "Введите адрес издательства: ";
        inputString(b.PublishmentInfo.PublishmentAddress, 50);
        b.isPublishmentName = false; 
    }

    std::cout << "Введите количество страниц: ";
    b.NumberofPages = ifPositiveInt();

    return b;
}


Book* AllocationWhile(int& count)
{
    int size = 1;
    Book* books = new Book[size];
    count = 0;

    while (true)
    {
        if (count >= size)
        {
            size *= 2;
            Book* new_books = new Book[size];
            for (int i = 0; i < count; i++)
            {
                new_books[i] = books[i];
            }
            delete[] books;
            books = new_books;
        }

        std::cout << "Введите данные о книге (введите \"СТОП\" в названии книги, чтобы завершить ввод):\n";
        Book temp = AllocationFor1();
        if (strcmp(temp.BookName, "СТОП") == 0) 
        {
            break;
        }
        books[count++] = temp;
    }

    return books;
}


Book* AllocationByN(int N)
{
    Book* books = new Book[N];
    for (int i = 0; i < N; i++)
    {
        std::cout << "Данные для книги #" << i + 1 << ": \n";
        books[i] = AllocationFor1();
    }
    return books;
}

Book* DialogueInput(int& count)
{
    int size = 1;
    Book* p = new Book[size];
    count = 0;

    while (true)
    {
        if (count >= size)
        {
            size *= 2;
            Book* new_p = new Book[size];
            for (int i = 0; i < count; i++)
            {
                new_p[i] = p[i];
            }
            delete[] p;
            p = new_p;
        }

        std::string Z;
        std::cout << "Желаете ввести данные о книге #" << count + 1 << "? (Введите \"Да\", если хотите продолжить): ";
        std::getline(std::cin, Z);

        if (Z == "Да")
        {
            p[count++] = AllocationFor1();
        }
        else
        {
            break;
        }
    }

    return p;
}
