#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>

#pragma warning(disable:4996)

extern const char* first_names_f[]; //массивы для случайных имен, фамилий и отчеств (женские)
extern const int num_first_names_f;
extern const char* last_names_f[];
extern const int num_last_names_f;
extern const char* middle_names_f[];
extern const int num_middle_names_f;
extern const char* first_names_m[]; //массивы для случайных имен, фамилий и отчеств (мужские)
extern const int num_first_names_m;
extern const char* last_names_m[];
extern const int num_last_names_m;
extern const char* middle_names_m[];
extern const int num_middle_names_m;
extern const char* subjects[]; //массив для учебных предметов
extern const int num_subjects;
extern const int num_subjects_hours;
extern const char* subjects_room[]; //номер кабинета
extern int num_subjects_room;
extern const char* group[];
extern const int num_group; //массив для номера группы
extern const char* subjects_hours[]; //количество часов

//количество элементов в массивах
#define NUM_ENTRIES 100
#define NUM_SUBJECTS 12

//максимальная длина строки
#define MAX_NAME_LENGTH 100

//структура для хранения данных
typedef struct {
    char full_name[MAX_NAME_LENGTH];
    char birth_date[11]; // Формат DD.MM.YYYY
    char subjects[NUM_SUBJECTS][MAX_NAME_LENGTH];
    char subjects_room[NUM_SUBJECTS][MAX_NAME_LENGTH];
    char subjects_hours[NUM_SUBJECTS][MAX_NAME_LENGTH];
    char group[MAX_NAME_LENGTH];
    char gender;
} Person;


//функция для генерации случайной даты рождения
void generate_birth_date(char* birth_date) {
    int year = 2000 + rand() % 9; // Год от 2000 до 2008
    int month = 1 + rand() % 12; // Месяц от 1 до 12
    int day;
    if (month == 2) // Февраль
    {
        day = 1 + rand() % 28;
    }
    else
    {
        day = 1 + rand() % 30;
    }
    sprintf(birth_date, "%02d.%02d.%04d", day, month, year);
}

//функция для заполнения структуры случайными данными
void generate_person(Person* person, int min_disciplines, int max_disciplines) {
    //случайный выбор пола
    person->gender = (rand() % 2) ? 'M' : 'F'; // 'M' - мужской, 'F' - женский
    char full_name[MAX_NAME_LENGTH];

    //выбор случайного имени, фамилии и отчества в зависимости от пола
    if (person->gender == 'F') {
        strcpy(full_name, last_names_f[rand() % num_last_names_f]);
        strcat(full_name, " ");
        strcat(full_name, first_names_f[rand() % num_first_names_f]);
        strcat(full_name, " ");
        strcat(full_name, middle_names_f[rand() % num_middle_names_f]);
        strncpy(person->full_name, full_name, MAX_NAME_LENGTH - 1);
    }
    else {
        strcpy(full_name, last_names_m[rand() % num_last_names_m]);
        strcat(full_name, " ");
        strcat(full_name, first_names_m[rand() % num_first_names_m]);
        strcat(full_name, " ");
        strcat(full_name, middle_names_m[rand() % num_middle_names_m]);
        strncpy(person->full_name, full_name, MAX_NAME_LENGTH - 1);
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

void print_students(Person* people, int num_people)
{
    for (int i = 0; i < num_people; i++) {
        printf("Человек %d:\n", i + 1);
        printf("  Имя: %s\n", people[i].full_name);
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
}
/*
int main_old() {
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
        generate_person(&people[i], 1, 1);
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
*/

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    char request[16]; // Строка с запросом, 16 - Макс. длина запроса

    Person* people = (Person*)malloc(0); // Далее память будет выделяться realloc внутри процедуры
    long long mem = 0; // Тут хранится занимаемая память
    int min_disciplines = 10;
    int max_disciplines = 20;
    while (1)
    {
        scanf("%s", &request);

        if (!strcmp(request, "gen")) // Отрицание, т.к. strcmp возвращает 0, при совпадениии строк
        {
            int gen_num; // Кол-во для генерации
            scanf("%d", &gen_num);
            people = realloc(people, gen_num * sizeof(Person));
            mem += gen_num * sizeof(Person);
            if (people == NULL)
            {
                printf("Недостаточно памяти!\n");
                continue;
            }
            for (int i = 0; i < gen_num; i++)
            {
                generate_person(&people[i], min_disciplines, max_disciplines);
            }
        }
        if (!strcmp(request, "get_size"))
        {
            printf("%lli B\n", mem);
            printf("%3.2Lf Kb\n", (double)mem / 1024);
            printf("%3.2Lf Mb\n", (double)mem / 1024 / 1024);
            printf("%3.2Lf Gb\n", (double)mem / 1024 / 1024 / 1024);
        }
        if (!strcmp(request, "print_students"))
        {
            int print_num; // Сколько стундентов вывести
            scanf("%d", &print_num);
            int num_generated_students = mem/sizeof(people[0]);
            if ((print_num > num_generated_students) || (print_num == -1))
            {
                print_num = num_generated_students;
            }
            print_students(people, print_num);
        }
        if (!strcmp(request, "clean"))
        {
            free(people);
            mem = 0;
        }
    }
}