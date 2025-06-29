#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const unsigned int WIDTH = (VideoMode::getDesktopMode().size.x / 2);
const unsigned int HEIGHT = (VideoMode::getDesktopMode().size.y / 2);
constexpr int N = 11;
constexpr float RADIUS = 30.f;
constexpr Color GRAY{77, 77, 77, 255};
constexpr Color RED{255,12,123, 255};
constexpr Color GREEN{55, 255, 155, 255};
constexpr Color WHITE{255, 255, 255, 255};

static Font font;

class Circle {
  private:
    int m_num;
    CircleShape m_circle;
    float m_radius;
    Color m_color;

    float m_sx;
    float m_sy;

    bool m_active;

    Font m_font;
    Text m_text;

  public:
    Circle() : m_text(m_font) {
      m_num = 0;
      m_radius = 0.0;
      m_color = WHITE;
      m_sx = 0.0;
      m_sy = 0.0;
      m_active = false;

      m_circle.setRadius(50.f);
      m_circle.setFillColor(GREEN);
      m_circle.setOrigin({m_circle.getRadius() / 2, m_circle.getRadius() / 2});
    }

    Circle(int num, float radius, Color color) : m_text(m_font) {
      if (!m_font.openFromFile("/usr/share/fonts/TTF/Arial.TTF"))
        throw runtime_error("failed to load font");
      m_num = num;
      m_radius = radius;
      m_color = color;
      m_sx = 0.0;
      m_sy = 0.0;
      m_active = false;

      m_circle = CircleShape(rand() % (30 - 10 + 1) + 10, 30);
      m_circle.setOrigin({m_circle.getRadius() / 2, m_circle.getRadius() / 2});
      m_circle.setPosition({0, 0});
      m_circle.setFillColor(m_color);
    }

    Vector2f getpos() {
      return m_circle.getPosition();
    }

    void setpos(Vector2f pos) {
      m_circle.setPosition(pos);
      m_text.setFont(m_font);
      m_text.setString(to_string(m_num));
      m_text.setPosition(pos);
      m_text.setFillColor(Color::Black);
      m_text.setCharacterSize(m_radius);
    }

    void draw(RenderWindow* window) {
      window->draw(m_circle);
      window->draw(m_text);
    }

    bool getactive() {
      return m_active;
    }

    void setactive(bool activebool) {
      m_active = activebool;
    }

    Color getcolor() {
      return m_color;
    }

    void setcolor(Color color) {
      m_circle.setFillColor(color);
    }

    int getnum() {
      return m_num;
    }

    void setnum(int num) {
      m_num = num;
    }

    float getsx() {
      return m_sx;
    }

    void setsx(float sx) {
      m_sx = sx;
    }


    float getsy() {
      return m_sy;
    }

    void setsy(float sy) {
      m_sy = sy;
    }

    CircleShape* getcircle() {
      return &m_circle;
    }

    void move() {

      m_circle.move({m_sx, m_sy});

      if (m_sx > 0.0) {
        m_sx -= 0.05;
      }
      else if (m_sx < 0.0) {
        m_sx += 0.05;
      }
      else {
        m_sx = 0.000000;
      }

      if (m_sy > 0.0) {
        m_sy -= 0.05;
      }
      else if (m_sy < 0.0) {
        m_sy += 0.05;
      }
      else {
        m_sy = 0.000000;
      }

      if (m_circle.getPosition().x + m_radius > WIDTH) {
        m_circle.setPosition({WIDTH - m_radius, m_circle.getPosition().y});
        m_sx = -1.0 * m_sx;
      }
      else if (m_circle.getPosition().x - m_radius < 0.0) {
        m_circle.setPosition({m_radius, m_circle.getPosition().y});
        m_sx = -1.0 * m_sx;
      }

      if (m_circle.getPosition().y + m_radius > HEIGHT) {
        m_circle.setPosition({m_circle.getPosition().x, HEIGHT - m_radius});
        m_sy = -1.0 * m_sy;
      }
      else if (m_circle.getPosition().y - m_radius < 0.0) {
        m_circle.setPosition({m_circle.getPosition().x, m_radius});
        m_sy = -1.0 * m_sy;
      }

      m_text.setPosition(m_circle.getPosition());

    }
};

float getrand(int max, int min, int i) {
  float num;
  srand(i * time(NULL));
  num = rand() % (max - min + 1) + min;
  return num;
}

void mainloop() {

  RenderWindow window(VideoMode({WIDTH, HEIGHT}), "window", Style::None, State::Windowed);
  window.setFramerateLimit(60);
  window.setPosition({static_cast<int>(WIDTH - window.getSize().x / 2), static_cast<int>(HEIGHT - window.getSize().y / 2)});


  Circle circles[N];
  for (int i = 0; i < N; i++) {
    circles[i] = Circle(i, 30.0, RED);
  }
  int num;
  num = getrand(N - 1, 0, 0);
  float w;
  float h;
  for (int i = 0; i < N; i++) {
    w = getrand(WIDTH, 10, i);
    h = getrand(HEIGHT, 10, i);
    circles[i].setpos({w, h});
    for (int j = N - 1; j >= 0; j--) {
      FloatRect aBounds = circles[i].getcircle()->getGlobalBounds();
      FloatRect bBounds = circles[j].getcircle()->getGlobalBounds();
      if (!aBounds.findIntersection(bBounds)) {
      }
      else if (aBounds.findIntersection(bBounds)) {
        w = getrand(WIDTH, 10, j);
        h = getrand(HEIGHT, 10, j);
        circles[i].setpos({w, h});
      }
    }
  }


  Circle* active = &circles[num];
  circles[num].setactive(true);

  while (window.isOpen()) {

    while (const optional event = window.pollEvent()) {
      if (event->is<Event::Closed>() || (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Q))
        window.close();
      if (event->is<Event::KeyPressed>()) {
        switch (event->getIf<Event::KeyPressed>()->code) {
          case (Keyboard::Key::Tab):
            circles[num].setactive(false);
            if (num == 10)
              num = 0;
            else
              num += 1;
            circles[num].setactive(true);
            break;
          case (Keyboard::Key::H):
            active->setsx(active->getsx() - 1.0);
            break;
          case (Keyboard::Key::J):
            active->setsy(active->getsy() + 1.0);
            break;
          case (Keyboard::Key::K):
            active->setsy(active->getsy() - 1.0);
            break;
          case (Keyboard::Key::L):
            active->setsx(active->getsx() + 1.0);
            break;
          default:
            break;
        }
      }
    }

    window.clear(GRAY);

    for (int i = 0; i < N; i++) {
      if (circles[i].getactive() == true) {
        active = &circles[i];
        circles[i].setcolor(GREEN);
      }
      else
        circles[i].setcolor(RED);
      circles[i].draw(&window);
      circles[i].move();
    }

    window.display();
  }
}

int main(void) {

  mainloop();

  return 0;
}
