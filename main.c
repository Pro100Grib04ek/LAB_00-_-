#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)
#include <locale.h>



// Количество элементов в массивах
#define NUM_ENTRIES 100
#define NUM_SUBJECTS 12

// Максимальная длина строки
#define MAX_NAME_LENGTH 50

// Структура для хранения данных
typedef struct {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char middle_name[MAX_NAME_LENGTH];
    char birth_date[11]; // Формат DD.MM.YYYY
    char subjects[NUM_SUBJECTS][MAX_NAME_LENGTH];
} Person;

// Массивы для случайных имен, фамилий и отчеств
const char* first_names[] = {
    "Анна", "Мария", "Елена", "Ольга", "Татьяна", "Наталья", "Ирина", "Светлана", "Екатерина", "Александра",
    "Людмила", "Вера", "Галина", "Лариса", "Валентина", "Нина", "Зинаида", "Маргарита", "Раиса", "Лидия"
};
const int num_first_names = sizeof(first_names) / sizeof(first_names[0]);

const char* last_names[] = {
    "Иванова", "Петрова", "Сидорова", "Смирнова", "Кузнецова", "Васильева", "Попова", "Новикова", "Морозова", "Волкова",
    "Алексеева", "Лебедева", "Семенова", "Егорова", "Павлова", "Козлова", "Степанова", "Николаева", "Орлова", "Андреева"
};
const int num_last_names = sizeof(last_names) / sizeof(last_names[0]);

const char* middle_names[] = {
    "Александровна", "Андреевна", "Борисовна", "Владимировна", "Дмитриевна", "Евгеньевна", "Ивановна", "Константиновна",
    "Михайловна", "Николаевна", "Павловна", "Сергеевна", "Федоровна", "Юрьевна", "Валентиновна", "Викторовна", "Геннадьевна",
    "Леонидовна", "Олеговна", "Станиславовна"
};
const int num_middle_names = sizeof(middle_names) / sizeof(middle_names[0]);

// Массив для учебных предметов
const char* subjects[] = {
    "Высшая математика:лекции", "Физика", "Элективная физическая культура и спорт", "Основы информационной безопасности", "История России", "Философия", "Структуры данных:лекция", "Структуры данных:Лабораторные",
    "Английский язык", "Физика:Лабораторные", "ВВПД", "Высшая математика:практика"
};
const int num_subjects = sizeof(subjects) / sizeof(subjects[0]);

// Функция для генерации случайной даты рождения
void generate_birth_date(char* birth_date) {
    int year = 2000 + rand() % 9; // Год от 2000 до 2008
    int month = 1 + rand() % 12; // Месяц от 1 до 12
    int day = 1 + rand() % 28;   // День от 1 до 28 (упрощение)

    sprintf(birth_date, "%02d.%02d.%04d", day, month, year);
}

// Функция для заполнения структуры случайными данными
void generate_person(Person* person) {
    // Выбор случайного имени, фамилии и отчества
    strncpy(person->first_name, first_names[rand() % num_first_names], MAX_NAME_LENGTH - 1);
    strncpy(person->last_name, last_names[rand() % num_last_names], MAX_NAME_LENGTH - 1);
    strncpy(person->middle_name, middle_names[rand() % num_middle_names], MAX_NAME_LENGTH - 1);

    // Генерация случайной даты рождения
    generate_birth_date(person->birth_date);

    // Выбор случайных учебных предметов
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        strncpy(person->subjects[i], subjects[rand() % num_subjects], MAX_NAME_LENGTH - 1);
    }
}


int main() {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Создание массива структур
    Person people[NUM_ENTRIES];

    // Заполнение массива структур случайными данными
    for (int i = 0; i < NUM_ENTRIES; i++) {
        generate_person(&people[i]);
    }

    // Вывод данных
    for (int i = 0; i < NUM_ENTRIES; i++) {
        setlocale(LC_ALL, "Rus");
        printf("Человек %d:\n", i + 1);
        printf("  Имя: %s %s %s\n", people[i].last_name, people[i].first_name, people[i].middle_name);
        printf("  Дата рождения: %s\n", people[i].birth_date);
        printf("  Учебные предметы:\n");
        for (int j = 0; j < NUM_SUBJECTS; j++) {
            printf("    - %s\n", people[i].subjects[j]);
        }
        printf("\n");
    }

    return 0;
}// this is test main file
