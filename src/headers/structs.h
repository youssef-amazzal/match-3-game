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
        if (head != nullptr) {
            Node* current = head;
            do {
                Node* next = current->next;
                delete current;
                current = next;
            } while (current != head);
        }
    }

    void push_back(const T& data) {
        Node* node = new Node(data);

        if (head == nullptr) {
            head = node;
            node->next = node;
        } else {
            Node* last = back();

            node->next = head;
            last->next = node;
        }

        count++;
    }

    void push_front(const T& data) {
        Node* node = new Node(data);

        if (head == nullptr) {
            head = node;
            node->next = node;
        } else {
            Node* last = back();

            node->next = head;
            head = node;
            last->next = head;
        }

        count++;
    }

    void pop_back() {
        if (count == 0) return;

        Node* last = back();
        if (head == last) {
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next != last) {
                current = current->next;
            }
            current->next = head;
        }
        delete last;

        count--;
    }

    void pop_front() {
        if (count == 0) return;

        Node* last = back();
        if (head == last) {
            head = nullptr;
        } else {
            head = head->next;
            last->next = head;
        }

        count--;
    }

    int size() {
        return count;
    }

//    Node* get(int index) {
//        if (index < 0 || index >= count) return nullptr;
//
//        Node* current = head;
//        for (int i = 0; i < index; i++) {
//            current = current->next;
//        }
//
//        return current;
//    }

    void remove(const T& data) {
        if (head == nullptr) return;

        Node* current = head;
        Node* prev = nullptr;
        do {
            if (current->data == data) {
                if (prev == nullptr) {
                    if (current->next == head) { // Check if head is the only node in the list
                        head = nullptr;
                    } else {
                        head = current->next;
                    }
                } else {
                    prev->next = current->next;
                }
                delete current;
                count--;
                return;
            }

            prev = current;
            current = current->next;
        } while (current != head);
    }

    Node* front() {
        return head;
    }

    Node* back() {
        if (head == nullptr) return nullptr;

        Node* current = head;
        while (current->next != head) {
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
    int count;

public:
    DoubleLinkedList() : head(nullptr), count(0) {}

    ~DoubleLinkedList() {
        if (head != nullptr) {
            Node* current = head;
            do {
                Node* next = current->next;
                delete current;
                current = next;
            } while (current != head);
        }
    }

    void push_back(const T& data) {
        Node* node = new Node(data);

        if (head == nullptr) {
            head = node;
            node->next = node->prev = node;
        } else {
            Node* last = head->prev;

            node->next = head;
            node->prev = last;

            last->next = head->prev = node;
        }

        count++;
    }

    void push_front(const T& data) {
        push_back(data);
        head = head->prev;
    }

    void pop_back() {
        if (count == 0) return;

        Node* last = head->prev;
        if (head == last) {
            head = nullptr;
        } else {
            head->prev = last->prev;
            last->prev->next = head;
        }
        delete last;

        count--;
    }

    void pop_front() {
        if (count == 0) return;

        Node* next = head->next;
        if (head == next) {
            next = nullptr;
        } else {
            next->prev = head->prev;
            head->prev->next = next;
        }
        delete head;
        head = next;

        count--;
    }


    int size() {
        return count;
    }

//    Node* get(int index) {
//        if (index < 0 || index >= count) return nullptr;
//
//        Node* current = head;
//        for (int i = 0; i < index; i++) {
//            current = current->next;
//        }
//
//        return current;
//    }

    void remove(const T& data) {
        if (head == nullptr) return;

        Node* current = head;
        do {
            if (current->data == data) {
                if (current == head) {
                    if (current->next == head) { // Check if head is the only node in the list
                        head = nullptr;
                    } else {
                        head = current->next;
                    }
                }

                if (head != nullptr) { // Only update links if head is not null
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                count--;
                return;
            }

            current = current->next;
        } while (current != head);
    }

    Node* front() {
        return head;
    }

    Node* back() {
        return head ? head->prev : nullptr;
    }

    void shiftLeft() {
        if (head) head = head->next;
    }
};


