#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARR_SIZE 10
#define EMPTY 0
#define WOOD 1
#define STONE 2
#define WHEAT_SEEDS 3
#define CORN_SEEDS 4
#define CLAY 5
#define CARBON 6
#define SHOVEL_LV_1 7
#define RAKE_LV_1 8
#define AXE_LV_1 9
#define DAY_HOURS 24
#define MAX_ITEMS 10
#define MAX_NAME_LEN 31
#define MAX_PLAYER_NAME_LEN 32


void fill_inventory(int inventory[ARR_SIZE])
{
    inventory[0] = RAKE_LV_1;
    inventory[1] = SHOVEL_LV_1;
    inventory[2] = AXE_LV_1;
    inventory[3] = WHEAT_SEEDS;
    inventory[4] = CLAY;
    inventory[5] = CARBON;
    inventory[6] = EMPTY;
    inventory[7] = CARBON;
    inventory[8] = WOOD;
    inventory[9] = CARBON;
}

void set_default_item_names(char item_names[ARR_SIZE][MAX_NAME_LEN])
{
    const char *default_names[ARR_SIZE] = {
        "Пусто",
        "Дерево",
        "Камень",
        "Семена_пшеницы",
        "Семена_кукурузы",
        "Глина",
        "Уголь",
        "Лопата_уровень_1",
        "Грабли_уровень_1",
        "Топор_уровень_1"
    };

    for (int i = 0; i < ARR_SIZE; i++)
    {
        strncpy(item_names[i], default_names[i], MAX_NAME_LEN - 1);
        item_names[i][MAX_NAME_LEN - 1] = '\0';
    }
}

void set_item_names(char item_names[ARR_SIZE][MAX_NAME_LEN], const char *file_name)
{
    set_default_item_names(item_names);

    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("ВНИМАНИЕ! Файл '%s' не найден в корневой директории. Используются значения по умолчанию.\n", file_name);
        return;
    }

    int id;
    char file_line[MAX_NAME_LEN + 1];
    while (fgets(file_line, sizeof(file_line), file) != NULL)
    {
        char name[MAX_NAME_LEN + 1];
        if (sscanf(file_line, "%d %31s", &id, name) != 2)
        {
            continue;
        }
        if (id < 0 || id >= ARR_SIZE)
        {
            printf("ВНИМАНИЕ! В файле '%s' указан недопустимый ID %d. Строка пропущена.\n", file_name, id);
            continue;
        }
        strncpy(item_names[id], name, MAX_NAME_LEN - 1);
        item_names[id][MAX_NAME_LEN - 1] = '\0';
    }
    fclose(file);
}

void print_reference(const char *player_name)
{
    printf("\nВесёлый фермер, %s! Вам доступны следующие действия:\n", player_name);
    printf("[0] Выход\n");
    printf("[1] Посмотреть на часы\n");
    printf("[2] Промотать время (Поработать)\n");
    printf("[3] Посмотреть инвентарь\n");
    printf("[4] Положить предмет в слот\n");
    printf("[5] Выбросить предмет\n");
    printf("[6] Ревизия ресурсов\n");
    printf("[7] Поиск предмета в рюкзаке по названию\n");
    printf("[8] Записать состояние в дневник фермера\n");
    printf("[9] Поисковик по «Энциклопедии фермера» \n");
    printf("\n");
}

int get_safe_int_input(const char *input_prompt, int min, int max)
{
    int input_val;
    int ch;
    printf("%s >>", input_prompt);
    while (scanf("%d", &input_val) != 1 || input_val > max || input_val < min)
    {
        if (feof(stdin))
        {
            printf("\nВвод завершён. Выход из игры.\n");
            exit(EXIT_SUCCESS);
        }
        printf("Ошибка! Допустимы целые числа от %d до %d\n%s >>", min, max, input_prompt);
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }
    return input_val;
}

void search_by_item_id(int item_id, int inventory[ARR_SIZE])
{
    int counter = 0;
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (inventory[i] == item_id)
        {
            counter++;
            printf("%d ", i);
        }
    }
    if (counter)
    {
        printf("\nОбщее количество включений предмета: %d\n", counter);
    }
    else
    {
        printf("-\n");
    }
}

