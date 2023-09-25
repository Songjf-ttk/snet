#include "util.h"

void Login(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string user = req->json()["user"];
    std::string password = req->json()["password"];
    wfrest::Json json;
    bool passwordright = false;

    // 判断密码是否正确
    passwordright = true;

    if (passwordright) 
    {      
        json["success"] = true;
    }else 
    {
        json["success"] = false;
    }
    resp->Json(json);
}

void Logout(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    wfrest::Json json;
    json["success"] = true;
    resp->Json(json);
}

void Signin(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string user = req->json()["user"];
    std::string password1 = req->json()["password1"];
    std::string password2 = req->json()["password2"];
    std::string email = req->json()["email"];

    wfrest::Json json;
    if (password1 != password2){
        json["success"] = false;
        resp->Json(json);
        return;
    }
    // 注册

    
    json["success"] = true;
    resp->Json(json);
}

void ResetPassword(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    // if (req->content_type() != wfrest::MULTIPART_FORM_DATA)
    // {
    //     resp->set_status(HttpStatusBadRequest);
    //     return;
    // }

    std::string oldpassword = req->json()["oldpassword"];
    std::string newpassword1 = req->json()["newpassword1"];
    std::string newpassword2 = req->json()["newpassword2"];
    wfrest::Json json;
    // 验证旧密码
    
    if(newpassword1 != newpassword2) {
        json["success"] = false;
    }

    //更新密码

    json["success"] = true;
    resp->Json(json);
}




void ProducePaper(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    std::string difficulty = req->json()["difficulty"];
    std::string question_num = req->json()["num"];
    
    // 生成题目

    wfrest::Json json;
    json["success"] = true;
    resp->Json(json);
}


void GetQuesion(const wfrest::HttpReq *req, wfrest::HttpResp *resp)
{
    const std::string numstr = req->param("questionId");
    int num = std::stoi(numstr);
    // 获取题目

    wfrest::Json json;
    json["question"] = "null";
    json["options"] = "A B C D";
    resp->Json(json);
}

