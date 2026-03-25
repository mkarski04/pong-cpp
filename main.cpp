#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
    window.setFramerateLimit(60);

    sf::RectangleShape leftPaddle(sf::Vector2f(15.f, 100.f));
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setPosition(50.f, 250.f);

    sf::RectangleShape rightPaddle(sf::Vector2f(15.f, 100.f));
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setPosition(735.f, 250.f);

    float paddleSpeed = 5.f;

    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(390.f, 290.f);
    float ballVelocityX = (rand() % 2 == 0) ? 5.f : -5.f;
    float ballVelocityY = (rand() % 2 == 0) ? 5.f : -5.f;

    sf::Clock resetClock;
    bool isBallWaiting = true;

    sf::Font font;
    if (!font.loadFromFile("calibri.ttf")) {
        return -1;
    }

    int leftScore = 0;
    int rightScore = 0;

    sf::Text leftScoreText;
    leftScoreText.setFont(font);
    leftScoreText.setString("0");
    leftScoreText.setCharacterSize(200);
    leftScoreText.setFillColor(sf::Color(255, 255, 255, 50));
    leftScoreText.setPosition(150.f, 150.f);

    sf::Text rightScoreText;
    rightScoreText.setFont(font);
    rightScoreText.setString("0");
    rightScoreText.setCharacterSize(200);
    rightScoreText.setFillColor(sf::Color(255, 255, 255, 50));
    rightScoreText.setPosition(550.f, 150.f);

    sf::RectangleShape middleLine(sf::Vector2f(2.f, 600.f));
    middleLine.setFillColor(sf::Color(255, 255, 255, 50));
    middleLine.setPosition(399.f, 0.f);

    bool isPlaying = false;

    sf::Text startText;
    startText.setFont(font);
    startText.setString("Press SPACE to start");
    startText.setCharacterSize(50);
    startText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = startText.getLocalBounds();
    startText.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    startText.setPosition(400.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // GAME LOGIC
        if (!isPlaying) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                isPlaying = true;
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                isPlaying = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                leftPaddle.move(0.f, -paddleSpeed);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                leftPaddle.move(0.f, paddleSpeed);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                rightPaddle.move(0.f, -paddleSpeed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                rightPaddle.move(0.f, paddleSpeed);
            }

            if (isBallWaiting) {
                if (resetClock.getElapsedTime().asSeconds() > 1.0f) {
                    isBallWaiting = false;
                }
            }else {
                ball.move(ballVelocityX, ballVelocityY);
            }
        }

            // BOUNDARIES
            if (leftPaddle.getPosition().y < 0.f) {
                leftPaddle.setPosition(50.f, 0.f);
            }
            if (leftPaddle.getPosition().y > 500.f) {
                leftPaddle.setPosition(50.f, 500.f);
            }
            if (rightPaddle.getPosition().y < 0.f) {
                rightPaddle.setPosition(735.f, 0.f);
            }
            if (rightPaddle.getPosition().y > 500.f) {
                rightPaddle.setPosition(735.f, 500.f);
            }

            if (ball.getPosition().y < 0.f || ball.getPosition().y > 580.f) {
                ballVelocityY = -ballVelocityY;
            }

            if (ball.getPosition().x < 0.f) {
                rightScore++;
                rightScoreText.setString(std::to_string(rightScore));

                ball.setPosition(390.f, 290.f);
                ballVelocityX = (rand() % 2 == 0 ) ? 5.f : -5.f;
                ballVelocityY = (rand() % 2 == 0 ) ? 5.f : -5.f;

                isBallWaiting = true;
                resetClock.restart();
            }
            if (ball.getPosition().x > 800.f) {
                leftScore++;
                leftScoreText.setString(std::to_string(leftScore));

                ball.setPosition(390.f, 290.f);
                ballVelocityX = (rand() % 2 == 0 ) ? 5.f : -5.f;
                ballVelocityY = (rand() % 2 == 0 ) ? 5.f : -5.f;

                isBallWaiting = true;
                resetClock.restart();
            }

            // COLLISIONS
            sf::FloatRect overlap;

            if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds(), overlap)) {
                if (overlap.width < overlap.height) {
                    ballVelocityX *= -1.05f;
                    ballVelocityY *= 1.05f;
                    ball.move(overlap.width, 0.f);
                } else {
                    ballVelocityY *= -1.05f;
                    ballVelocityX *= 1.05f;
                    if (ball.getPosition().y < leftPaddle.getPosition().y + 50.f) {
                        ball.move(0.f, -overlap.height);
                    } else {
                        ball.move(0.f, overlap.height);
                    }
                }
            }

            if (ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds(), overlap)) {
                if (overlap.width < overlap.height) {
                    ballVelocityX *= -1.05f;
                    ballVelocityY *= 1.05f;
                    ball.move(-overlap.width, 0.f);
                } else {
                    ballVelocityY *= -1.05f;
                    ballVelocityX *= 1.05f;
                    if (ball.getPosition().y < rightPaddle.getPosition().y + 50.f) {
                        ball.move(0.f, -overlap.height);
                    } else {
                        ball.move(0.f, overlap.height);
                    }
                }
            }

            window.clear(sf::Color::Black);

            if (!isPlaying) {
                window.draw(startText);
            }else {
                window.draw(leftScoreText);
                window.draw(rightScoreText);
                window.draw(middleLine);

                window.draw(leftPaddle);
                window.draw(rightPaddle);
                window.draw(ball);
            }

                window.display();
        }

    return 0;
}