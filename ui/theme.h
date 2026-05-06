#ifndef THEME_H
#define THEME_H

#include <QString>

namespace Theme
{
    // 主色调 - 北大红
    const QString PRIMARY = "#8B1E2D";
    const QString PRIMARY_LIGHT = "#FBECEE";
    const QString PRIMARY_LIGHTER = "#FFE4E4";
    const QString PRIMARY_DARK = "#7A1A25";

    // 背景色
    const QString BACKGROUND = "#F7F3EF";
    const QString CARD_BG = "#FFFFFF";
    const QString BORDER = "#EFEAEA";

    const QString TEXT_PRIMARY = "#222222";
    const QString TEXT_SECONDARY = "#666666";
    const QString TEXT_TERTIARY = "#999999";

    const QString SUCCESS = "#2E7D32";
    const QString WARNING = "#F57C00";
    const QString DANGER = "#C62828";

    const int CARD_RADIUS = 16;
    const int BUTTON_RADIUS = 12;
    const int INPUT_RADIUS = 10;

    QString cardStyle();
    QString primaryButtonStyle();
    QString secondaryButtonStyle();
    QString inputStyle();
}

#endif