#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Lista duplamente encadeada

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void displayList(Node*);
void insertAfter(Node*, int);
void insertBefore(Node*, int);
void deleteNode(Node**, Node*);
Node* searchNodebyValue(Node**, int);
void deleteNodebyValue(Node**, int);

int main()
{
    cout << "------------ LISTA DUPLAMENTE ENCADEADA ------------" << endl;

    Node* head = nullptr;
    Node* emptyHead = nullptr;
    cout << "Testando função displayList: " << endl;
    cout << "Lista vazia -> ";
    displayList(emptyHead);
    cout << "Lista não vazia -> ";
    displayList(head);
    cout << "-----------------------------------------------------" << endl;

    cout << "Testanto função insertEnd:" << endl;
    insertEnd(&head, 0);
    insertEnd(&head, 1);
    insertEnd(&head, 3);
    insertEnd(&head, 7);
    displayList(head);
    cout << "-----------------------------------------------------" << endl;
    cout << "Testando função insertFront:" << endl;
    insertFront(&head, 10);
    insertFront(&head, 13);
    insertFront(&head, 24);
    insertFront(&head, 42);
    displayList(head);
    cout << "-----------------------------------------------------" << endl;

    cout << "Testanto função deleteNode:" << endl;
    Node* remove = head;
    int iRemovePayload = 13;
    /*
    while (remove->iPayload != iRemovePayload || remove->ptrNext != nullptr) remove = remove->ptrNext;

    if (remove->ptrNext == nullptr && remove->iPayload == iRemovePayload)
    {

    }
    */
    cout << "-----------------------------------------------------" << endl;

    cout << "Testanto função searchNodebyValue:" << endl;
    Node* temp = searchNodebyValue(&head, 13);
    displayList(head);
    cout << "Endereço do Node: " << temp << endl;   
    cout << "-----------------------------------------------------" << endl;

    cout << "Testanto função deleteNodebyValue:" << endl;
    deleteNodebyValue(&head, 42); // Deletando nó do início da lista
    cout << "Deletando o 42 -> ";
    displayList(head);
    deleteNodebyValue(&head, 10); // Deletando nó do meio da lista
    cout << "Deletando o 10 -> ";
    displayList(head);
    deleteNodebyValue(&head, 7); // Deletando nó do fim da lista
    cout << "Deletando o 7 -> ";
    displayList(head);
    cout << "-----------------------------------------------------" << endl;
}

Node* createNode(int iPayload)
{
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->iPayload = iPayload;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;

    return temp;
}

void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: Não é possível realizar displayList" << endl;
        return;
    }

    if (node->ptrPrev != nullptr)
    {
        cout << "Meio ou Fim da Lista: Não é possível realizar displayList" << endl; //Meio é qualquer nó que não esteja no começo ou no fim
        return;
    }

    Node* temp = node;

    cout << "Payload: ";

    //Percorremos a lista até seu fim (ptrNext do último nó é NULL)
    while (temp != nullptr)
    {
        cout << temp->iPayload << " ";
        temp = temp->ptrNext;
    }
    
    cout << endl; 
}

void insertFront(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
    
    if (*head != nullptr)
    {
        // newNode->ptrPrev = nullptr
        (*head)->ptrPrev = newNode;
        newNode->ptrNext = (*head);
        (*head) = newNode;
        return;
    }
    (*head) = newNode;
}

void insertEnd(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);

    if (*head == nullptr)
    {
        (*head) = newNode; // Entre parênteses pq estamos derreferenciando um ponteiro (Pinho gosta de escrever assim)
        return;
    }

    Node* temp = (*head);

    //Percorremos a lista até seu fim (ptrNext do último nó é NULL)
    while (temp->ptrNext != nullptr) temp = temp->ptrNext;

    newNode->ptrPrev =  temp; //newNode aponta para o fim da lista
    temp->ptrNext = newNode; //Antigo último elemento aponta para o novo nó
}

// Recebe um nó que pode estar em qualquer lugar da lista
void insertAfter(Node* ptrLocation, int iPayLoad)
{
    if (ptrLocation == nullptr)
    {
        cout << "Location é NULL." << endl;
        return;
    }

    Node* newNode = createNode(iPayLoad);

    // Corrigir nó a ser inserido
    newNode->ptrNext = ptrLocation->ptrNext;
    newNode->ptrPrev = ptrLocation;

    // Corrigir o ponto de inserção
    ptrLocation->ptrNext = newNode;

    if (newNode->ptrNext == nullptr) newNode->ptrNext->ptrPrev=newNode;
}

void insertBefore(Node* ptrLocation, int iPayload)
{
    
}

void deleteNode(Node** head, Node* ptrDelete)
{
    if (*head == nullptr || ptrDelete == nullptr)
    {
        cout << "Não foi possível remover." << endl;
        return;
    }

    // Caso o ptrDelete seja o primeiro elemento da lista
    if (*head == ptrDelete) (*head) = ptrDelete->ptrNext;

    // Se o ptrDelete não é o primeiro nó
    if (ptrDelete->ptrNext != nullptr) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;

    // Se o ptrDelete não é o primeiro nó
    if (ptrDelete->ptrPrev != nullptr) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;

    free(ptrDelete);
}

Node* searchNodebyValue(Node** head, int iPayload)
{
    if (*head == nullptr)
    {
        cout << "Lista vazia. Impossível achar nó correspondente ao valor passado." << endl;
        return *head;
    }

    Node* temp = (*head);

    while (temp->ptrNext != nullptr && temp->iPayload != iPayload) temp = temp->ptrNext;

    if (temp->ptrNext == nullptr && temp->iPayload != iPayload)
    {
        cout << "Valor de nó não existente na Lista." << endl;
        return *head ;
    }

    return temp;
}

void deleteNodebyValue(Node** head, int iPayload)
{
    Node* temp = searchNodebyValue(head, iPayload);

    deleteNode(head, temp);

    return;
}

/* Exercícios para entregar ao monitor

Exercício 1: Elaborar a função void insertBefore(Node*, int);

Exercício 2: Elaborar a função void deleteNodebyValue(Node**, int);

Exercício 3: Elaborar a função Node* searchNodebyValue(Node**, int);

*/