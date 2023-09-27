#ifndef _EMAIL_H_
#define _EMAIL_H_

#include <string>
#include <vector>
#include <utility>

class EmailSender 
{
public:
    EmailSender(const std::string& smtp_server,
                const int smtp_port,
                const std::string& from_email,
                const std::string& password,
                const std::string& from_name="");
    ~EmailSender();
    void setEmailContent(const std::string& subject="",
                         const std::string& body=""); // body can be html format or plain text
    void addRecvEmailAddr(std::string email_addr, std::string name="");
    void addAttachment(const std::string& filename);
    bool send();

private:
    std::string m_smtp_url_;
    std::pair<std::string, std::string> m_from_;
    std::string m_password_;
    std::vector<std::pair<std::string, std::string>> m_recvs_; // list of (email,name)
    std::string m_email_subject_;
    std::string m_email_body_;
    std::vector<std::string> m_attachments_; // list of filename
    int m_smtp_port_;
};
 

#endif 