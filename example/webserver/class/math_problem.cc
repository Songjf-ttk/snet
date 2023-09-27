//定义基类 MathProblem 的方法

#include "math_problem.h"

#include <cmath>
#include <ctime>
#include <random>
#include <sstream>
#include <stack>

vector_tuple MathProblem::GetProblemSet(int num)
{
  srand(time(NULL));  //初始化随机数
  vector_tuple problem_set;
  for(int i = 0, num_operand = 0; i < num ;) {
    vtuple problem;
    num_operand = GetNumOperand(); //生成操作数
    std::get<0>(problem) = GenerateProblem(num_operand);  //生成初始题目
    std::get<0>(problem) = DecorateProblem(std::get<0>(problem), num_operand);  //修饰生成的题目
    if(!CheckRepeat(problem_set, std::get<0>(problem))) {  //查重
      continue;
    }
    std::string correct_answer = GetCorrectAnswer(std::get<0>(problem));  //获取正确答案
    SetAnswerSet(problem, rand()%4 + 1, correct_answer);  //获取答案集
    problem_set.push_back(problem);
    ++i;
  }
  return problem_set;
}

std::string MathProblem::GenerateProblem(int num_operand) {
  std::string problem = "";
  for(int i = 0, k = -1; i < num_operand; ++i) {  //k用来选择符号
    k = rand()%4;
    problem += std::to_string(rand()%100 + 1);
    if(i == num_operand -1) {
      break;
    }
    if(k == 0) {
      problem += " + ";
    }else if(k == 1) {
      problem += " - ";
    }else if(k == 2) {
      problem += " * ";
    }else {  //k == 3
      problem += " / ";
    }
  }
  return problem;
}

bool MathProblem::CheckRepeat(vector_tuple problem_set, std::string problem) {
  int vector_size = problem_set.size();
  if(vector_size == 0) {
    return true;
  }
  std::stringstream stringstream_problem(problem);
  std::string element = "";
  int size_problem = 0;
  while(stringstream_problem >> element) {
    size_problem +=1;
  }
  for(int i = 0, k = 0; i < vector_size; ++i) {
    if(std::get<0>(problem_set.at(i)) == problem) {
      return false;
    }
    k = 0;
    stringstream_problem << problem;
    while(stringstream_problem >> element) {
      ++k;
    }
    if(size_problem != 3) {
      continue;
    }
    if(k == 3) {
      std::string element_string[3];
      stringstream_problem << problem;
      stringstream_problem >> element_string[0];
      stringstream_problem >> element_string[1];
      stringstream_problem >> element_string[2];
      stringstream_problem << problem;
      bool isnosame = false;
      for(int j = 2; stringstream_problem >> element; j -=1) {
        if(element != element_string[i]) {
          isnosame = true;
        }
      }
      if(isnosame == false) {
        return false;
      }
    }
  }
  return true;
}

std::string MathProblem::GetWrongAnswer(std::string correct_answer, int i) {
  std::string wrong_answer = correct_answer;
  int index = rand()%wrong_answer.length();
  if(wrong_answer[index] == '.') {
    if(rand()%2 == 1) {
      index += rand()%(wrong_answer.length() - index - 1) + 1;
    }else {
      index -= rand()%index - 1;
    }
  }
  if(wrong_answer[index] == '-') {
    index += 1;
  }
  if(wrong_answer[index] + i < '0') {
    wrong_answer[index] += (i + 10);
  }else if(wrong_answer[index] + i > '9') {
    wrong_answer[index] += (i - 10);
  }else {
    wrong_answer[index] += i;
  }
  return wrong_answer;
}

