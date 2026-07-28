#include "normalenemy.h"

NormalEnemy::NormalEnemy(const QString& name, int hp, QGraphicsItem *parent)
    : Enemy(name, hp, parent)
{
    QString formattedName = name.toLower().replace(" ", "_");

    if (formattedName == "green_louse") formattedName = "lousegreen";
    else if (formattedName == "red_louse") formattedName = "lousered";
    else if (formattedName == "blue_slaver") formattedName = "slaverblue";
    else if (formattedName == "red_slaver") formattedName = "slaverred";
    else if (formattedName == "jaw_worm") formattedName = "jawworm";
    else if (formattedName == "small_slime") formattedName = "smallslime";
    else if (formattedName == "medium_slime") formattedName = "mediumslime";
    else if (formattedName == "large_slime") formattedName = "largeslime";
    else if (formattedName == "spheric_guardian") formattedName = "sphericguardian";
    else if (formattedName == "cultist") formattedName = "cultist";

    m_imagePath = QString(":/normalenemies/%1.png").arg(formattedName);
}

NormalEnemy::NormalEnemy(const NormalEnemy& other) : Enemy(other) {}

int NormalEnemy::getGoldReward() const {
    return 15 + (rand() % 11);
}

bool NormalEnemy::hasPotionDrop() const {
    return (rand() % 100) < 30;
}