#ifndef EXAM_TICKETS_DECK_H
#define EXAM_TICKETS_DECK_H


// Класс, реализующий стопку билетов.
class TicketsDeckImpl;
class TicketsDeck
{
public:
    // Конструктор.
    explicit TicketsDeck(int size);
    // Деструктор.
    ~TicketsDeck();

    // Опциональные методы для корректной работы.
    TicketsDeck(const TicketsDeck&) = delete;
    TicketsDeck& operator=(const TicketsDeck&) = delete;

    // Методы взаимодействия с билетами.
    int get();
    void put(int ticket);

private:
    TicketsDeckImpl* impl;
};


#endif //EXAM_TICKETS_DECK_H
