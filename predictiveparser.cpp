#include <iostream>
#include <cstring>
using namespace std;

char stack[100];
int top = -1;

void push(char c)
{
    stack[++top] = c;
}

char pop()
{
    return stack[top--];
}

void displayStack()
{
    for (int i = 0; i <= top; i++)
        cout << stack[i];
}

int main()
{
    char input[100];
    int ip = 0;
    char X, a;

    /*
        Grammar:
        E -> TR
        R -> +TR | #
        T -> FY
        Y -> *FY | #
        F -> (E) | i

        # represents epsilon.
    */

    cout << "Enter the input string (use i for identifier): ";
    cin >> input;

    strcat(input, "$");

    push('$');
    push('E');

    cout << "\nStack\t\tInput\t\tAction\n";
    cout << "---------------------------------------------\n";

    while (top >= 0)
    {
        X = stack[top];
        a = input[ip];

        displayStack();
        cout << "\t\t" << (input + ip) << "\t\t";

        if (X == '$' && a == '$')
        {
            cout << "Accept\n";
            return 0;
        }

        if (X == a)
        {
            pop();
            ip++;

            cout << "Match " << a << "\n";
        }

        else if (X == 'E')
        {
            pop();

            if (a == 'i' || a == '(')
            {
                push('R');
                push('T');

                cout << "E -> TR\n";
            }
            else
            {
                cout << "Error\n";
                return 0;
            }
        }

        else if (X == 'R')
        {
            pop();

            if (a == '+')
            {
                push('R');
                push('T');
                push('+');

                cout << "R -> +TR\n";
            }
            else if (a == ')' || a == '$')
            {
                cout << "R -> epsilon\n";
            }
            else
            {
                cout << "Error\n";
                return 0;
            }
        }

        else if (X == 'T')
        {
            pop();

            if (a == 'i' || a == '(')
            {
                push('Y');
                push('F');

                cout << "T -> FY\n";
            }
            else
            {
                cout << "Error\n";
                return 0;
            }
        }

        else if (X == 'Y')
        {
            pop();

            if (a == '*')
            {
                push('Y');
                push('F');
                push('*');

                cout << "Y -> *FY\n";
            }
            else if (a == '+' || a == ')' || a == '$')
            {
                cout << "Y -> epsilon\n";
            }
            else
            {
                cout << "Error\n";
                return 0;
            }
        }

        else if (X == 'F')
        {
            pop();

            if (a == 'i')
            {
                push('i');

                cout << "F -> i\n";
            }
            else if (a == '(')
            {
                push(')');
                push('E');
                push('(');

                cout << "F -> (E)\n";
            }
            else
            {
                cout << "Error\n";
                return 0;
            }
        }

        else
        {
            cout << "Error\n";
            return 0;
        }
    }

    cout << "Rejected\n";

    return 0;
}
 