/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Edited by Hannes Tuhkala and Malcolm Vigren as part of lab 4 in TDDD86
 *
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk();
    Junk(Unit* c);
	bool isJunk() const override;

    void moveTowards(const Point& p) override;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;
};

#endif // JUNK_H
