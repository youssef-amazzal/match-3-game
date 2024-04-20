#pragma once

#include "Gem.h"

struct GemList {


    struct Node {
        Gem gem;
        Node *next = nullptr;

        Node *nextColor = nullptr;
        Node *prevColor = nullptr;

        Node *nextShape = nullptr;
        Node *prevShape = nullptr;

        explicit Node(const Gem &data) :
                gem(data), next(nullptr),
                nextColor(nullptr), prevColor(nullptr),
                nextShape(nullptr), prevShape(nullptr)
        {}

    };

    Node* head = nullptr;
    Node* tail = nullptr;

    std::unordered_map <V_COLORS , Node*> colorHeads;
    std::unordered_map <V_SHAPES , Node*> shapeHeads;
    std::unordered_map <V_COLORS,  Node*> colorTails;
    std::unordered_map <V_SHAPES,  Node*> shapeTails;

    int count = 0;

    GemList() = default;
    ~GemList() {
        while (head != nullptr) {
            pop_front();
        }
    }

    int size() const {
        return count;
    }

    Node* front() {
        return head;
    }

    Node* back() {
        return tail;
    }

    void push_front(Gem &data) {
        Node* node = new Node(data);
        Node*& headColor = colorHeads[data.getColor()];
        Node*& headShape = shapeHeads[data.getShape()];
        Node*& tailColor = colorTails[data.getColor()];
        Node*& tailShape = shapeTails[data.getShape()];

        std::cout << "push_front: " << data.toString() << std::endl;

        if (head == nullptr) {
            // setup heads and tails
            head = tail = node;

            headColor = node;
            tailColor = node;

            headShape = node;
            tailShape = node;

            // setup next and prev
            head->next = head;
            tail->next = head;

            node->nextColor = node;
            node->prevColor = node;

            node->nextShape = node;
            node->prevShape = node;

        } else {
            // setup new head
            node->next = head;
            head = node;
            tail->next = head;

            // setup variant's

            // Scenario 1: variant's list is empty
            if (headColor == nullptr) {
                headColor = tailColor = node;
            }
            if (headShape == nullptr) {
                headShape = tailShape = node;
            }

            // Scenario 2: variant's list is not empty
            node->nextColor = headColor;
            node->prevColor = tailColor;
            node->nextShape = headShape;
            node->prevShape = tailShape;

            headColor->prevColor = node;
            tailColor->nextColor = node;
            headShape->prevShape = node;
            tailShape->nextShape = node;

            headColor = node;
            headShape = node;
        }

        count++;
    }

    void push_back(Gem &data) {
        Node* node = new Node(data);
        Node*& headColor = colorHeads[data.getColor()];
        Node*& headShape = shapeHeads[data.getShape()];
        Node*& tailColor = colorTails[data.getColor()];
        Node*& tailShape = shapeTails[data.getShape()];

        std::cout << "push_back: " << data.toString() << std::endl;

        if (head == nullptr) {
            // setup heads and tails
            head = tail = node;

            headColor = node;
            tailColor = node;

            headShape = node;
            tailShape = node;

            // setup next and prev
            head->next = head;
            tail->next = head;

            node->nextColor = node;
            node->prevColor = node;

            node->nextShape = node;
            node->prevShape = node;

        } else {
            // setup new tail
            tail->next = node;
            node->next = head;
            tail = node;

            // setup variant's

            // Scenario 1: variant's list is empty
            if (headColor == nullptr) {
                headColor = tailColor = node;
            }
            if (headShape == nullptr) {
                headShape = tailShape = node;
            }

            // Scenario 2: variant's list is not empty
            node->nextColor = headColor;
            node->prevColor = tailColor;
            node->nextShape = headShape;
            node->prevShape = tailShape;

            headColor->prevColor = node;
            tailColor->nextColor = node;
            headShape->prevShape = node;
            tailShape->nextShape = node;

            tailColor = node;
            tailShape = node;
        }

        count++;
    }

