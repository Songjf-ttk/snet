#include "user.h"

#include <cmath>
#include <fstream>
#include <vector>
#include <tuple>

Student::Student() {
  account_ = "";
  password_ = "";
  username_ = "";
  num_problem_ = 0;
  problem_set_.clear();
}

int Student::Login(std::string account, std::string password) {
  int state = -1;   //账号不存在
  std::ifstream read_file;
  read_file.open("user_information.txt", std::ios::in);
  std::string read_username;
  std::string read_account;
  std::string read_password;
  while(read_file >> read_username >> read_account >>  read_password) {
    if(read_account == account ) {
      if(read_password == password) {
        username_ = read_username;
        account_ = read_account;
        password_ = read_password;
        state = 1;    //登录成功
      }else { //read_password == password
        state = -2;   //密码错误
      }
      break;
    }
  }
  read_file.close();
  return state;
}

int Student::CheckExist(std::string account) {
  if(CheckAccount(account)) {
    return 1;
  }
  return -1;
}

bool Student::CheckAccount(std::string account) {
  bool state = true;
  std::ifstream read_file;
  read_file.open("user_information.txt", std::ios::in);
  std::string read_username;
  std::string read_account;
  std::string read_password;
  while(read_file >> read_username >> read_account >>  read_password) {
    if(read_account == account ) {
      state = false;  //存在相同邮箱（账号）
      break;
    }
  }
  read_file.close();
  return state;
}

bool Student::CheckUsername(std::string username) {
  bool state = true;
  std::ifstream read_file;
  read_file.open("user_information.txt", std::ios::in);
  std::string read_username;
  std::string read_account;
  std::string read_password;
  while(read_file >> read_username >> read_account >>  read_password) {
    if(read_username == username) {
      state = false;  //存在用户名
      break;
    }
  }
  read_file.close();
  return state;
}

bool Student::CheckPasswordSuit(std::string password) {
  bool capital = false;   //大写
  bool lowercase = false; //小写
  bool figure = false;    //数字
  int password_length = password.length();
  if(password_length >= 6 && password_length <= 10) {
    for(int i = 0; i < password_length; ++i) {
      if(password[i] >= 'A' && password[i] <= 'Z') {
        capital = true;
      }else if(password[i] >= 'a' && password[i] <= 'z') {
        lowercase = true;
      }else if(password[i] >= '0' && password[i] <= '9') {
        figure = true;
      }
    }
  }
  return capital && lowercase && figure;
}

int Student::Register(std::string username, 
                      std::string account, 
                      std::string password_1, 
                      std::string password_2) {
  if(!CheckUsername(username)) {
    return -1;
  }else if(password_1 != password_2) {
    return -2;  //两次密码不同
  }else if(!CheckPasswordSuit(password_1)) {
    return -3;
  }
  std::ofstream write_file;
  write_file.open("user_information.txt", std::ios::out | std::ios::app);
  write_file << username << " " << account << " " << password_1 << "\n";
  username_ = username;
  account_ = account;
  password_ = password_1;
  write_file.close();
  return 1;
}

int Student::SetProblem(std::string type, int n) {
  problem_set_.clear();
  MathProblem *math_problem;
  if(type == "小学") {
    math_problem = new PrimaryMathProblem();
  }else if(type == "初中") {
    math_problem = new JuniorMathProblem();
  }else {  //type == "高中"
    math_problem = new SeniorMathProblem();
  }
  problem_set_ = math_problem->GetProblemSet(n);
  delete math_problem;
  if(problem_set_.size() != n) {
    return -1;
  }
  num_problem_ = n;
  return 1;
}

int Student::EditPassword(std::string oldpassword, std::string new_password_1, std::string new_password_2) {
  if(oldpassword != password_) {
    return -1;
  }else if(new_password_1 != new_password_2) {
    return -2;  //两次密码不同
  }else if(!CheckPasswordSuit(new_password_1)) {
    return -3;
  }
  vector_user vuser = ReturnUser();
  int vuser_size = vuser.size();
  std::ofstream write_file;
  write_file.open("user_information.txt", std::ios::out | std::ios::trunc);
  for(int i = 0; i < vuser_size; ++i) {
    if(std::get<1>(vuser.at(i)) == account_) {
      std::get<2>(vuser.at(i)) = new_password_1;
    }
    write_file << std::get<0>(vuser.at(i)) << " " << 
                  std::get<1>(vuser.at(i)) << " " <<
                  std::get<2>(vuser.at(i)) << "\n";
  }
  return 1;
}

vector_user Student::ReturnUser() {
  vector_user vuser;
  std::ifstream read_file;
  read_file.open("user_information.txt", std::ios::in);
  tuple_user tuser;
  while(read_file >> std::get<0>(tuser) >> std::get<1>(tuser) >> std::get<2>(tuser)) {
    vuser.push_back(tuser);
  }
  read_file.close();
  return vuser;
}

vtuple Student::get_problem(int n)
{
  return problem_set_.at(n - 1);
}

void Student::set_answer(int n, char answer)
{
  std::get<6>(problem_set_.at(n - 1)) = answer;
}

std::string Student::get_account()
{
  return account_;
}

std::string Student::get_username()
{
  return username_;
}

double Student::get_score()
{
  double correct_num = 0;
  for(int i = 0; i < num_problem_; ++i) {
    if(std::get<5>(problem_set_.at(i)) == std::get<6>(problem_set_.at(i))) {
      correct_num += 1;
    }
  }
  return round(correct_num * 100 / num_problem_);
}

int Student::get_num_problem() {
  return num_problem_;
}
