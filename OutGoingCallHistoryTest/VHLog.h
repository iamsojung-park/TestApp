#ifndef VH_VHLOG_H__
#define VH_VHLOG_H__

#include <QObject>
#include <QString>
#include <QTime>

// DEBUG OUTPUT OPTION
#define VH_DEBUG_OUTPUT                 1   // Total control - 0: OFF, 1: ON

// TICKTIME OUTPUT OPTION
#define VH_DEBUG_TICKTIME               1   // TickTime control - 0: OFF, 1: ON

class VHLog
{
public:

    static void debug(QString message);

private:
    VHLog();
};

#endif // VH_VHLOG_H__
