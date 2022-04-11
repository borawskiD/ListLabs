#include <iostream>
/* definiujemy strukturę która będzie elementem naszej listy, składa się z dwóch atrybutów: data będący intem, czyli po prostu zawartość komórki listy
   oraz wskaźnik na następny element, który też oczywiście jest strukturą. */
struct element {
    int data;
    struct element* nextElement;
};
/* metoda odpowiadająca za wrzucenie elementu na sam początek listy, jako parametry przyjmuje wskaźnik na wskaźnik szczytu (głowy) listy,
   czyli początku, oraz oczywiście numer który ma być zawartością komórki listy. */
void pushFront(element** head, int number) {
    //tworzymy nowy element rezerwując w pamięci odpowiednią ilość miejsca
    element* currentElement = (element*)malloc(sizeof(element));
    //przypisujemy do tego nowego elementu dostarczony w argumencie funkcji numer
    currentElement->data = number;
    //oraz jako nextElement przypisujemy wskaźnik do początku listy, a później uznajemy currentElement za początek listy
    currentElement->nextElement = (*head);
    *head = currentElement;
}
/* funkcja odpowiadająca za dodanie elementu do końca listy, przyjmuje analogicznie do poprzednika
   wskaźnik na wskaźnik szczytu listy oraz liczbę, która ma być umieszczona na końcu */
void pushBack(element** head, int number) {
    /* jeśli *head wskazuje na NULL, to lista jest pusta
       jeśli lista jest pusta nie ma sensu szukać/iterować w poszukiwaniu kolejnych wskaźników, w związku z tym
       po prostu element dodany tą metodą będzie na szczycie listy. */
    if (*head == NULL) {
        //alokuję pamięć dla nowego elementu w strukturze
        *head = (element*)malloc(sizeof(element));
        /* i przypisuje do szczytu listy odpowiednie parametry, tj number czyli liczbę oraz (!) NULL na wskaźniku
           następcy. */
        (*head)->data = number;
        (*head)->nextElement = NULL;
    }
    //jeśli lista nie jest pusta to zaczynamy iterację w poszukiwaniu ostatniego elementu w pamięci
    else {
        //wskaźnik aktualnego elementu będzie przechowywany w currentElement.
        element* currentElement = *head;
        /* rozpoczynam iterację, każdy "obrót" to przejście do kolejnego parametru nextElement aż do momentu
        kiedy nie będzie następcy (nextElement wskaże NULL). */
        while (currentElement->nextElement != NULL) {
            currentElement = currentElement->nextElement;
        }
        //jak już znajdziemy ten element, to alokujemy w pamięci miejsce dla kolejnego elementu
        currentElement->nextElement = (element*)malloc(sizeof(element));
        /* przypisujemy do następnego elementu kolejne parametry - liczbę oraz wskaźnik na NULL (bo teraz ten
           element jest ostatnim). */
        currentElement->nextElement->data = number;
        currentElement->nextElement->nextElement = NULL;
    }
}
//proste wyświetlanie elementów listy, przekazujemy kopię listy, ponieważ nic nie będziemy zmieniać
void showList(element* head) {
    std::cout << std::endl;
    //obsługa sytuacji wyjątkowej, gdy lista jest pusta
    if (head == NULL) std::cout << "List is empty";
    //w przeciwnym wypadku działamy
    else {
        //tworzymy wskaźnik na bieżący element
        element* currentElement = head;
        //iterujemy do momentu napotkania wskaźnika na NULL
        do {
            //z każdą iteracją wyświetlamy liczbę pod elementem
            std::cout << currentElement->data << " ";
            //oraz przepisujemy bieżący wskaźnik do kolejnej iteracji
            currentElement = currentElement->nextElement;
        } while (currentElement != NULL);
        std::cout << std::endl;
    }
}
/* metoda zwracająca liczbę elementów w liście, w zasadzie analogiczna do powyższej, jedynie zamiast wyświetlania dajemy
   inkrementację zmiennej, którą później zwracamy (ewentualnie 0, gdy lista jest pusta). */
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
/* najtrudniejsza operacja, dodajemy element po indeksie, przyjmujemy oczywiście
   wskaźnik na wskaźnik listy, numer do wstawienia oraz indeks, do którego musimy dodać element */
