#ifndef LOGOUTPUTHANDLER_H
#define LOGOUTPUTHANDLER_H

#include <ompl/util/Console.h>  // Provides ompl::msg::LogLevel, OutputHandler, etc.
#include <QTextEdit>
#include <QColor>

/**
 * @brief A custom OMPL OutputHandler that writes log messages into a QTextEdit.
 *
 * This class inherits from ompl::msg::OutputHandler and overrides the
 * log(...) method. Depending on the log level, it writes text in
 * different colors.
 */
class LogOutputHandler : public ompl::msg::OutputHandler
{
public:
    /**
     * @brief Construct a LogOutputHandler with a pointer to a QTextEdit
     *        (the widget where logs should appear).
     */
    explicit LogOutputHandler(QTextEdit* textEdit);

    /**
     * @brief Called by OMPL whenever a log message is printed.
     * @param text     The message to be logged.
     * @param level    The log severity level (Debug, Info, Warn, Error, etc.).
     * @param filename The source file that generated this log (unused here).
     * @param line     The line number that generated this log (unused here).
     */
    void log(const std::string &text,
             ompl::msg::LogLevel level,
             const char *filename,
             int line) override;

private:
    // Helper methods for writing in different colors:
    void debug(const QString &text);
    void inform(const QString &text);
    void warn(const QString &text);
    void error(const QString &text);

    QTextEdit *textEdit_;  ///< The text widget where messages are displayed.

    // Example colors:
    QColor redColor_;
    QColor orangeColor_;
    QColor greenColor_;
    QColor blackColor_;
};

#endif // LOGOUTPUTHANDLER_H
