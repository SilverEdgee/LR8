#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

typedef struct {
    int RegisterNumber;
    char AuthorName[50];
    char BookName[50];
    int Year;
    union {
        char PublishmentName[50]; 
        char PublishmentAddress[50];
    } PublishmentInfo;
    bool isPublishmentName;
    int NumberofPages;
} Book;


// Функции для валидации ввода
int ifInt();
int ifPositiveInt();
int ifChoice1or2();
int ifValidNewCount(int currentCount);

// Функции для управления продуктами
void CalculateTotalPrice(Book &p);
Book* AddToExistingArray(Book *existingBooks, int &currentCount, int newCount);
void PrintBooks(Book *p, int count);
void DeleteBooks(Book *&p, int &BookCount);
void ModifyBook(Book *p, int BookCount);
void insertionSort(std::string* array, int arrayLength);
void Alphabetical(Book* p, int BookCount);
// Функции для управлением памятью
Book AllocationFor1();
Book* AllocationWhile(int &count);
Book* AllocationByN(int N);
Book* DialogueInput(int &count);

bool writeToFile(const std::string filename, Book *book, int ProductCount);
void readFromFile(const std::string filename);
void editRecord(const std::string filename);

void inputString(char* buffer, int maxLength);