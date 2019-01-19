#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include <exception>
#include <string>
#include <QString>

class AppException : public std::exception
{

protected:
    AppException(QString file, long line, QString msg, QString type, QString details);

public: // overrides from std::exception
    virtual const char* what() const throw();
    virtual ~AppException() throw();
public:
    QString getFile() const { return m_file; }
    long getLine() const { return m_line; }
    QString getMsg() const { return m_msg; }
    QString getExceptionDetails() const { return m_details; }
    QString getType() const { return m_type; }

private:
    std::string generateWhat() const;

private:
    QString m_file;
    long m_line;
    QString m_msg;
    QString m_details;
    QString m_type;
    std::string m_what;
};


#endif // APPEXCEPTION_H
