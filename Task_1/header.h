#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

typedef union {
    int workshopNumber;
    char workshopName[50] = {0};
} Workshop;

typedef struct {
    char name[50] = {0};
    int NumOfProducts;
    Workshop workshopInfo;
    bool isWorkshopName;
    double price;
    double totalPrice;
} Product;

// Функции для валидации ввода
int ifInt();
int ifPositiveInt();
double ifPositive();
int ifChoice1or2();
int ifValidNewCount(int currentCount);

// Функции для управления продуктами
void CalculateTotalPrice(Product &p);
Product* AddToExistingArray(Product *existingProducts, int &currentCount, int newCount);
void PrintStruct(Product *p, int count);
void FindSmth(Product *p, int ProductCount, bool found, std::vector<int> &foundIndices);
void DeleteProducts(Product *&p, int &ProductCount);
void ModifyProduct(Product *p, int ProductCount);
void shekerSort(int *NumofProducts, int count);
void SortStruct(Product *p, int ProductCount);
void PrintProductsByWorkshop(Product *p, int ProductCount);

// Функции для управлением памятью
Product AllocationFor1();
Product* AllocationWhile(int &count);
Product* AllocationByN(int N);
Product* DialogueInput(int &count);
//  Работа с файлами(засунуты в inputoutput.cpp)
bool writeToFile(const std::string filename, Product *product, int ProductCount);
void readFromFile(const std::string filename);
void editRecord(const std::string filename);
void inputString(char *buffer, int maxLength);