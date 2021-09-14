#ifndef _ARRAYLIST_H
#define _ARRAYLIST_H

#include <stdbool.h>

/**
 * Element of the list
 */
struct element{
    char* text;             /// content of the element
    struct element* next;   /// next element
};


/**
 * The list
 */
struct list{
    struct element* element;    /// the first element of the list
    int size;                   /// number of elements in the list
};


/**
 * Creates new list
 *
 * Function allocates memory for new list and sets it's size to 0. There is
 * no element in the list at this moment.
 *
 * @return reference to the newly created list or NULL, if something goes wrong.
 */
struct list* create_list();


/**
 * Creates new element
 *
 * Function allocates memory for new element with text. If no text is provided,
 * no new element will be created and function returns NULL. Otherwise returns
 * reference to the newly created element.
 * Text must remain intact!
  *
 * @param text the text of the element
 * @return reference to the newly created element
 */
struct element* create_element(char* text);


/**
 * Appends new element to the list
 *
 * Appends new element at the end of the list. If no list or element is given
 * (NULL) nothing will be done. Otherwise new element will be added at the
 * end of the list of elements.
 * If the element was appended successfully, counter will be increased by 1.
 *
 * @param list the reference to the list
 * @param element new element to append
 * @return reference to the appended element or NULL on error
 */
struct element* append(struct list* list, struct element* element);


/**
 * Inserts the element at the position in the list.
 *
 * If list or element is not given (they are NULL) or index is negative, nothing
 * will happen. If new element is inserted at given position, the rest of the
 * list is append to the newly inserted element. Size of the list is increased
 * by 1. If index is greater than size of list, nothing will be inserted.
  *
 * @param list reference to the list
 * @param index position of the element to add
 * @param element the element for insertion
 * @return
 */
void insert(struct list* list, int index, struct element* element);


/**
 * Get element at given position from the list
 *
 * Returns reference to the element of the list from given position.
 * If list doesn't exist (is NULL) or index is < 0, function returns
 * NULL. If index is greater than the size of list, function will
 * return NULL. First entry of the list starts at index 0.
 *
 * @param list the reference to the list
 * @param index position of the element
 * @return reference to the element at given position, or NULL, if something went wrong.
 */
struct element* get(struct list* list, int index);


/**
 * Returns the number of elements in list.
 *
 * Function returns the number of elements in the list. If the list is
 * not given (NULL), function returns value -1.
 *
 * @param list the reference to the list
 * @return number of elements in the list or -1 if error
 */
int size(struct list* list);


/**
 * Returns true, if list is empty, otherwise false
 *
 * Function checks, if the given list is empty or not. If the list is empty (it's
 * size is 0 and list doesn't contain any elements), function retusn true. If
 * the list contains any number of elements, returns false.
 *
 * @param list the reference to the list
 */
bool is_empty(struct list* list);


/**
 * Returns the index of the first occurrence of the specified element in this list, or -1 if this list does not contain the element.
 *
 * Function searches for an element of given text. If such element is found, it's
 * index is returned. If there are several elements with same text, index of first
 * one is returned. If there is no such element, function returns -1. If the list
 * or text is not specified (NULL), function returns -1.
 *
 * @param list the reference to the list
 * @param text text element to find
 * @return returns the index of first founded element or -1 if error or not found
 *
 */
int get_index_of(struct list* list, const char* text);



/**
 * Removes element at specific index
 *
 * Function removes element at given index and returns it's reference. The size of list is decreased by 1 on successful
 * removal. If list doesn't exist (is NULL) or wrong index is passed, function returns NULL with no change in list.
 *
 * @param list the reference to the list
 * @param index the index of element to remove
 * @return the reference to the removed element or null if there is no such element or on error
 *
 */
struct element* remove_at(struct list* list, int index);


/**
 * Removes all elements from list which equals to given text
 *
 * Function finds first element, which contain given text and removes it from
 * the list. The list and it's size is then decreased by 1. Function returns
 * the reference to the removed element. If list or text are not given,
 * function returns NULL.
 *
 * @param list the reference to the list
 * @param text the text of element to remove
 * @return the reference of the removed element or NULL on error
 */
struct element* remove_element(struct list* list, char* text);


/**
 * Function frees the content of the list from memory
 *
 * Function removes all the elements of the list from the memory and also the list structure.
 *
 * @param list the reference to the list
 */
void free_list(struct list* list);


/**
 * Function frees the element from the memory
 *
 * @param element the reference to the element
 */
void free_element(struct element* element);
#endif
