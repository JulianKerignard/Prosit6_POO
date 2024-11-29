#include <iostream>
#include <stack>
#include <string>
#include <cctype>
using namespace std;

class Calculator {
private:
    stack<int> operandStack;   // Pile pour les opérandes
    stack<char> operatorStack; // Pile pour les opérateurs

public:
    void parseExpression(string expression) {
        for (int i = 0; i < expression.length(); ++i) {
            char ch = expression[i];

            // Si c'est un chiffre, on le traite (et on prend en compte les multiples chiffres)
            if (isdigit(ch)) {
                int num = 0;
                // Traiter tous les chiffres de l'opérande (ex: 10, 20, ...)
                while (i < expression.length() && isdigit(expression[i])) {
                    num = num * 10 + (expression[i] - '0');
                    ++i;
                }
                --i; // On revient une étape car le for fera un ++i
                operandStack.push(num);  // Empiler le nombre entier
            }
            // Si c'est un opérateur
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                operatorStack.push(ch);  // Empiler l'opérateur
            }
            // Si c'est une parenthèse fermante, on effectue les calculs
            else if (ch == ')') {
                performOperation();  // Effectuer l'opération lors de la rencontre de ')'
            }
        }
    }

    void performOperation() {
        int operand2 = operandStack.top(); operandStack.pop();
        int operand1 = operandStack.top(); operandStack.pop();
        char op = operatorStack.top(); operatorStack.pop();

        int result = 0;
        if (op == '+') {
            result = operand1 + operand2;
        } else if (op == '-') {
            result = operand1 - operand2;
        } else if (op == '*') {
            result = operand1 * operand2;
        } else if (op == '/') {
            result = operand1 / operand2;
        }

        operandStack.push(result);  // Empile le résultat
    }

    int calculate() {
        while (!operatorStack.empty()) {
            performOperation();  // Effectue toutes les opérations restantes
        }
        return operandStack.top();  // Retourne le résultat final
    }
};

int main() {
    Calculator calc;
    string expression = "((2+5)-10)*2";  // Exemple d'expression
    calc.parseExpression(expression);
    cout << "Résultat: " << calc.calculate() << endl;  // Affiche le résultat
    return 0;
}
