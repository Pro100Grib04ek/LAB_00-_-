#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#pragma warning(disable:4996)


/* ========== Структуры данных ========== */

#pragma pack(push, 1) // Выравнивание = 1 байт

typedef struct {
    const char* name;
    const char* room_lec;
    const char* room_lab;
    uint16_t hours;
    uint8_t format; // 0-экзамен, 1-зачет, 2-курсовая
} PackedSubject;

typedef struct {
    uint8_t num_subjects;
    PackedSubject* subjects;
} StudentGroup;

typedef struct {
    uint16_t name_indexes : 15; // 5 бит на каждый индекс (0-26)
    uint8_t gender : 1;  // 0-муж, 1-жен
    uint8_t group_index : 7;  // 0-127 групп
    uint16_t birth_days;  // дни с 01.01.1990 (0-16383)
} Student;

#pragma pack(pop) // Вернули предыдущую настройку выравнивания

/* ========== Глобальные константы ========== */
const char* first_names_f[] = {
    "Анна", "Мария", "Елена", "Ольга", "Татьяна", "Наталья", "Ирина",
    "Светлана", "Екатерина", "Александра", "Людмила", "Вера", "Галина",
    "Лариса", "Валентина", "Нина", "Зинаида", "Маргарита", "Раиса", "Лидия"
};

const char* first_names_m[] = {
    "Александр", "Дмитрий", "Михаил", "Сергей", "Андрей", "Иван", "Владимир",
    "Николай", "Алексей", "Евгений", "Павел", "Константин", "Артем", "Игорь",
    "Виталий", "Олег", "Юрий", "Василий", "Геннадий", "Станислав"
};

const char* last_names_f[] = {
    "Иванова", "Петрова", "Сидорова", "Смирнова", "Кузнецова", "Васильева",
    "Попова", "Новикова", "Морозова", "Волкова", "Алексеева", "Лебедева",
    "Семенова", "Егорова", "Павлова", "Козлова", "Степанова", "Николаева",
    "Орлова", "Андреева"
};

const char* last_names_m[] = {
    "Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов", "Васильев",
    "Попов", "Новиков", "Морозов", "Волков", "Алексеев", "Лебедев",
    "Семенов", "Егоров", "Павлов", "Козлов", "Степанов", "Николаев",
    "Орлов", "Андреев"
};

const char* middle_names_f[] = {
    "Александровна", "Андреевна", "Борисовна", "Владимировна", "Дмитриевна",
    "Евгеньевна", "Ивановна", "Константиновна", "Михайловна", "Николаевна",
    "Павловна", "Сергеевна", "Федоровна", "Юрьевна", "Валентиновна",
    "Викторовна", "Геннадьевна", "Леонидовна", "Олеговна", "Станиславовна"
};

const char* middle_names_m[] = {
    "Александрович", "Дмитриевич", "Михайлович", "Сергеевич", "Андреевич",
    "Иванович", "Владимирович", "Николаевич", "Алексеевич", "Евгеньевич",
    "Павлович", "Константинович", "Артемович", "Игоревич", "Витальевич",
    "Олегович", "Юрьевич", "Васильевич", "Геннадьевич", "Станиславович"
};

const char* groups[] = {
    "5151004/40001", "51510001/40001", "5151001/40002", "5151001/40003",
    "5151003/40001", "5151003/40002", "5151003/40003", "5151004/40002"
};

const char* att_format[] = {
    "Экзамен", "Зачёт", "Курсовая"
};

PackedSubject all_subjects[] = {
    {"Высшая математика", "301", "401", 120, 0},
    {"Физика", "202", "302", 90, 0},
    {"Физкультура", "Политехник", "Политехник", 60, 1},
    {"Информационная безопасность", "501", "502", 75, 2},
    {"История России", "105", "-", 60, 1},
    {"Философия", "210", "-", 45, 1},
    {"Структуры данных", "410", "411", 110, 0},
    {"Английский язык", "508", "509", 80, 1},
    {"ВВПД", "307", "308", 70, 2},
    {"Цифровой практикум", "415", "416", 90, 2},
    {"Алгоритмизация", "412", "-", 100, 0},
    {"Матанализ", "201", "-", 120, 0},
    {"Линейная алгебра", "203", "-", 80, 0},
    {"Дискретная математика", "205", "-", 70, 0},
    {"Теормех", "305", "306", 85, 0},
    {"Численные методы", "405", "-", 95, 0},
    {"Базы данных", "409", "410", 110, 2},
    {"Проектная деятельность", "100", "-", 60, 2},
    {"Теория вероятностей", "207", "-", 75, 0},
    {"Оптимизация", "209", "-", 65, 0},
    {"ООП", "415", "416", 105, 2},
    {"Архитектура ПК", "510", "-", 80, 0},
    {"Микроконтроллеры", "512", "513", 90, 2}
};

