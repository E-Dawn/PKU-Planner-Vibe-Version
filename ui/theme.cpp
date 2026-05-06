#include "theme.h"

QString Theme::cardStyle() {
    return QString("background:%1; border-radius:%2px; border:1px solid %3;")
        .arg(CARD_BG).arg(CARD_RADIUS).arg(BORDER);
}

QString Theme::primaryButtonStyle() {
    return QString(
        "QPushButton {"
        "   background: %1;"
        "   color: white;"
        "   border: none;"
        "   border-radius: %2px;"
        "   padding: 10px 20px;"
        "   font-weight: 600;"
        "}"
        "QPushButton:hover { background: %3; }"
        "QPushButton:pressed { background: %4; }"
    ).arg(PRIMARY).arg(BUTTON_RADIUS).arg(PRIMARY_DARK).arg("#6A1520");
}

QString Theme::secondaryButtonStyle() {
    return QString(
        "QPushButton {"
        "   background: transparent;"
        "   color: %1;"
        "   border: 1px solid %2;"
        "   border-radius: %3px;"
        "   padding: 8px 16px;"
        "   font-weight: 600;"
        "}"
        "QPushButton:hover { background: %4; color: white; }"
    ).arg(PRIMARY).arg(PRIMARY_LIGHT).arg(BUTTON_RADIUS).arg(PRIMARY);
}

QString Theme::inputStyle() {
    return QString(
        "QLineEdit, QComboBox, QSpinBox, QDateTimeEdit {"
        "   border: 1px solid %1;"
        "   border-radius: %2px;"
        "   padding: 10px 12px;"
        "   background: %3;"
        "   color: %4;"
        "   font-size: 13px;"
        "}"
        "QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QDateTimeEdit:focus {"
        "   border: 2px solid %5;"
        "}"
    ).arg(BORDER).arg(INPUT_RADIUS).arg(CARD_BG).arg(TEXT_PRIMARY).arg(PRIMARY);
}