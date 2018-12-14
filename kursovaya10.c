/* Пример файла "AviaCassa.txt":
|.Номер.рейса.|......Город.направления......|..Цена(В.рублях)..|Время.вылета-прилёта|Ожидание(пересадки)|
|..........142|.......................Москва|..............1023|.........17:01-15:20|.................30|
|.........4738|...................Красноярск|.............10740|.......5:04-10:51 51|................204|
|........83574|.......................Москва|..............1532|.........10:41-12:32|..................0|
|.........2834|......................Иркутск|.............15234|.........15:41-22:01|.................41|
|.........2834|..............Нижний Новгород|.............15234|.........15:41-22:01|.................41|
|.........2833|.......................Москва|.............15234|.........15:41-22:01|.................41|
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAXLINE 500

typedef struct Node
{
	//Data
	int n_flight;//номер рейса!!!(Номер рейса свой для каждого рейса)!!!
	char to[50];//город, в который направляется рейс
	int price;//цена (в рублях)
	char time_t_l[15];//время вылета-прилёта
	int time_wait;//премя ожидания при пересадке(в минутах)

	//Pointer to next Node
	struct Node *ptr_next;

} Node;

static Node *head_ptr;//указатель на первый элемент списка

/*функция для инициализации полей одного узла, используя строку(строка содержит все поля одного узла,
поля в строке разделены меду собой '.'и'|')*/
void give_Data(char buf[], Node *pNode)
{
	int i;
	char line[50];
	char *ptr_line = line, *ptr_buf = buf;

	//инициализация n_flight
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;

	while (*ptr_buf != '|')
	{
		*ptr_line = *ptr_buf;
		ptr_line++;
		ptr_buf++;
	}
	*ptr_line = '\0';
	pNode->n_flight = atoi(line);
	ptr_line = line;

	//инициализация to[]
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;

	i = 0;
	while (*ptr_buf != '|')
	{
		pNode->to[i] = *ptr_buf;
		ptr_buf++;
		i++;
	}
	pNode->to[i] = '\0';

	//инициализация price
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;

	while (*ptr_buf != '|')
	{
		*ptr_line = *ptr_buf;
		ptr_line++;
		ptr_buf++;
	}
	*ptr_line = '\0';
	pNode->price = atoi(line);
	ptr_line = line;

	//инициализация time_t_l
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;

	i = 0;
	while (*ptr_buf != '|')
	{
		pNode->time_t_l[i] = *ptr_buf;
		ptr_buf++;
		i++;
	}
	pNode->time_t_l[i] = '\0';


	//инициализация time_wait
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;

	while (*ptr_buf != '|')
	{
		*ptr_line = *ptr_buf;
		ptr_line++;
		ptr_buf++;
	}
	*ptr_line = '\0';
	pNode->time_wait = atoi(line);

}

//функция для получения нового узла
Node * give_next_Node(Node *pNode)//аргумент-указатель на данный узел. Выделяет память,инициализирует ptr_next для следующего узла и возвращает указатель на следующий узел
{

	Node *Nnode;//указатель на новый узел
	Nnode = (Node *)malloc(sizeof(Node));//выделение памяти для нового узла
	pNode->ptr_next = Nnode;
	Nnode->ptr_next = NULL;//инициализакия следующего указаделя нового узла
	return Nnode;
}

//функция для удаления узла
void delete_node(Node *pNode)
{
	Node *nNode;
	Node *prevNode;

	//Если удаляемый узел в начале вписка
	if (pNode == head_ptr)
	{
		head_ptr = pNode->ptr_next;
		free(pNode);
	}
	else
	{//если удаляемый узел в конце списка
		if (pNode->ptr_next == NULL)
		{
			nNode = head_ptr;
			prevNode = nNode;
			while (nNode->ptr_next != NULL)
			{
				prevNode = nNode;
				nNode = nNode->ptr_next;
			}
			free(nNode);
			prevNode->ptr_next = NULL;
		}
		else//если удаляемый узел не является началом или концом списка
		{
			nNode = head_ptr;
			prevNode = nNode;
			nNode = nNode->ptr_next;
			while (prevNode->ptr_next != pNode)
			{
				prevNode = nNode;
				nNode = nNode->ptr_next;
			}

			prevNode->ptr_next = nNode->ptr_next;
			free(nNode);
		}
	}
}

