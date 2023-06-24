//
// Max Base
// https://github.com/BaseMax/MathematicalExpressionEvaluator
// 06/24/2023
//

#include <stack>
#include <string>
#include <iostream>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int applyOperator(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}

int evaluateExpression(const string& expression) {
    stack<int> values;
    stack<char> operators;

    int i = 0;
    while (i < expression.length()) {
        char c = expression[i];

        if (c == '(') {
            operators.push(c);
        } else if (isdigit(c)) {
            int num = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;

            values.push(num);
        } else if (c == ')') {
            while (operators.top() != '(') {
                char op = operators.top();
                operators.pop();

                int b = values.top();
                values.pop();

                int a = values.top();
                values.pop();

                values.push(applyOperator(a, b, op));
            }

            operators.pop();  // Discard the opening parenthesis
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                char op = operators.top();
                operators.pop();

                int b = values.top();
                values.pop();

                int a = values.top();
                values.pop();

                values.push(applyOperator(a, b, op));
            }

            operators.push(c);
        }

        i++;
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

        int b = values.top();
        values.pop();

        int a = values.top();
        values.pop();

        values.push(applyOperator(a, b, op));
    }

    return values.top();
}

int main() {
    // Test case 1: (5+((8+2)*2))
    string expression1 = "(5+((8+2)*2))";
    int result1 = evaluateExpression(expression1);
    cout << expression1 << " = " << result1 << endl;

    // Test case 2: ((6*(2+1))*(3+(3+1)))
    string expression2 = "((6*(2+1))*(3+(3+1)))";
    int result2 = evaluateExpression(expression2);
    cout << expression2 << " = " << result2 << endl;

    // User input
    string expression;
    cout << "Enter the mathematical expression: ";
    getline(cin, expression);

    int result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}
