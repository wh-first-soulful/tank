#include "KeyPressEventFilter.h"

KeyPressEventFilter::KeyPressEventFilter(QObject *parent) : QObject(parent), isKeyPressed(false) {
    repeatTimer.setInterval(repeatInterval);
    repeatTimer.setSingleShot(false);
    connect(&repeatTimer, &QTimer::timeout, this, &KeyPressEventFilter::handleRepeat);
}

bool KeyPressEventFilter::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (!isKeyPressed) {
            isKeyPressed = true;
            currentKey = keyEvent->key();
            keyTimer.start();
            repeatTimer.start();
            emit keyPressStarted(currentKey);
        }
        return true;
    } else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (isKeyPressed && keyEvent->key() == currentKey) {
            isKeyPressed = false;
            repeatTimer.stop();
            if (keyTimer.elapsed() < longPressThreshold) {
                emit keySinglePress(currentKey);
            } else {
                emit keyLongPressFinished(currentKey);
            }
            emit keyPressFinished(currentKey);
        }
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void KeyPressEventFilter::handleRepeat() {
    emit keyRepeat(currentKey);
}
