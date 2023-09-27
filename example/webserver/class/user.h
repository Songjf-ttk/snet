//定义虚拟类 user，以及派生类 student
#ifndef USER_USER_H_
#define USER_USER_H_

#include "math_problem.h"

using tuple_user = std::tuple<std::string, std::string , std::string>;
using vector_user = std::vector<tuple_user>;

class User {
 public:
  //登录  登录成功返回 1，账号不存在返回 -1，密码错误返回 -2
  virtual int Login(std::string account, std::string password) = 0;

  //查询邮箱号是否注册过  未注册返回 1，已注册返回 -1
  virtual int CheckExist(std::string account) = 0;

  //注册成功返回 1，用户名重复返回 -1，两次密码不同返回 -2，密码不符合要求，返回 -3
  virtual int Register(std::string username,
                       std::string account,
                       std::string password_1,
                       std::string password_2) = 0;

  //调用 MathProblem 类的函数，返回问题集，到 problem_set_    成功返回 1，失败返回 -1
  virtual int SetProblem(std::string type,int n) = 0;

  //修改密码成功返回 1，旧密码错误返回 -1，新密码两次不相同返回 -2，密码不符合要求，返回 -3
  virtual int EditPassword(std::string oldpassword, 
                           std::string new_password_1, 
                           std::string new_password_2) = 0;

  //获取题目
  virtual vtuple get_problem(int n) = 0;

  //答题
  virtual void set_answer(int n, char answer) = 0;

  //获取邮箱号
  virtual std::string get_account() = 0;

  //获取用户名
  virtual std::string get_username() = 0;

  //获取分数
  virtual double get_score() = 0;

  //获取num
  virtual int get_num_problem() = 0;
};

class Student: public User {
 public:
  Student();

  //登录  登录成功返回 1，账号不存在返回 -1，密码错误返回 -2
  int Login(std::string account, std::string password);

  //查询邮箱号是否注册过  未注册返回 1，已注册返回 -1
  int CheckExist(std::string account);

  //存在相同邮箱返回 false
  bool CheckAccount(std::string account);

  //存在相同用户名返回 false
  bool CheckUsername(std::string username);

  //密码 6-10位，包含大小写，不满足返回false
  bool CheckPasswordSuit(std::string password);

  //注册成功返回 1，用户名重复返回 -1，两次密码不同返回 -2，密码不符合要求，返回 -3
  int Register(std::string username,
               std::string account,
               std::string password_1,
               std::string password_2);

  //调用 MathProblem 类的函数，返回问题集，到 problem_set_    成功返回 1，失败返回 -1
  int SetProblem(std::string type,int n);

  //修改密码成功返回 1，旧密码错误返回 -1，新密码两次不相同返回 -2，密码不符合要求，返回 -3
  int EditPassword(std::string oldpassword, 
                   std::string new_password_1, 
                   std::string new_password_2);

  //获取所有账号信息
  vector_user ReturnUser();

  //获取题目
  vtuple get_problem(int n);

  //答题
  void set_answer(int n, char answer);

  //获取邮箱号
  std::string get_account();

  //获取用户名
  std::string get_username();

  //获取分数
  double get_score();

  //获取num
  int get_num_problem();

 private:
  std::string account_;  //邮箱号
  std::string password_; //密码
  std::string username_; //用户名
  int num_problem_;      //题目数目
  vector_tuple problem_set_;  //问题集
};

#endif //USER_USER_H_
