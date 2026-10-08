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

int main()
{
	int current_day = 1;
	int current_hour = 8;
	
	int inventory[ARR_SIZE] = {0};

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
		printf("Для выбора действия введите цифру от 0 до 6 >>");
		while (scanf("%d", &choice) != 1 || choice < 0 || choice > 6)
		{
			printf("Ошибка! Введите цифру от 0 до 6 >>");
			while (getchar() != '\n');
		}

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
				printf("Введите количество часов, которые хотите потратить на работу >>");

				while (scanf("%d", &work_hours) != 1)
				{
					printf("Ошибка! Количество часов должно быть целым числом\n");
					printf("Введите количество часов, которые хотите потратить на работу >>");
					while (getchar() != '\n');
				}

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
				/*for (int i = 0; i < ARR_SIZE; i++)
				{
					switch (inventory[i])
					{
						case WOOD:
							printf("Слот %d: [1] (Дерево)\n", i);
							break;
						case STONE:
							printf("Слот %d: [2] (Камень)\n", i);
							break;
						case SEEDS:
							printf("Слот %d: [3] (Семена)\n", i);
							break;
						case GRASS:
							printf("Слот %d: [4] (Трава)\n", i);
							break;
						case CLAY:
							printf("Слот %d: [5] (Глина)\n", i);
							break;
						case LEAF:
							printf("Слот %d: [6] (Листья)\n", i);
							break;
						case CARBON:
							printf("Слот %d: [7] (Уголь)\n", i);
							break;
						case IRON:
							printf("Слот %d: [1] (Железо)\n", i);
							break;
						case GOLD:
							printf("Слот %d: [1] (Золото)\n", i);
							break;
						default:
							printf("Слот %d: [0]\n", i);
							break;
					}
				}*/
				break;
			case 4:
				printf("Введите индекс слота от 0 до 9 >>");

				while (scanf("%d", &index) < 0 || index > ARR_SIZE - 1)
				{
					printf("Ошибка! Индекс не может быть меньше 0 и больше %d\n", ARR_SIZE - 1);
					printf("Введите индекс слота от 0 до 9 >>");
					while (getchar() != '\n');
				}

				printf("Введите ID предмета от 0 до 9 >>");

				while (scanf("%d", &item_id) < 0 || item_id > 9)
				{
					printf("Ошибка! ID предмета не может быть меньше 0 и больше %d\n", ARR_SIZE - 1);
					printf("Введите ID предмета от 0 до 9 >>");
					while (getchar() != '\n');
				}

				inventory[index] = item_id;
				printf("Инвентарь успешно изменён!\n");
				break;
			case 5:
				printf("Введите индекс слота от 0 до 9 >>");

				while (scanf("%d", &index) < 0 || index > ARR_SIZE - 1)
				{
					printf("Ошибка! Индекс не может быть меньше 0 и больше %d\n", ARR_SIZE - 1);
					printf("Введите индекс слота от 0 до 9 >>");
					while (getchar() != '\n');
				}

				inventory[index] = EMPTY;
				printf("Предмет удалён из инвентаря.\n");
				break;
			case 6:
				printf("Введите ID предмета от 0 до 9 >>");

				while (scanf("%d", &item_id) < 0 || item_id > 9)
				{
					printf("Ошибка! ID предмета не может быть меньше 0 и больше %d\n", ARR_SIZE - 1);
					printf("Введите ID предмета от 0 до 9 >>");
					while (getchar() != '\n');
				}

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
