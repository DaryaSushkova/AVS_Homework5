#ifndef EXAM_TEACHER_H
#define EXAM_TEACHER_H

#include <string>
#include "Student.h"


// Класс, реализующий преподавателя.
class TeacherImpl;
class Teacher
{
public:
    // Конструктор.
    explicit Teacher(int nTickets, const std::string& Name);
    // Деструктор.
    ~Teacher();

    // Методы для взаимодействия со студентами.
    int giveTicket();
    int receiveAnswer(Student* student);

private:
    TeacherImpl* impl;
};


#endif //EXAM_TEACHER_H
