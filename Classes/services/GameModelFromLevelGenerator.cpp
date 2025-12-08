#include "GameModelFromLevelGenerator.h"

GameModel *GameModelFromLevelGenerator::generateGameModel(const LevelConfig &config)
{
    GameModel *model = new GameModel();

    int idCounter = 0;

    for (const auto &cc : config.playfieldCards)
    {
        CardModel *card = new CardModel();
        card->init(idCounter++, cc.face, cc.suit, cc.position);
        card->setFaceUp(true); // Default to true for now
        model->addPlayfieldCard(card);
    }

    for (const auto &cc : config.stackCards)
    {
        CardModel *card = new CardModel();
        card->init(idCounter++, cc.face, cc.suit, cc.position);
        card->setFaceUp(false);
        model->addReserveCard(card);
    }

    // Flip the top card of the stack (draw one from reserve)
    CardModel *topStack = model->drawFromReserve();
    if (topStack)
    {
        topStack->setFaceUp(true);
    }

    return model;
}
