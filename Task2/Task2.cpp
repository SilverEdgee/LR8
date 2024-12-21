#include <iostream>
#include <string>
#include "Task2.h"
#include <fstream>

int main()
{
    const char* filename = "books.txt"; 
    Book *Books = nullptr;
    int newCount = 0;
    int BookCount = 0;
    while (true)
    {
        std::cout << "\nМеню:\n"
                  << "1. Ввод данных\n"
                  << "2. Показать введённые данные\n"
                  << "3. Дополнение уже существующего массива книг новыми книгами\n"
                  << "4. Удаление книг\n"
                  << "5. Изменение характеристик книги\n"
                  << "6. Вывести список книг с фамилиями авторов в алфавитном порядке,"
                  << "изданных после заданного года.\n"
                  << "7. Ввод текстового файла\n"
                  << "8. Редактирование текстового файла\n"
                  << "9. Выйти\n"
                  << "Ваш выбор: ";
        int choice = ifInt();

        switch (choice)
        {
        case 1:
        {
            std::cout << "\nВыберите метод ввода данных:\n"
                      << "1. Ввести заранее заданное количество книг\n"
                      << "2. Ввод книг до команды \"СТОП\"\n"
                      << "3. Диалоговый ввод книг\n"
                      << "4. Отмена\n"
                      << "Ваш выбор: ";
            int inputMethod = ifInt();
            if (inputMethod == 1)
            {
                std::cout << "Введите количество книг: ";
                int N = ifPositiveInt();
                Books = AllocationByN(N);
                BookCount = N;
            }
            else if (inputMethod == 2)
            {
                Books = AllocationWhile(BookCount);
            }
            else if (inputMethod == 3)
            {
                Books = DialogueInput(BookCount);
            }
            else if (inputMethod == 4)
            {
                break;
            }
            break;
        }
        case 2:
            PrintBooks(Books, BookCount);
            break;
        case 3:
            Books = AddToExistingArray(Books, BookCount, newCount);
            break;
        case 4:
            DeleteBooks(Books, BookCount);
            break;
        case 5:
            ModifyBook(Books, BookCount);
            break;
        case 6:
            Alphabetical(Books, BookCount);
            break;
        case 7:
        {
            bool write = writeToFile(filename, Books, BookCount);
            if (write)
                std::cout << "Успешный ввод";
            else
                std::cout << "Неуспешный ввод";
            break;
        }
        case 8:
            editRecord(filename);
            break;
        case 9:
            delete[] Books;
            return 0;
        default:
            std::cout << "Некорректный ввод. Попробуйте снова.\n";
        }
    }
}
