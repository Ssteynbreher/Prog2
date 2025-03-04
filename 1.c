#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;   // Вправо
    struct node* prev;   // Влево 
    struct node* above; // Вверх 
    struct node* below;   // Вниз 
};

// Создание нового узла
struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;  
    newNode->above = NULL; 
    newNode->below = NULL;
    return newNode;
}

// Добавление узла в конец списка
void appendNode(struct node** head, int data) {
    struct node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp; //prev для двусвязного списка
}

void printList(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Связывание списков 
void linkLists(struct node* list1, struct node* list2) {
    struct node* temp1 = list1;
    struct node* temp2 = list2;
    while (temp1 != NULL && temp2 != NULL) {
        temp1->below = temp2; 
        temp2->above = temp1; 
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
}

int main() {
    struct node* list1 = NULL;
    struct node* list2 = NULL;
    int input;
    printf("Введите элементы для 1 списка (0-стоп):\n");
    do {
        scanf("%d", &input);
        if (input != 0) appendNode(&list1, input);
    } while (input != 0);

    printf("Введите элементы для 2 списка (0-стоп):\n");
    do {
        scanf("%d", &input);
        if (input != 0) appendNode(&list2, input);
    } while (input != 0);

    linkLists(list1, list2); 

    struct node* S = list1; 
    struct node* current = S; 
    char command;

    printf("Введите WASD или 2468 для перемещения.\n");
    while (1) {
        if (current)
            printf("Текущее число: %d\n", current->data);
        else
            printf("Вы находитесь за пределами списка.\n");

        printf("Команда (W/8 - вверх, S/2 - вниз, A/4 - влево, D/6 - вправо, Q - выход): ");
        scanf(" %c", &command);

        switch (command) {
            case '6':
            case 'D':
            case 'd': // Вправо
                if (current && current->next) {
                    current = current->next;
                } else {
                    printf("Вы достигли конца списка справа.\n");
                }
                break;
            case '4':
            case 'A':
            case 'a': // Влево
                if (current && current->prev) {
                    current = current->prev;
                } else {
                    printf("Вы достигли конца списка слева.\n");
                }
                break;
            case '8':
            case 'W':
            case 'w': // Вверх
                if (current && current->above) {
                    current = current->above;
                } else {
                    printf("Вы достигли верха списка.\n");
                }
                break;
            case '2':
            case 'S':
            case 's': // Вниз
                if (current && current->below) {
                    current = current->below;
                } else {
                    printf("Вы достигли низа списка.\n");
                }
                break;
            case 'Q':
            case 'q': // Выход
                printf("Выход.\n");
                return 0;
            default:
                printf("Неверная команда.\n");
        }
    }
}