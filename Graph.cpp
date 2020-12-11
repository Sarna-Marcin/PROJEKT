#include "Graph.hpp"

int losuj(int a, int b) {//wiadomo
	return rand() % (b - a + 1) + a;
}

float getAngleByCoordinates(float x, float y)//zwraca kat miedzy osia y+ zgodnie z ruchem wskazowek zegara do punku (x,y)
{
	if (x == 0) {
		if (y > 0) return 0.f;
		else return 180.f;
	}
	if (y == 0) {
		if (x > 0) return 90.f;
		else return 270.f;
	}
	if (x > 0 && y > 0) return 90.f - atan(fabs(y / x)) * M_RAD;
	if (x > 0 && y < 0) return 90.f + atan(fabs(y / x)) * M_RAD;
	if (x < 0 && y < 0) return 270.f - atan(fabs(y / x)) * M_RAD;
	if (x < 0 && y > 0) return 270.f + atan(fabs(y / x)) * M_RAD;
}

float getLenght(sf::Vector2f p1, sf::Vector2f p2) {//odleglosc miedzy dwoma punktami w przestrzeni
	return sqrtf(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void Graph::draw(sf::RenderWindow& window) {
	for (int i = 1; i <= n; i++) //TO RYSUJE KRAWEDZIE //NIE DOTYKAC //trzeba dodac tryb krawedzi skierowanej xD
		for (int j = 0; j < graf[i].size(); j++) {
			if (isDirected == 0 && i > graf[i][j].first) continue;//zeby dwa razy tej samej nie rysowac w nieskierowanym
			sf::Vector2f pos1 = grafika[i].position, pos2 = grafika[graf[i][j].first].position;
			float len = getLenght(pos1, pos2);
			float angle = getAngleByCoordinates(pos2.x - pos1.x, pos1.y - pos2.y);
			sf::RectangleShape kraw(sf::Vector2f(len, 4));
			kraw.setOrigin(0, 2.f);
			kraw.setPosition(pos1);
			kraw.setFillColor(sf::Color::Black);
			kraw.setRotation(angle - 90);
			window.draw(kraw);
		}
	rep(i, 1, n) { //wierzcholki
		window.draw(grafika[i].circle);
		window.draw(grafika[i].text);
	}
}

void Graph::addEdge(int v, int u, int w, int isDirected) {
	graf[v].push_back({ u,w });
	if (!isDirected) graf[u].push_back({ v,w });
}

void Graph::addVertice() {
	grafika[++n] = Vertex(n, sf::Vector2f((float)losuj(100, 900), (float)losuj(100, 500)), &textures[0], font);
}

void Graph::calculateForces() {
	rep(i, 1, n) force[i] = { 0.f,0.f };
	//przyciaganie do srodka


	//odpychanie sie wierzcholkow
	rep(i,1,n)
		rep(j, i + 1, n) {
		// i -> j

		//j -> i
	}

	//przyciaganie sie na krawedziach


}

Graph::Graph() {
	font.loadFromFile("Fonts/ABeeZee-Regular.ttf");
	textures[0].loadFromFile("Textures/vertex.png");//kolory wierzcholków, enum na kolory
	textures[0].setSmooth(true);
	isDirected = 0;//wstepnie na nieskierowany
	isWeighted = 0;//wstepnie na niewazony
	n = 0;
	rep(i, 1, 12)
		addVertice();
	addEdge(1, 2, 1, 0);
	addEdge(2, 3, 1, 1);
	addEdge(3, 4, 1, 1);
}

Vertex::Vertex(int num, sf::Vector2f p, sf::Texture* texturePtr, sf::Font& font) {
	position = p;
	circle.setTexture(*texturePtr);
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
	circle.setPosition(p);
	text.setFont(font);
	text.setString(std::to_string(num));
	text.setCharacterSize(30);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(p.x - 3, p.y - 9);
}

Vertex::Vertex() {}