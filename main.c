#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#pragma warning(disable:4996)


// количество элементов в массивах
#define NUM_ENTRIES 100
#define NUM_SUBJECTS 12

// максимальная длина строки
#define MAX_NAME_LENGTH 100
#define MAX_DISCIPLINE_NAME 30 

// Кол-во дисциплин. Должна задаваться пользователем
#define MAX_DISCIPLINES 20

// Структура для дисциплин
typedef struct
{
    char name[MAX_DISCIPLINE_NAME];
    char room_lections;
    char room_labs;
    char hours;
    char format[MAX_NAME_LENGTH]; // экзамен, зачет, курсовая
} subject;

// структура для хранения студентов
typedef struct
{
    char full_name[MAX_NAME_LENGTH];
    char birth_date[11]; // Формат DD.MM.YYYY
    subject subjects[MAX_DISCIPLINES];
    char group[MAX_NAME_LENGTH];
} Person;

// массивы для случайных имен, фамилий и отчеств
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

// массив для учебных предметов
const char* subjects[] = {
    "Высшая математика:лекции", "Физика", "Элективная физическая культура и спорт", "Основы информационной безопасности", "История России", "Философия", "Структуры данных:лекция", "Структуры данных:Лабораторные",
    "Английский язык", "Физика:Лабораторные", "ВВПД", "Высшая математика:практика"
};
const int num_subjects = sizeof(subjects) / sizeof(subjects[0]);

// количество часов
const char* subjects_hours[] = {
    "46", "28", "72", "36", "12", "26", "24", "28",
    "28", "14", "28", "46"
};
const int num_subjects_hours = sizeof(subjects_hours) / sizeof(subjects_hours[0]);

// номер кабинета
const char* subjects_room[] = {
    "270", "237", "Политехник", "110", "237", "235", "235", "175",
    "106", "186", "324", "106"
};
const int num_subjects_room = sizeof(subjects_room) / sizeof(subjects_room[0]);


// массив для номера группы
const char* group[] = {
    "5151004/40001", "51510001/40001", "5151001/40002", "5151001/40003", "5151003/40001", "5151003/40002", "5151003/40003", "5151004/40002"
};
const int num_group = sizeof(group) / sizeof(group[0]);


// функция для генерации случайной даты рождения
void generate_birth_date(char* birth_date)
{
    int year = 2000 + rand() % 9; // Год от 2000 до 2008
    int month = 1 + rand() % 12; // Месяц от 1 до 12
    int day = 1 + rand() % 28;   // День от 1 до 28 (упрощение)

    sprintf(birth_date, "%02d.%02d.%04d", day, month, year);
}

// функция для заполнения структуры случайными данными
void generate_person(Person* person)
{
    char first_name = first_names[rand() % num_first_names];
    char middle_name = middle_names[rand() % num_middle_names];
    char last_name = last_names[rand() % num_last_names];
    char full_name = strcat(first_name, middle_name);
    full_name = strcat(full_name, last_name);
    // выбор случайного имени, фамилии и отчества
    strcpy(person->full_name, full_name);

    strncpy(person->group, group[rand() % num_group], MAX_NAME_LENGTH - 1);

    // генерация случайной даты рождения
    generate_birth_date(person->birth_date);

    // выбор случайных учебных предметов
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        strncpy(person->subjects->hours, subjects_hours[rand() % num_subjects_hours], MAX_NAME_LENGTH - 1);
        strncpy(person->subjects->room_labs, subjects_room[rand() % num_subjects_room], MAX_NAME_LENGTH - 1);
        strncpy(person->subjects->room_lections, subjects_room[rand() % num_subjects_room], MAX_NAME_LENGTH - 1);
    }
}


int main()
{
    srand(time(NULL)); // инициализация генератора случайных чисел

    // запрос количества учащихся
    int num_people;
    scanf("%d", &num_people);

    // создание динамического массива
    Person* people = (Person*)malloc(num_people * sizeof(Person));

    // проверка допустимой памяти
    if (people == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    // заполнение массива структур случайными данными // TODO в отдельную процедуру
    for (int i = 0; i < num_people; i++) {
        generate_person(&people[i]);
    }

    // вывод данных TODO в отдельную процедуру
    for (int i = 0; i < num_people; i++)
    {
        setlocale(LC_ALL, "Rus");
        printf("Человек %d:\n", i + 1);
        printf("  ФИО: %s\n", people[i].full_name);
        printf("  Дата рождения: %s\n", people[i].birth_date);
        printf("  Учебные предметы:\n");
        printf("  Группа: %s\n", people[i].group);
        for (int j = 0; j < NUM_SUBJECTS - (rand() % 6); j++) {
            printf("    - %s\n", people[i].subjects[j]);
            printf("  Количество часов: %s\n", people[i].subjects[j].hours);
            printf("  Номер кабинета лекций: %s\n", people[i].subjects[j].room_lections);
            printf("  Номер кабинета лабораторных: %s\n", people[i].subjects[j].room_labs);
        }
        printf("\n");
    }

    return 0;
}
