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

std::map<std::string, std::string> loadConfig(const std::string& filename) {
    std::map<std::string, std::string> config;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open config file: " << filename << std::endl;
        return config;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, ':')) {
            std::string value;
            if (std::getline(is_line, value)) {
                config[key] = value;
            }
        }
    }

    return config;
}

bool SendEmail(std::string &to_email, std::string &to_name, std::string &verifycode)
{
    
    auto config = loadConfig("config.txt");
    std::string smtp_server = config["smtp_server"];
    int smtp_port = 25;
    std::string from_email = config["from_email"];
    std::string password = config["password"];
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

void Login(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    wfrest::Json json;
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    std::string account = req->json()["account"];
    std::string password = req->json()["password"];
    // 判断密码是否正确
    std::shared_ptr<User> user = std::make_shared<Student>();
    int ret = user->Login(account, password);

    if (ret == -1) 
    {      
        json["success"] = false;
        json["info"] = "account doesn't exit";
        resp->Json(json);
        return;
    }else if(ret == -2)
    {
        json["success"] = false;
        json["info"] = "password error";
        resp->Json(json);
        return;
    }
    json["success"] = true;
    json["username"] = user->get_username();
    json["info"] = "login success";
    resp->Json(json);
}

void Logout(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    wfrest::Json json;
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    json["success"] = true;
    resp->Json(json);
}

void SigninPre(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    wfrest::Json json;
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    std::string email = req->json()["email"];
    std::string name = "teacher";
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(100000, 999999);
    int code = distr(eng);
    std::string verifycode = std::to_string(code);
    bool send_success = SendEmail(email, name, verifycode);
    
    if(send_success){
        resp->Save("code/"+email, verifycode);
        json["success"] = true;
    }
    else 
        json["success"] = false;

    resp->Json(json);
}

void Signin(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    wfrest::Json json;
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    std::string username = req->json()["username"];
    std::string password1 = req->json()["password1"];
    std::string password2 = req->json()["password2"];
    std::string email = req->json()["email"];
    std::string verifycode = req->json()["verifycode"];

    json["success"] = false;
    std::string sendcode = readFile("code/"+email);
    if (sendcode != verifycode)
    {
        json["info"] = "verifycode error";
        resp->Json(json);
        return;
    }
    std::filesystem::remove("code/"+email);
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
    resp->Json(json);
}

void ResetPassword(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    wfrest::Json json;
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    std::string account = req->json()["account"];
    std::string oldpassword = req->json()["oldpassword"];
    std::string newpassword1 = req->json()["newpassword1"];
    std::string newpassword2 = req->json()["newpassword2"];

    std::shared_ptr<User> user = std::make_shared<Student>(account);
    int ret = user->EditPassword(oldpassword, newpassword1, newpassword2);

    if(ret == -1)
    {
        json["success"] = false;
        json["info"] = "oldpassword error";
        resp->Json(json);
        return;
    }else if(ret == -2)
    {
        json["success"] = false;
        json["info"] = "The passwords entered twice are different"; 
        resp->Json(json);
        return;
    }else if(ret == -3)
    {
        json["success"] = false;
        json["info"] = "The password does not meet the requirements";
        resp->Json(json);
        return;
    }

    json["success"] = true;
    json["info"] = "reset password success";

    resp->Json(json);
}




void ProducePaper(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    wfrest::Json json;
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    
    std::string account = req->json()["account"];
    std::string type = req->json()["type"];
    int question_num = req->json()["num"];
    
    // 生成题目
    std::shared_ptr<User> user = std::make_shared<Student>(account);
    int ret = user->SetProblem(type, question_num);

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
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    wfrest::Json json;
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    std::string numstr = req->param("questionId");
    std::string account = req->json()["account"];
    int num = std::stoi(numstr);
    // 获取题目
    std::shared_ptr<User> user = std::make_shared<Student>(account);
    vtuple question = user->get_problem(num);

    std::string q = std::get<0>(question);
    std::string opa = std::get<1>(question);
    std::string opb = std::get<2>(question);
    std::string opc = std::get<3>(question);
    std::string opd = std::get<4>(question);
    char correctAns = std::get<5>(question);
    char currentAns = std::get<6>(question);

    json["question"] =  q;
    json["optionA"] = opa;
    json["optionB"] = opb;
    json["optionC"] = opc;
    json["optionD"] = opd;
    json["correctAns"] = correctAns;
    json["currentAns"] = currentAns;
    resp->Json(json);
}

void GetScore(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    wfrest::Json json;
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    std::string account = req->json()["account"];
    std::shared_ptr<User> user = std::make_shared<Student>(account);
    double score = user->get_score();
    json["success"] = true;
    json["score"] = score;
    resp->Json(json);
}

void UploadAnswers(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    resp->add_header("Access-Control-Allow-Origin", "*");
    resp->add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE");
    resp->add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    std::string method = req->get_method();
    wfrest::Json json;
    if(method == "OPTIONS"){
        resp->Json(json);
        return;
    }
    std::string account = req->json()["account"];
    std::string IdStr = req->json()["n_problem"];
    int Id = std::stoi(IdStr);
    std::string anwser = req->json()["anwser"];
    std::shared_ptr<User> user = std::make_shared<Student>(account);
    user->set_answer(Id, anwser.c_str()[0]);
    json["success"] = true;
    resp->Json(json);
}
