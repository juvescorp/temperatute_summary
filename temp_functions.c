#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_functions.h"

// Вывод справки
void print_help(){
	  // Если параметр -h - выводим справку
       printf("Справка по команде:\n");
       printf("-h Описание функционала приложения. Список ключей, которые обрабатывает данное приложение и их назначение.\n");
       printf("-f <filename.csv> входной файл csv для обработки.\n");
       printf("-m <номер месяца> если задан данный ключ, то выводится только статистика за указанный месяц.\n");
}

// Проверка ввода. 
// arg_count - количество аргументов командной строки
// *arguments[] - сами аргументы командной строки
// *month_numb - номер месяца (непонятно, зачем он тут, можно наверно локальной переменной обойтись)
char* input_check(int arg_count,char *arguments[],int *month_numb){
  char* filename=""; // имя файла
  FILE *filetest; // переменная для проверки на существование файла
  int file_exists=0; // флаг, сообщающий, существует ли указанный файл или нет
  int month_numb_entered_correct=0; // флаг, сообщающий, введён ли месяц верно или нет
  
  *month_numb=0; 
  if(strcmp ( arguments[1], "-h" ) == 0) {
    // Если параметр -h - выводим справку
    print_help();
    exit(0);
  }
    
  for (int i=1; i < arg_count; i++){
   // обработка аргумента командной строки для имени файла (-f)
    // Сделать проверку имени файла отдельной функцией int input_check_filename(int arg_count,char *arguments[]); 
    // Также может пригодиться проверка: имя файла после -f должно заканчиваться на .csv. Если нет - ошибка.

    if (strcmp (arguments[i], "-f") == 0) {
	 // Проверка, задано ли имя файла после -f
     if (arguments[i+1]){
      filename=arguments[i+1];
      // Проверка, существует ли файл
      if (filetest = fopen(filename, "r")){
       printf("Имя файла %s\n",filename);
       fclose(filetest);
       file_exists=1;
      }   
      // Если такого файла нет - выводим ошибку и выходим
      else {
       printf("Ошибка. Файл не существует: %s\n",filename);
       file_exists=0;
       exit(1);
      }
      continue; // Переходим к следующему аргументу командной строки
     }
     // Если имя файла пустое - выводим ошибку и выходим
     else {
      printf("Ошибка: задано пустое имя файла\n");
      file_exists=0;
      exit(1);
     }
    }
    // Сделать проверку месяца отдельной функцией // int input_check_month(int arg_count,char *arguments[]);
   // обработка аргумента командной строки для месяца (-m)
    if (strcmp (arguments[i], "-m") == 0 ){
     if (arguments[i+1]){
	  // Переводим номер месяца из строки в число (неидеально, ниже поясню, почему, но пусть будет так)
      *month_numb=atoi(arguments[i+1]);
      // Здесь строка "11f" будет преобразована в число 11, "1f1 в 1, 
      // а при начале на любой символ, кроме цифры, строка будет преобразована в 0. Например, "f" в 0
      
      //   Проверка на ввод: введено число от 1 до 12-ти или что-то другое
      if ((*month_numb>0)&&(*month_numb<=12)){
       printf("Месяц %d\n",*month_numb);
       month_numb_entered_correct=1;
      }
      // Если не число от 1 до 12 - выводим ошибку и выходим
      else {
       printf("Ошибка: введён неверный номер месяца. После -m нужно вводить число от 1 до 12.\n");
       month_numb_entered_correct=0;
       exit(1);
      }
     }
     // Если месяц не задан - выводим ошибку и выходим
     else {
      printf("Ошибка: месяц после ключа -m не задан\n");
      month_numb_entered_correct=0;
      exit(1);
     }
     continue; // Переходим к следующему аргументу командной строки
    }
   }
  // Если файл существует - возвращаем его имя. Если нет - выводим ошибку и выходим
  if (file_exists==1)
   return filename;
  else
   {
	printf("Не существует или не задан файл.\n");
    exit(1);
   }
}

