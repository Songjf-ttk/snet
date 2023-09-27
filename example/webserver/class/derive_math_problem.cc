//定义基类 MathProblem 的派生类的方法

#include "math_problem.h"

#include <cmath>
#include <ctime>
#include <random>
#include <sstream>
#include <stack>

int PrimaryMathProblem::GetNumOperand() {
  return rand()%4 + 2;
}

std::string PrimaryMathProblem::DecorateProblem(std::string problem, int num_operand) {
  std::string decorate_problem = "";
  if(num_operand == 2) {
    decorate_problem = problem;
  }else {
    std::stringstream stringstream_problem(problem);
    int left = rand()%(num_operand - 1);
    int right = left + 1 + rand()%(num_operand - left - 1);
    if(left == 0 && right == num_operand -1) {
      rand()%2?++left:--right;
    }
    left *= 2;
    right *= 2;
    std::string element = "";
    for(int i = 0; stringstream_problem >> element; ++i) {
      if(i != 0) {
        decorate_problem += " ";
      }
      if(i == left) {
        decorate_problem = decorate_problem + "(" + " " + element;
      }else if( i == right) {
        decorate_problem = decorate_problem + element + " " + ")";
      }else {
        decorate_problem = decorate_problem + element;
      }
    }
  }
  return decorate_problem;
}

double PrimaryMathProblem::GetData(std::string string_operator) {
  return std::stod(string_operator);
}

int JuniorMathProblem::GetNumOperand() {
  return rand()%5 + 1;
}

std::string JuniorMathProblem::DecorateProblem(std::string problem, int num_operand) {
  std::string decorate_problem = "";
  if(num_operand == 1) {
    if(rand()%2 == 0) {  //根号
      decorate_problem = "\u221a" + problem;
    }else {  //rand()%2 == 1    平方
      decorate_problem = problem + "^2";
    }
  }else {
    std::stringstream stringstream_problem(problem);
    std::string element = "";
    for(int i = 0, must = rand()%num_operand * 2; stringstream_problem >> element; ++i) {
      if(i != 0) {
        decorate_problem += " ";
      }
      if(i%2 == 1) {
        decorate_problem = decorate_problem + element;
      }else if(rand()%2 == 1 || must == i) {
        if(rand()%2 == 0) {
          decorate_problem = decorate_problem + "\u221a" + element;
        }else {
          decorate_problem = decorate_problem + element + "^2";
        }
      }else {
        decorate_problem = decorate_problem + element;
      }
    }
  }
  return decorate_problem;
}

double JuniorMathProblem::GetData(std::string string_operator) {
  if(string_operator.find("\u221a") != std::string::npos) {
    return sqrt(std::stod(string_operator.substr(3, string_operator.length() - 3)));
  }else if(string_operator.find("^2") != std::string::npos) {
    return pow(std::stod(string_operator.substr(0, string_operator.length() - 2)), 2);
  }
  return std::stod(string_operator);
}

int SeniorMathProblem::GetNumOperand() {
  return rand()%5 + 1;
}

std::string SeniorMathProblem::DecorateProblem(std::string problem, int num_operand) {
  std::string decorate_problem = "";
  if(num_operand == 1) {
    decorate_problem = GetTriangleFunction();
  }else {
    std::stringstream stringstream_problem(problem);
    std::string element = "";
    for(int i = 0, must = rand()%num_operand * 2; stringstream_problem >> element; ++i) {
      if(i != 0) {
        decorate_problem += " ";
      }
      if(i%2 == 1) {
        decorate_problem = decorate_problem + element;
      }else if(rand()%2 == 1 || must == i) {
        decorate_problem = decorate_problem + GetTriangleFunction();
      }else {
        decorate_problem = decorate_problem + element;
      }
    }
  }
  return decorate_problem;
}

double SeniorMathProblem::GetData(std::string string_operator) {
  if(string_operator == "sin30\u00b0" || string_operator == "cos60\u00b0") {
    return 0.5;
  }else if(string_operator == "cos30\u00b0" || string_operator == "sin60\u00b0") {
    return 0.866;
  }else if(string_operator == "tan30\u00b0") {
    return 0.577;
  }else if(string_operator == "tan60\u00b0") {
    return 1.732;
  }else if(string_operator == "sin37\u00b0" || string_operator == "cos53\u00b0") {
    return 0.6;
  }else if(string_operator == "cos37\u00b0" || string_operator == "sin53\u00b0") {
    return 0.8;
  }else if(string_operator == "tan37\u00b0") {
    return 0.75;
  }else if(string_operator == "tan53\u00b0") {
    return 1.333;
  }else if(string_operator == "sin45\u00b0" || string_operator == "cos45\u00b0") {
    return 0.707;
  }else if(string_operator == "tan45\u00b0") {
    return 1;
  }
  return std::stod(string_operator);
}

std::string SeniorMathProblem::GetTriangleFunction() {
  std::string triangle_function = "";
  int triangle_rand = rand()%3;
  if(triangle_rand == 0) {
    triangle_function += "sin";
  }else if(triangle_rand == 1) {
    triangle_function += "cos";
  }else {  //triangle_rand == 2
    triangle_function += "tan";
  }
  triangle_rand = rand()%5;
  if(triangle_rand == 0) {
    triangle_function += "30\u00b0";
  }else if(triangle_rand == 1) {
    triangle_function += "37\u00b0";
  }else if(triangle_rand == 2) {
    triangle_function += "45\u00b0";
  }else if(triangle_rand == 3) {
    triangle_function += "53\u00b0";
  }else {  //triangle_rand == 4
    triangle_function += "60\u00b0";
  }
  return triangle_function;
}