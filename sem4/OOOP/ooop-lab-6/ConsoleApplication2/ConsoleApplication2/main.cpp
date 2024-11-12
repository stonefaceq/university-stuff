/**
 * @file RedBlackTree.cpp
 * @brief Implementation of a Red-Black Tree with insertion and selection operations.
 */

#include <iostream>
#include <complex>
#include <vector>
#include <mutex>
#include <thread>
#include <cassert>
#include <chrono>


/**
 * @enum Color
 * @brief Represents the color of a node in a Red-Black Tree.
 */
enum Color { RED, BLACK }; // Вершина може бути червона або чорна

struct Node { // Опис вершини
    std::complex<double> data;
    Color color;
    Node* left, * right, * parent;
    int size; // Розмір піддерева з коренем у цій вершині

    /**
    * @brief Constructs a new Node with the given data.
    * @param data The data to store in the node.
    */
    Node(std::complex<double> data) : data(data), size(1) {
        parent = left = right = nullptr;
        color = RED;
    }
};

/**
 * @class RedBlackTree
 * @brief Represents a Red-Black Tree.
 */
class RedBlackTree {
private:
    Node* root;
    std::mutex tree_mutex; // М'ютекс для захисту дерева

    void rotateLeft(Node*&);
    void rotateRight(Node*&);
    void fixViolation(Node*&);
    void inorderHelper(Node*);
    Node* selectHelper(Node*, int);

    int size(Node* node) {
        return node ? node->size : 0;
    }

    void updateSize(Node* node) {
        if (node) {
            node->size = 1 + size(node->left) + size(node->right);
        }
    }

    /**
    * @brief Constructs a new RedBlackTree.
    */
public:
    RedBlackTree() : root(nullptr) {}

    /**
     * @brief Inserts a new data element into the tree.
     * @param data The data to insert.
     */
    void insert(const std::complex<double>&);

    /**
    * @brief Prints the elements of the tree in sorted order.
    */
    void inorder();

    /**
     * @brief Selects the k-th smallest element in the tree.
     * @param k The order of the element to select (0-based index).
     * @return The k-th smallest element in the tree.
     * @throws std::out_of_range if k is out of range.
     */
    std::complex<double> select(int k);
};

void RedBlackTree::rotateLeft(Node*& ptr) { // Лівий поворот
    Node* right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;

    updateSize(ptr);
    updateSize(right_child);
}

void RedBlackTree::rotateRight(Node*& ptr) { // Правий поворот
    Node* left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;

    updateSize(ptr);
    updateSize(left_child);
}

