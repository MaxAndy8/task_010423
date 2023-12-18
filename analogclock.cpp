#include "analogclock.h"
//#include "ui_analogclock.h"
#include <QPainter>
#include <QTime>
#include <QTimer>

AnalogClock::AnalogClock(QWidget *parent)
    : QWidget(parent)  {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));

    timer->start(1000);

    setWindowTitle(tr("Analog Clock"));
    resize(200, 200);
}

void AnalogClock::paintEvent(QPaintEvent *) {
    static const QPoint hourHand[4] = {
                                       QPoint(5, 7),
                                       QPoint(-5, 7),
                                       QPoint(0, -40)

    };
    static const QPoint minuteHand[4] = {
                                         QPoint(5, 7),
                                         QPoint(-5, 7),
                                         QPoint(0, -70)

    };

    static const QPoint secondsHand[4] = {
        QPoint(1, 14),
        QPoint(-1, 14),
        QPoint(0, -89)
    };

    const QColor hourColor(127, 0, 127);
    const QColor minuteColor(0, 127, 127);
    const QColor secondsColor(0, 0, 127);

    int side = qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    QTime time = QTime::currentTime();

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();

    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();
    painter.setPen(hourColor);
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * time.minute());
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setBrush(secondsColor);

    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(secondsHand, 3);
    painter.drawEllipse(-3, -3, 6, 6);
    painter.restore();

    painter.setPen(minuteColor);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }



}

AnalogClock::~AnalogClock()
{

}

