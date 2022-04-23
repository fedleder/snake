#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

int cell_size = 50;
int window_width = cell_size*10;
int window_height = cell_size*10;

//srand(unsigned(time(NULL)));

sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SNAKE", sf::Style::Close);

bool isHover(int x1, int x2, int y1, int y2) { 
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    //std::cout << mousePos.x << ", " << mousePos.y << std::endl;

    if (mousePos.x >= x1 && mousePos.x <= x2) {
        if (mousePos.y >= y1 && mousePos.y <= y2) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

class Food {
public:

    sf::Vector2f pos;
    sf::RectangleShape piece;
    sf::Color color;

    Food() { 
        sf::RectangleShape Piece(sf::Vector2f(cell_size/2, cell_size/2));
        int x = rand() % 10;
        int y = rand() % 10;
        //std::cout << x << ", " << y << std::endl;
        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;
        color = sf::Color(r, g, b);
        pos.x = x;
        pos.y = y;
        piece = Piece;
    }

    void draw_food() {
        piece.setFillColor(color);
        piece.setPosition(pos.x * cell_size + cell_size/4, pos.y * cell_size + cell_size/4);
        window.draw(piece);
    }

};

class Block {
public:

    sf::Vector2f pos;
    sf::RectangleShape piece;
    sf::Color color;

    Block(int x = 0, int y = 0, sf::Color Color = sf::Color{255, 36, 0}) {
        sf::RectangleShape Piece(sf::Vector2f(cell_size, cell_size));
        pos.x = x;
        pos.y = y;
        piece = Piece;
        color = Color;
    }

    void draw_piece() {
        piece.setFillColor(color);
        piece.setPosition(pos.x * cell_size, pos.y * cell_size);
        window.draw(piece);
    }

};

int main()
{
    int punteggio = 0;
    bool running = false;
    bool primapartita = true;

    int green = rand() % 255;

    bool addgreen = true;

    int colorazione;

    sf::Font font;

    if ( !font.loadFromFile( "PIXELADE.TTF" ) ) 
    {
        std::cout << "Error loading font from file!" << std::endl;
        system("pause");
    }

    /*
    int cell_size = 25;
    int window_width = cell_size*40;
    int window_height = cell_size*24;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SNAKE", sf::Style::Close);
    */
    window.setFramerateLimit(60);
    sf::RectangleShape head(sf::Vector2f(cell_size, cell_size));
    //head.setFillColor(sf::Color::Yellow);
    head.setFillColor(sf::Color{255, 36, 0});
    sf::Vector2f direction(1, 0);
    sf::Vector2f rect_pos(3, 5);

    //Block body[] = {Block(5, 7), Block(4, 7), Block(3, 7)}; //, Block(4, 7)};
    sf::Color listacolori[50] = {sf::Color(255, 36, 0), sf::Color(255, 36, 0), sf::Color(255, 36, 0),sf::Color(255, 36, 0)};
    int lenght = 2;
    Block body[100] = {Block(2, 5, sf::Color(255, 56, 0)), Block(1, 5, sf::Color(255, 76, 0))};
    Block scacchiera[50];

    int scacchiera_cout = 0;
    bool pari = true;
    for (int i = 0; i < 10; i++) {
        //scacchiera[i].color = sf::Color{8, 8, 8};
        if (pari) {
            for (int h = 0; h < 10; h++) {
                scacchiera[scacchiera_cout].pos.x = i;
                scacchiera[scacchiera_cout].pos.y = h;
                scacchiera[scacchiera_cout].color = sf::Color{8, 8, 8};
                h++;
                scacchiera_cout++;
            }
            pari = false;
        } else {
            for (int h = 1; h < 11; h++) {
                scacchiera[scacchiera_cout].pos.x = i;
                scacchiera[scacchiera_cout].pos.y = h;
                scacchiera[scacchiera_cout].color = sf::Color{8, 8, 8};
                h++;
                scacchiera_cout++;
            }
            pari = true;
        }
    }

    Food food[3] = {Food(), Food(), Food()}; //Food();

    sf::RectangleShape background(sf::Vector2f(cell_size*20, cell_size*20));
    //background.setPosition(0, 0);
    background.setFillColor(sf::Color{19, 19, 18});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                direction = sf::Vector2f(1, 0);
                rect_pos = sf::Vector2f(3, 5);
                lenght = 2;
                //{Block(2, 5, sf::Color(255, 56, 0)), Block(1, 5, sf::Color(255, 76, 0))};
                body[0] = Block(2, 5, sf::Color(255, 56, 0));
                body[1] = Block(1, 5, sf::Color(255, 76, 0));
                if (primapartita == false) {
                    for (int i=0; i< sizeof food/sizeof food[0]; i++) {
                        food[i] = Food();
                    }
                }
                punteggio = 0;
                primapartita = false;    
                running = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (direction.x != -1){
                    direction.x = 1; direction.y = 0;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (direction.x != 1){
                    direction.x = -1; direction.y = 0;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (direction.y != -1){
                    direction.x = 0; direction.y = 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (direction.y != 1){
                    direction.x = 0; direction.y = -1;
                }
            }
        }

        sf::Vector2f cp_pos;  
        cp_pos = rect_pos;
        if (running == true) {
            rect_pos += direction;
        }

        head.setPosition(rect_pos.x * cell_size, rect_pos.y * cell_size);
        window.clear();

        window.draw(background);

        sf::RectangleShape head_light1(sf::Vector2f(cell_size*3, cell_size*3));
        head_light1.setPosition(rect_pos.x * cell_size - 50, rect_pos.y * cell_size - 50); //* cell_size - 50, rect_pos.y * cell_size - 50);
        head_light1.setFillColor(sf::Color{255, 36, 0, 20});

        sf::RectangleShape head_light2(sf::Vector2f(cell_size*5, cell_size*5));
        head_light2.setPosition(rect_pos.x * cell_size - 100, rect_pos.y * cell_size - 100);
        head_light2.setFillColor(sf::Color{255, 36, 0, 15});

        sf::RectangleShape head_light3(sf::Vector2f(cell_size*7, cell_size*7));
        head_light3.setPosition(rect_pos.x * cell_size - 150, rect_pos.y * cell_size - 150);
        head_light3.setFillColor(sf::Color{255, 36, 0, 10});

        sf::RectangleShape head_light4(sf::Vector2f(cell_size*9, cell_size*9));
        head_light4.setPosition(rect_pos.x * cell_size - 200, rect_pos.y * cell_size - 200);
        head_light4.setFillColor(sf::Color{255, 36, 0, 5});

        sf::RectangleShape head_light5(sf::Vector2f(cell_size*11, cell_size*11));
        head_light5.setPosition(rect_pos.x * cell_size - 250, rect_pos.y * cell_size - 250);
        head_light5.setFillColor(sf::Color{255, 36, 0, 2});

        sf::RectangleShape head_light6(sf::Vector2f(cell_size*13, cell_size*9));
        head_light6.setPosition(rect_pos.x * cell_size - 300, rect_pos.y * cell_size - 200);
        head_light6.setFillColor(sf::Color{255, 36, 0, 2});

        sf::RectangleShape head_light7(sf::Vector2f(cell_size*9, cell_size*13));
        head_light7.setPosition(rect_pos.x * cell_size - 200, rect_pos.y * cell_size - 300);
        head_light7.setFillColor(sf::Color{255, 36, 0, 2});

        window.draw(head_light1);
        window.draw(head_light2);
        window.draw(head_light3);
        window.draw(head_light4);
        window.draw(head_light5);
        //window.draw(head_light6);
        //window.draw(head_light7);
        //sf::Color{13, 13, 13}
        //(19, 19, 18)
        //(8, 8, 8)

        //window.draw(head);

        sf::Vector2f cop_pos;

        for (int i=0; i< sizeof scacchiera/sizeof scacchiera[0]; i++) {
            scacchiera[i].draw_piece();
        }

        
        for (int i=0; i< sizeof body/sizeof body[0]; i++){
            cop_pos = body[i].pos;
            //body[i].pos += direction;
            if (running == true) {
                body[i].pos = cp_pos;
            }
            if (i <= lenght) { 
                if (i != 0 && i != 1) {
                    if (i < 11) { //body[i].color.g != 255 && addgreen == true) {
                        body[i].color = body[i-1].color + sf::Color(0, 20, 0);
                    } else if (i < 23) {
                        //body[i].color.r = body[i-1].color.r - 20;
                        //body[i].color = body[i-1].color - sf::Color(0, 20, 0);
                        //body[i].color = body[i-1].color + sf::Color(0, 0, 20);
                        body[i].color.r = body[i-1].color.r - 20;
                        //body[i].color.g = body[i-1].color.g;
                        body[i].color.g = body[i-1].color.g; //- 20;
                        body[i].color.b = body[i-1].color.b + 20;
                    } else if (i < 33) {
                        body[i].color.r = body[i-1].color.r;
                        body[i].color.g = body[i-1].color.g - 20;
                        body[i].color.b = body[i-1].color.b;
                    } else {
                        body[i].color.r = body[i-1].color.r + 20;
                        body[i].color.g = body[i-1].color.g;
                        body[i].color.b = body[i-1].color.b;
                        if (body[i].color.g < 50) {
                            std::cout << "colorazione: " << i << std::endl;
                        }
                    }
                }
                body[i].draw_piece();
            }
            cp_pos = cop_pos;
            
        }  

        for (int i=0; i< sizeof food/sizeof food[0]; i++){
            food[i].draw_food();
        }

        window.draw(head);

        if (running == true) {
            window.display();
            sf::sleep(sf::milliseconds(125));
        }
        //std::cout << rect_pos.x << ", " << rect_pos.y << std::endl;
        if (rect_pos.x < 0) {
            //std::cout << "Game Over!" << std::endl;
            //window.close();
            //running = false;
            rect_pos.x = 10;
        } else if (rect_pos.x > 10) {
            rect_pos.x = 0;
        } else if (rect_pos.y < 0) {
            rect_pos.y = 10;
        } else if (rect_pos.y > 9) {
            rect_pos.y = 0;
        } else if (rect_pos.x == 10) {
             rect_pos.x = 0;
        } else if (rect_pos.x == -1) {
            rect_pos.x = 10;
        } else if (rect_pos.y == 10) {
            rect_pos.y = 0;
        } else if (rect_pos.y == -1) {
            rect_pos.y = 10;
        }
        
        for (int i=0; i< sizeof body/sizeof body[0]; i++){
            for (int k=0; k< sizeof food/sizeof food[0]; k++){
                if (body[i].pos == rect_pos && i < lenght) {
                    running = false;
                } else if (rect_pos == food[k].pos) {
                    food[k] = Food();
                    punteggio += 1;
                    lenght += 1;
                    for (int h=0; h< sizeof food/sizeof food[0]; h++) {
                        if (food[h].pos == food[k].pos) {
                            food[k] = Food();
                        }
                    }
                    std::cout << punteggio << std::endl;
                    //int positionx = body[sizeof body/sizeof body[0] - 1].pos.x;
                    //int positiony = body[sizeof body/sizeof body[0] - 1].pos.y;
                    //body[sizeof body/sizeof body[0]] = Block(cop_pos.x, cop_pos.y);
                    int size = sizeof body/sizeof body[0];
                    //std::cout << size << std::endl;
                    //std::cout << body << std::endl;
                    //body[size] = Block(cop_pos.x, cop_pos.y);
                } else if (body[i].pos == food[k].pos && i <= lenght) {
                    food[k] = Food();
                    for (int h=0; h< sizeof food/sizeof food[0]; h++) {
                        if (food[h].pos == food[k].pos) {
                            food[k] = Food();
                        }
                    }
                    //punteggio += 1;
                    //lenght += 1;
                    std::cout << punteggio << std::endl;
                    int size = sizeof body/sizeof body[0];
                }
            }
        }

        if (running == false && primapartita == true) {
            //creating transparent background and buttons
            sf::RectangleShape blocchetto(sf::Vector2f(cell_size, cell_size));
            blocchetto.setFillColor(sf::Color{8, 8, 8});
            sf::RectangleShape background_menu(sf::Vector2f(cell_size * 20, cell_size * 20));
            background_menu.setFillColor(sf::Color{19, 19, 18, 150});
            window.draw(blocchetto);
            window.draw(background_menu);

            sf::RectangleShape play_button(sf::Vector2f(cell_size * 3.5, cell_size * 1.5));
            play_button.setFillColor(sf::Color(255, green, 0));
            play_button.setPosition((cell_size*10)/2-(cell_size*3.5)/2, 265);
            
            sf::Text text_button("GIOCA", font, 50);
            text_button.setStyle(sf::Text::Style::Bold);
            text_button.setFillColor(sf::Color(26, 26, 26));
            sf::FloatRect bounds(text_button.getLocalBounds());
            sf::Vector2f box(play_button.getSize());
            text_button.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
            text_button.setPosition((cell_size*10)/2-(cell_size*3.5)/2, 265);

            sf::Text title_text("SNAKE", font, 100);
            title_text.setStyle(sf::Text::Style::Bold);
            sf::FloatRect bounds2(title_text.getLocalBounds());
            sf::Vector2f box2(play_button.getSize());
            //title_text.setOrigin((bounds2.width - box2.x) / 2 + bounds2.left, (bounds2.height - box2.y) / 2 + bounds2.top);
            title_text.setPosition((cell_size*10)/2-(bounds2.width/2), 100);

            int x1 = (cell_size*10)/2-(cell_size*3.5)/2;
            int x2 = x1 + cell_size * 3.5;
            int y1 = 265;
            int y2 = y1 + cell_size * 1.5;
            if (isHover(x1, x2, y1, y2)) {
                play_button.setFillColor(sf::Color(155, green, 0));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    running = true;
                    primapartita = false;
                    lenght = 2;
                    //{Block(2, 5, sf::Color(255, 56, 0)), Block(1, 5, sf::Color(255, 76, 0))};
                    body[0] = Block(2, 5, sf::Color(255, 56, 0));
                    body[1] = Block(1, 5, sf::Color(255, 76, 0));
                }
            } else {
                play_button.setFillColor(sf::Color(255, green, 0));
            }
            //isHover(x1, x2, y1, y2);

            window.draw(title_text);
            window.draw(play_button);
            window.draw(text_button);
            window.display();
        } else if (running == false && primapartita == false) {
            sf::RectangleShape blocchetto(sf::Vector2f(cell_size, cell_size));
            blocchetto.setFillColor(sf::Color{8, 8, 8});
            sf::RectangleShape background_menu(sf::Vector2f(cell_size * 20, cell_size * 20));
            background_menu.setFillColor(sf::Color{19, 19, 18, 150});
            window.draw(blocchetto);
            window.draw(background_menu);

            sf::RectangleShape rigioca_button(sf::Vector2f(cell_size * 3.5, cell_size * 1.5));
            rigioca_button.setFillColor(sf::Color(255, green, 0));
            rigioca_button.setPosition((cell_size*10)/2-(cell_size*3.5)-12.5, 265);
            
            sf::Text text_button("RIGIOCA", font, 50);
            text_button.setStyle(sf::Text::Style::Bold);
            text_button.setFillColor(sf::Color(26, 26, 26));
            sf::FloatRect bounds(text_button.getLocalBounds());
            sf::Vector2f box(rigioca_button.getSize());
            text_button.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
            text_button.setPosition((cell_size*10)/2-(cell_size*3.5)-12.5, 265);

            sf::RectangleShape esci_button(sf::Vector2f(cell_size * 3.5, cell_size * 1.5));
            esci_button.setFillColor(sf::Color(255, green, 0));
            esci_button.setPosition((cell_size*10)/2+12.5, 265);

            sf::Text esci_text("ESCI", font, 50);
            esci_text.setStyle(sf::Text::Style::Bold);
            esci_text.setFillColor(sf::Color(26, 26, 26));
            sf::FloatRect bounds3(esci_text.getLocalBounds());
            sf::Vector2f box3(esci_button.getSize());
            esci_text.setOrigin((bounds3.width - box3.x) / 2 + bounds3.left, (bounds3.height - box3.y) / 2 + bounds3.top);
            esci_text.setPosition((cell_size*10)/2+12.5, 265);

            sf::Text title_text("GAME OVER", font, 100);
            title_text.setStyle(sf::Text::Style::Bold);
            sf::FloatRect bounds2(title_text.getLocalBounds());
            sf::Vector2f box2(rigioca_button.getSize());
            //title_text.setOrigin((bounds2.width - box2.x) / 2 + bounds2.left, (bounds2.height - box2.y) / 2 + bounds2.top);
            title_text.setPosition((cell_size*10)/2-(bounds2.width/2), 100);

            int x1 = (cell_size*10)/2-(cell_size*3.5)-12.5;
            int x2 = x1 + cell_size * 3.5;
            int y1 = 265;
            int y2 = y1 + cell_size * 1.5;
            if (isHover(x1, x2, y1, y2)) {
                rigioca_button.setFillColor(sf::Color(155, green, 0));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    direction = sf::Vector2f(1, 0);
                    rect_pos = sf::Vector2f(3, 5);
                    lenght = 2;
                    //{Block(2, 5, sf::Color(255, 56, 0)), Block(1, 5, sf::Color(255, 76, 0))};
                    body[0] = Block(2, 5, sf::Color(255, 56, 0));
                    body[1] = Block(1, 5, sf::Color(255, 76, 0));
                    for (int i=0; i< sizeof food/sizeof food[0]; i++) {
                        food[i] = Food();
                    }
                    punteggio = 0;
                    running = true;
                }
            } else {
                rigioca_button.setFillColor(sf::Color(255, green, 0));
            }
            //isHover(x1, x2, y1, y2);

            int x12 = (cell_size*10)/2+12.5;
            int x22 = x12 + cell_size * 3.5;
            int y12 = 265;
            int y22 = y12 + cell_size * 1.5;

            if (isHover(x12, x22, y12, y22)) {
                esci_button.setFillColor(sf::Color(155, green, 0));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    window.close();
                }
            } else {
                esci_button.setFillColor(sf::Color(255, green, 0));
            }

            window.draw(title_text);
            window.draw(rigioca_button);
            window.draw(text_button);
            window.draw(esci_button);
            window.draw(esci_text);
            window.display();
        }

    }

    return 0;
}