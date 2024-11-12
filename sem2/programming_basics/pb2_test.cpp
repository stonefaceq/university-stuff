#include <iostream>
using namespace std;


// в мене варіант 1. зробив 3 обов'язкові завдання та 1 з зірочкою (але його не завершив, бо поспішав через справи, прошу вибачити).
// скидаю тільки функції, як просили, мейну тут немає, тому можливо задля перевірки треба буде ще мейн для кожної. 
// я все писав у 1 файлі, тому вони в мене не збереглись, але якщо вам треба буде -- сповістіть, я напишу мейни заново і скину вам окремими файлами з функціями.
// також через поспішання тут майже немає коментів (якби був час я б розписав детальніше), тому також вибачаюсь, якщо важко читається. 
// ____________________________________ TASK 1.1
struct Node1 {
    int data;
    Node1* next;
};


void rearrangeList(Node1** head) {
    if (*head == nullptr)
        return;

    Node1* negativeHead = NULL;  
    Node1* negativeTail = NULL;  
    Node1* positiveHead = NULL;  
    Node1* positiveTail = NULL;  

    Node1* curr = *head;
    while (curr->next) {
        Node1* nextNode = curr->next;  

        if (curr->data < 0) {
            
            if (negativeHead == NULL) {
                
                negativeHead = curr;
                negativeTail = curr;
                negativeTail->next = NULL;
            }
            else {
                
                negativeTail->next = curr;
                negativeTail = curr;
                negativeTail->next = NULL;
            }
        }
        else {
           
            if (positiveHead == NULL) {
               
                positiveHead = curr;
                positiveTail = curr;
                positiveTail->next = NULL;
            }
            else {
                
                positiveTail->next = curr;
                positiveTail = curr;
                positiveTail->next = NULL;
            }
        }

        curr = nextNode;  
    } 

    if (negativeHead != NULL) {
        
        negativeTail->next = positiveHead;
        *head = negativeHead;
    }
}


Node1* createNode(int data) {
    Node1* newNode = new Node1;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void printList(Node1* head) {
    if (head == NULL)
        return;

    Node1* curr = head;
    while (true) {
        cout << curr->data << " ";
        curr = curr->next;
        if (curr == NULL) {
            break;
        }
    }
        
     

    cout << endl;
}

// ________________________________ TASK 2.1

struct Node2 {
    int data;
    Node2* left;
    Node2* right;
};

Node2* createNode2(int data) {
    Node2* newNode = new Node2;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node2* insertNode(Node2* root, int data) {
    if (root == NULL) {
        root = createNode2(data);
    }
    else if (data <= root->data) {
        root->left = insertNode(root->left, data);
    }
    else {
        root->right = insertNode(root->right, data);
    }
    return root;
}


void postorderTraversal(Node2* root) {
    if (root == NULL)
        return;

    const int MAX_NODES = 1000;
    Node2* stack[MAX_NODES];
    int top = -1;

    Node2* curr = root;
    Node2* lastVisitedNode = NULL;

    while (curr != NULL || top != -1) {
        if (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        else {
            Node2* peekNode = stack[top];


            if (peekNode->right != NULL && lastVisitedNode != peekNode->right) {
                curr = peekNode->right;
            }
            else {
                cout << peekNode->data << " ";
                lastVisitedNode = peekNode;
                top--;
            }
        }
    }
}

// _____________________________ TASK 3.1 

const int MAX_VERTICES = 100;

void findReachableVertices(int adjacencyMatrix[][MAX_VERTICES], int numVertices, int startVertex) {
    bool visited[MAX_VERTICES] = { false };
    int stack[MAX_VERTICES];
    int top = -1;

    stack[++top] = startVertex;
    visited[startVertex] = true;

    std::cout << "Reachable vertices: " << startVertex << ": ";

    while (top != -1) {
        int currVertex = stack[top--];

        std::cout << currVertex << " ";

        for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
            if (adjacencyMatrix[currVertex][neighbor] == 1 && !visited[neighbor]) {
                stack[++top] = neighbor;
                visited[neighbor] = true;
            }
        }
    }

    cout << endl;
}

//_______________________TASK 4.4 -- на жаль, не працює, не завершив((( 

const int MAX_EXPRESSION_LENGTH = 100;
bool isOperator(char c) {
    return (c == '+' || c == '*');
}


int performOperation(char op, int operand1, int operand2) {
    if (op == '+') {
        return operand1 + operand2;
    }
    else if (op == '*') {
        return operand1 * operand2;
    }
    return 0;
}


int evaluateExpression(const char* expression) {
    int result = 0;
    int stack[100];
    int top = -1;

    for (int i = 0; expression[i] != '\0'; ++i) {
        char currentChar = expression[i];

        if (isdigit(currentChar)) {
            int operand = currentChar - '0';
            stack[++top] = operand;
        }
        else if (isOperator(currentChar)) {
            int operand2 = stack[top--];
            int operand1 = stack[top--];
            int operationResult = performOperation(currentChar, operand1, operand2);
            stack[++top] = operationResult;
        }
    }

    result = stack[top--];

    return result;
}