const int min_sub = 10;
const int max_sub = 20;
/* ========== Глобальные настройки ========== */
#define MAX_GROUPS 128
#define DAYS_OFFSET 631152000 // UNIX время для 01.01.1990

StudentGroup group_cache[MAX_GROUPS];
uint8_t total_groups = 8;

/* ========== Функции работы с системой ========== */
void init_system() {
    for (int i = 0; i < total_groups; i++) {
        group_cache[i].num_subjects = rand()%(max_sub - min_sub + 1) + min_sub; // Случайное кол-во предметов для группы 10-20
        group_cache[i].subjects = malloc(group_cache[i].num_subjects * sizeof(PackedSubject));
        for (int j = 0; j < group_cache[i].num_subjects; j++) {
            group_cache[i].subjects[j] = all_subjects[rand() % 23];
        }
    }
}

void unix_to_date(uint16_t days) {
    time_t rawtime = DAYS_OFFSET + days * 86400;
    struct tm* timeinfo = localtime(&rawtime);
    printf("%02d.%02d.%d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
}

/* ========== Основные функции ========== */
void generate_student(Student* s) {
    s->gender = rand() % 2;
    s->name_indexes = (rand() % 20) << 10 | (rand() % 20) << 5 | (rand() % 20);
    s->group_index = rand() % total_groups;
    s->birth_days = (rand() % 6200) + 1;
    //StudentGroup* g = &group_cache[s->group_index];
}

const char* get_name(Student* s, int part) {
    uint8_t idx = (s->name_indexes >> (10 - part * 5)) & 0x1F;
    return s->gender ?
        (part == 0 ? last_names_f[idx] :
            part == 1 ? first_names_f[idx] : middle_names_f[idx]) :
        (part == 0 ? last_names_m[idx] :
            part == 1 ? first_names_m[idx] : middle_names_m[idx]);
}

void print_student(Student* s) {
    printf("Студент: %s %s %s\n",
        get_name(s, 0), get_name(s, 1), get_name(s, 2));
    printf("Группа: %s\n", groups[s->group_index]);
    printf("Дата рождения: ");
    unix_to_date(s->birth_days);
    printf("\nДисциплины:\n");

    StudentGroup* g = &group_cache[s->group_index];
    for (int i = 0; i < g->num_subjects; i++) {
        printf("  %s:\n", g->subjects[i].name);
        printf("    -Количество часов: %hu\n", g->subjects[i].hours);
        printf("    -Кабинет лекции: %s\n", g->subjects[i].room_lec);
        printf("    -Кабинет лабы: %s\n", g->subjects[i].room_lab);
        printf("    -Формат аттестации: %s\n", att_format[g->subjects[i].format]);
    }
    printf("----------------\n");
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");
    init_system();

    Student* students = NULL;
    int count = 0;
    long long total_mem = 0;

    while (1) {
        char cmd[16];
        printf("Введите команду: ");
        scanf("%s", cmd);

        if (strcmp(cmd, "gen") == 0) {
            int n;
            scanf("%d", &n);

            students = realloc(students, (count + n) * sizeof(Student));
            for (int i = 0; i < n; i++) {
                generate_student(&students[count + i]);
            }

            total_mem += n * sizeof(Student);
            count += n;
        }
        else if (strcmp(cmd, "print") == 0) {
            int print;
            scanf("%d", &print);
            if ((print > count) || (print == -1))
            {
                print = count;
            }
            for (int i = 0; i < print; i++)
                print_student(&students[i]);
        }
        else if (strcmp(cmd, "mem") == 0) {
            printf("Всего студентов: %d\n", count);
            printf("Память структур: %d b\n\t\t %d kb\n\t\t %d mb\n", total_mem, total_mem/1024, total_mem/1024/1024);
        }
        else if (strcmp(cmd, "clear") == 0) {
            free(students);
            students = NULL;
            total_mem = 0;
            count = 0;
            /*
            for (int i = 0; i < total_groups; i++) {
                free(group_cache[i].subjects);
            }
            */
        }
    }

    return 0;
}