// Проверка количества аргументов
int input_check_arg_count(int args_count, char* program_name){
// Если не ввели параметры для программы - выводим справку
   if ( args_count==1){
	  printf("Вы забыли ввести аргументы.\n");
      print_help();
      exit(1);
   } 
// Если ввели слишком много параметров - выводим ошибку и ключ для справки
   if ( args_count > 5 ){
      printf("Слишком много аргументов\n");
      printf("Справка: %s -h\n",program_name);
      exit(1);
   }
}

// Вывод на экрана номера ошибочной строки
void print_error_string(char* s, int string_number){
	char error[100] = {0}; // ошибкочная строка в файле
    sscanf(s,"%[^\n]",error); // [^\n] означает все символы в строке, кроме (^) \n (перенос строки). То есть все в переменную error запишется вся строка за исключением символа перехода на следующую строку
    printf("Ошибочная строка: %s\n;номер строки %d\n",error, string_number); // Выводим строку с ошибкой и её номер
    
    // Можно ещё выводить причину ошибки: 
    // пустое поле, неправильный день в месяце, неправильный месяц, неправильный год, неправильная температура
    // Здесь в программе, возможно, не все случаи обработаны
}

// Проверка количества элементов строки в файле: если чисел в строке не шесть, то выводим ошибку и продолжаем цикл
int check_count_of_values(int count, char* s, int string_number){
	if(count != 6){
            print_error_string(s, string_number);
            return 0;
    }
    else {
		return 1;
		}    
}

// Проверка года: если год не между 0 и 9999, то выводим ошибку и продолжаем цикл
int check_year(int year, char* s, int string_number){
	if ((year<0) || (year>9999)){
            print_error_string(s, string_number);
            return 0;
    }
    else {
			return 1; 
	}
}

// Проверка месяца: если месяц не между 1 и 12, то выводим ошибку и продолжаем цикл
int check_month(int month, char* s, int string_number){
	if ((month<1) || (month>12)){
            print_error_string(s, string_number);
            return 0;	
	}
	    else {
			return 1; 
	}
}

// Проверка дня и вывод ошибки, если такого дня не существует в году или месяце 
        // 1) Если день не между 1 и 31 - ошибка
        // 2) Проверка номера дня по месяцам (в каких-то 30, в каких-то 31)
        // 3) Проверка дня в феврале (високосный - 29 и невисокосный год - 28)
int check_day(int day, int month, int year, int* days_in_month, char* s, int string_number){

	if ((month!=2)&&((day>days_in_month[month-1])||(day<1)))
        {
            char error[100] = {0}; // ошибкочная строка в файле
            sscanf(s,"%[^\n]",error); // [^\n] означает все символы в строке, кроме (^) \n (перенос строки). То есть все в переменную error запишется вся строка за исключением символа перехода на следующую строку
            printf("Ошибочная строка: %s\n;номер строки %d\n",error, string_number); // Выводим строку с ошибкой и её номер
            // добавить возврат значения в функцию (означает ошибку)
			return 0;
        }
        // Проверка дня в феврале (високосный и невисокосный год)
    if (month==2){
     if ((year%4)!=0)
      if ((day>days_in_month[month-1])||(day<1)){
       char error[100] = {0}; // ошибкочная строка в файле
       sscanf(s,"%[^\n]",error); // [^\n] означает все символы в строке, кроме (^) \n (перенос строки). То есть все в переменную error запишется вся строка за исключением символа перехода на следующую строку
       printf("Ошибочная строка: %s\n;номер строки %d\n",error, string_number); // Выводим строку с ошибкой и её номер
       return 0;
      }
      if (year%4==0)
	   if ((day>29)||(day<1)){
		char error[100] = {0}; // ошибкочная строка в файле
        sscanf(s,"%[^\n]",error); // [^\n] означает все символы в строке, кроме (^) \n (перенос строки). То есть все в переменную error запишется вся строка за исключением символа перехода на следующую строку 
        printf("Ошибочная строка: %s\n;номер строки %d\n",error, string_number); // Выводим строку с ошибкой и её номер
        return 0;
		}
     }
   return 1;
}

