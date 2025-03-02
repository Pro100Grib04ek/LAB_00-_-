//массивы для случайных имен, фамилий и отчеств (женские)
extern const char* first_names_f[] = {
    "Анна", "Мария", "Елена", "Ольга", "Татьяна", "Наталья", "Ирина", "Светлана", "Екатерина", "Александра",
    "Людмила", "Вера", "Галина", "Лариса", "Валентина", "Нина", "Зинаида", "Маргарита", "Раиса", "Лидия"
};
extern const int num_first_names_f = sizeof(first_names_f) / sizeof(first_names_f[0]);

extern const char* last_names_f[] = {
    "Иванова", "Петрова", "Сидорова", "Смирнова", "Кузнецова", "Васильева", "Попова", "Новикова", "Морозова", "Волкова",
    "Алексеева", "Лебедева", "Семенова", "Егорова", "Павлова", "Козлова", "Степанова", "Николаева", "Орлова", "Андреева"
};
extern const int num_last_names_f = sizeof(last_names_f) / sizeof(last_names_f[0]);

extern const char* middle_names_f[] = {
    "Александровна", "Андреевна", "Борисовна", "Владимировна", "Дмитриевна", "Евгеньевна", "Ивановна", "Константиновна",
    "Михайловна", "Николаевна", "Павловна", "Сергеевна", "Федоровна", "Юрьевна", "Валентиновна", "Викторовна", "Геннадьевна",
    "Леонидовна", "Олеговна", "Станиславовна"
};
extern const int num_middle_names_f = sizeof(middle_names_f) / sizeof(middle_names_f[0]);

//массивы для случайных имен, фамилий и отчеств (мужские)
extern const char* first_names_m[] = {
    "Александр", "Дмитрий", "Михаил", "Сергей", "Андрей", "Иван", "Владимир", "Николай", "Алексей", "Евгений",
    "Павел", "Константин", "Артем", "Игорь", "Виталий", "Олег", "Юрий", "Василий", "Геннадий", "Станислав"
};
extern const int num_first_names_m = sizeof(first_names_m) / sizeof(first_names_m[0]);

extern const char* last_names_m[] = {
    "Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов", "Васильев", "Попов", "Новиков", "Морозов", "Волков",
    "Алексеев", "Лебедев", "Семенов", "Егоров", "Павлов", "Козлов", "Степанов", "Николаев", "Орлов", "Андреев"
};
extern const int num_last_names_m = sizeof(last_names_m) / sizeof(last_names_m[0]);

extern const char* middle_names_m[] = {
    "Александрович", "Дмитриевич", "Михайлович", "Сергеевич", "Андреевич", "Иванович", "Владимирович", "Николаевич",
    "Алексеевич", "Евгеньевич", "Павлович", "Константинович", "Артемович", "Игоревич", "Витальевич", "Олегович",
    "Юрьевич", "Васильевич", "Геннадьевич", "Станиславович"
};
extern const int num_middle_names_m = sizeof(middle_names_m) / sizeof(middle_names_m[0]);

//массив для учебных предметов
extern const char* subjects[] = {
    "Высшая математика", "Физика", "Элективная физическая культура и спорт", 
    "Основы информационной безопасности", "История России", "Философия", 
    "Структуры данных", "Английский язык", "ВВПД",
    "Цифровой пракикум", "Цифровая грамотность", "Алгоритмизация и программирование",
    "Математический анализ", "Линейная алгебра и аналитическая геометрия",
    "Дискретная математика", "Теоритическая ммеханика", "Численные методы",
    "Базы данных", "Основы проектной деятельности", "Основы математической физики",
    "Основы функционального анализа", "Теория вероятностей", "Математическая статистика",
    "Методы оптимизиции", "Технология программирования", "Наука прораммирования",
    "Теория графов", "Теория автоматического управления", "Объектно ориентированное проргаммирование",
    "Ахрхитектура суперкомпьютеров", "Программирование микроконтроллеров", "Цифровая культура",
    "Математическая логика и теория автоматов"
};
extern const int num_subjects = sizeof(subjects) / sizeof(subjects[0]);

//количество часов
extern const char* subjects_hours[] = { 
    "12", "14", "24", "26", 
    "28", "36", "46", "72"
};
extern const int num_subjects_hours = sizeof(subjects_hours) / sizeof(subjects_hours[0]);

//номер кабинета
extern const char* subjects_room[] = {
    "270", "237", "110", "237", "235", "235", "175",
    "106", "186", "324", "106"
};
extern int num_subjects_room = sizeof(subjects_room) / sizeof(subjects_room[0]);

//массив для номера группы
extern const char* group[] = {
    "5151004/40001", "51510001/40001", "5151001/40002", "5151001/40003", "5151003/40001", "5151003/40002", "5151003/40003", "5151004/40002"
};
extern const int num_group = sizeof(group) / sizeof(group[0]);

extern const char* subject_format[] = {
    "Экзамен", "Зачет", "Курсовая"
};
