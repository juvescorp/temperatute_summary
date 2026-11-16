#ifndef _TEMP_FUNCTIONS_H_
#define _TEMP_FUNCTIONS_H_

// Объявление структур
// структура, в которую записываются полученные из файла данные: 
// год, месяц, день, час, минута, температура
struct data {
    int year, month, day, hour, min, t;
};
// структура, хранящая среднюю, максимальную и минимальнуютемпературу за период (здесь - месяц и год, но может быть и другой период)
struct temperature {
    int sum; // сумма температур за период
    int count; // количество замеров за период
    float average; // средняя температура за период
    struct data max, min; // максимальная и минимальная температура за период с указанием конкретной даты и времени (год, месяц, день, час, минута) 
    int exists; // признак того, что в периоде были замеры температуры
};

// функция проверки ввода параметров
char* input_check(int arg_count,char *arguments[],int *month_numb);
// функция проверки количества вводимых парметров
int input_check_arg_count(int args_count, char* program_name);
// функция вывода справки
void print_help();
// функция вывода ошибочной строки и её номера
void print_error_string(char* s, int string_number);
// проверка количества значений в строке
int check_count_of_values(int count, char* s, int string_number);
// проверка года
int check_year(int year, char* s, int string_number);
// проверка месяца
int check_month(int month, char* s, int string_number);
// проверка дня в месяце
int check_day(int day, int month, int year, int* days_in_month, char* s, int string_number);
// проверка часа
int check_hour(int hour, char* s, int string_number);
// проверка минуты
int check_minute(int minute, char* s, int string_number);
// проверка температуры
int check_temperature(int temperature, char* s, int string_number);
// Получение минимума и максимума на первом замере в месяце
void get_month_min_max (int month_number, int current_temp, struct temperature * month_temp);
// Получение минимума и максимума на первом замере в году
void get_year_min_max (int current_temp, struct temperature * year_temp);
// Получение текущего минимума и максимума в месяце
void set_month_min_max (int current_temp, int current_month, int current_day, int current_hour, int current_minute, struct temperature * month_temp);
// Получение текущего минимума и максимума в году
void set_year_min_max (int current_temp, int current_month, int current_day, int current_hour, int current_minute, struct temperature * year_temp);
// вычисление и вывод средней, вывод максимальной и минимальной температуры в указанном месяце
void calc_and_print_month_average (struct temperature* month_temp, int month_numb);
// Получение средней температуры для всех месяцев
void get_average_for_all_months(struct temperature* month_temp);
// Получение средней температуры для года
void get_average_for_year(struct temperature* month_year);

// Вывод средней, минимальной и максимальной температуры за все месяцы 
void print_all_months_average(struct temperature* month_temp);
// Вывод средей, минимальной и максимальной температуры за год
void print_year_max_min_avg (struct temperature* temp_year, int month_numb);

#endif
