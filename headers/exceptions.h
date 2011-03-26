#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class Error
{
    QString msg_;
public:
    Error(const QString &str)
    {
        msg_ = str;
    }
    const QString& msg()
    {
        return msg_;
    }
};

#endif // EXCEPTIONS_H