void search_by_item_name(const char *search_query, char item_names[ARR_SIZE][MAX_NAME_LEN], int inventory[ARR_SIZE])
{
    int item_id = -1;
    for (int i = 0; i < ARR_SIZE; i++)
    {
        if (strcmp(item_names[i], search_query) == 0)
        {
            item_id = i;
            break;
        }
    }
    if (item_id == -1)
    {
        printf("Предмет с названием '%s' не найден в каталоге предметов.\n", search_query);
    }
    else
    {
        printf("Предмет [%d] '%s' находится в следующих слотах: ", item_id, item_names[item_id]);
        search_by_item_id(item_id, inventory);
    }
}

void write_to_diary(const char *player_name, int current_day, int current_hour, char item_names[ARR_SIZE][MAX_NAME_LEN],
    int inventory[ARR_SIZE], const char *file_name)
{
    FILE *file = fopen(file_name, "a");

    if (file == NULL)
    {
        printf("Ошибка при записи дневника в файл %s\n", file_name);
        return;
    }

    printf("\n--- Дневник фермера ---\n");
    printf("Имя фермера: %s\n", player_name);
    fprintf(file, "Имя фермера: %s\n", player_name);
    printf("Текущее время: День %d, %02d:00\n", current_day, current_hour);
    fprintf(file, "Текущее время: День %d, %02d:00\n", current_day, current_hour);
    printf("Инвентарь:\n");
    fprintf(file, "Инвентарь:\n");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("Слот %d: [%d] - %s\n", i, inventory[i], item_names[inventory[i]]);
        fprintf(file, "Слот %d: [%d] - %s\n", i, inventory[i], item_names[inventory[i]]);
    }
    fprintf(file, "\n");

    fclose(file);
    printf("Дневник успешно записан в файл %s\n", file_name);
}

/* Приводит к нижнему регистру ASCII и русские буквы в UTF-8.
 * Длина строки в байтах при этом не меняется. */
void utf8_to_lower(char *text)
{
    unsigned char *p = (unsigned char *)text;

    while (*p != '\0')
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            *p = (unsigned char)(*p - 'A' + 'a');
            p++;
        }
        else if (p[0] == 0xD0 && p[1] == 0x81) /* Ё -> ё */
        {
            p[0] = 0xD1;
            p[1] = 0x91;
            p += 2;
        }
        else if (p[0] == 0xD0 && p[1] >= 0x90 && p[1] <= 0x9F) /* А-П -> а-п */
        {
            p[1] = (unsigned char)(p[1] + 0x20);
            p += 2;
        }
        else if (p[0] == 0xD0 && p[1] >= 0xA0 && p[1] <= 0xAF) /* Р-Я -> р-я */
        {
            p[0] = 0xD1;
            p[1] = (unsigned char)(p[1] - 0x20);
            p += 2;
        }
        else if ((p[0] & 0xE0) == 0xC0 && p[1] != '\0')
        {
            p += 2;
        }
        else if ((p[0] & 0xF0) == 0xE0 && p[1] != '\0' && p[2] != '\0')
        {
            p += 3;
        }
        else if ((p[0] & 0xF8) == 0xF0 && p[1] != '\0' && p[2] != '\0' && p[3] != '\0')
        {
            p += 4;
        }
        else
        {
            p++;
        }
    }
}

void search_in_wiki(const char *search_query, const char *input_file_name, const char *output_file_name)
{
    if (search_query[0] == '\0')
    {
        printf("Поисковый запрос пуст.\n");
        return;
    }

    FILE *input_file = fopen(input_file_name, "r");

    if (input_file == NULL)
    {
        printf("Файл %s не найден в корневом каталоге.\n", input_file_name);
        return;
    }

    FILE *output_file = fopen(output_file_name, "w");

    if (output_file == NULL)
    {
        printf("Возникла ошибка при записи в файл %s\n", output_file_name);
        fclose(input_file);
        return;
    }

    char file_line[256];
    char lower_query[256];
    strncpy(lower_query, search_query, sizeof(lower_query) - 1);
    lower_query[sizeof(lower_query) - 1] = '\0';
    utf8_to_lower(lower_query);
    size_t query_len = strlen(lower_query);

    int found_count = 0;

    while (fgets(file_line, sizeof(file_line), input_file) != NULL)
    {
        file_line[strcspn(file_line, "\r\n")] = '\0';

        char lower_line[256];
        strncpy(lower_line, file_line, sizeof(lower_line) - 1);
        lower_line[sizeof(lower_line) - 1] = '\0';
        utf8_to_lower(lower_line);

        char result[1024];
        size_t result_len = 0;
        size_t line_len = strlen(file_line);
        size_t pos = 0;
        int matches_in_line = 0;

        while (pos < line_len && result_len + 3 < sizeof(result))
        {
            if (pos + query_len <= line_len &&
                strncmp(lower_line + pos, lower_query, query_len) == 0)
            {
                result[result_len++] = '[';
                memcpy(result + result_len, file_line + pos, query_len);
                result_len += query_len;
                result[result_len++] = ']';
                pos += query_len;
                matches_in_line++;
            }
            else
            {
                result[result_len++] = file_line[pos++];
            }
        }
        result[result_len] = '\0';

        if (matches_in_line > 0)
        {
            found_count++;
            printf("%d. %s\n", found_count, result);
            fprintf(output_file, "%d. %s\n", found_count, result);
        }
    }

    if (found_count == 0)
    {
        printf("Совпадений по запросу '%s' не найдено.\n", search_query);
    }
    else
    {
        printf("Найдено статей: %d. Результат сохранён в файл %s\n", found_count, output_file_name);
    }

    fclose(output_file);
    fclose(input_file);
}

