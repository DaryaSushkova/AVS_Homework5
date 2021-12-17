#include "Student.h"
#include "Teacher.h"
#include <pthread.h>
#include <unistd.h>
#include <sstream>


// ��������� ��� �������� ������ ��������.
struct StudentImpl
{
    StudentImpl(Teacher* t, int id)
        : teacher{t}
        , studId{id}
    {}

    Teacher* teacher;
    int studId;
    int ticketNo{};
    pthread_t tid{};
};

// ���������� ������������.
Student::Student(int id, Teacher* teacher)
        : impl{new StudentImpl{teacher, id}}
{
    pthread_create(&impl->tid, nullptr, do_exam, this);
}

// ���������� �����������.
Student::~Student()
{
    if (impl->tid > 0)
        pthread_join(impl->tid, nullptr);
    delete impl;
}

// ���������� ������ ������.
void Student::requestTicket()
{
    auto ticket = impl->teacher->giveTicket();
    std::ostringstream oss;
    oss << "Student " << impl->studId << " got ticket #" << ticket << '\n';
    auto buf = oss.str();
    write(STDOUT_FILENO, buf.c_str(), buf.size());
    impl->ticketNo = ticket;
}

// �����, ����������� �����.
void Student::answer()
{
    std::ostringstream oss;

    oss << "Student " << impl->studId << " answering\n";
    auto buf = oss.str();
    write(STDOUT_FILENO, buf.c_str(), buf.size());

    auto grade = impl->teacher->receiveAnswer(this);

    oss.str(std::string{});
    oss << "Student " << impl->studId << " got grade " << grade << '\n';
    buf = oss.str();
    write(STDOUT_FILENO, buf.c_str(), buf.size());
}

// ������� ������.
int Student::id() const
{
    return impl->studId;
}

// ������� ������.
int Student::ticket() const
{
    return impl->ticketNo;
}

// �����, ����������� ����� ��������.
void* Student::do_exam(void* arg)
{
    auto student = static_cast<Student*>(arg);
    student->requestTicket();
    student->prepare();
    student->answer();
    return nullptr;
}

// �����, ����������� ���������� � ������.
void Student::prepare()
{
    std::ostringstream oss;
    oss << "Student " << impl->studId << " preparing\n";
    auto buf = oss.str();
    write(STDOUT_FILENO, buf.c_str(), buf.size());
}
