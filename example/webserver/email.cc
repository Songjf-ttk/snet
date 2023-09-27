#include "email.h"
#include <iostream>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>

EmailSender::EmailSender(const std::string& smtp_server,
                         const int smtp_port,
                         const std::string& from_email,
                         const std::string& password,
                         const std::string& from_name)
{
    // init settings
    m_smtp_url_ = smtp_server; // smtp://example.com
    m_from_ = std::make_pair(from_email, from_name);
    m_password_ = password;
    m_smtp_port_ = smtp_port;
}

EmailSender::~EmailSender()
{
}

void EmailSender::setEmailContent(const std::string& subject,
                                  const std::string& body)
{
    // set email title and body content
    m_email_subject_ = subject;
    m_email_body_ = body;
}

void EmailSender::addRecvEmailAddr(std::string email_addr, std::string name)
{
    // add receiver to list
    m_recvs_.push_back(std::make_pair(email_addr, name));
}

void EmailSender::addAttachment(const std::string& filename)
{
    // add attach filename to list
    m_attachments_.push_back(filename); // NOTICE: can be absolute or relative file path
}

bool EmailSender::send()
{
    try {
        Poco::Net::MailMessage message;
        for(auto recep:m_recvs_){
            message.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, std::move(recep.first), std::move(recep.second)));
        }
        message.setSender(m_from_.first);
        message.setSubject(m_email_subject_);
        message.setContent(m_email_body_);

        Poco::Net::SMTPClientSession session(m_smtp_url_, m_smtp_port_);
        session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, m_from_.first, m_password_);
        session.sendMessage(message);
        session.close();
    }
    catch (const Poco::Exception& e) {
        std::cerr << e.displayText() << std::endl;
        return false;
    }
    return true;
}