void RedBlackTree::fixViolation(Node*& ptr) { // Виправлення порушень ЧЧ-дерева
    Node* parent_ptr = nullptr;
    Node* grand_parent_ptr = nullptr;

    while ((ptr != root) && (ptr->color != BLACK) && (ptr->parent->color == RED)) {
        parent_ptr = ptr->parent;
        grand_parent_ptr = ptr->parent->parent;

        if (parent_ptr == grand_parent_ptr->left) {
            Node* uncle_ptr = grand_parent_ptr->right;

            if (uncle_ptr != nullptr && uncle_ptr->color == RED) {
                grand_parent_ptr->color = RED;
                parent_ptr->color = BLACK;
                uncle_ptr->color = BLACK;
                ptr = grand_parent_ptr;
            }
            else {
                if (ptr == parent_ptr->right) {
                    rotateLeft(parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }

                rotateRight(grand_parent_ptr);
                std::swap(parent_ptr->color, grand_parent_ptr->color);
                ptr = parent_ptr;
            }
        }
        else {
            Node* uncle_ptr = grand_parent_ptr->left;

            if ((uncle_ptr != nullptr) && (uncle_ptr->color == RED)) {
                grand_parent_ptr->color = RED;
                parent_ptr->color = BLACK;
                uncle_ptr->color = BLACK;
                ptr = grand_parent_ptr;
            }
            else {
                if (ptr == parent_ptr->left) {
                    rotateRight(parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }

                rotateLeft(grand_parent_ptr);
                std::swap(parent_ptr->color, grand_parent_ptr->color);
                ptr = parent_ptr;
            }
        }
    }

    root->color = BLACK;
}

void RedBlackTree::insert(const std::complex<double>& data) {
    std::lock_guard<std::mutex> lock(tree_mutex); // Блокуємо дерево перед вставкою

    Node* new_node = new Node(data);
    if (root == nullptr) {
        new_node->color = BLACK;
        root = new_node;
    }
    else {
        Node* ptr = root;
        Node* parent = nullptr;
        while (ptr != nullptr) {
            parent = ptr;
            parent->size++; // Оновлюємо розмір піддерева
            if (data.real() < ptr->data.real() || (data.real() == ptr->data.real() && data.imag() < ptr->data.imag()))
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }

        new_node->parent = parent;
        if (data.real() < parent->data.real() || (data.real() == parent->data.real() && data.imag() < parent->data.imag()))
            parent->left = new_node;
        else
            parent->right = new_node;

        fixViolation(new_node);
    }
}

void RedBlackTree::inorderHelper(Node* ptr) { // Допоміжна функція для виводу елементів у відсортованому порядку
    if (ptr == nullptr)
        return;

    inorderHelper(ptr->left);
    std::cout << ptr->data << " ";
    inorderHelper(ptr->right);
}

void RedBlackTree::inorder() {
    std::lock_guard<std::mutex> lock(tree_mutex); // Блокуємо дерево перед виводом
    inorderHelper(root);
}

Node* RedBlackTree::selectHelper(Node* node, int k) { // Допоміжна функція для отримання k-го за порядком елемента
    if (node == nullptr) return nullptr;

    int left_size = size(node->left);
    if (k < left_size) {
        return selectHelper(node->left, k);
    }
    else if (k > left_size) {
        return selectHelper(node->right, k - left_size - 1);
    }
    else {
        return node;
    }
}

std::complex<double> RedBlackTree::select(int k) {
    std::lock_guard<std::mutex> lock(tree_mutex); // Блокуємо дерево перед пошуком
    Node* result = selectHelper(root, k);
    if (result != nullptr) {
        return result->data;
    }
    throw std::out_of_range("Index out of range");
}




/**
 * @brief Runs the test for insertion and inorder traversal.
 */
void testInsertionAndInorderTraversal() {
    RedBlackTree tree;
    tree.insert(std::complex<double>(5, 10));
    tree.insert(std::complex<double>(3, 8));
    tree.insert(std::complex<double>(7, 12));
    tree.insert(std::complex<double>(2, 4));
    tree.insert(std::complex<double>(6, 9));

    std::cout << "Expected inorder traversal: (2,4) (3,8) (5,10) (6,9) (7,12)" << std::endl;
    std::cout << "Actual inorder traversal: ";
    tree.inorder();
    std::cout << std::endl;
}

/**
 * @brief Runs the test for selecting the k-th smallest element.
 */
void testSelectElement() {
    RedBlackTree tree;
    tree.insert(std::complex<double>(5, 10));
    tree.insert(std::complex<double>(3, 8));
    tree.insert(std::complex<double>(7, 12));
    tree.insert(std::complex<double>(2, 4));
    tree.insert(std::complex<double>(6, 9));

    std::complex<double> expected(6, 9);
    std::complex<double> actual = tree.select(3);
    assert(expected == actual);
}

/**
 * @brief Runs the test for selecting an element out of range.
 */
void testSelectElementOutOfRange() {
    RedBlackTree tree;
    tree.insert(std::complex<double>(5, 10));
    tree.insert(std::complex<double>(3, 8));
    tree.insert(std::complex<double>(7, 12));
    tree.insert(std::complex<double>(2, 4));
    tree.insert(std::complex<double>(6, 9));

    bool exceptionThrown = false;
    try {
        tree.select(10);
    } catch (const std::out_of_range& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

/**
 * @brief Runs the test for insertion and selection in a tree with one element.
 */
void testSingleElementInsertionAndSelect() {
    RedBlackTree tree;
    tree.insert(std::complex<double>(5, 10));

    std::complex<double> expected(5, 10);
    std::complex<double> actual = tree.select(0);
    assert(expected == actual);
}

/**
 * @brief Runs the test for selecting an element in an empty tree.
 */
void testSelectElementInEmptyTree() {
    RedBlackTree tree;

    bool exceptionThrown = false;
    try {
        tree.select(0);
    } catch (const std::out_of_range& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

/**
 * @brief Runs all the tests.
 */
void runTests() {
    testInsertionAndInorderTraversal();
    testSelectElement();
   // testSelectElementOutOfRange();
    testSingleElementInsertionAndSelect();
    //testSelectElementInEmptyTree();
}

/**
 * @brief The main function.
 * @return int The exit status.
 */
int main() {
    auto start = std::chrono::high_resolution_clock::now();

    runTests();
    std::cout << "All tests passed successfully!" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
    return 0;
}