    void pop_front() {
        // no elements
        if (count == 0) return;

        std::cout << "pop_front: " << head->gem.toString() << std::endl;

        // only one element
        if (count == 1) {
            // nullify variant's heads and tails
            colorHeads[head->gem.getColor()] = nullptr;
            colorTails[head->gem.getColor()] = nullptr;

            shapeHeads[head->gem.getShape()] = nullptr;
            shapeTails[head->gem.getShape()] = nullptr;

            // delete main head
            head->gem.destruct();
            delete head;

            // nullify main head and tail
            head = nullptr;
            tail = nullptr;

        } else { // more than one element
            // Get node to delete
            Node *node = head;

            // change main head and tail
            head = head->next;
            tail->next = head;

            // change variant's heads and tails
            colorHeads[node->gem.getColor()] = node->nextColor;
            colorTails[node->gem.getColor()] = node->prevColor;

            shapeHeads[node->gem.getShape()] = node->nextShape;
            shapeTails[node->gem.getShape()] = node->prevShape;

            // link variant's new head and tail
            node->nextColor->prevColor = node->prevColor;
            node->prevColor->nextColor = node->nextColor;

            node->nextShape->prevShape = node->prevShape;
            node->prevShape->nextShape = node->nextShape;

            // delete node
            node->gem.destruct();
            delete node;
        }

        count--;
    }

    void pop_back() {
        // no elements
        if (count == 0) return;

        // find before last element
        Node* last = head;
        while (last->next != tail) {
            last = last->next;
        }

        // only one element
        if (count == 1) {
            // nullify variant's heads and tails
            colorHeads[tail->gem.getColor()] = nullptr;
            colorTails[tail->gem.getColor()] = nullptr;

            shapeHeads[tail->gem.getShape()] = nullptr;
            shapeHeads[tail->gem.getShape()] = nullptr;

            // delete main tail
            tail->gem.destruct();
            delete tail;

            // nullify main head and tail
            head = nullptr;
            tail = nullptr;
        } else { // more than one element
            // change main tail
            tail = last;
            tail->next = head;

            // change variant's heads and tails
            colorHeads[last->gem.getColor()] = last->nextColor;
            colorTails[last->gem.getColor()] = last->prevColor;

            shapeHeads[last->gem.getShape()] = last->nextShape;
            shapeTails[last->gem.getShape()] = last->prevShape;

            // link variant's new head and tail
            last->nextColor->prevColor = last->prevColor;
            last->prevColor->nextColor = last->nextColor;

            last->nextShape->prevShape = last->prevShape;
            last->prevShape->nextShape = last->nextShape;

            // delete node
            last->gem.destruct();
            delete last;
        }

        count--;
    }

    void remove(int index) {
        // no elements
        if (count == 0) return;

        // find the gem's node (warning: infinite loop if gem is not in the list, because of the circular list)
        Node* target = front();
        Node* before = back();

        for (int i = 0; i < index; i++) {
            before = target;
            target = target->next;
        }

        std::cout << "remove: " << target->gem.toString() << std::endl;

        Node*& colorHead = colorHeads[target->gem.getColor()];
        Node*& colorTail = colorTails[target->gem.getColor()];
        Node*& shapeHead = shapeHeads[target->gem.getShape()];
        Node*& shapeTail = shapeTails[target->gem.getShape()];

        // only one element
        if (count == 1) {
            // nullify variant's heads and tails
            colorHead = nullptr;
            colorTail = nullptr;

            shapeHead = nullptr;
            shapeTail = nullptr;

            // delete the only node
            target->gem.destruct();
            delete target;

            // nullify main head and tail
            head = nullptr;
            tail = nullptr;

        } else { // more than one element

            // Scenario 1 : target isn't the only element, but it is the head or tail in the main list
            // change main head and tail
            if (target == head) {
                head = target->next;
            }

            if (target == tail) {
                tail = before;
            }

            // Scenario 2 : target isn't the only element, but it is the head or tail in the variant lists (that one was the hardest to figure out)
            // change variant's head and tail
            if (target == colorHead) {
                colorHead = target->nextColor;
            }

            if (target == colorTail) {
                colorTail = target->prevColor;
            }

            if (target == shapeHead) {
                shapeHead = target->nextShape;
            }

            if (target == shapeTail) {
                shapeTail = target->prevShape;
            }

            // link new heads and tails
            colorHead->prevColor = colorTail;
            colorTail->nextColor = colorHead;

            shapeHead->prevShape = shapeTail;
            shapeTail->nextShape = shapeHead;

            tail->next = head;

            // Scenario 3: target is in the middle of the list
            // link before and after target
            target->prevColor->nextColor = target->nextColor;
            target->nextColor->prevColor = target->prevColor;

            target->prevShape->nextShape = target->nextShape;
            target->nextShape->prevShape = target->prevShape;

            before->next = target->next;

            // Scenario 4: target is the only element in his variant
            // nullify variant's heads and tails
            if (colorHead == colorTail && colorHead == target) {
                colorHead = colorTail = nullptr;
            }

            if (shapeHead == shapeTail && shapeHead == target) {
                shapeHead = shapeTail = nullptr;
            }

            // delete node
            target->gem.destruct();
            delete target;
        }

        count--;
    }

