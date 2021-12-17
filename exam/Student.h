#ifndef EXAM_STUDENT_H
#define EXAM_STUDENT_H


// Класс, реализующий сущность студента.
class Teacher;
class StudentImpl;
class Student
{
public:
    // Конструктор.
    explicit Student(int id, Teacher* teacher);
    // Деструктор.
    ~Student();

    // Методы доступа к номеру и билету.
    int id() const;
    int ticket() const;

private:
    //  Методы для взаимодействия во время экзамена.
    static void* do_exam(void*);

    void requestTicket();
    void prepare();
    void answer();

private:
    StudentImpl* impl;
};


#endif //EXAM_STUDENT_H
