//声明基类 MathProblem 以及它的派生类

#ifndef MATH_PROBLEM_PROBLEM_H_
#define MATH_PROBLEM_PROBLEM_H_

#include <string>
#include <tuple>
#include <vector>

using vtuple=std::tuple<
    std::string,std::string,std::string,std::string,std::string,  //存储题目和四个选项
    char,char>;  //存储正确答案和所选答案
using vector_tuple = std::vector<vtuple>;

//题目类的虚拟类
class MathProblem {
 public:
  //获取问题集    num为需要生成的题目个数
  //返回用vector<tuple>存储的题目、4个答案、正确答案、所选答案，vector大小为num
  //函数使用顺序：  1
  vector_tuple GetProblemSet(int num);

  //生成简单问题，只包含加减乘除
  //函数使用顺序：  3
  std::string GenerateProblem(int num_oprand);

  //查重
  //函数使用顺序：  5
  bool CheckRepeat(vector_tuple problem_set, std::string problem);

  //根据问题获取答案
  //函数使用顺序：  6
  std::string GetCorrectAnswer(std::string problem);

  //中缀表达式转后缀表达式
  //函数使用顺序：  7
  std::string GetMachineProblem(std::string problem);

    //根据参数 i 获取错误答案
  //函数使用顺序：  9
  std::string GetWrongAnswer(std::string correct_answer, int i);
  
  //生成所有答案集，包含四个选项，一个正确选项，一个需选选项
  //函数使用顺序：  10
  void SetAnswerSet(vtuple &problem, int correct_index, std::string correct_answer);

  //获取操作数数目
  //函数使用顺序：  2
  virtual int GetNumOperand() = 0;

  //根据难度修饰生成的简单问题
  //函数使用顺序：  4
  virtual std::string DecorateProblem(std::string problem, int num_operand) = 0;

  //string To double
  //函数使用顺序：  8
  virtual double GetData(std::string string_operator) = 0;

    //删除空格
  void deletespace(vtuple &problem);
};

//小学题目，派生MathProblem
class PrimaryMathProblem: public MathProblem {
 public:

  //为简单表达式子修饰一个括号
  std::string DecorateProblem(std::string problem, int num_operand);

  //string To double
  double GetData(std::string string_operator);

  //操作数数目大于等于 2 且小于等于 5
  int GetNumOperand();
};

//初中题目，派生MathProblem
class JuniorMathProblem: public MathProblem {
 public:

  //为简单式子修饰根号或平方
  std::string DecorateProblem(std::string problem, int num_operand);

  //string To double
  double GetData(std::string string_operator);

  //操作数数目大于等于 1 且小于等于 5
  int GetNumOperand();
};

//高中题目，派生MathProblem
class SeniorMathProblem: public MathProblem {
 public:
  //为简单式子修饰sin、cos、tan，并把其改为能够计算出来的值
  std::string DecorateProblem(std::string problem, int num_operand);

  //string To double
  double GetData(std::string string_operator);

  //获取可计算的三角函数
  std::string GetTriangleFunction();

  //操作数数目大于等于 1 且小于等于 5
  int GetNumOperand();
};

#endif  //MATH_PROBLEM_PROBLEM_H_