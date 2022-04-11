#include <iostream>
//definiujemy strukturę która będzie elementem naszej listy, składa się z dwóch atrybutów: data będący intem, czyli po prostu zawartość komórki listy
//oraz wskaźnik na następny element, który też oczywiście jest strukturą.
struct element {
    int data;
    struct element* nextElement;
};
//metoda odpowiadająca za wrzucenie elementu na sam początek listy, jako parametry przyjmuje wskaźnik na wskaźnik głowy listy,
//czyli początku, oraz oczywiście numer który ma być zawartością komórki listy.
void pushFront(element** head, int number) {
    //tworzymy nowy element rezerwując w pamięci odpowiednią ilość miejsca
    element* currentElement = (element*)malloc(sizeof(element));
    //przypisujemy do tego nowego elementu dostarczony w argumencie funkcji numer
    currentElement->data = number;
    //oraz jako nextElement przypisujemy wskaźnik do głowy 
    currentElement->nextElement = (*head);
    *head = currentElement;
}
void pushBack(element** head, int number) {
    if (*head == NULL) {
        *head = (element*)malloc(sizeof(element));
        (*head)->data = number;
        (*head)->nextElement = NULL;
    }
    else {
        element* currentElement = *head;
        while (currentElement->nextElement != NULL) {
            currentElement = currentElement->nextElement;
        }
        currentElement->nextElement = (element*)malloc(sizeof(element));
        currentElement->nextElement->data = number;
        currentElement->nextElement->nextElement = NULL;
    }
}
void showList(element* head) {
    std::cout << std::endl;
    if (head == NULL) std::cout << "List is empty";
    else {
        element* currentElement = head;
        do {
            std::cout << currentElement->data << " ";
            currentElement = currentElement->nextElement;
        } while (currentElement != NULL);
        std::cout << std::endl;
    }
}

int listSize(element* head) {
    int counter = 0;
    if (head == NULL) return 0;
    else {
        element* currentElement = head;
        do {
            counter++;
            currentElement = currentElement->nextElement;
        } while (currentElement != NULL);
    }
    return counter;
}
void pushByIndex(element** head, int number, int index) {
    if (index == 0) pushFront(head, number);
    else if (index == listSize(*head) - 1) pushBack(head, number);
    else {
        element* currentElement = *head;
        element* tmp;
        int i = 0;
        while (currentElement->nextElement != NULL && i < index - 1) {
            currentElement = currentElement->nextElement;
            i++;
        }
        tmp = currentElement->nextElement;
        currentElement->nextElement = (element*)malloc(sizeof(element));
        currentElement->nextElement->data = number;
        currentElement->nextElement->nextElement = tmp;
    }
}
void popFront(element** head) {
    element* tmp = NULL;
    if (*head != NULL) {
        tmp = (*head)->nextElement;
        delete* head;
        *head = tmp;
    }
}
void popBack(element** head) {
    if (*head != NULL) {
        if ((*head)->nextElement == NULL) {
            *head = NULL;
        }
        else {
            element* currentElement = *head;
            while (currentElement->nextElement->nextElement != NULL) {
                currentElement = currentElement->nextElement;
            }
            delete currentElement->nextElement;
            currentElement->nextElement = NULL;
        }
    }
}
void popByIndex(element** head, int index) {
    if (index == 0) popFront(head);
    else if (index = listSize(*head) - 1) popBack(head);
    else {
        element* currentElement = *head;
        element* tmp;
        int i = 0;
        while (currentElement->nextElement != NULL && i < index - 1) {
            currentElement = currentElement->nextElement;
            i++;
        }
        tmp = currentElement->nextElement;
        currentElement->nextElement = tmp->nextElement;
        delete tmp;
    }
}
int main()
{
    element* head = NULL;
    bool timeToEnd = false;
    do {
        int choice;
        std::cout << "\nCurrent look of the list:";
        showList(head);
        std::cout << "\n1. Push an item to the head of the list \n"
                     "2. Push an item to the tail of the list. \n"
                     "3. Push an item to the specific index. \n"
                     "4. Pop an item from the head of the list. \n"
                     "5. Pop an item from the tail of the list. \n"
                     "6. Pop an item from the specific index of the list. \n"
                     "7. Display list. \n"
                     "8. Display the size of the list \n"
                     "0. Exit \n";
        std::cout << "Choose option: ";
        std::cin >> choice;
        int element, index;
        switch (choice) {
            case 0:
                timeToEnd = true;
                break;
            case 1:
                std::cout << "Enter element to push: ";
                std::cin >> element;
                pushFront(&head, element);
                break;
            case 2:
                std::cout << "Enter element to push: ";
                std::cin >> element;
                pushBack(&head, element);
                break;
            case 3:
                std::cout << "Enter index:";
                std::cin >> index;
                std::cout << "Enter element to push: ";
                std::cin >> element;
                pushByIndex(&head, element, index);
                break;
            case 4:
                popFront(&head);
                break;
            case 5:
                popBack(&head);
                break;
            case 6:
                std::cout << "Enter index:";
                std::cin >> index;
                popByIndex(&head, index);
                break;
            case 7:
                showList(head);
                break;
            case 8:
                std::cout << "Size of the current list: " << listSize(head) << "\n";
                break;
            default:
                std::cout << "Incorrect choice, try again \n";
                break;

        }
    } while (!timeToEnd);
    return 0;
}