void MathProblem::SetAnswerSet(vtuple &problem, int correct_index, std::string correct_answer) {
  if(correct_index == 1) {
    std::get<1>(problem) = correct_answer;
    std::get<2>(problem) = GetWrongAnswer(correct_answer, 1);
    std::get<3>(problem) = GetWrongAnswer(correct_answer, 2);
    std::get<4>(problem) = GetWrongAnswer(correct_answer, 3);
    std::get<5>(problem) = 'A';
  }else if(correct_index == 2) {
    std::get<1>(problem) = GetWrongAnswer(correct_answer, -1);
    std::get<2>(problem) = correct_answer;
    std::get<3>(problem) = GetWrongAnswer(correct_answer, 1);
    std::get<4>(problem) = GetWrongAnswer(correct_answer, 2);
    std::get<5>(problem) = 'B';
  }else if(correct_index == 3) {
    std::get<1>(problem) = GetWrongAnswer(correct_answer, -2);
    std::get<2>(problem) = GetWrongAnswer(correct_answer, -1);
    std::get<3>(problem) = correct_answer;
    std::get<4>(problem) = GetWrongAnswer(correct_answer, 1);
    std::get<5>(problem) = 'C';
  }else if(correct_index == 4) {
    std::get<1>(problem) = GetWrongAnswer(correct_answer, -3);
    std::get<2>(problem) = GetWrongAnswer(correct_answer, -2);
    std::get<3>(problem) = GetWrongAnswer(correct_answer, -1);
    std::get<4>(problem) = correct_answer;
    std::get<5>(problem) = 'D';
  }
  std::get<6>(problem) = '\0';
}

std::string MathProblem::GetCorrectAnswer(std::string problem) {
  std::string machine_problem = GetMachineProblem(problem); 
  double calculated_value = 0;
  std::stack<double> operator_stack;
  std::stringstream stringstream_element(machine_problem);
  std::string element = "";
  while(stringstream_element >> element) {
    if(element == "+") {
      calculated_value = operator_stack.top();
      operator_stack.pop();
      calculated_value = operator_stack.top() + calculated_value;
      operator_stack.pop();
      operator_stack.push(calculated_value);
    }else if(element == "-") {
      calculated_value = operator_stack.top();
      operator_stack.pop();
      calculated_value = operator_stack.top() - calculated_value;
      operator_stack.pop();
      operator_stack.push(calculated_value);
    }else if(element == "*") {
      calculated_value = operator_stack.top();
      operator_stack.pop();
      calculated_value = operator_stack.top() * calculated_value;
      operator_stack.pop();
      operator_stack.push(calculated_value);
    }else if(element == "/") {
      calculated_value = operator_stack.top();
      operator_stack.pop();
      calculated_value = operator_stack.top() / calculated_value;
      operator_stack.pop();
      operator_stack.push(calculated_value);
    }else {
      operator_stack.push(GetData(element));
    }
  }
  element = std::to_string(std::round(operator_stack.top() * 100) / 100);
  return element.substr(0, element.length() - 4);
}

std::string MathProblem::GetMachineProblem(std::string problem) {
  std::string machine_problem = "";
  std::stringstream stringstream_problem(problem);
  std::stack<std::string> oprand_stack;
  std::string element = "";
  while(stringstream_problem >> element) {
    if(element[0] == '(') {
      oprand_stack.push("(");
    }else if(element[element.length() - 1] == ')') {
      while(oprand_stack.top() != "(") {
        machine_problem += oprand_stack.top() + " ";
        oprand_stack.pop();
      }
      oprand_stack.pop();
    }else if(element == "+" || element =="-") {
      if(!oprand_stack.empty() && oprand_stack.top() != "("){
        if((oprand_stack.top() == "*" || oprand_stack.top() == "/")) {
          while(!oprand_stack.empty() && oprand_stack.top() != "(") {
            machine_problem += oprand_stack.top() + " ";
            oprand_stack.pop();
          }
        }else {
          machine_problem += oprand_stack.top() + " ";
          oprand_stack.pop();
        }
      }
      oprand_stack.push(element);
    }else if(element == "*" || element =="/") {
      if(!oprand_stack.empty() && (oprand_stack.top() == "*" || oprand_stack.top() == "/")) {
        machine_problem += oprand_stack.top() + " ";
        oprand_stack.pop();
      }
      oprand_stack.push(element);
    }else {
      machine_problem += element + " ";
    }
  }
  while(!oprand_stack.empty()) {
    machine_problem += oprand_stack.top() + " ";
    oprand_stack.pop();
  }
  return machine_problem;
}