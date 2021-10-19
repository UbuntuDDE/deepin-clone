/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
 *
 * Author:     zccrs <zccrs@live.com>
 *
 * Maintainer: zccrs <zhangjide@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CLONEJOB_H
#define CLONEJOB_H

#include <QThread>

class CloneJob : public QThread
{
    Q_OBJECT

public:
    enum Status {
        Stoped,
        Started,
        Clone_Headgear,
        Clone_PartitionTable,
        Clone_Partition,
        Save_Info,
        Fix_Boot,
        Failed
    };

    explicit CloneJob(QObject *parent = 0);
    ~CloneJob();

    bool start(const QString &from, const QString &to);
    void abort();

    Status status() const;
    qreal progress() const;
    int estimateTime() const; // seconds

    QString errorString() const;

signals:
    void statusChanged(Status status);
    void failed(const QString &error);
    void finished();
    void progressChanged(qreal progress);

private:
    using QThread::start;

    void run() Q_DECL_OVERRIDE;

    void setStatus(Status s);
    void setErrorString(const QString &error);

    Status m_status;
    bool m_abort = false;

    QString m_from;
    QString m_to;

    QString m_errorString;

    qreal m_progress = 0;
    int m_estimateTime = 0;
};

#endif // CLONEJOB_H