    void shiftColorLeft(V_COLORS color) {
        // get variant's head and tails
        Node*& colorHead = colorHeads[color];
        Node*& colorTail = colorTails[color];

        // store the initial variant head temporary to use it after looping
        V_SHAPES tempShape;
        if (colorHead != nullptr) tempShape = colorHead->gem.getShape();

        Node* current = colorHead;

        if (colorHead != nullptr) {
            std::cout << "shiftColorLeft: " << color << std::endl;

            // loop through the color's list
            do {
                current->gem.setShape(current->nextColor->gem.getShape());
                current = current->nextColor;
            } while (current != colorHead);

            // set the last element's shape to the first element's shape
            colorTail->gem.setShape(tempShape);

            // correct all the shapes in the main list
            correctShapes();
        }
    }

    void shiftShapeLeft(V_SHAPES shape) {
        // get variant's head and tails
        Node*& shapeHead = shapeHeads[shape];
        Node*& shapeTail = shapeTails[shape];

        // store the initial variant head temporary to use it after looping
        V_COLORS tempColor;
        if (shapeHead != nullptr) tempColor = shapeHead->gem.getColor();

        Node* current = shapeHead;

        if (shapeHead != nullptr) {
            std::cout << "shiftShapeLeft: " << shape << std::endl;

            // loop through the shape's list
            do {
                current->gem.setColor(current->nextShape->gem.getColor());
                current = current->nextShape;
            } while (current != shapeHead);

            // set the last element's color to the first element's color
            shapeTail->gem.setColor(tempColor);

            // correct all the colors in the main list
            correctColors();
        }
    }

    void correctShapes() {
        std::cout << "correctShapes" << std::endl;

        // clear all shape lists
        for (auto& [shape, shapeHead] : shapeHeads) {
            shapeHead = nullptr;
        }

        for (auto& [shape, shapeTail] : shapeTails) {
            shapeTail = nullptr;
        }

        // refill shape lists

        Node* current = head;
        do {
            Node*& headShape = shapeHeads[current->gem.getShape()];
            Node*& tailShape = shapeTails[current->gem.getShape()];

            if (headShape == nullptr) {
                headShape = tailShape = current;
                current->nextShape = current;
                current->prevShape = current;
            } else {
                current->nextShape = headShape;
                current->prevShape = tailShape;

                headShape->prevShape = current;
                tailShape->nextShape = current;

                tailShape = current;
            }

            current = current->next;
        } while (current != head);
    }

    void correctColors() {
        std::cout << "correctColors" << std::endl;

        // clear all color lists
        for (auto& [color, colorHead] : colorHeads) {
            colorHead = nullptr;
        }

        for (auto& [color, colorTail] : colorTails) {
            colorTail = nullptr;
        }

        // refill color lists

        Node* current = head;
        do {
            Node*& headColor = colorHeads[current->gem.getColor()];
            Node*& tailColor = colorTails[current->gem.getColor()];

            if (headColor == nullptr) {
                headColor = tailColor = current;
                current->nextColor = current;
                current->prevColor = current;
            } else {
                current->nextColor = headColor;
                current->prevColor = tailColor;

                headColor->prevColor = current;
                tailColor->nextColor = current;

                tailColor = current;
            }

            current = current->next;
        } while (current != head);
    }

    void print() {
        Node* current = head;
        do {
            std::cout << current->gem.toString() << std::endl;
            current = current->next;
        } while (current != head);

        std::cout << "======================" << std::endl;

        for (auto& [color, colorHead] : colorHeads) {
            if (colorHead != nullptr) {
                std::cout << "Color: " << color << std::endl;
                current = colorHead;
                do {
                    std::cout << current->gem.toString() << std::endl;
                    current = current->nextColor;
                } while (current != colorHead);
            }
        }

        std::cout << "======================" << std::endl;

        for (auto& [shape, shapeHead] : shapeHeads) {
            if (shapeHead != nullptr) {
                std::cout << "Shape: " << shape << std::endl;
                current = shapeHead;
                do {
                    std::cout << current->gem.toString() << std::endl;
                    current = current->nextShape;
                } while (current != shapeHead);
            }
        }

        std::cout << "======================" << std::endl;
    }
};