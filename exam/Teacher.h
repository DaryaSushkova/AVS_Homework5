#ifndef EXAM_TEACHER_H
#define EXAM_TEACHER_H

#include <string>
#include "Student.h"


// �����, ����������� �������������.
class TeacherImpl;
class Teacher
{
public:
    // �����������.
    explicit Teacher(int nTickets, const std::string& Name);
    // ����������.
    ~Teacher();

    // ������ ��� �������������� �� ����������.
    int giveTicket();
    int receiveAnswer(Student* student);

private:
    TeacherImpl* impl;
};


#endif //EXAM_TEACHER_H
