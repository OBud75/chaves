#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    int age;
} Person;

int are_persons_equals(Person *p1, Person *p2) {
    // return 1 if same age
    if (p1->age == p2->age) {
        return 1;
    } else {
        return 0;
    };  
};

typedef struct Book {
    int pages;
} Book;

int are_books_equals(Book *b1, Book *b2) {
    // return 1 if same nb of pages
    if (b1->pages == b2->pages) {
        return 1;
    } else {
        return 0;
    };
};

int are_equals(
    void *obj1, void *obj2, 
    int (*compare_fnc)(void *, void *)) {
    return compare_fnc(obj1, obj2);
}

int is_in_array(
    void *obj_to_find, 
    void *array[], 
    int nb_of_elems_in_array, 
    size_t elem_size, 
    int (*compare_fnc)(void *, void *)) {
    
    for (int i = 0; i < nb_of_elems_in_array; i++) {
        if (compare_fnc(obj_to_find, array[i]) == 1) {
            return 1;
        };
    }
    return 0;
};

int is_greater_persons (Person *obj1, Person *obj2) {
    if (obj1->age > obj2->age) {
        return 1;
    } else {
        return 0;
    };
};

int if_greater_books (Book *obj1, Book *obj2) {
    if (obj1->pages > obj2->pages) {
        return 1;
    } else {
        return 0;
    };
};

int is_greater(
    // return 1 if obj1 is greater than obj2
    void *obj1, void *obj2,
    int (*compare_fnc)(void *, void *)) {
        return compare_fnc(obj1, obj2);
    };

// Une manière de comparer directement serait de renvoyer
// -1 si obj1 < obj2, 1 si obj1 > obj2 et 0 si obj1 == obj2

void swap(void *obj1, void *obj2, size_t size) {
    //allouer de la mémoire pour un objet temporaire
    void *temp = malloc(size);
    //copier obj1 dans temp
    memcpy(temp, obj1, size);
    //copier obj2 dans obj1
    memcpy(obj1, obj2, size);
    //copier temp dans obj2
    memcpy(obj2, temp, size);
    //libérer la mémoire allouée pour temp
    free(temp);
};

void sort(
    void *array[],
    int nb_of_elems_in_array,
    size_t elem_size){

    for (int i = 0; i < nb_of_elems_in_array; i++){
        for (int j = i + 1; j < nb_of_elems_in_array; j++){        
            if (is_greater(array[i], array[j], (int (*)(void *, void *)) is_greater_persons) == 1){
                swap(array[i], array[j], elem_size);
            }
        }
    }
};