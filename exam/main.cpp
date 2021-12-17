#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "Teacher.h"
#include "Student.h"


// Описание аргументов командной строки.
static void print_usage(bool is_error)
{
    std::ostream& os = is_error ? std::cerr : std::cout;
    os << "Usage: " << program_invocation_short_name << " [options]\n"<<
          "Options:\n"
          "  -f FILE   Read FILE as input.\n"
          "  -h        Print this message.\n"
          "  -o FILE   Print output to FILE.\n"
          "  -s NUM    Set id of students.\n"
          "  -t NUM    Set id of tickets.\n";
}

// Точка входа в приложение.
int main(int argc, char** argv)
{
    const std::string DEFAULT_INPUT = "input.txt";
    const std::string DEFAULT_OUTPUT = "output.txt";

    std::string inFile, outFile;
    int nStudents = 0;
    int nTickets = 0;

    // Случай для каждого аргумента командной строки.
    int opt;
    while ((opt = getopt(argc, argv, "f:ho:s:t:")) != -1)
    {
        switch (opt)
        {
            case 'f':
                inFile = optarg;
                break;
            case 'h':
                print_usage(false);
                return EXIT_SUCCESS;
            case 'o':
                outFile = optarg;
                break;
            case 's':
                nStudents = std::stoi(optarg);
                break;
            case 't':
                nTickets = std::stoi(optarg);
                break;
            default:
                print_usage(true);
                return EXIT_FAILURE;
        }
    }

    // Присутствие пустых значений.
    if (inFile.empty())
    {
        if (nStudents == 0 && nTickets == 0)
        {
            inFile = DEFAULT_INPUT;
        }
        else if (nStudents == 0 || nTickets == 0)
        {
            print_usage(true);
            return EXIT_FAILURE;
        }
    }

    // Ошибка открытия файла.
    if (!inFile.empty())
    {
        std::ifstream is{inFile};
        if (!is)
        {
            std::cerr << "Error opening file " << inFile << '\n';
            return EXIT_FAILURE;
        }
        is >> nStudents >> nTickets;
    }

    if (outFile.empty())
        outFile = DEFAULT_OUTPUT;

    Teacher teacher{nTickets, outFile};
    for (int i = 0; i < nStudents; ++i)
        Student{i + 1, &teacher};
    return 0;
}
