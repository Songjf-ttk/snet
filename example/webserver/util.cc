#include "util.h"
#include <memory>
#include <random>
#include <fstream>
#include <filesystem>
#include "class/user.h"

std::string readFile(const std::string &filename)
{
    std::string content;
    if(!std::filesystem::exists(filename)){
        return content;
    }
    std::ifstream file(filename);
    if(!file){
        return content;
    }

    std::stringstream buffer;
    buffer<<file.rdbuf();
    return buffer.str();
}

bool SendEmail(std::string &to_email, std::string &to_name, std::string &verifycode)
{
    std::string smtp_server = "smtp.example.com";
    int smtp_port = 25;
    std::string from_email = "example@126.com";
    std::string password = "yourpassword";
    std::string email_subject = "Webserver verification code";
    std::string email_body =  "verification code is: "+verifycode+
                        "\n"
                        "thanks for watching, good luck\n"; // html format
    std::string from_name = "webserver";
    EmailSender email_sender(smtp_server, smtp_port, from_email, password, from_name);
    email_sender.addRecvEmailAddr(to_email, to_name);
    email_sender.setEmailContent(email_subject, email_body);
    bool sendsuccess = email_sender.send();
    return sendsuccess;
}

void options(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type");
    resp->String("");
}

void Login(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string account = req->json()["account"];
    std::string password = req->json()["password"];
    wfrest::Json json;

    // 判断密码是否正确
    std::shared_ptr<User> user = std::make_shared<Student>();
    int ret = user->Login(account, password);

    if (ret == -1) 
    {      
        json["success"] = false;
        json["info"] = "account doesn't exit";
        resp->add_header("Access-Control-Allow-Origin", "*");
        resp->Json(json);
        return;
    }else if(ret == -2)
    {
        json["success"] = false;
        json["info"] = "password error";
        resp->add_header("Access-Control-Allow-Origin", "*");
        resp->Json(json);
        return;
    }
    json["success"] = true;
    json["info"] = "login success";
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->Json(json);
    
}

void Logout(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    wfrest::Json json;
    json["success"] = true;
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->Json(json);
}

void SigninPre(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string email = req->json()["email"];
    std::string name = "teacher";
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(100000, 999999);
    int code = distr(eng);
    std::string verifycode = std::to_string(code);
    bool send_success = SendEmail(email, name, verifycode);
    wfrest::Json json;
    if(send_success){
        resp->Save(email, verifycode);
        json["success"] = true;
    }
    else 
        json["success"] = false;
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->Json(json);
}

void Signin(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string username = req->json()["username"];
    std::string password1 = req->json()["password1"];
    std::string password2 = req->json()["password2"];
    std::string email = req->json()["email"];
    std::string verifycode = req->json()["verifycode"];

    wfrest::Json json;
    json["success"] = false;
    std::string sendcode = readFile(email);
    if (sendcode != verifycode)
    {
        json["info"] = "verifycode error";
        resp->Json(json);
        return;
    }
    std::filesystem::remove(email);
    // 注册
    std::shared_ptr<User> user = std::make_shared<Student>();
    int ret = user->Register(username, email, password1, password2);
    
    
    if(ret == -1)
    {
        json["info"] = "username duplicate";
        resp->Json(json);
        return;
    }else if (ret == -2)
    {
        json["info"] = "The passwords entered twice are different";
        resp->Json(json);
        return;
    }else if(ret == -3)
    {
        json["info"] = "The password does not meet the requirements";
        resp->Json(json);
        return;
    }

    json["success"] = true;
    json["info"] = "register success";
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->Json(json);
}

void ResetPassword(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string oldpassword = req->json()["oldpassword"];
    std::string newpassword1 = req->json()["newpassword1"];
    std::string newpassword2 = req->json()["newpassword2"];
    wfrest::Json json;

    std::shared_ptr<User> user = std::make_shared<Student>();
    int ret = user->EditPassword(oldpassword, newpassword1, newpassword2);

    if(ret == -1)
    {
        json["success"] = false;
        json["info"] = "oldpassword error";
        resp->add_header("Access-Control-Allow-Origin", "*");
        resp->Json(json);
        return;
    }else if(ret == -2)
    {
        json["success"] = false;
        json["info"] = "The passwords entered twice are different";
        resp->add_header("Access-Control-Allow-Origin", "*");          
        resp->Json(json);
        return;
    }else if(ret == -3)
    {
        json["success"] = false;
        json["info"] = "The password does not meet the requirements";
        resp->add_header("Access-Control-Allow-Origin", "*");
        resp->Json(json);
        return;
    }

    json["success"] = true;
    json["info"] = "reset password success";
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->Json(json);
}




void ProducePaper(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string type = req->json()["type"];
    int question_num = req->json()["num"];
    
    // 生成题目
    std::shared_ptr<User> user = std::make_shared<Student>();
    int ret = user->SetProblem(type, question_num);

    wfrest::Json json;
    if(ret == -1)
    {
        json["success"] = false;
        resp->Json(json);
        return;
    }
    json["success"] = true;
    resp->Json(json);
}


void GetQuesion(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string numstr = req->param("questionId");
    int num = std::stoi(numstr);
    // 获取题目
    std::shared_ptr<User> user = std::make_shared<Student>();
    vtuple question = user->get_problem(num);

    wfrest::Json json;
    json["question"] =  std::get<0>(question);
    json["optionA"] = std::get<1>(question);
    json["optionB"] = std::get<2>(question);
    json["optionC"] = std::get<3>(question);
    json["optionD"] = std::get<4>(question);
    json["correctAns"] = std::get<5>(question);
    json["currentAns"] = std::get<6>(question);

    resp->Json(json);
}

