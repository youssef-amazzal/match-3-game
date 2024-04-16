#pragma once

template <typename T>
struct SingleLinkedList {

private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
    int size;

public:
    SingleLinkedList() : head(nullptr), size(0) {}

    ~SingleLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(T data) {
        Node* node = new Node();
        node->data = data;
        node->next = nullptr;

        if (head == nullptr) {
            head = node;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = node;
        }

        size++;
    }

    void push_front(T data) {
        Node* node = new Node();
        node->data = data;
        node->next = head;
        head = node;
        size++;
    }

    void pop_back() {
        if (size == 0) return;

        Node* current = head;
        Node* prev = nullptr;
        while (current->next != nullptr) {
            prev = current;
            current = current->next;
        }
        delete current;
        if (prev != nullptr) {
            prev->next = nullptr;
        } else {
            head = nullptr;
        }

        size--;
    }

    void pop_front() {
        if (size == 0) return;

        Node* node = head;
        head = head->next;
        delete node;
        size--;
    }

    void insert(int index, T data) {
        if (index < 0 || index > size) return;

        if (index == 0) {
            push_front(data);
        } else if (index == size) {
            push_back(data);
        } else {
            Node* node = new Node();
            node->data = data;

            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            node->next = current->next;
            current->next = node;

            size++;
        }
    }



    int getSize() {
        return size;
    }
};


template <typename T>
struct DoubleLinkedList {

private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoubleLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(T data) {
        Node* node = new Node();
        node->data = data;
        node->next = nullptr;
        node->prev = tail;

        if (head == nullptr) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;

        size++;
    }

    void push_front(T data) {
        Node* node = new Node();
        node->data = data;
        node->next = head;
        node->prev = nullptr;

        if (head != nullptr) {
            head->prev = node;
        }
        head = node;
        if (tail == nullptr) {
            tail = node;
        }

        size++;
    }

    void pop_back() {
        if (size == 0) return;

        Node* node = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete node;

        size--;
    }

    void pop_front() {
        if (size == 0) return;

        Node* node = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete node;

        size--;
    }

    void insert(int index, T data) {
        if (index < 0 || index > size) return;

        if (index == 0) {
            push_front(data);
        } else if (index == size) {
            push_back(data);
        } else {
            Node* node = new Node();
            node->data = data;

            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            node->next = current;
            node->prev = current->prev;
            current->prev->next = node;
            current->prev = node;

            size++;
        }
    }

    int getSize() {
        return size;
    }
};