int main(void)
{
    int current_day = 1;
    int current_hour = 8;

    char item_names[MAX_ITEMS][MAX_NAME_LEN];
    int inventory[ARR_SIZE] = {0};

    set_item_names(item_names, "items.txt");
    fill_inventory(inventory);

    char player_name[MAX_PLAYER_NAME_LEN + 1];

    printf("Введите ваше имя >>");
    if (scanf("%32s", player_name) != 1)
    {
        strcpy(player_name, "Фермер");
        printf("\nИмя не введено. Используется имя '%s'.\n", player_name);
    }
    printf("%s, добро пожаловать в меню игры 'Весёлый фермер'!\n", player_name);

    int choice;
    int work_hours;
    int index, item_id;
    while (1)
    {
        print_reference(player_name);
        choice = get_safe_int_input("Для выбора действия введите число от 0 до 9", 0, 9);
        switch (choice)
        {
            case 0:
                printf("Выход из игры...");
                return 0;
            case 1:
                printf("Текущее время: День %d, %02d:00\n", current_day, current_hour);
                break;
            case 2:
                printf("Вы можете работать от 1 до 20 часов.\n");
                work_hours = get_safe_int_input("Введите количество часов, которые хотите потратить на работу", 1, 20);
                current_hour += work_hours;
                if (current_hour >= DAY_HOURS)
                {
                    int full_days_count = current_hour / DAY_HOURS;
                    current_day += full_days_count;
                    current_hour -= full_days_count * DAY_HOURS;
                }
                printf("Время успешно обновлено!\n");
                break;
            case 3:
                for (int i = 0; i < ARR_SIZE; i++)
                {
                    printf("Слот %d: [%d] - %s\n", i, inventory[i], item_names[inventory[i]]);
                }
                break;
            case 4:
                index = get_safe_int_input("Введите индекс слота для обновления", 0, ARR_SIZE - 1);
                item_id = get_safe_int_input("Введите ID добавляемого предмета", 0, MAX_ITEMS - 1);
                inventory[index] = item_id;
                printf("Инвентарь успешно изменён!\n");
                break;
            case 5:
                index = get_safe_int_input("Введите индекс слота для удаления", 0, ARR_SIZE - 1);
                inventory[index] = EMPTY;
                printf("Предмет удалён из инвентаря. В слот %d записано значение '%s'\n", index, item_names[0]);
                break;
            case 6:
                item_id = get_safe_int_input("Введите ID предмета для поиска", 0, MAX_ITEMS - 1);
                printf("Предмет находится в следующих слотах: ");
                search_by_item_id(item_id, inventory);
                break;
            case 7:
            {
                char search_query[MAX_NAME_LEN];
                printf("Введите поисковый запрос >>");
                if (scanf("%30s", search_query) != 1)
                {
                    printf("Некорректный ввод.\n");
                    break;
                }
                search_by_item_name(search_query, item_names, inventory);
                break;
            }
            case 8:
                write_to_diary(player_name, current_day, current_hour, item_names, inventory, "diary.txt");
                break;
            case 9:
            {
                char wiki_search_query[256];
                printf("Введите поисковый запрос >>");
                if (scanf("%255s", wiki_search_query) != 1)
                {
                    printf("Некорректный ввод.\n");
                    break;
                }
                search_in_wiki(wiki_search_query, "input.txt", "output.txt");
                break;
            }
        }
    }

    return 0;
}
