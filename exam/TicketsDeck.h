#ifndef EXAM_TICKETS_DECK_H
#define EXAM_TICKETS_DECK_H


// �����, ����������� ������ �������.
class TicketsDeckImpl;
class TicketsDeck
{
public:
    // �����������.
    explicit TicketsDeck(int size);
    // ����������.
    ~TicketsDeck();

    // ������������ ������ ��� ���������� ������.
    TicketsDeck(const TicketsDeck&) = delete;
    TicketsDeck& operator=(const TicketsDeck&) = delete;

    // ������ �������������� � ��������.
    int get();
    void put(int ticket);

private:
    TicketsDeckImpl* impl;
};


#endif //EXAM_TICKETS_DECK_H
