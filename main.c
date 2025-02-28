#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#pragma warning(disable:4996)

//количество элементов в массивах
#define NUM_ENTRIES 100
#define NUM_SUBJECTS 12

//максимальная длина строки
#define MAX_NAME_LENGTH 50

//структура для хранения данных
typedef struct {
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char middle_name[MAX_NAME_LENGTH];
    char birth_date[11]; // Формат DD.MM.YYYY
    char subjects[NUM_SUBJECTS][MAX_NAME_LENGTH];
    char subjects_room[NUM_SUBJECTS][MAX_NAME_LENGTH];
    char subjects_hours[NUM_SUBJECTS][MAX_NAME_LENGTH];
    char group[MAX_NAME_LENGTH];
    char gender; 
} Person;

//массивы для случайных имен, фамилий и отчеств (женские)
const char* first_names_f[] = {
    "Анна", "Мария", "Елена", "Ольга", "Татьяна", "Наталья", "Ирина", "Светлана", "Екатерина", "Александра",
    "Людмила", "Вера", "Галина", "Лариса", "Валентина", "Нина", "Зинаида", "Маргарита", "Раиса", "Лидия"
};
const int num_first_names_f = sizeof(first_names_f) / sizeof(first_names_f[0]);

const char* last_names_f[] = {
    "Иванова", "Петрова", "Сидорова", "Смирнова", "Кузнецова", "Васильева", "Попова", "Новикова", "Морозова", "Волкова",
    "Алексеева", "Лебедева", "Семенова", "Егорова", "Павлова", "Козлова", "Степанова", "Николаева", "Орлова", "Андреева"
};
const int num_last_names_f = sizeof(last_names_f) / sizeof(last_names_f[0]);

const char* middle_names_f[] = {
    "Александровна", "Андреевна", "Борисовна", "Владимировна", "Дмитриевна", "Евгеньевна", "Ивановна", "Константиновна",
    "Михайловна", "Николаевна", "Павловна", "Сергеевна", "Федоровна", "Юрьевна", "Валентиновна", "Викторовна", "Геннадьевна",
    "Леонидовна", "Олеговна", "Станиславовна"
};
const int num_middle_names_f = sizeof(middle_names_f) / sizeof(middle_names_f[0]);

//массивы для случайных имен, фамилий и отчеств (мужские)
const char* first_names_m[] = {
    "Александр", "Дмитрий", "Михаил", "Сергей", "Андрей", "Иван", "Владимир", "Николай", "Алексей", "Евгений",
    "Павел", "Константин", "Артем", "Игорь", "Виталий", "Олег", "Юрий", "Василий", "Геннадий", "Станислав"
};
const int num_first_names_m = sizeof(first_names_m) / sizeof(first_names_m[0]);

const char* last_names_m[] = {
    "Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов", "Васильев", "Попов", "Новиков", "Морозов", "Волков",
    "Алексеев", "Лебедев", "Семенов", "Егоров", "Павлов", "Козлов", "Степанов", "Николаев", "Орлов", "Андреев"
};
const int num_last_names_m = sizeof(last_names_m) / sizeof(last_names_m[0]);

const char* middle_names_m[] = {
    "Александрович", "Дмитриевич", "Михайлович", "Сергеевич", "Андреевич", "Иванович", "Владимирович", "Николаевич",
    "Алексеевич", "Евгеньевич", "Павлович", "Константинович", "Артемович", "Игоревич", "Витальевич", "Олегович",
    "Юрьевич", "Васильевич", "Геннадьевич", "Станиславович"
};
const int num_middle_names_m = sizeof(middle_names_m) / sizeof(middle_names_m[0]);

//массив для учебных предметов
const char* subjects[] = {
    "Высшая математика:лекции", "Физика", "Элективная физическая культура и спорт", "Основы информационной безопасности", "История России", "Философия", "Структуры данных:лекция", "Структуры данных:Лабораторные",
    "Английский язык", "Физика:Лабораторные", "ВВПД", "Высшая математика:практика"
};
const int num_subjects = sizeof(subjects) / sizeof(subjects[0]);

//количество часов
const char* subjects_hours[] = {
    "46", "28", "72", "36", "12", "26", "24", "28",
    "28", "14", "28", "46"
};
const int num_subjects_hours = sizeof(subjects_hours) / sizeof(subjects_hours[0]);

