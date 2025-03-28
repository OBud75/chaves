#include "exercices.h"
#include <stdio.h>

// Comparaisons de personnes
void eq_function_persons() {
    Person person1 = {30};
    Person person2 = {30};
    int same_age = are_equals(
        &person1, 
        &person2, 
        (int (*)(void *, void *)) are_persons_equals);
        
    if (same_age == 1) {
        printf("Persons are equals\n");
    } else {
        printf("Persons are not equals\n");
    };
}

// Comparaisons de livres
void eq_function_books() {
    Book book1 = {27};
    Book book2 = {30};
    int same_pages = are_equals(
        &book1, 
        &book2, 
        (int (*)(void *, void *)) are_books_equals);
    
    if (same_pages == 1) {
        printf("--------------------\n");
        printf("Books are equals\n");
    } else {
        printf("--------------------\n");
        printf("Books are not equals\n");
    };
}

// Une fonction de comparaison qui passe partout serait de return -1 si obj1 < obj2, 1 si obj1 > obj2 et 0 si égaux

void linear_search() {
    // Recherche de personne dans un tableau
    Person person1 = {30};
    Person p1 = {20};
    Person p2 = {30};
    Person *people[] = { &p1, &p2 };

    int found = is_in_array(
        &person1, 
        (void **)people, 
        sizeof(people) / (sizeof(Person)),
        sizeof(Person),
        (int (*)(void *, void *)) are_persons_equals
    );
    if (found == 1) {
        printf("--------------------\n");
        printf("Person is in array\n");
    } else {
        printf("--------------------\n");
        printf("Person is not in array\n");
    };

    // Recherche de book dans un tableau
    Book book1 = {70};
    Book b1 = {40};
    Book b2 = {70};
    Book *library[] = { &b1, &b2 };

    found = is_in_array(
        &book1, 
        (void **)library, 
        sizeof(library) / (sizeof(Book)),
        sizeof(Book),
        (int (*)(void *, void *)) are_books_equals
    );
    if (found == 1) {
        printf("the Book is in array\n");
    } else {
        printf("the Book is not in array\n");
    };
}

void generic_swap() {
    Person person1 = {50};
    Person person2 = {25};
    swap(&person1, &person2, sizeof(Person));
    Book b1 = {50};
    Book b2 = {25};
    swap(&b1, &b2, sizeof(Book));

    printf("--------------------\n");
    printf("Person1 age: %d\n", person1.age);
    printf("Person2 age: %d\n", person2.age);
    printf("--------------------\n");
    printf("Book1 pages: %d\n", b1.pages);
    printf("Book2 pages: %d\n", b2.pages);
};



int main() {
    eq_function_books();
    eq_function_persons();
    linear_search();
    generic_swap();

    Person p1 = {20};
    Person p2 = {50};
    Person p3 = {188};
    Person p4 = {2};

    Person *people[] = {&p1, &p2, &p3, &p4};
    sort(
        (void **)people,
        sizeof(people) / (sizeof(people[0])),
        sizeof(Person)
    );
    printf("--------------------\n");
    for (int i = 0; i < sizeof(people) / (sizeof(people[0])); i++) {
        printf("Person %d age: %d\n", i, people[i]->age);
    };

    // On peut éventuellement itérer sur les personnes du tableau:
    // for (Person *p = people; p < people + sizeof(people) / (sizeof(people[0])); p++) {
    //     printf("Person age: %d\n", p->age);}
 
}

