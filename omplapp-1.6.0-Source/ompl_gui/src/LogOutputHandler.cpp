#include <pinocchio/fwd.hpp>
#include "LogOutputHandler.h"

#include <QMetaType>
#include <QThread>
#include <QScrollBar>
#include <QDebug>

LogOutputHandler::LogOutputHandler(QTextEdit* textEdit)
    : textEdit_(textEdit)
{
    // Setup some default colors
    redColor_    = QColor(255, 0, 0);
    orangeColor_ = QColor(255, 128, 0);
    greenColor_  = QColor(0, 255, 64);
    blackColor_  = QColor(0, 0, 0);
}

void LogOutputHandler::log(const std::string &text,
                           ompl::msg::LogLevel level,
                           const char *filename,
                           int line)
{
    Q_UNUSED(filename);
    Q_UNUSED(line);

    // Convert std::string to QString
    const QString qText = QString::fromStdString(text);

    // Pick the output style based on log level
    switch (level)
    {
        case ompl::msg::LOG_DEBUG:
            debug(qText);
            break;
        case ompl::msg::LOG_INFO:
            inform(qText);
            break;
        case ompl::msg::LOG_WARN:
            warn(qText);
            break;
        case ompl::msg::LOG_ERROR:
            error(qText);
            break;
        case ompl::msg::LOG_DEV1:
        case ompl::msg::LOG_DEV2:
            // If you want developer-level logs to appear like debug:
            debug(qText);
            break;
        default:
            // Fallback if new levels were introduced, etc.
            qDebug() << "[Unknown log level]" << qText;
            inform(qText);
            break;
    }

    // Optionally, ensure the view scrolls to the bottom:
    if (textEdit_->verticalScrollBar())
    {
        textEdit_->verticalScrollBar()->setValue(
            textEdit_->verticalScrollBar()->maximum());
    }
}

void LogOutputHandler::debug(const QString &text)
{
    textEdit_->setTextColor(greenColor_);
    textEdit_->append(text);
}

void LogOutputHandler::inform(const QString &text)
{
    textEdit_->setTextColor(blackColor_);
    textEdit_->append(text);
}

void LogOutputHandler::warn(const QString &text)
{
    textEdit_->setTextColor(orangeColor_);
    textEdit_->append(text);
}

void LogOutputHandler::error(const QString &text)
{
    textEdit_->setTextColor(redColor_);
    textEdit_->append(text);
}
