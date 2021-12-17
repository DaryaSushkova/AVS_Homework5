#ifndef EXAM_STUDENT_H
#define EXAM_STUDENT_H


// �����, ����������� �������� ��������.
class Teacher;
class StudentImpl;
class Student
{
public:
    // �����������.
    explicit Student(int id, Teacher* teacher);
    // ����������.
    ~Student();

    // ������ ������� � ������ � ������.
    int id() const;
    int ticket() const;

private:
    //  ������ ��� �������������� �� ����� ��������.
    static void* do_exam(void*);

    void requestTicket();
    void prepare();
    void answer();

private:
    StudentImpl* impl;
};


#endif //EXAM_STUDENT_H