// Проверка часа: если не от 0 до 23, то выводим ошибку
int check_hour(int hour, char* s, int string_number){
	if ((hour<0) || (hour>23))
        {
            char error[100] = {0}; // ошибкочная строка в файле
            sscanf(s,"%[^\n]",error); // [^\n] означает все символы в строке, кроме (^) \n (перенос строки). То есть все в переменную error запишется вся строка за исключением символа перехода на следующую строку
            printf("Ошибочная строка: %s\n;номер строки %d\n",error, string_number); // Выводим строку с ошибкой и её номер
            return 0;
        }
    else {
     return 1; 
    }
}

// Проверка минут: если не от 0 до 59, то выводим ошибку
int check_minute(int minute, char* s, int string_number){
	  if ((minute<0) || (minute>59))
        {
            char error[100] = {0}; // ошибкочная строка в файле
            sscanf(s,"%[^\n]",error); // [^\n] означает все символы в строке, кроме (^) \n (перенос строки). То есть все в переменную error запишется вся строка за исключением символа перехода на следующую строку
            printf("Ошибочная строка: %s\n;номер строки %d\n",error, string_number); // Выводим строку с ошибкой и её номер
            return 0;
        }
      else {
	   return 1;
	  }
}

// Проверка температуры: если не от -99 до 99, то выводим ошибку
int check_temperature(int temperature, char* s, int string_number){
       if ((temperature<-99) || (temperature>99))
        {
            char error[100] = {0}; // ошибкочная строка в файле
            sscanf(s,"%[^\n]",error); // [^\n] означает все символы в строке, кроме (^) \n (перенос строки). То есть все в переменную error запишется вся строка за исключением символа перехода на следующую строку
            printf("Ошибочная строка: %s\n;номер строки %d\n",error, string_number); // Выводим строку с ошибкой и её номер
            return 0;
        } 
       else {
		   return 1;
	   }
}
// Пустая функция. Удалить отсюда и из .h
int input_from_file(){
}

// Первое значение из замеров - это и максимум и минимум в месяце
void get_month_min_max (int month_number, int current_temp, struct temperature * month_temp){
 			if (!month_temp[month_number-1].exists){
				month_temp[month_number-1].exists=1;
				month_temp[month_number-1].max.t=current_temp;
				month_temp[month_number-1].min.t=current_temp;
			}
}

// Первое значение из замеров - это и максимум и минимум в году
void get_year_min_max (int current_temp, struct temperature * year_temp){
			if (!year_temp->exists){
				year_temp->exists=1;
				year_temp->max.t=current_temp;
				year_temp->min.t=current_temp;
			}
}

// Получаем текущие максимум и минимум за месяц
void set_month_min_max (int current_temp, int current_month, int current_day, int current_hour, int current_minute, struct temperature * month_temp){
	        // Максимум за месяц
			if (current_temp>month_temp[current_month-1].max.t){
				month_temp[current_month-1].max.t = current_temp;
				month_temp[current_month-1].max.day = current_day;
				month_temp[current_month-1].max.month = current_month;
				month_temp[current_month-1].max.hour = current_hour;
				month_temp[current_month-1].max.min = current_minute;
			
			}
			// Минимум за месяц        
			if (current_temp<=month_temp[current_month-1].min.t){
				month_temp[current_month-1].min.t = current_temp;
				month_temp[current_month-1].min.day = current_day;
				month_temp[current_month-1].min.month = current_month;
				month_temp[current_month-1].min.hour = current_hour;
				month_temp[current_month-1].min.min = current_minute;
			}
}

