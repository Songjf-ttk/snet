#ifndef _UTIL_H_
#define _UTIL_H_
#include <map>
#include "workflow/WFFacilities.h"
#include "wfrest/HttpServer.h"
#include "email.h"

// api: /login POST
// in : json{account, password}
// out: json{success, info} 
void Login(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

// api: /logout POST
// in : json{}
// out: json{success}
void Logout(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

// api: /signinpre POST
// in : json{email}
// out: json{success}
void SigninPre(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

// api: /signin POST
// in : json{username, password1, password2, email, verifycode}
// out: json{success, info}
void Signin(const wfrest::HttpReq *req, wfrest::HttpResp *resp);


// api: /reset-password POST
// in : json{account, oldpassword, newpassword1, newpassword2}
// out: json{success, info} 
void ResetPassword(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

// api: /produce-paper POST
// in : json{account, type, num}
// out: json{success}
void ProducePaper(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

// api: /get-question/{questionId} GET
// in : null
// out: json{quesiton, optionA, optionsB, optionsC, 
//           optionD, correctAns, currentAns}
void GetQuesion(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

//api: /get-score POST
//in : json{account}
//out: json{success, score}
void GetScore(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

//api: /upload-answer POST
//in : json{account, n_problem, answer}
//out: 
void UploadAnswers(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

bool SendEmail(std::string &to_email, std::string &to_name, std::string &verifycode);

std::string readFile(const std::string&);

std::map<std::string, std::string> loadConfig(const std::string& filename);

#endif