#include "Teacher.h"
#include "TicketsDeck.h"
#include <pthread.h>
#include <fstream>
#include <random>
#include <utility>
#include <unordered_map>


// �����, ���������� ��������� ������.
class GradeGen
{
public:
    GradeGen()
            : rnd{std::random_device{}()}
            , dist{2, 5}
    {}

    int operator()()
    {
        return dist(rnd);
    }

private:
    std::default_random_engine rnd;
    std::uniform_int_distribution<int> dist;
};

// ���������, �������� ���������� �� �������.
struct Record
{
    Record(int g, int t)
        : grade{g}
        , ticketNo{t}
    {}

    int grade;
    int ticketNo;
};

// ���������, ����������� "������ ������".
struct Journal
{
    explicit Journal(std::string  fn)
        : fileName{std::move(fn)}
        , mutex(PTHREAD_MUTEX_INITIALIZER)
    {}

    ~Journal()
    {
        std::ofstream os{fileName};
        if (os)
        {
            for (const auto& [sid, rec]: data)
                os << "Student " << sid << " ticket #" << rec.ticketNo << " grade " << rec.grade << '\n';
        }
    }

    void add(int sid, const Record& rec)
    {
        pthread_mutex_lock(&mutex);
        data.emplace(sid, rec);
        pthread_mutex_unlock(&mutex);
    }

    std::unordered_map<int, Record> data;
    pthread_mutex_t mutex;
    std::string fileName;
};

// ���������, �������� ������ � �������������.
struct TeacherImpl
{
    explicit TeacherImpl(int n, const std::string&  fileName)
        : tickets{n}
        , journal{fileName}
    {}

    TicketsDeck tickets;
    Journal journal;
};

// ���������� ������������.
Teacher::Teacher(int nTickets, const std::string& fileName)
        : impl{new TeacherImpl{nTickets, fileName}}
{
}

// ���������� �����������.
Teacher::~Teacher()
{
    delete impl;
}

// ���������� ������ ������.
int Teacher::giveTicket()
{
    return impl->tickets.get();
}

// ���������� ������ ������.
int Teacher::receiveAnswer(Student* student)
{
    static GradeGen gradeGen;

    auto grade = gradeGen();
    auto ticket = student->ticket();
    impl->journal.add(student->id(), {grade, ticket});
    impl->tickets.put(ticket);
    return grade;
}

