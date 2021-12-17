#include "TicketsDeck.h"
#include <random>
#include <set>
#include <pthread.h>
#include <semaphore.h>


// ����� ��� �������������� � ��������.
class TicketsDeckImpl
{
public:
    // �����������.
    explicit TicketsDeckImpl(int size)
        : rnd{std::random_device{}()}
        , mutex(PTHREAD_MUTEX_INITIALIZER)
        , sem{}
    {
        for (int i = 0; i < size; ++i)
            tickets.insert(i + 1);
        sem_init(&sem, 0, size);
    }

    // ���������� �������.
    int count() const
    {
        return static_cast<int>(tickets.size());
    }

    // ��������� ������.
    int get()
    {
        sem_wait(&sem);
        pthread_mutex_lock(&mutex);
        std::uniform_int_distribution<int> dist(1u, count());
        auto ticket = dist(rnd);
        tickets.erase(ticket);
        pthread_mutex_unlock(&mutex);
        return ticket;
    }

    // ������ ������.
    void put(int n)
    {
        pthread_mutex_lock(&mutex);
        tickets.insert(n);
        sem_post(&sem);
        pthread_mutex_unlock(&mutex);
    }

private:
    std::set<int> tickets;
    std::default_random_engine rnd;
    // ������������� ������� � ��������.
    pthread_mutex_t mutex;
    sem_t sem;
};

// ���������� ������������.
TicketsDeck::TicketsDeck(int size)
    : impl{new TicketsDeckImpl{size}}
{}

// ���������� �����������.
TicketsDeck::~TicketsDeck()
{
    delete impl;
}

// ���������� ��������� ������.
int TicketsDeck::get()
{
    return impl->get();
}

// ���������� ������ ������.
void TicketsDeck::put(int ticket)
{
    impl->put(ticket);
}
