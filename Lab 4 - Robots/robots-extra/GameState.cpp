/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Edited by Hannes Tuhkala and Malcolm Vigren as part of lab 4 in TDDD86
 *
 */

#include <iostream>
#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <typeinfo>

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot = new Robot();
        while (!isEmpty(*robot) && robot->isJunk()) {
            delete robot;
            robot = new Robot();
        }

        robots.push_back(robot);
    }
    teleportHero();
}

GameState::~GameState() {
    this->clear();
}

GameState::clear() {
    for (Robot* robot : robots) {
        delete robot;
    }

    robots.clear();
}

GameState::GameState(const GameState& gs) {
    *this = gs;
}

GameState& GameState::operator=(const GameState& gs) {
    if (this != &gs) {
        this->hero = gs.hero;

        this->clear();

        for (Robot* robot : gs.robots) {
            Robot* temp = new Robot(*robot);
            this->robots.push_back(temp);
        }
    }

    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();

    for (size_t i = 0; i < robots.size(); ++i) {
        robots[i]->draw(scene);
    }

    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards (hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;
    while (i < robots.size()) {
        bool hitJunk = robots[i]->isJunk();
        bool collision = (countRobotsAt(*robots[i]) > 1);
        if (collision && !hitJunk) {
            Robot* temp = robots[i];
            robots[i] = new Junk((*robots[i]));
            delete temp;
            numberDestroyed++;
        } else {
            i++;
        }
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for (Robot* robot : robots) {
        if (!robot->isJunk()) {
            return true;
        }
    }

    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++) {
        if (robots[i]->attacks(unit)) return false;
    }

    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(const Unit& unit) const {
    return (countRobotsAt(unit) == 0);// && !(robot.isJunk());
}

/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}
