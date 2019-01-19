#include "appexception.h"
#include <sstream>

AppException::AppException(QString file, long line, QString msg, QString type, QString details)
    : m_file(file),
    m_line(line),
    m_msg(msg),
    m_details(details),
    m_type(type)
{
    m_what = generateWhat();
}

AppException::~AppException() throw()
{

}
const char* AppException::what() const throw()
{
    return m_what.c_str();
}

std::string AppException::generateWhat() const
{
    std::stringstream s;
    s << m_type.toStdString() << " (" << m_file.toStdString() << ":" << m_line << "): " << m_msg.toStdString();
    if (!m_details.isEmpty())
    {
        s << std::endl << m_details.toStdString();
    }
    return s.str();
}
