#pragma once

template <typename T>
struct SingleLinkedList {

private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;
    int count;

public:
    SingleLinkedList() : head(nullptr), count(0) {}

    ~SingleLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(const T& data) {
        Node* node = new Node(data);
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

        count++;
    }

    void push_front(const T& data) {
        Node* node = new Node(data);
        node->next = head;
        head = node;
        count++;
    }

    void pop_back() {
        if (count == 0) return;

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

        count--;
    }

    void pop_front() {
        if (count == 0) return;

        Node* node = head;
        head = head->next;
        delete node;
        count--;
    }

    void insert(int index, const T& data) {
        if (index < 0 || index > count) return;

        if (index == 0) {
            push_front(data);
        } else if (index == count) {
            push_back(data);
        } else {
            Node* node = new Node(data);

            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            node->next = current->next;
            current->next = node;

            count++;
        }
    }

    int size() {
        return count;
    }

    Node* get(int index) {
        if (index < 0 || index >= count) return nullptr;

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current;
    }

    void remove(int index) {
        if (index < 0 || index >= count) return;

        if (index == 0) {
            pop_front();
        } else {
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            Node* node = current->next;
            current->next = node->next;
            delete node;

            count--;
        }
    }

    Node* front() {
        return head;
    }

    Node* back() {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current;
    }
};


template <typename T>
struct DoubleLinkedList {

private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        explicit Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoubleLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(const T& data) {
        Node* node = new Node(data);
        node->next = nullptr;
        node->prev = tail;

        if (head == nullptr) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;

        count++;
    }

    void push_front(const T& data) {
        Node* node = new Node(data);
        node->next = head;
        node->prev = nullptr;

        if (head != nullptr) {
            head->prev = node;
        }
        head = node;
        if (tail == nullptr) {
            tail = node;
        }

        count++;
    }

    void pop_back() {
        if (count == 0) return;

        Node* node = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete node;

        count--;
    }

    void pop_front() {
        if (count == 0) return;

        Node* node = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete node;

        count--;
    }

    void insert(int index, const T& data) {
        if (index < 0 || index > count) return;

        if (index == 0) {
            push_front(data);
        } else if (index == count) {
            push_back(data);
        } else {
            Node* node = new Node(data);

            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            node->next = current;
            node->prev = current->prev;
            current->prev->next = node;
            current->prev = node;

            count++;
        }
    }

    int size() {
        return count;
    }

    Node* get(int index) {
        if (index < 0 || index >= count) return nullptr;

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current;
    }

    void remove(int index) {
        if (index < 0 || index >= count) return;

        if (index == 0) {
            pop_front();
        } else if (index == count - 1) {
            pop_back();
        } else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;

            count--;
        }
    }

    Node* front() {
        return head;
    }

    Node* back() {
        return tail;
    }

    void shiftLeft() {
        if (head && head->next) head = head->next;
    }
};