//вывод на экран всех рейсов
void print_table(char *line_table)
{
	printf("%s", line_table);

	Node *nNode;
	nNode = head_ptr;
	int len, ry;

	while (nNode != NULL)
	{
		//
		printf("|");
		len = 0;
		ry = nNode->n_flight;
		do
		{
			len++;
			ry /= 10;
		} while (ry != 0);
		for (ry = 13 - len; ry != 0; ry--)
			printf(".");

		printf("%d", nNode->n_flight);
		printf("|");
		//
		len = strlen(nNode->to);
		for (ry = 29 - len; ry != 0; ry--)
			printf(".");
		printf("%s", nNode->to);
		printf("|");
		//
		len = 0;
		ry = nNode->price;
		do
		{
			len++;
			ry /= 10;
		} while (ry != 0);
		for (ry = 18 - len; ry != 0; ry--)
			printf(".");

		printf("%d", nNode->price);
		printf("|");
		//
		len = strlen(nNode->time_t_l);
		for (ry = 20 - len; ry != 0; ry--)
			printf(".");
		printf("%s", nNode->time_t_l);
		printf("|");
		//
		len = 0;
		ry = nNode->time_wait;
		do
		{
			len++;
			ry /= 10;
		} while (ry != 0);
		for (ry = 19 - len; ry != 0; ry--)
			printf(".");

		printf("%d", nNode->time_wait);
		printf("|");
		printf("\n");

		nNode = nNode->ptr_next;
	}
}

//добавление нового рейса. Параметр функции-номер строки, куда пользователь хочет впихнуть новый рейс (для того что бы можно было добавлять не только в конец.
Node *add_flight(int num_string_add)
{
	Node *nNode;
	Node *prevNode;
	Node *new_ptr;

	if (num_string_add == 1)
	{
		new_ptr = (Node *)malloc(sizeof(Node));
		new_ptr->ptr_next = head_ptr;
		head_ptr = new_ptr;
		return head_ptr;
	}

	nNode = head_ptr;
	prevNode = nNode;

	for (; num_string_add > 1; num_string_add--)
	{
		if (nNode->ptr_next == NULL)//следует необходимо добавить в конец списка
		{
			new_ptr = (Node *)malloc(sizeof(Node));
			nNode->ptr_next = new_ptr;
			new_ptr->ptr_next = NULL;
			return new_ptr;
		}

		prevNode = nNode;
		nNode = nNode->ptr_next;

	}

	new_ptr = (Node *)malloc(sizeof(Node));
	prevNode->ptr_next = new_ptr;
	new_ptr->ptr_next = nNode;
	return new_ptr;
}

int edit_Node(int num_flight)//редактирование рейса
{
	Node *nNode = head_ptr;
	int bool = 0;

	while (nNode->n_flight != num_flight)
	{
		if (nNode->ptr_next == NULL)
		{
			printf("Такого рейса нет\n");
			system("pause");
			return 1;
		}
		nNode = nNode->ptr_next;
	}
	printf("[1] Если хотите изменить номер рейса: \n[0] Если хотите оставить неизменным номер рейса: \n");
	scanf("%d", &bool);
	printf("\n");

	if (bool)
	{
		printf("Введите изменённый номер рейса: ");
		scanf("%d", &nNode->n_flight);
		printf("\n");
		bool = 0;
	}

	printf("[1] Если хотите изменить город направления данного рейса: \n[0] Если хотите оставить неизменным город направления данного рейса: \n");
	scanf("%d", &bool);
	printf("\n");

	if (bool)
	{
		printf("Введите город в который направляется рейс:");
		scanf_s("%s", &nNode->to, 50);
		getchar();
		printf("\n");
		bool = 0;
	}

	printf("[1] Если хотите изменить цену: \n[0] Если хотите оставить цену: \n");
	scanf("%d", &bool);
	printf("\n");

	if (bool)
	{
		printf("Введите цену рейса в рублях:");
		scanf("%d", &nNode->price);
		printf("\n");
		bool = 0;
	}

	printf("[1] Если хотите изменить время вылета-прилёта: \n[0] Если хотите оставить время вылета-прилёта: \n");
	scanf("%d", &bool);
	printf("\n");

	if (bool)
	{
		printf("Введите время вылета-приземления фаормата :'10:50-15:30'");
		scanf_s("%s", &nNode->time_t_l, 15);
		getchar();
		printf("\n");
		bool = 0;
	}

	printf("[1] Если хотите изменить время ожидания при пересадках: \n[0] Если хотите оставить неизменным вреям ожидания при пересадках: \n");
	scanf("%d", &bool);
	printf("\n");

	if (bool)
	{
		printf("Введите время ожидания при пересадках в минутах: ");
		scanf("%d", &nNode->time_wait);
		printf("\n");
		bool = 0;
	}

	return 0;

}

