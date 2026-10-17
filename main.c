#include <stdio.h>
#include <string.h>
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

void set_item_names(char item_names[ARR_SIZE][MAX_NAME_LEN], const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("ВНИМАНИЕ! Файл '%s' не найден в корневой директории. Используются значения по умолчанию.\n", file_name);
        strcpy(item_names[0], "Пусто");
        strcpy(item_names[1], "Дерево");
        strcpy(item_names[2], "Камень");
        strcpy(item_names[3], "Семена_пшеницы");
        strcpy(item_names[4], "Семена_кукурузы");
        strcpy(item_names[5], "Глина");
        strcpy(item_names[6], "Уголь");
        strcpy(item_names[7], "Лопата_уровень_1");
        strcpy(item_names[8], "Грабли_уровень_1");
        strcpy(item_names[9], "Топор_уровень_1");
    }
    else
    {
        int id;
        char file_line[MAX_NAME_LEN + 1];
        while (fscanf(file, "%d %31s", &id, file_line) != EOF)
        {
            strncpy(item_names[id], file_line, MAX_NAME_LEN - 1);
            item_names[id][MAX_NAME_LEN - 1] = '\0';
        }
        fclose(file);
    }
}

void print_reference()
{
    printf("\nВам доступны следующие действия:\n");
    printf("[0] Выход\n");
    printf("[1] Посмотреть на часы\n");
    printf("[2] Промотать время (Поработать)\n");
    printf("[3] Посмотреть инвентарь\n");
    printf("[4] Положить предмет в слот\n");
    printf("[5] Выбросить предмет\n");
    printf("[6] Ревизия ресурсов\n\n");
}

int get_safe_int_input(const char *input_prompt, int min, int max)
{
    int input_val;
    printf("%s >>", input_prompt);
    while (scanf("%d", &input_val) != 1 || input_val > max || input_val < min)
    {
        printf("Ошибка! Допустимы целые числа от %d до %d\n%s >>", min, max, input_prompt);
        while (getchar() != '\n');
    }
    return input_val;
}

int main()
{
	int current_day = 1;
	int current_hour = 8;

	char item_names[MAX_ITEMS][MAX_NAME_LEN];
    int inventory[ARR_SIZE] = {0};

    set_item_names(item_names, "items.txt");
	fill_inventory(inventory);

	char player_name[32];
	
	printf("Введите ваше имя: >>");
	scanf("%31s", player_name);
	printf("%s, добро пожаловать в меню игры \"Весёлый фермер\"!\n", player_name);

    int choice;
    int work_hours;
	int index, item_id;
	int counter;
	while (1)
	{
        print_reference();
		choice = get_safe_int_input("Для выбора действия введите число от 0 до 6", 0, 6);
		switch (choice)
		{
			case 0:
				printf("Выход из игры...");
				return 0;
			case 1:
				if (current_hour <= 9)
				{
					printf("Текущее время: День %d, 0%d:00\n", current_day, current_hour);
				}
				else
					printf("Текущее время: День %d, %d:00\n", current_day, current_hour);
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
				counter = 0;
				printf("Предмет находится в следующих слотах: ");
				for (int i = 0; i < ARR_SIZE; i++)
				{
					if (inventory[i] == item_id)
					{
						counter++;
						printf("%d ", i);
					}
				}
				printf("\nОбщее количество включений предмета: %d\n", counter);
		}
	}

	return 0;
}
