#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdlib.h>

#define WIDTH (VideoMode::getDesktopMode().size.x / 2)
#define HEIGHT (VideoMode::getDesktopMode().size.y / 2)
#define N 11
#define GRAY (Color){77, 77, 77, 255}
#define RED (Color){255,12,123, 255}
#define GREEN (Color){55, 255, 155, 255}
#define WHITE (Color){255, 255, 255, 255}
#define RADIUS 30.0

using namespace std;
using namespace sf;

class Circle {
  private:
    int m_num;
    CircleShape m_circle;
    float m_radius;
    Color m_color;

    float m_sx;
    float m_sy;

    bool m_active;
  public:

    Circle() {
      m_num = 0;
      m_radius = 0.0;
      m_color = WHITE;
      m_sx = 0.0;
      m_sy = 0.0;
      m_active = false;
    }

    Circle(int num, float radius, Color color) {
      m_num = num;
      m_radius = radius;
      m_color = color;
      m_sx = 0.0;
      m_sy = 0.0;
      m_active = false;

      srand(m_num * time(NULL));
      float w = rand() % (WIDTH - 10 + 1) + 10;
      float h = rand() % (HEIGHT - 10 + 1) + 10;

      m_circle = CircleShape(rand() % (30 - 10 + 1) + 10, 30);
      m_circle.setOrigin({m_circle.getRadius() / 2, m_circle.getRadius() / 2});
      m_circle.setPosition({w, h});
      m_circle.setFillColor(m_color);
    }

    Vector2f getpos() {
      return m_circle.getPosition();
    }

    void draw(RenderWindow* window) {
      window->draw(m_circle);
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

    void move() {
      m_circle.move({m_sx, m_sy});



      if (m_sx > 0.0) {
        m_sx -= 0.00001;
      }
      else if (m_sx < 0.0) {
        m_sx += 0.00001;
      }
      else {
        m_sx = 0.000000;
      }

      if (m_sy > 0.0) {
        m_sy -= 0.00001;
      }
      else if (m_sy < 0.0) {
        m_sy += 0.00001;
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

    }
};

void mainloop() {

  RenderWindow window(VideoMode({WIDTH, HEIGHT}), "window", Style::None, State::Windowed);
  window.setFramerateLimit(60);
  window.setPosition({static_cast<int>(WIDTH - window.getSize().x / 2), static_cast<int>(HEIGHT - window.getSize().y / 2)});


  Circle circles[11];
  for (int i = 0; i < 11; i++) {
    circles[i] = Circle(i, 30.0, RED);
  }
  int num = rand() % (11 - 0 + 1) + 0;
  Circle* active = &circles[num];

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
            active->setsx(active->getsx() - 0.1);
            break;
          case (Keyboard::Key::J):
            active->setsy(active->getsy() + 0.1);
            break;
          case (Keyboard::Key::K):
            active->setsy(active->getsy() - 0.1);
            break;
          case (Keyboard::Key::L):
            active->setsx(active->getsx() + 0.1);
            break;
          default:
            break;
        }
      }
    }

    window.clear(GRAY);

    for (int i = 0; i < N; i++) {
      circles[i].draw(&window);
      circles[i].move();
      if (circles[i].getactive() == true) {
        active = &circles[i];
        circles[i].setcolor(GREEN);
      }
      else
        circles[i].setcolor(RED);
    }

    window.display();
  }
}

int main(void) {

  mainloop();
  
  return 0;
}
