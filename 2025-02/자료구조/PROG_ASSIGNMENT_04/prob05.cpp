#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

const string OPERATORS = "+-*/()";
const int PRECEDENCE[] = { 1, 1, 2, 2, -1, -1 };

stack<double> operand_stack;    // 피연산자 스택
stack<char> operator_stack;     // 연산자 스택

// 연산자 확인
string::size_type is_operator(char ch) {
    return OPERATORS.find(ch);
}

// 연산자 우선순위 반환
int precedence(char op) {
    return PRECEDENCE[is_operator(op)];
}

double eval_infix(const string& expr);                                  // 중위표기식 계산
bool get_next_token(const string& expr, size_t& pos, string& token);    // 토큰 파싱
double apply_op(char op, double lhs, double rhs);                       // 연산 수행

int main() {
    string expr;
    cout << "Enter an infix expression: ";
    getline(cin, expr);

    try {
        double result = eval_infix(expr);
        cout << result << endl;
    }

    catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}

// 후위표기식으로 변환과 계산을 동시에 수행
// 입력: 중위표기식, 출력: 계산 결과 (double)
double eval_infix(const string& expr) {
    size_t pos = 0; // 현재 파싱 위치
    string token;   // 현재 토큰

    // 토큰 단위로 파싱
    while (get_next_token(expr, pos, token)) {
        // 피연산자 처리
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            operand_stack.push(stod(token));
        }

        // 연산자 처리
        else if (is_operator(token[0]) != string::npos) {
            char op = token[0];

            // '('괄호 처리
            if (op == '(') {
                operator_stack.push(op);
            }

            // ')'괄호 처리
            else if (op == ')') {
                // '('까지 연산 수행
                while (!operator_stack.empty() && operator_stack.top() != '(') {
                    char top_op = operator_stack.top();
                    operator_stack.pop();

                    // 피연산자 부족 예외 처리
                    if (operand_stack.size() < 2)
                        throw runtime_error("Syntax Error: Not enough operands.");

                    // 연산 수행
                    double rhs = operand_stack.top(); operand_stack.pop();
                    double lhs = operand_stack.top(); operand_stack.pop();

                    operand_stack.push(apply_op(top_op, lhs, rhs));
                }

                // '('가 없으면 예외 처리
                if (operator_stack.empty() || operator_stack.top() != '(')
                    throw runtime_error("Unmatched parenthesis.");

                operator_stack.pop();
            }

            // 기타 연산자 처리 (+,-,*,/)
            else {
                while (!operator_stack.empty() && operator_stack.top() != '(' && precedence(op) <= precedence(operator_stack.top())) {
                    char top_op = operator_stack.top();
                    operator_stack.pop();

                    // 피연산자 부족 예외 처리
                    if (operand_stack.size() < 2)
                        throw runtime_error("Syntax Error: Not enough operands.");

                    // 연산 수행
                    double rhs = operand_stack.top(); operand_stack.pop();
                    double lhs = operand_stack.top(); operand_stack.pop();

                    operand_stack.push(apply_op(top_op, lhs, rhs));
                }

                operator_stack.push(op);
            }
        }

        // 잘못된 문자 처리
        else {
            throw runtime_error("Syntax Error: invalid character encountered.");
        }
    }

    // 남은 연산자 처리
    while (!operator_stack.empty()) {
        char top_op = operator_stack.top();
        operator_stack.pop();

        // 괄호에 대한 연산은 이미 처리되었어야 함
        if (top_op == '(')
            throw runtime_error("Unmatched parenthesis.");

        // 피연산자 부족 예외 처리
        if (operand_stack.size() < 2)
            throw runtime_error("Syntax Error: Not enough operands.");

        // 연산 수행
        double rhs = operand_stack.top(); operand_stack.pop();
        double lhs = operand_stack.top(); operand_stack.pop();

        operand_stack.push(apply_op(top_op, lhs, rhs));
    }

    // 스택에 하나의 결과만 남아 있어야 함
    if (operand_stack.size() != 1)
        throw runtime_error("Syntax Error: Stack should be empty.");

    // 최종 결과 반환
    double answer = operand_stack.top();
    operand_stack.pop();

    return answer;
}

// 토큰 파싱: 연산자/피연산자 구분, 공백/붙여쓰기/여러칸 허용
bool get_next_token(const string& expr, size_t& pos, string& token) {
    token.clear();  // 토큰 초기화

    // 공백 무시
    while (pos < expr.size() && isspace(expr[pos])) {
        pos++;
    }

    // 끝 도달 시 false 반환
    if (pos >= expr.size())
        return false;

    // 연산자 처리
    if (is_operator(expr[pos]) != string::npos) {
        token += expr[pos++];

        return true;
    }

    // 피연산자 처리: 음수/실수 모두 허용
    bool dot = false;   // 소수점 등장 여부 (피연산자에 하나만 허용)

    // 음수 처리
    if (expr[pos] == '-') {
        token += expr[pos++];
    }

    // 숫자 및 소수점 처리
    while (pos < expr.size() && (isdigit(expr[pos]) || expr[pos] == '.')) {
        // 소수점이 이미 등장했으면 예외 발생 (ex: 12.345.6과 같은 입력의 경우 토큰 구분 불가)
        if (expr[pos] == '.') {
            if (dot)
                throw runtime_error("Syntax Error: multiple decimal points in operand.");

            dot = true;
        }

        token += expr[pos++];
    }

    return !token.empty();
}

// 연산 수행
double apply_op(char op, double lhs, double rhs) {
    switch (op) {
    case '+': return lhs + rhs;
    case '-': return lhs - rhs;
    case '*': return lhs * rhs;
    case '/': return lhs / rhs;
    }
}