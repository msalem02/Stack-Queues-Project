// Mohammad Yousef Salem - 1203022 - Section 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1000

// Node for stack and queue
typedef struct Node {
    char word[MAX_TEXT_LENGTH];
    int index;
    char operation;  // 'I' for Insert, 'R' for Remove
    struct Node* next;
} Node;

// Structure for stack
typedef struct {
    Node* top;
} Stack;

// Structure for queue
typedef struct {
    Node* front;
    Node* rear;
} Queue;


// Function Prototypes
void printMenu();
void push(Stack* stack, const char* word, int index, char operation);
Node* pop(Stack* stack);
void enqueue(Queue* queue, const char* word);
Node* dequeue(Queue* queue);
void loadTextFromFile(const char* filename, char* text);
void saveTextToFile(const char* filename, const char* text);
void printText(const char* text);
void insertText(char* text, const char* toInsert, int index);
void removeText(char* text, const char* toRemove);
void undo(Stack* undoStack, Stack* redoStack, char* text);
void redo(Stack* redoStack, Stack* undoStack, char* text);
void printStack(const char* name, Stack* stack);



// Main function and menu
int main() {
    char text[MAX_TEXT_LENGTH] = {0};
    Stack undoStack = {NULL};
    Stack redoStack = {NULL};
    Queue addQueue = {NULL, NULL};

    int choice;
    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline
        switch (choice) {
            case 1:
                loadTextFromFile("C:\\Users\\Tech Zone\\CLionProjects\\ProjectTwo\\input.txt", text);
                break;
            case 2:
                printText(text);
                break;
            case 3: {
                char insert[MAX_TEXT_LENGTH];
                int index;
                printf("Enter text to insert and index (-1 for end): ");
                fgets(insert, MAX_TEXT_LENGTH, stdin);
                scanf("%d", &index);
                getchar(); // consume newline
                insert[strlen(insert)-1] = '\0'; // remove newline
                insertText(text, insert, index);
                push(&undoStack, insert, index, 'I');
                break;
            }
            case 4: {
                char toRemove[MAX_TEXT_LENGTH];
                printf("Enter text to remove: ");
                fgets(toRemove, MAX_TEXT_LENGTH, stdin);
                toRemove[strlen(toRemove)-1] = '\0'; // Remove newline
                removeText(text, toRemove);
                push(&undoStack, toRemove, -1, 'R');
                break;
            }
            case 5:
                undo(&undoStack, &redoStack, text);
                break;
            case 6:
                redo(&redoStack, &undoStack, text);
                break;
            case 7:
                printStack("Undo", &undoStack);
                printStack("Redo", &redoStack);
                break;
            case 8:
                saveTextToFile("C:\\Users\\Tech Zone\\CLionProjects\\ProjectTwo\\output.txt", text);
                break;
            case 9:
                return 0;
        }
    } while (choice != 9);

    return 0;
}



// Function to print the menu options
void printMenu() {
    printf("\nMenu:\n");
    printf("1. Load input file\n");
    printf("2. Print loaded text\n");
    printf("3. Insert strings to text\n");
    printf("4. Remove strings from text\n");
    printf("5. Perform Undo operation\n");
    printf("6. Perform Redo operation\n");
    printf("7. Print Undo and Redo stacks\n");
    printf("8. Save updated text to output file\n");
    printf("9. Exit\n");
}


// Function to push an operation onto a stack
void push(Stack* stack, const char* word, int index, char operation) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->index = index;
    newNode->operation = operation;
    newNode->next = stack->top;
    stack->top = newNode;
}


// Function to pop an operation from a stack
Node* pop(Stack* stack) {
    if (stack->top == NULL)
        return NULL;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    temp->next = NULL;
    return temp;
}


// Function to enqueue a word into a queue
void enqueue(Queue* queue, const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}


// Function to dequeue a word from a queue
Node* dequeue(Queue* queue) {
    if (queue->front == NULL) return NULL;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    return temp;
}


// Function to load text from a file
void loadTextFromFile(const char* filename, char* text) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    if (fgets(text, MAX_TEXT_LENGTH, file) != NULL) {
        printf("File read successfully.\n");
    } else {
        printf("Failed to read from file.\n");
    }
    fclose(file);
}


// Function to save text to a file
void saveTextToFile(const char* filename, const char* text) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    if (fputs(text, file) != EOF) {
        printf("File saved successfully.\n");
    } else {
        printf("Failed to save to file.\n");
    }
    fclose(file);
}


// Function to print the text
void printText(const char* text) {
    if (text[0] == '\0') {
        printf("No text to display.\n");
    } else {
        printf("Current text:\n%s\n", text);
    }
}


// Function to insert a string into text at a specific index
void insertText(char* text, const char* toInsert, int index) {
    int insertLength = strlen(toInsert) + 1; // +1 for the space
    if (index < 0)
        index = strlen(text); // Append to the end if index is -1

    // Check if adding the new text exceeds buffer limits
    if (index + insertLength >= MAX_TEXT_LENGTH - strlen(text)) {
        printf("Insertion exceeds maximum text length!\n");
        return;
    }

    char buffer[MAX_TEXT_LENGTH] = {0};
    strncpy(buffer, text, index);
    strcat(buffer, toInsert);
    strcat(buffer, " "); // Add space after the inserted text
    strcat(buffer, text + index);
    strcpy(text, buffer);
}


// Function to remove the first occurrence of a specified string from text
void removeText(char* text, const char* toRemove) {
    char* start = strstr(text, toRemove); // Find the start of the substring to remove
    if (start == NULL) {
        printf("String not found!\n");
        return; // Return if the string is not found
    }

    int length = strlen(toRemove);
    char* end = start + length; // Calculate the end of the substring to remove

    // Shift the rest of the text over the part to remove
    while (*end) {
        *start++ = *end++;
    }
    *start = '\0'; // Null-terminate the modified string
}


// Function to handle undo and redo logic
void undo(Stack* undoStack, Stack* redoStack, char* text) {
    Node* operation = pop(undoStack);
    if (operation == NULL)
        return;

    // Push to redo stack before undoing the change
    push(redoStack, operation->word, operation->index, operation->operation == 'I' ? 'R' : 'I');

    // Undo the change in text
    if (operation->operation == 'I') {
        // Undo insert: remove the word
        removeText(text, operation->word);
    } else {
        // Undo remove: insert the word
        insertText(text, operation->word, operation->index);
    }

    free(operation);
}


void redo(Stack* redoStack, Stack* undoStack, char* text) {
    Node* operation = pop(redoStack);
    if (operation == NULL) return;

    // Push to undo stack before redoing the change
    push(undoStack, operation->word, operation->index, operation->operation);

    // Redo the change in text
    if (operation->operation == 'I') {
        // Redo insert: insert the word
        insertText(text, operation->word, operation->index);
    } else {
        // Redo remove: remove the word
        removeText(text, operation->word);
    }

    free(operation);
}


// Function to print the contents of a stack
void printStack(const char* name, Stack* stack) {
    printf("%s Stack:\n", name);
    Node* current = stack->top;
    if (current == NULL) {
        printf("  [Empty]\n");
    } else {
        while (current != NULL) {
            printf("  Word: '%s', Index: %d, Operation: '%c'\n", current->word, current->index, current->operation);
            current = current->next;
        }
    }
}