void struct_free()
{
	Node *pNode = NULL;
	Node *nNode = head_ptr;

	while ((pNode = nNode) != NULL)
	{
		nNode = nNode->ptr_next;
		free(pNode);
	}

}

int main()
{
	FILE *fptr;//указатель на файлы
	char *ptr;//Указатель для получаемой строки из исходного файла
	char line[MAXLINE];
	char line_titul_table[MAXLINE];
	Node *Node_ptr = NULL;
	int choice_main;//переменная для выбора одного из 5 (см. ТЗ)
	int num_flight;
	Node *add_Node_ptr = NULL;
	int num_delete;
	int min;
	Node *Node_min = NULL;

	system("chcp 1251");//для использования русской кодировки

	fptr = fopen("AviaCassa.txt", "rt");

	if (fptr == NULL)
	{
		printf("Error opening or creating file or my code is fu*king turd");
		return 1;
	}
	ptr = fgets(line_titul_table, MAXLINE, fptr);//запоминаем 1 строку
	//выделение памяти и инициализация полей Data первого Node
	if (!feof(fptr))
	{

		if ((ptr = fgets(line, MAXLINE, fptr)) != NULL)
		{
			head_ptr = (Node *)malloc(sizeof(Node));//выделение памяти для первого узла списка
			head_ptr->ptr_next = NULL;//инициализация следующего указателя

			give_Data(line, head_ptr);//заполнение полей Data первого узла звписка
		}
	}

	//выделение памяти и инициализация полей Data второго Node
	if (!feof(fptr))
	{

		if ((ptr = fgets(line, MAXLINE, fptr)) != NULL)
		{
			Node_ptr = give_next_Node(head_ptr);
			give_Data(line, Node_ptr);
		}
	}
	//выделение памяти и инициализация полей Data оставшихся Node
	while (!feof(fptr))
	{
		if ((ptr = fgets(line, MAXLINE, fptr)) != NULL)
		{
			Node_ptr = give_next_Node(Node_ptr);
			give_Data(line, Node_ptr);
		}
	}
	//внесение данных из файла в поля списка закончено
	system("cls");//очиска консоли

	do
	{
		system("cls");

		printf("[0] Выйти из программы.\n[1] Добавить рейс.\n[2] Редактировать рейс.\n[3] Удалить рейс.\n[4] Подобрать маршрут с наименьшим временем ожидания при пересадке.\n[5] Подобрать маршрут с наименьшей стоимостью.\n[6] Вывести авиакассу на экран\n\n");
		scanf("%d", &choice_main);

		switch (choice_main)
		{
		case 1:
			system("cls");
			//добавить рейс
			print_table(line_titul_table);
			printf("\n\n");
			printf("Введите номер строки, в которую нужно впихнуть новый рейс: ");
			scanf("%d", &num_flight);

			add_Node_ptr = add_flight(num_flight);

			system("cls");
			//заполнеие узла списка

			printf("Введите номер рейса, численного формата: ");
			scanf("%d", &add_Node_ptr->n_flight);
			printf("\n");

			printf("Введите город в который направляется рейс: ");
			scanf_s("%s", &add_Node_ptr->to, 50);
			getchar();
			printf("\n");

			printf("Введите цену рейса в рублях: ");
			scanf("%d", &add_Node_ptr->price);
			printf("\n");

			printf("Введите время вылета-приземления фаормата '10:50-15:30': ");
			scanf_s("%s", add_Node_ptr->time_t_l, 15);
			getchar();
			printf("\n");

			printf("Введите время ожидания при пересадках в минутах: ");
			scanf("%d", &add_Node_ptr->time_wait);
			printf("\n");

			system("cls");
			print_table(line_titul_table);

			system("pause");

			break;

		case 2:
			system("cls");
			//редактировать рейс
			print_table(line_titul_table);
			printf("\n\n");
			printf("Введите номер рейса, который хотите редактировать: ");
			scanf("%d", &num_flight);
			printf("\n");

			edit_Node(num_flight);//редактирование рейса

			system("cls");
			print_table(line_titul_table);
			system("pause");

			break;

		case 3:
			system("cls");
			//удалить рейс
			print_table(line_titul_table);
			printf("\n\n");
			printf("Введите номер рейса, который хотите удалить: ");
			scanf("%d", &num_delete);
			printf("\n");

			Node_ptr = head_ptr;
			while (Node_ptr->n_flight != num_delete)
			{
				Node_ptr = Node_ptr->ptr_next;
			}

			delete_node(Node_ptr);

			system("cls");
			print_table(line_titul_table);
			system("pause");

			break;

		case 4:
			system("cls");
			//подобрать маршрут с наименьшим временем ожиданя при пересадке
			print_table(line_titul_table);
			printf("\n\n");
			printf("Введите город в который вы хотите полететь: ");
			scanf_s("%s", &line, 50);
			getchar();
			printf("\n\n");

			Node_ptr = head_ptr;
			min = 2100000000;
			while (Node_ptr != NULL)
			{
				if (strcmp(line, Node_ptr->to) == 0)
				{
					if (Node_ptr->time_wait < min)
					{
						min = Node_ptr->time_wait;
						Node_min = Node_ptr;
					}
				}
				Node_ptr = Node_ptr->ptr_next;
			}

			printf("У маршрута номер %d наименьшее время ожидания при пересадке: %d минут\n", Node_min->n_flight, Node_min->time_wait);
			system("pause");

			break;
		case 5:
			system("cls");
			//подобрать маршрут наименьший по стоимости

			print_table(line_titul_table);
			printf("\n\n");
			printf("Введите город в который вы хотите полететь\n");
			scanf_s("%s", &line, 50);
			getchar();

			Node_ptr = head_ptr;
			min = 2100000000;
			while (Node_ptr != NULL)
			{
				if (strcmp(line, Node_ptr->to) == 0)
				{
					if (Node_ptr->price < min)
					{
						min = Node_ptr->price;
						Node_min = Node_ptr;
					}
				}
				Node_ptr = Node_ptr->ptr_next;
			}

			printf("В город %s самый дешёвый рейс номер: %d. Цена:%d\n", line, Node_min->n_flight, Node_min->price);
			system("pause");

			break;

		case 6:
			//вывод авиакассы на экран
			system("cls");
			print_table(line_titul_table);
			printf("\n");
			system("pause");

			break;
		case 0:
			break;

		default:
			printf("Вы ввели несуществующую опцию, введите ещё раз!");
			system("pause");

			break;
		};


	} while (choice_main != 0);

	fclose(fptr);
	//перезапить изменённой базы данных в файл
	fptr = fopen("AviaCassa.txt", "wt");
	if (fptr == NULL)
	{
		printf("Ошибка перезаписи в файл, исходная авиакасса останется неизменённой");
	}
	else
	{
		fputs(line_titul_table, fptr);

		Node_ptr = head_ptr;
		while (Node_ptr != NULL)
		{
			//запись в файл


			int len, ry;
			fputc('|', fptr);
			len = 0;
			ry = Node_ptr->n_flight;

			do
			{
				len++;
				ry /= 10;
			}while (ry != 0);

			for (ry = 13 - len; ry != 0; ry--)
				fputc('.', fptr);

			fprintf(fptr, "%d", Node_ptr->n_flight);
			fputc('|', fptr);
			//
			len = strlen(Node_ptr->to);
			for (ry = 29 - len; ry != 0; ry--)
				fputc('.', fptr);
			fputs( Node_ptr->to, fptr);
			fputc('|', fptr);
			//
			len = 0;
			ry = Node_ptr->price;
			do
			{
				len++;
				ry /= 10;
			} while (ry != 0);
			for (ry = 18 - len; ry != 0; ry--)
				fputc('.', fptr);

			fprintf(fptr, "%d", Node_ptr->price);
			fputc('|', fptr);
			//
			len = strlen(Node_ptr->time_t_l);
			for (ry = 20 - len; ry != 0; ry--)
				fputc('.', fptr);
			fputs( Node_ptr->time_t_l, fptr);
			fputc('|', fptr);
			//
			len = 0;
			ry = Node_ptr->time_wait;
			do
			{
				len++;
				ry /= 10;
			} while (ry != 0);
			for (ry = 19 - len; ry != 0; ry--)
				fputc('.', fptr);

			fprintf(fptr, "%d", Node_ptr->time_wait);
			fputc('|', fptr);
			fputc('\n', fptr);

			Node_ptr = Node_ptr->ptr_next;

		}
		//окончание перезаписи в файл
	}
	fclose(fptr);

	struct_free();//освобождение памяти, занятой списком

	return 0;
}
