#ifndef _UTIL_H_
#define _UTIL_H_
#include "workflow/WFFacilities.h"
#include "wfrest/HttpServer.h"

// api: /login POST
// in : json{user,password}
// out: json{success} 
void Login(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

// api: /logout POST
// in : json{}
// out: json{success}
void Logout(const wfrest::HttpReq *req, wfrest::HttpResp *resp);


// api: /signin POST
// in : json{user,password1,password2,email}
// out: json{success}
void Signin(const wfrest::HttpReq *req, wfrest::HttpResp *resp);


// api: /reset-password POST
// in : json{oldpassword,newpassword1,newpassword2}
// out: json{success} 
void ResetPassword(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

// api: /produce-paper
// in : json{difficulty,num}
// out: json{success}
void ProducePaper(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

// api: /get-question/{questionId} GET
// in : null
// out: json{quesiton,options}
void GetQuesion(const wfrest::HttpReq *req, wfrest::HttpResp *resp);

#endif