// Получение текущего минимума и максимума в году
void set_year_min_max (int current_temp, int current_month, int current_day, int current_hour, int current_minute, struct temperature * year_temp){
	
	        // Максимум за год
			if (current_temp>year_temp->max.t){
				year_temp->max.t = current_temp;
				year_temp->max.day = current_day;
				year_temp->max.month = current_month;
				year_temp->max.hour = current_hour;
				year_temp->max.min = current_minute;
			}
			// Минимум за год
			if (current_temp<=year_temp->min.t){
				year_temp->min.t = current_temp;  
				year_temp->min.day = current_day;
				year_temp->min.month = current_month;
				year_temp->min.hour = current_hour;
				year_temp->min.min = current_minute;
			}

}

// Вычисление и вывод средней, вывод максимальной и минимальной температуры за указанный месяц
void calc_and_print_month_average (struct temperature* month_temp, int month_numb){
    // Если указан конкретный месяц от 1 до 12, то нужно посчитать и вывести данные только для него
    if ((month_numb>0)&&(month_numb<=12)){
		if (month_temp[month_numb-1].count!=0){
			month_temp[month_numb-1].average=month_temp[month_numb-1].sum/month_temp[month_numb-1].count;
			printf("Месяц %d, средняя температура = %f; число замеров = %d\n",month_numb,month_temp[month_numb-1].average, month_temp[month_numb-1].count);
		    printf("Месяц %d, максимальная температура = %d; число замеров = %d\n",month_numb,month_temp[month_numb-1].max.t, month_temp[month_numb-1].count);
		    printf("Месяц %d, минимальная температура = %d; число замеров = %d\n",month_numb,month_temp[month_numb-1].min.t, month_temp[month_numb-1].count);
		}
		else
		    printf("Замеров за указанный месяц не было\n");
    }
	
}

// Получение средней температуры для всех месяцев
void get_average_for_all_months(struct temperature* month_temp){
     for (int i=0;i<=11;i++)
		if (month_temp[i].count!=0)
			month_temp[i].average=month_temp[i].sum/month_temp[i].count;
}

// Получение средней температуры за год
void get_average_for_year(struct temperature* month_year){
    if (month_year->count!=0)
     //year.average=y
		month_year->average=month_year->sum/month_year->count;
}

// Вывод средней, минимальной и максимальной температуры за все месяцы
void print_all_months_average(struct temperature* month_temp){
     for (int i=0;i<=11;i++)
		if (month_temp[i].exists){
    //  строка диагностическая/отладочная. Выводит сумму температур в месяце и количество замеров. Поэтому закомментировал
    //			printf("Month %d sum = %d count = %d\n",i+1,month[i].sum, month[i].count);
			printf("Месяц %d, средняя температура = %f; число замеров = %d\n",i+1,month_temp[i].average, month_temp[i].count);
			printf("Месяц %d, максимальная температура = %d; число замеров = %d\n",i+1,month_temp[i].max.t, month_temp[i].count);
			printf("Месяц %d, минимальная температура = %d; число замеров = %d\n",i+1,month_temp[i].min.t, month_temp[i].count);
		}	 
}

// Вывод средей, минимальной и максимальной температуры за год
void print_year_max_min_avg (struct temperature* temp_year, int month_numb){
    if ((temp_year->exists)&&(month_numb==0)){
	//  строка диагностическая/отладочная. Выводит сумму температур в году и количество замеров. Поэтому закомментировал	
	//	printf("Year sum = %d count = %d\n",year.sum, year.count);
		printf("Средняя температура за год = %f; число замеров = %d\n",temp_year->average, temp_year->count);
		printf("Максимальная температура за год = %d; число замеров = %d\n",temp_year->max.t, temp_year->count);
		printf("Минимальная температура за год = %d; число замеров = %d\n",temp_year->min.t, temp_year->count);
	}
}
