#include "TicketsDeck.h"
#include <random>
#include <set>
#include <pthread.h>
#include <semaphore.h>


// Класс для взаимодействия с билетами.
class TicketsDeckImpl
{
public:
    // Констурктор.
    explicit TicketsDeckImpl(int size)
        : rnd{std::random_device{}()}
        , mutex(PTHREAD_MUTEX_INITIALIZER)
        , sem{}
    {
        for (int i = 0; i < size; ++i)
            tickets.insert(i + 1);
        sem_init(&sem, 0, size);
    }

    // Количество билетов.
    int count() const
    {
        return static_cast<int>(tickets.size());
    }

    // Получение билета.
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

    // Отдача билета.
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
    // Использование мютекса и семафора.
    pthread_mutex_t mutex;
    sem_t sem;
};

// Реализация конструктора.
TicketsDeck::TicketsDeck(int size)
    : impl{new TicketsDeckImpl{size}}
{}

// Реализация деструктора.
TicketsDeck::~TicketsDeck()
{
    delete impl;
}

// Реализация получения билета.
int TicketsDeck::get()
{
    return impl->get();
}

// Реализация отдачи билета.
void TicketsDeck::put(int ticket)
{
    impl->put(ticket);
}
