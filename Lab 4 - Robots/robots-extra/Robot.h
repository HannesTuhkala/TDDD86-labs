/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Edited by Hannes Tuhkala and Malcolm Vigren as part of lab 4 in TDDD86
 *
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    Robot();
    Robot(Unit* c);
	virtual bool isJunk() const;

    void draw(QGraphicsScene* scene) const override;

    /*
    * Am I in the same square as u?
    */
    bool at(const Unit& u) const;

    /*
     * Returns whether the robot can attack u
     */
    bool attacks(const Unit& u) const;
};

#endif // ROBOT_H