void pushByIndex(element** head, int number, int index) {
    /* gdy index jest rowny zero, znaczy, że chcemy po prostu dodać nowy element na szczyt listy
       mamy od tego metodę :-) */
    if (index == 0) pushFront(head, number);
    //tak samo w momencie gdy podany index będzie po prostu indexem ostatniego elementu
    else if (index == listSize(*head) - 1) pushBack(head, number);
    /* w przeciwnym wypadku iterujemy wzdłuż listy, z uwagi na specyfikę tej struktury, musimy zacząć od
       początku mimo że znamy już dokładną pozycję poszukiwanego elementu */
    else {
        //zaczynamy od początku, zatem tworzymy nowy wskaźnik currentElement, który wskazuje na szczyt listy (head).
        element* currentElement = *head;
        //oraz tymczasowy wskaźnik, w którym będziemy roboczo przechowywać nasz element listy
        element* tmp;
        //zaczynamy od zera :-)
        int i = 0;
        /* iterujemy, do momentu aż nie natrafimy na koniec listy (wskaźnik na następny element nie wskazuje na NULL)
           oraz i jest mniejsze od indeksu - 1. */
        while (currentElement->nextElement != NULL && i < index - 1) {
            //każda iteracja to przeskoczenie o jeden elementu w liście oraz inkrementacja i.
            currentElement = currentElement->nextElement;
            i++;
        }
        //jak już znajdziemy odpowiedni element na liście, przepisujemy wskaźnik na następny element do wskaźnika tmp
        tmp = currentElement->nextElement;
        //tworzymy nowy element (rezerwujemy dla niego pamięć)
        currentElement->nextElement = (element*)malloc(sizeof(element));
        //uzupełniamy go danymi - liczbą
        currentElement->nextElement->data = number;
        //podmieniamy wskaźnik nextElement na temp, w ten sposób element ląduje pomiędzy elementy "starej" listy.
        currentElement->nextElement->nextElement = tmp;
    }
}
//prosta metoda na wyrzucenie pierwszego (szczytowego) elementu,
void popFront(element** head) {
    //tworzymy wskaźnik na NULL, to tymczasowe
    element* tmp = NULL;
    //sprawdzamy czy lista jest pusta, jeśli nie - wykonujemy operację
    if (*head != NULL) {
        /* przepisujemy wskaźnik następnego od szczytu elementu listy (od lewej będzie to drugi (!) element)
           do wskaźnika tmp */
        tmp = (*head)->nextElement;
        //usuwamy wskaźnik będący poprzednim szczytem listy
        delete* head;
        //nowym szczytem (głową) listy jest wskaźnik tmp, czyli wcześniejszy następca starego szczytu listy.
        *head = tmp;
    }
}
//funkcja odpowiadająca za usuwanie ostatniego elementu
void popBack(element** head) {
    //sprawdzamy czy lista nie jest pusta, jeśli by była - nie ma co usuwać
    if (*head != NULL) {
        /* jeśli nie jest, to sprawdzamy czy lista ma więcej niż 1 element, jeśli nie, to po prostu ustawiamy
           wskaźnik szczytu na NULL i finito */
        if ((*head)->nextElement == NULL) {
            *head = NULL;
        }
        //jeśli nie, to rozpoczynamy operację
        else {
            //ponownie będziemy iterować, zatem ponownie przypisujemy startowy wskaźnik do szczytu listy
            element* currentElement = *head;
            /* i ponownie iterujemy wzdłuż listy, tutaj jednak iterujemy do momentu aż znajdziemy element który
               nie ma następcy następcy (!), to dość skomplikowane, ale kod mówi wszystko :-) */
            while (currentElement->nextElement->nextElement != NULL) {
                currentElement = currentElement->nextElement;
            }
            //teraz usuwamy poszukiwanego następce z pamięci
            delete currentElement->nextElement;
            //i przypisujemy wskaźnik na NULL, ponieważ currentElement jest teraz wskaźnikiem na ostatni element
            currentElement->nextElement = NULL;
        }
    }
}
//funkcja która pozwala na usuwanie wybranego elementu listy (po indeksie)
void popByIndex(element** head, int index) {
    //jak indeks jest równy 0, to wyrzucamy przygotowaną wcześniej metodą element szczytowy
    if (index == 0) popFront(head);
    //jak indeks jest równy rozmiarowi listy, to usuwamy ostatni element zgodnie z przygotowaną wcześniej funkcją
    else if (index = listSize(*head) - 1) popBack(head);
    //w przeciwnym wypadku znowu iterujemy
    else {
        //ustawiamy wskaźnik currentElement na szczyt listy
        element* currentElement = *head;
        //tworzymy też wskaźnik pomocniczy tmp
        element* tmp;
        //oraz licznik i = 0
        int i = 0;
        //dopóki nie dobrniemy do krańca listy i i będzie mniejsze od indexu minus 1 (bo liczymy od zera)
        while (currentElement->nextElement != NULL && i < index - 1) {
            //przenosimy wskaźnik na bieżący element
            currentElement = currentElement->nextElement;
            //inkrementujemy i
            i++;
        }
        //jak pętla skończy bieg, to możemy usuwać - ustawiamy wskaźnik tymczasowy na następny od obecnego element
        tmp = currentElement->nextElement;
        /* tutaj najważniejsza linijka - ustawiamy wskaźnik bieżącego elementu na wskaźnik następcy następcy
        trochę masło maślane, ale w skrócie przeskakujemy potomka, i ustawiamy wskaźnik na kolejny element. */
        currentElement->nextElement = tmp->nextElement;
        //usuwamy element który jest nam zbędny
        delete tmp;
    }
}
int main()
{
    //ustawiamy wskaźnik początkowy head na NULL
    element* head = NULL;
    //zmienna pomocnicza do obsługi pętli
    bool timeToEnd = false;
    //pętla do obsługi menu
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

/*
 * Dominik Borawski A1 215IC
 * Lista jednokierunkowa
 */

/*
 * Przykładowy output
 */

/*
Current look of the list:
List is empty
1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 1
Enter element to push: 4

Current look of the list:
4

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 2
Enter element to push: 2

Current look of the list:
4 2

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 2
Enter element to push: 0

Current look of the list:
4 2 0

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 1
Enter element to push: 3

Current look of the list:
3 4 2 0

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 3
Enter index:2
Enter element to push: 1

Current look of the list:
3 4 1 2 0

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 4

Current look of the list:
4 1 2 0

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 5

Current look of the list:
4 1 2

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 6
Enter index:1

Current look of the list:
4 1

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 7

4 1

Current look of the list:
4 1

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 8
Size of the current list: 2

Current look of the list:
4 1

1. Push an item to the head of the list
2. Push an item to the tail of the list.
3. Push an item to the specific index.
4. Pop an item from the head of the list.
5. Pop an item from the tail of the list.
6. Pop an item from the specific index of the list.
7. Display list.
8. Display the size of the list
0. Exit
Choose option: 0

Process finished with exit code 0

 */