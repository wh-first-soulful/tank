#ifndef KEYPRESSEVENTFILTER_H
#define KEYPRESSEVENTFILTER_H

#include <QEvent>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QObject>
#include <QTimer>

class KeyPressEventFilter : public QObject {
    Q_OBJECT

public:
    explicit KeyPressEventFilter(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void keyPressStarted(int key);
    void keySinglePress(int key);
    void keyLongPressFinished(int key);
    void keyPressFinished(int key);
    void keyRepeat(int key);

private slots:
    void handleRepeat();

private:
    bool isKeyPressed;
    int currentKey;
    QElapsedTimer keyTimer;
    QTimer repeatTimer;
    const int longPressThreshold = 500; // Threshold for long press in milliseconds
    const int repeatInterval = 100; // Interval for repeat in milliseconds
};

#endif // KEYPRESSEVENTFILTER_H
