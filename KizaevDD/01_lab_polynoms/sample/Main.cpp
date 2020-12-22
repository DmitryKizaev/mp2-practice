#include <iostream>
#include "TPolynom.h"
#include <string>

using namespace std;

void main()
{
    int mode = 0;
    cout << "Enter mode: 1 - tests, 2 - count" << endl;
    cin >> mode;
    if (mode == 1)
    {
        cout << endl << "Test data:" << endl << endl;
        string string_1 = "2x^5yz^3+4z-100", string_2 = "xyz", string_3 = "3xy";
        double k = 10;
        cout << "first polynomial (A):" << endl;
        cout << string_1 << endl;
        cout << "second polynomial (B):" << endl;
        cout << string_2 << endl;
        cout << "monomial (D):" << endl;
        cout << string_3 << endl;
        cout << "const (K):" << endl;
        cout << k << endl;
        TPolynom a(string_1);
        TPolynom b(string_2);
        TMonom d(string_3);
        TPolynom dd(string_3);
        try
        {
            TPolynom test1 = a + b;
            cout << endl << "polynomial + polynomial:" << endl;
            cout << test1 << endl;
        }
        catch (char* error_msg)
        {
            cout << error_msg << endl;
        };
        try
        {
            TPolynom test2 = a - b;
            cout << endl << "polynomial - polynomial:" << endl;
            cout << test2 << endl;
        }
        catch (char* error_msg)
        {
            cout << error_msg << endl;
        };
        try
        {
            TPolynom test3 = a * b;
            cout << endl << "polynomial * polynomial:" << endl;
            cout << test3 << endl;
        }
        catch (char* error_msg)
        {
            cout << error_msg << endl;
        };
        try
        {
            TPolynom test4 = a + dd;
            cout << endl << "polynomial + monomial:" << endl;
            cout << test4 << endl;
        }
        catch (char* error_msg)
        {
            cout << error_msg << endl;
        };

        try
        {
            TPolynom test5 = a - dd;
            cout << endl << "polynomial - monomial:" << endl;
            cout << test5 << endl;
        }
        catch (char* error_msg)
        {
            cout << error_msg << endl;
        };

        try
        {
            TPolynom test6 = a * dd;
            cout << endl << "polynomial * monomial:" << endl;
            cout << test6 << endl;
        }
        catch (char* error_msg)
        {
            cout << error_msg << endl;
        };

        try
        {
            TPolynom test7 = a * k;
            cout << endl << "polynomial * const:" << endl;
            cout << test7 << endl;
        }
        catch (char* error_msg)
        {
            cout << error_msg << endl;
        };

        try
        {
            TPolynom test8 = -a;
            cout << endl << "-polynomial:" << endl;
            cout << test8 << endl;
        }
        catch (char* error_msg)
        {
            cout << error_msg << endl;
        };

        cout << endl << "All tests passed" << endl;
        string go_on;
        cin >> go_on;
        cout << endl;
    }
    else if (mode == 2)
        while (true)
        {
            int oper;
            try
            {
                cout << "Choose operation:" << endl <<
                    "1 - polynomial + polynomial" << endl <<
                    "2 - polynomial - polynomial" << endl <<
                    "3 - polynomial * polynomial" << endl <<
                    "4 - polynomial * const" << endl <<
                    "5 - polynomial += polynomial" << endl <<
                    "6 - polynomial -= polynomial" << endl <<
                    "7 - polynomial *= polynomial" << endl <<
                    "8 - polynomial *= const" << endl <<
                    "9 - polynomial * (-1)" << endl <<
                    endl;
                cin >> oper;
                while (!((oper >= 1) && (oper <= 15)))
                    cin >> oper;

                cout << endl;
                switch (oper)
                {
                case 1:
                    try
                    {
                        string string_1, string_2;
                        cout << "Enter first polynomial (A):" << endl;
                        cin >> string_1;
                        cout << "Enter second polynomial (B):" << endl;
                        cin >> string_2;
                        TPolynom a(string_1);
                        TPolynom b(string_2);
                        TPolynom c = a + b;
                        cout << endl << "A + B:" << endl;
                        cout << c << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                case 2:
                    try
                    {
                        string string_1, string_2;
                        cout << "Enter first polynomial (A):" << endl;
                        cin >> string_1;
                        cout << "Enter second polynomial (B):" << endl;
                        cin >> string_2;
                        TPolynom a(string_1);
                        TPolynom b(string_2);
                        TPolynom c = a - b;
                        cout << endl << "A - B:" << endl;
                        cout << c << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                case 3:
                    try
                    {
                        string string_1, string_2;
                        cout << "Enter first polynomial (A):" << endl;
                        cin >> string_1;
                        cout << "Enter second polynomial (B):" << endl;
                        cin >> string_2;
                        TPolynom a(string_1);
                        TPolynom b(string_2);
                        TPolynom c = a * b;
                        cout << endl << "A * B:" << endl;
                        cout << c << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                case 4:
                    try
                    {
                        string string_1;
                        double b;
                        cout << "Enter polynomial (A):" << endl;
                        cin >> string_1;
                        cout << "Enter const (B):" << endl;
                        cin >> b;
                        TPolynom a(string_1);
                        TPolynom c = a * b;
                        cout << endl << "A * B:" << endl;
                        cout << c << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                case 5:
                    try
                    {
                        string string_1, string_2;
                        cout << "Enter first polynomial (A):" << endl;
                        cin >> string_1;
                        cout << "Enter second polynomial (B):" << endl;
                        cin >> string_2;
                        TPolynom a(string_1);
                        TPolynom b(string_2);
                        a += b;
                        cout << endl << "A += B:" << endl;
                        cout << a << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                case 6:
                    try
                    {
                        string string_1, string_2;
                        cout << "Enter first polynomial (A):" << endl;
                        cin >> string_1;
                        cout << "Enter second polynomial (B):" << endl;
                        cin >> string_2;
                        TPolynom a(string_1);
                        TPolynom b(string_2);
                        a -= b;
                        cout << endl << "A -= B:" << endl;
                        cout << a << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                case 7:
                    try
                    {
                        string string_1, string_2;
                        cout << "Enter first polynomial (A):" << endl;
                        cin >> string_1;
                        cout << "Enter second polynomial (B):" << endl;
                        cin >> string_2;
                        TPolynom a(string_1);
                        TPolynom b(string_2);
                        a *= b;
                        cout << endl << "A *= B:" << endl;
                        cout << a << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                case 8:
                    try
                    {
                        string string_1;
                        double b;
                        cout << "Enter polynomial (A):" << endl;
                        cin >> string_1;
                        cout << "Enter const (B):" << endl;
                        cin >> b;
                        TPolynom a(string_1);
                        a *= b;
                        cout << endl << "A *= B:" << endl;
                        cout << a << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                case 9:
                    try
                    {
                        string string_1;
                        cout << "Enter polynomial (A):" << endl;
                        cin >> string_1;
                        TPolynom a(string_1);
                        TPolynom c = -a;
                        cout << endl << "-A:" << endl;
                        cout << c << endl;
                    }
                    catch (char* error_msg)
                    {
                        cout << error_msg << endl;
                    }
                    break;
                default:
                    break;
                }
            }
            catch (char* error_msg)
            {
                cout << error_msg;
            }
            cout << endl;
            string go_on;
            cin >> go_on;
            cout << endl;
        }
}