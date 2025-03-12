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
extern const char* group[];
extern const int num_group; //массив для номера группы
extern const char* subject_format[];

//количество элементов в массивах
#define NUM_SUBJECTS 12

//максимальная длина строки
#define MAX_NAME_LENGTH 100

//структура для дисциплин
typedef struct
{
    char name[43]; // Самое длинное название - 42 символа
    char room_lec[4]; // < 256
    char room_lab[4]; // < 256
    char hours[4]; // < 256
    char format[10]; // Экзамен, зачёт, курсовая
} Subject;

//структура для хранения данных
typedef struct {
    char* first_name;
    char* middle_name;
    char* last_name;
    int birth_date; // Формат DD.MM.YYYY -> UNIX TIME
    short num_subjects;
    Subject subjects[1];
    char group[MAX_NAME_LENGTH];
    char gender;
} Person;

#define IsLeapYear(year) ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 

int getTotalDaysInMonth(int month, int year)
{
    int days[] = {
        31, // Jan
        28, // Feb
        31, // Mar
        30, // Apr
        31, // May
        30, // Jun
        31, // Jul
        31, // Aug
        30, // Sep
        31, // Oct
        30, // Nov
        31  // Dec
    };
    return (days[month - 1] + (IsLeapYear(year) && month == 2 ? 1 : 0));
}

void UnixToTime(int x) {
    int year = 1970;
    int day = 1;
    int month = 1;

    while (x >= 86400) {
        x -= 86400;
        day++;
        if (day > getTotalDaysInMonth(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                year++;
                month = 1;
            }
        }
    }
    printf("%d-%d-%d\n", day, month, year);
}

//функция для заполнения структуры случайными данными
void generate_person(Person* person, int min_disciplines, int max_disciplines)
{
    //случайный выбор пола
    person->gender = (rand() % 2) ? 'M' : 'F'; // 'M' - мужской, 'F' - женский
    char full_name[MAX_NAME_LENGTH];

    //выбор случайного имени, фамилии и отчества в зависимости от пола
    if (person->gender == 'F')
    {
        person->last_name = last_names_f[rand() % num_last_names_f];
        person->first_name = first_names_f[rand() % num_first_names_f];
        person->middle_name = middle_names_f[rand() % num_middle_names_f];
    }
    else
    {
        person->last_name = last_names_m[rand() % num_last_names_m];
        person->first_name = first_names_m[rand() % num_first_names_m];
        person->middle_name = middle_names_m[rand() % num_middle_names_m];
    }

    //генерация случайной даты рождения
    // Даты рождения: 946674000 - 1230757199
    int min_date = 946674000;
    int max_date = 1230757199;
    person->birth_date = (rand() % (max_date + 1 - min_date)) + min_date;

    //выбор случайной группы
    strncpy(person->group, group[rand() % num_group], MAX_NAME_LENGTH - 1);

    //переменная для >_<
    int num_sub = rand() % num_subjects;

    //выбор случайных учебных предметов
    int rand_num_subjects = rand() % (max_disciplines + 1 - min_disciplines) + min_disciplines; // Случайное число в диапазоне [min_disciplines, max_disciplines]
    person->num_subjects = rand_num_subjects;

    //выбор случайных учебных предметов с привязкой
    for (int i = 0; i < rand_num_subjects; i++)
    {
        strncpy(person->subjects[i].name, subjects[rand() % num_subjects], MAX_NAME_LENGTH - 1);
        sprintf(person->subjects[i].room_lec, "%d", (rand() % 256));
        sprintf(person->subjects[i].room_lab, "%d", (rand() % 256));
        sprintf(person->subjects[i].hours, "%d", (rand() % 256));
        strncpy(person->subjects[i].format, subject_format[rand() % 3], 11);
    }
}

void print_students(Person* people, int num_people)
{
    for (int i = 0; i < num_people; i++)
    {
        printf("Человек %d:\n", i + 1);
        printf("  Имя: %s %s %s\n", people[i].first_name, people[i].middle_name, people[i].last_name);
        printf("  Дата рождения: "); UnixToTime(people[i].birth_date);
        printf("  Группа: %s\n", people[i].group);
        printf("  Учебные предметы:\n");
        for (int j = 0; j < people[i].num_subjects; j++)
        {
            printf("    - %s\n", people[i].subjects[j]);
            printf("      Количество часов: %s\n", people[i].subjects[j].hours);
            printf("      Номер кабинета (лекции): %s\n", people[i].subjects[j].room_lec);
            printf("      Номер кабинета (лабы): %s\n", people[i].subjects[j].room_lab);
            printf("      Формат аттестации: %s\n", people[i].subjects[j].format);
        }
        printf("\n");
    }
}

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
            if (people == NULL)
            {
                printf("Недостаточно памяти!\n");
                continue;
            }
            mem += gen_num * sizeof(Person);
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
            int num_generated_students = mem / sizeof(people[0]);
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
            Person* people = (Person*)malloc(0); // Чтобы не крашилось при попытке геерации после очистки
        }
        if (!strcmp(request, "min"))
        {
            scanf("%d", &min_disciplines);
            if (min_disciplines > num_subjects)
            {
                min_disciplines = num_subjects;
            }
        }
        if (!strcmp(request, "max"))
        {
            scanf("%d", &max_disciplines);
            if (max_disciplines > num_subjects)
            {
                max_disciplines = num_subjects;
            }
        }
    }
}