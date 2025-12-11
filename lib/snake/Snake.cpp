#include "Snake.h"

Snake::Snake() {
    reset();
}

void Snake::reset() {
    body.clear();
    // Начальная позиция в центре
    body.push_front({GRID_W / 2, GRID_H / 2});
    body.push_back({GRID_W / 2 - 1, GRID_H / 2});
    currentDirection = Direction::RIGHT;
    growing = false;
}

void Snake::setDirection(Direction dir) {
    // Запрещаем разворот на 180 градусов
    if (dir == Direction::UP && currentDirection == Direction::DOWN) return;
    if (dir == Direction::DOWN && currentDirection == Direction::UP) return;
    if (dir == Direction::LEFT && currentDirection == Direction::RIGHT) return;
    if (dir == Direction::RIGHT && currentDirection == Direction::LEFT) return;
    currentDirection = dir;
}

Direction Snake::getDirection() const {
    return currentDirection;
}

void Snake::update() {
    if (currentDirection == Direction::NONE) return;

    sf::Vector2i newHead = body.front();

    switch (currentDirection) {
        case Direction::UP:    newHead.y--; break;
        case Direction::DOWN:  newHead.y++; break;
        case Direction::LEFT:  newHead.x--; break;
        case Direction::RIGHT: newHead.x++; break;
        default: break;
    }

    body.push_front(newHead);

    if (!growing) {
        body.pop_back();
    } else {
        growing = false;
    }
}

void Snake::grow() {
    growing = true;
}

bool Snake::checkSelfCollision() const {
    sf::Vector2i head = body.front();
    // Проверяем, совпадает ли голова с любой другой частью тела
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i] == head) return true;
    }
    return false;
}

bool Snake::checkWallCollision() const {
    sf::Vector2i head = body.front();
    return (head.x < 0 || head.x >= GRID_W || head.y < 0 || head.y >= GRID_H);
}

const std::deque<sf::Vector2i>& Snake::getBody() const {
    return body;
}

sf::Vector2i Snake::getHead() const {
    return body.front();
}