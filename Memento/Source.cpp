#include<iostream>
#include<stack>
#include<ctime>
#include<cmath>


class Memento {
public:
	virtual int GetRispetto() = 0;
	virtual int GetMagia() = 0;
	virtual int GetOro() = 0;
	virtual ~Memento(){}
};

class Caratteristiche :public Memento {
private:
	int _rispetto;
	int _magia;
	int _oro;
public:
	Caratteristiche(int a,int b,int c):_rispetto(a),_magia(b),_oro(c){}
	int GetRispetto()override {
		return _rispetto;
	}
	int GetMagia()override {
		return _magia;
	}
	int GetOro() {
		return _oro;
	}
};

class Figura {
private:
	int _rispetto;
	int _magia;
	int _oro;
public:
	Figura(int a, int b, int c) :_rispetto(a), _magia(b), _oro(c) {}
	~Figura(){}
	void Carratter() {
		std::cout << "Уровень уважения : " << _rispetto << '\n';
		std::cout << "Уровень магии : " << _magia << '\n';
		std::cout << "Уровень золота : " << _oro << '\n';
	}
	void Rispetto() {
		srand(time(NULL));
		_rispetto = _rispetto + rand() % 20 - 10;
	}
	void Magia() {
		srand(time(NULL));
		_magia = _magia + rand() % 77 - 10;
	}
	void Oro() {
		srand(time(NULL));
		_oro = _oro + rand() % 2000 - 100;
	}
	Caratteristiche* salva() {
		return new Caratteristiche(_rispetto, _magia, _oro);
	}
	void Ripristino(Memento* mem) {
		_rispetto = mem->GetRispetto();
		_magia = mem->GetMagia();
		_oro = mem->GetOro();
		delete mem;
	}
};

class Memoria {
private:
	std::stack<Memento*> _memoria;
	Figura* _figura;
public:
	Memoria(Figura*fig):_figura(fig){}
	void Add() {
		_memoria.push(_figura->salva());
	}
	void PrendaMem() {
		if (_memoria.empty())return;
		_figura->Ripristino(_memoria.top());
		_memoria.pop();
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	Figura* figura = new Figura(20, 4, 1000);
	Memoria* memoria = new Memoria(figura);
	std::cout << " Начальные данные \n";
	figura->Carratter();
	std::cout << "\n Первый уровень\n";
	figura->Rispetto();
	figura->Magia();
	figura->Oro();
	figura->Carratter();
	std::cout << "\n Сохранение \n";
	memoria->Add();
	std::cout << "\n Второй уровень\n";
	figura->Rispetto();
	figura->Magia();
	figura->Oro();
	figura->Carratter();
	std::cout << "\n Восстановление предыдущих достижений\n";
	memoria->PrendaMem();
	figura->Carratter();


	return 0;
}