//номер кабинета
const char* subjects_room[] = {
    "270", "237", "Политехник", "110", "237", "235", "235", "175",
    "106", "186", "324", "106"
};
const int num_subjects_room = sizeof(subjects_room) / sizeof(subjects_room[0]);

//массив для номера группы
const char* group[] = {
    "5151004/40001", "51510001/40001", "5151001/40002", "5151001/40003", "5151003/40001", "5151003/40002", "5151003/40003", "5151004/40002"
};
const int num_group = sizeof(group) / sizeof(group[0]);

//функция для генерации случайной даты рождения
void generate_birth_date(char* birth_date) {
    int year = 2000 + rand() % 9; // Год от 2000 до 2008
    int month = 1 + rand() % 12; // Месяц от 1 до 12
    int day = 1 + rand() % 28;   // День от 1 до 28 (упрощение)

    sprintf(birth_date, "%02d.%02d.%04d", day, month, year);
}

//функция для заполнения структуры случайными данными
void generate_person(Person* person) {
    //случайный выбор пола
    person->gender = (rand() % 2) ? 'M' : 'F'; // 'M' - мужской, 'F' - женский

    //выбор случайного имени, фамилии и отчества в зависимости от пола
    if (person->gender == 'F') {
        strncpy(person->first_name, first_names_f[rand() % num_first_names_f], MAX_NAME_LENGTH - 1);
        strncpy(person->last_name, last_names_f[rand() % num_last_names_f], MAX_NAME_LENGTH - 1);
        strncpy(person->middle_name, middle_names_f[rand() % num_middle_names_f], MAX_NAME_LENGTH - 1);
    }
    else {
        strncpy(person->first_name, first_names_m[rand() % num_first_names_m], MAX_NAME_LENGTH - 1);
        strncpy(person->last_name, last_names_m[rand() % num_last_names_m], MAX_NAME_LENGTH - 1);
        strncpy(person->middle_name, middle_names_m[rand() % num_middle_names_m], MAX_NAME_LENGTH - 1);
    }

    //генерация случайной даты рождения
    generate_birth_date(person->birth_date);
    
    //выбор случайной группы
    strncpy(person->group, group[rand() % num_group], MAX_NAME_LENGTH - 1);
    
    //переменная для 
    int num_sub = rand() % num_subjects;
    
    //выбор случайных учебных предметов
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        strncpy(person->subjects[i], subjects[rand() % num_subjects], MAX_NAME_LENGTH - 1);
    }
    
    //выбор случайных учебных предметов с привязкой
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        
        int sub_index = rand() % num_subjects;

        strncpy(person->subjects[i], subjects[sub_index], MAX_NAME_LENGTH - 1);
        strncpy(person->subjects_hours[i], subjects_hours[sub_index], MAX_NAME_LENGTH - 1);
        strncpy(person->subjects_room[i], subjects_room[sub_index], MAX_NAME_LENGTH - 1);
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Rus"); 

    //запрос количества учащихся
    int num_people;
    scanf("%d", &num_people);

    //создание динамического массива
    Person* people = (Person*)malloc(num_people * sizeof(Person));

    //проверка выделения памяти
    if (people == NULL) {
        printf("Ошибка выделения памяти");
        return 1;
    }

    //заполнение массива структур случайными данными
    for (int i = 0; i < num_people; i++) {
        generate_person(&people[i]);
    }

    //вывод данных
    for (int i = 0; i < num_people; i++) {
        printf("Человек %d:\n", i + 1);
        printf("  Имя: %s %s %s\n", people[i].last_name, people[i].first_name, people[i].middle_name);
        printf("  Дата рождения: %s\n", people[i].birth_date);
        printf("  Группа: %s\n", people[i].group);
        printf("  Учебные предметы:\n");
        for (int j = 0; j < NUM_SUBJECTS - (rand() % 6); j++) {
            printf("    - %s\n", people[i].subjects[j]);
            printf("      Количество часов: %s\n", people[i].subjects_hours[j]);
            printf("      Номер кабинета: %s\n", people[i].subjects_room[j]);
        }
        printf("\n");
    }

    //освобождение памяти)
    free(people);

    return 0;
}
