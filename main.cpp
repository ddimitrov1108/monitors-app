#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
using namespace std;

#define MAX_LIMIT 100

/*
	Kursova rabota po BAZOVO PROGRAMIRANE na:
	Ime: Daniel Dimitrov, Fakulteten Nomer: 19621440,
	Fakultet: FITA, Katedra: KNT, Specialnost: KST, Grupa: 5B;
*/

class Monitor {
private:
	string serien_nomer, marka, model, cvqt;
	string razd_sposobnost, tip, status;
	double diagonal_ekran, cena;
	int promociq;
	bool TVTuner;
	string TVTunerCvqt = "---";
public:
	// Konstruktor s qvno zadadeni parametri koito priemat adres ot pametta.
	Monitor(string& sn, string& mrk, string& mod, string& cv, double& de, string& rs, double& c, string& t, string& st, bool& tvtun, string& tvtun_cvqt, int& promo);
	// Konstruktor za kopirvane i prisvoqvane na stoinosti ot obekt.
	Monitor(const Monitor* cpyObj);

	// Getter i Setter funkcii.
	void setSerienNomer(string& newNomer) { this->serien_nomer = newNomer; }
	string getSerienNomer() { return this->serien_nomer; }

	void setMarka(string& newMarka) { this->marka = newMarka; }
	string getMarka() { return this->marka; }

	void setModel(string& newModel) { this->model = newModel; }
	string getModel() { return this->model; }

	void setCvqt(string& newCvqt) { this->cvqt = newCvqt; }
	string getCvqt() { return this->cvqt; }

	void setRazdSposobnost(string& newRazdSp) { this->razd_sposobnost = newRazdSp; }
	string getRazdSposobnost() { return this->razd_sposobnost; }

	void setTip(string& newTip) { this->tip = newTip; }
	string getTip() { return this->tip; }

	void setStatus(string& newStatus) { this->status = newStatus; }
	string getStatus() { return this->status; }

	void setDiagonalNaEkran(double& newDiagEkran) { this->diagonal_ekran = newDiagEkran; }
	double getDiagonalNaEkran() { return this->diagonal_ekran; }

	void setCena(double& newCena) { this->cena = newCena; }
	double getCena() { return this->cena; }

	void setTVTuner(bool& newTVTuner) {
		if (newTVTuner == false) {
			this->TVTuner = false;
			this->TVTunerCvqt = "---";
		}
		else this->TVTuner = true;
	}
	string getTVTuner() { return (this->TVTuner == true ? "IMA" : "NQMA"); }

	void setTVTunerCvqt(string& newTunerCvqt) { this->TVTunerCvqt = newTunerCvqt; }
	string getTVTunerCvqt() { return this->TVTunerCvqt; }

	void setPromo(int& newPromo) { this->promociq = newPromo; }
	int getPromo() { return this->promociq; }

	// Funkciq koqto izchislqva cenata na Monitor sled prilagane na promociqta(%).
	double CalculatePromo() { return ((100.0 - this->promociq) / 100 * this->cena); }
};

Monitor::Monitor(string& sn, string& mrk, string& mod, string& cv, double& de, string& rs, double& c, string& t, string& st, bool& tvtun, string& tvtun_cvqt, int& promo) {
	// Konstruktor s qvno zadadeni parametri.
	this->serien_nomer = sn;
	this->marka = mrk;
	this->model = mod;
	this->cvqt = cv;
	this->diagonal_ekran = de;
	this->razd_sposobnost = rs;
	this->tip = t;
	this->cena = c;
	this->status = st;
	this->TVTuner = tvtun;
	this->TVTunerCvqt = tvtun_cvqt;
	this->promociq = promo;
}

Monitor::Monitor(const Monitor* cpyObj) {
	// Konstruktor za kopirvane i prisvoqvane na stoinosti ot obekt.
	this->serien_nomer = cpyObj->serien_nomer;
	this->marka = cpyObj->marka;
	this->model = cpyObj->model;
	this->cvqt = cpyObj->cvqt;
	this->diagonal_ekran = cpyObj->diagonal_ekran;
	this->razd_sposobnost = cpyObj->razd_sposobnost;
	this->tip = cpyObj->tip;
	this->cena = cpyObj->cena;
	this->status = cpyObj->status;
	this->TVTuner = cpyObj->TVTuner;
	this->TVTunerCvqt = cpyObj->TVTunerCvqt;
	this->promociq = cpyObj->promociq;
}

void LoadDB_Monitors(vector<Monitor*>& vec_mons) {
	/*
		Funkciqta zarejda informaciq za Monitori kato obekti v programata.
		Bufera FileStream vuvejda stoinosti vuv vsqka promenliva kudeto sled procheten red ot faila se izvikva
		konstruktora s qvno zadadeni parametri za suzdavane na obekt(Monitor) s informaciqta
		koqto se zapisva na edin red v bazata danni koeto oznachava che 1 red(row) e 1 zapis na obekt.
	*/
	string sn, mrk, mod, cv, rs, tip, st, tvtun_cvqt;
	double de, cena;
	int promo;
	bool tvtun;
	fstream out_db("monitors_database.txt", ios::in);
	if (out_db.good()) {
		if (out_db.peek() != EOF) {
			while (!out_db.eof()) {
				if (out_db.eof() || vec_mons.size() >= MAX_LIMIT)
					break;
				out_db >> sn >> mrk >> mod >> cv >> de >> rs >> cena >> tip >> st >> tvtun >> tvtun_cvqt >> promo;
				vec_mons.push_back(new Monitor(sn, mrk, mod, cv, de, rs, cena, tip, st, tvtun, tvtun_cvqt, promo));
			}
		}
	}
	else {
		printf("[ERROR] Fail s ime \"monitors_database.txt\" NE BESHE NAMEREN!\n");
		system("pause");
		exit(1);
	}
	out_db.close();
}

void SaveDB_Monitors(vector<Monitor*>& vec_mons) {
	/*
		Funkciqta zapazva informaciqta za vseki obekt ot klas Monitor na 1 red.
		Izvlicha informaciqta ot vseki obekt chrez getter funkciite definirani za vseki obekt koito e zapazen v konteinera.
	*/
	fstream in_db("monitors_database.txt", ios::out | ios::trunc);
	if (in_db.good()) {
		for (int i = 0; i < vec_mons.size(); i++) {

			in_db << vec_mons.at(i)->getSerienNomer() << " " << vec_mons.at(i)->getMarka() << " " << vec_mons.at(i)->getModel() << " " << vec_mons.at(i)->getCvqt() << " ";
			in_db << vec_mons.at(i)->getDiagonalNaEkran() << " " << vec_mons.at(i)->getRazdSposobnost() << " " << vec_mons.at(i)->getCena() << " ";
			in_db << vec_mons.at(i)->getTip() << " " << vec_mons.at(i)->getStatus() << " ";
			in_db << (vec_mons.at(i)->getTVTuner() == "IMA" ? "1" : "0") << " " << vec_mons.at(i)->getTVTunerCvqt() << " ";
			in_db << vec_mons.at(i)->getPromo() << (i < vec_mons.size() - 1 ? "\n" : "");
		}
	}
	else {
		printf("[ERROR] Fail s ime \"monitors_database.txt\" NE BESHE NAMEREN!\n");
		system("pause");
		exit(1);
	}
	in_db.close();
}

template<typename T>
T ValidateInput(T intervalA, T intervalB) {
	// Izpulnqva se cikul za vuvejdane na stoinost za promelivata N dokato N e izvun intervala ot A - B.
	T n;
	while (true) {
		if(sizeof(T) == sizeof(double))
			printf(" -> Vuvedi stoinost(REALNO CHISLO) v interval: %.2f do %.2f): ", intervalA, intervalB);
		else
			printf(" -> Vuvedi stoinost(CQLO CHISLO) v interval: %d do %d): ", intervalA, intervalB);
		cin >> n;
		if (n >= intervalA && n <= intervalB)
			// Ako stoinosta e v intervala se vrushta stoinostta pri obrushtenieto na funkciqta.
			return n;
		printf("[ERROR]: Vuvedi korektna stoinost!!!\n");
	}
}

char ValidateYNChoice() {
	char choice;
	while (true) {
		cin >> choice;
		if ((choice == 'Y' || choice == 'y') || (choice == 'N' || choice == 'n'))
			return choice;
		printf("Vuvedi validen izbor!!!: Y / N: ");
	}
}

bool CheckSerialNumber(vector<Monitor*>& vec_mons, string& sn) {
	// Proverqva dali serieniqt nomer podaden po adres sushtestvuva v konteinera.
	for (int i = 0; i < vec_mons.size(); i++)
		if (vec_mons.at(i)->getSerienNomer().compare(sn) == 0)
			// Ako sushtestvuva vrushta false.
			return false;
	// Ako NE sushtestvuva sledovatelno e validen za izpolzvane i vrushta true.
	return true;
}

int SearchSerialNumber(vector<Monitor*>& vec_mons, string& sn) {
	// Tursi dali podaden serien nomer po adres sushtestvuva v konteinera.
	for (int i = 0; i < vec_mons.size(); i++)
		if (vec_mons.at(i)->getSerienNomer() == sn)
			// Ako sushtestvuva vrushta indeksa na obekta v konteinera koito sudurja tozi serien nomer.
			return i;
	// Ako NE sushtestvuva vrushta -1.
	return -1;
}

string ValidateSerialNumber(bool allowZeros) {
	// Izpulnqva se cikul za vuvejda ne na serien nomer dokato stoinostta e < 0 i e > 100 miliona(do 8 simvola)
	string sn;
	bool notText;
	int countZeros;;
	printf(" >> Serien Nomer DO 10 cifri: ");
	while (true) {
		notText = false;
		countZeros = 0;
		cin >> sn;
		if (allowZeros == true) {
			for (int i = 0; i < sn.size(); i++) {
				if (sn.at(i) == '0')
					countZeros++;
			}

			if (countZeros == sn.size())
				return "0";
		}
		else {
			if (sn.size() == 0 || sn.size() > 10) {
				printf("[ERROR] Vuvedi Serien Nomer DO 10 CIFRI: ");
				continue;
			}
			else if (sn.at(0) == '-') {
				printf("[ERROR] Vuvedi POLOJITELNA STOINOST za Serien Nomer DO 10 CIFRI: ");
				continue;
			}
			else {
				for (int i = 0; i < sn.size(); i++) {
					if (sn.at(i) < 48 || sn.at(i) > 57) {
						notText = true;
						break;
					}
				}

				if (notText == true) {
					printf("[ERROR] Sereniqt Nomer moje da sudurja samo CHISLA v sebe si: ");
					continue;
				}
				else {
					for (int i = 0; i < sn.size(); i++) {
						if (sn.at(i) == '0')
							countZeros++;
					}
					if (countZeros == sn.size() && allowZeros == false) {
						printf("[ERROR] Sereniqt Nomer NE MOJE da sudurja samo nuli(0) v sebe si: ");
						continue;
					}
				}
			}
		}
		break;
	}
	return sn;
}

void ReplaceWhiteSpaces(string& str) {
	// Zamestva VSICHKI intervali ot simnolniq niz s dolna cherta ('_').
	for (int i = 0; i < str.size(); i++)
		if (str.at(i) == ' ')
			str.at(i) = '_';
}

string RemoveWhiteSpaces(string& str) {
	string new_str;
	for (int i = 0; i < str.size(); i++)
		if (str.at(i) != ' ') new_str += str.at(i);
	return new_str;
}

string ToUpperCase(string str) {
	// Preobrazuva vsichki simvoli v glavni
	string toupper_str;
	for (int i = 0; i < str.size(); i++)
		toupper_str += toupper(str.at(i));
	return toupper_str;
}

string ToLowerCase(string str) {
	// Preobrazuva vsichki simvoli v malki
	string tolower_str;
	for (int i = 0; i < str.size(); i++)
		tolower_str += tolower(str.at(i));
	return tolower_str;
}

string TrimString(string& str) {
	// Premahva NENUJNITE intervali v edin simvolen niz.
	string s, new_str;
	if (str.size() == 0)
		return str;

	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') {
			if (str.at(i) == ' ' && str.at(i + 1) == ' ')
				i++;
			if (str.at(i) == ' ' && str.at(i + 1) != ' ')
				s += str.at(i);
		}
		if (str.at(i) != ' ')
			s += str.at(i);
	}
	// Sled cikula vsichki nenujni intervali(t.e interval do interval) sa premahnati i sa ostanali samo po 1 interval v nachaloto/kraq/izmejdu niza.
	if (s.at(0) == ' ' || s.at(s.size() - 1 == ' ')) {
		// Ako ima ostanal interval predi ili v kraq na niza te trqbva da budat premahnati.
		int i = (s[0] == ' ' ? 1 : 0); // Ako e v nachaloto broqcha pochva ot 1.
		int sizeStr = (s.at(s.size() - 1) == ' ' ? (s.size() - 1) : s.size()); // Ako e v kraq duljinata na niza se namalq s 1(-1 iteraciq na cikula).
		for (i; i < sizeStr; i++)
			new_str += s.at(i);
		// vrushta kato stoinost noviqt niz koito veche e bez nenujnite intervali v nachalnite indexi i/ili krainite indexi niza.
		return new_str;
	}
	// Ako uslovniq operator ne e izpulnen vrushta noviqt niz koito ne e imal nenujni intervali predi ili sled niza.
	return s;
}

void SwapObjectProperties(Monitor& obj1, Monitor& obj2) {
	/*
		Razmenqt se stoinostite na 2 obekta(obj1 i obj2) chrez konstruktora za kopirvane i prisvoqvane na stoinosti ot drug obekt.
		Suzdavat se novi obekti s novi razmeneni stoinosti i dinamichniq obekt temp se iztriva ot hiipa.
	*/
	Monitor* temp = new Monitor(obj1);
	obj1 = new Monitor(obj2);
	obj2 = new Monitor(temp);
	delete temp;
}

int CountMonitorDupsByMarkaAndModel(vector<Monitor*>& vec_mons, string& mrk, string& mod, int statusMode) {
	/*
		Proverqva dali vuv vektora do momenta sushtestvuva Monitor s marka, model i status spored:
		statusMode = 0 - nqma znachenie dali e v prodajba, kapariran ili prodaden,
		statusMode = 1 - Ako e nalichen(v prodajba),
		statusMode = 2 - Ako e kapariran,
		statusMode = 3 - ako e prodaden;
		Broqcha(count) se uvelichava vseki put kogato zaseche Monitor sprqmo fakticheskite parametri.
		Sled tova vrushta stoinostta na broqcha pri obrushtenieto na funkciqta.
	*/
	int count = 0;
	for (int i = 0; i < vec_mons.size(); i++) {
		if (ToUpperCase(vec_mons.at(i)->getMarka()) == ToUpperCase(mrk) && ToUpperCase(vec_mons.at(i)->getModel()) == ToUpperCase(mod)) {
			if (statusMode != 0) {
				if (vec_mons.at(i)->getStatus() == (statusMode == 1 ? "V_PRODAJBA" : (statusMode == 2 ? "KAPARIRAN" : "PRODADEN"))) {
					count++;
				}
			}
			else {
				count++;
			}
		}
	}
	return count;
}

void ClearVector(vector<Monitor*>& vec_mons) {
	while (!vec_mons.empty())
		vec_mons.pop_back();
}

void CreateNewMonitors(vector<Monitor*>& vec_mons, int lenOfMonitorsToAdd) {
	/*
		Funkciq za suzdavane na nov obekt ot klas Monitor.
		Vuvejdat se korektni stoinosti za vsqka lokalna promenliva sled koeto
		v kraq na vektora chrez(push_back) se dobavq nov dinamichen obekt ot klas Monitor koito
		vika konstruktora s qvno zadadeni parametri. Stoinostite se podavat po adresi.
		V kraq na funkciqta se izvikva funkciqta koqto rabota i e
	*/
	string sn, mrk, mod, cv, rs, tip, st, tvtun_cvqt = "---";
	double de, cena;
	bool tvtun = false, StopAddingMonitors = false;
	int promo;
	char choice = ' ';

	system("cls");
	printf("\n (*). Suzdavane na ");
	(lenOfMonitorsToAdd == 1 ? printf("Monitor.") : printf(" Spisuk ot %d Monitori.", lenOfMonitorsToAdd));
	cin.ignore();


	for (int i = 0; i < lenOfMonitorsToAdd; i++) {
		printf("\n\n >> Vuvejdane na informaciq za Monitor #%d/%d:\n", (i + 1), lenOfMonitorsToAdd);
		printf("\n Vuvedi informaciq za:\n\n");

		while (true) {
			sn = ValidateSerialNumber(0);
			if (CheckSerialNumber(vec_mons, sn) == false)
				printf("[ERROR] Tozi Serien Nomer e ZAET! \n");
			else
				break;
		}
		cin.ignore();

		printf(" >> Marka na Monitor: ");
		getline(cin, mrk, '\n');
		mrk = TrimString(mrk);
		ReplaceWhiteSpaces(mrk);

		printf(" >> Model na Monitor: ");
		getline(cin, mod, '\n');
		mod = TrimString(mod);
		ReplaceWhiteSpaces(mod);

		printf(" >> Cvqt na Monitor: ");
		getline(cin, cv, '\n');
		cv = TrimString(cv);
		ReplaceWhiteSpaces(cv);

		printf(" >> Diagonal na Ekrana (Primer: 23.6): ");
		cin >> de;
		cin.ignore();

		printf(" >> Razdelitelna Sposobnost(Primer: 1920x1080): ");
		getline(cin, rs, '\n');
		rs = ToLowerCase(RemoveWhiteSpaces(rs));

		printf(" >> Originalna Cena (Primer: 324.99): ");
		cin >> cena;

		printf(" >> Tip:\n\t(1). NOV\n\t(2). VTORA RUKA\n");
		tip = (ValidateInput(1, 2) == 1 ? "NOV" : "VTORA_RUKA");

		printf(" >> Status:\n\t(1). V PRODAJBA\n\t(2). KAPARIRAN\n\t(3). PRODADEN\n");
		int izb_st = ValidateInput(1, 3);
		st = (izb_st == 1 ? "V_PRODAJBA" : (izb_st == 2 ? "KAPARIRAN" : "PRODADEN"));

		printf(" >> TV-Tuner:\n\t(1). IMA\n\t(2). NQMA\n");
		if (ValidateInput(1, 2) == 1) {
			cin.ignore();
			tvtun = true;
			printf(" >> Cvqt na TV-Tunera (Primer: cherveno): ");
			getline(cin, tvtun_cvqt, '\n');
			tvtun_cvqt = TrimString(tvtun_cvqt);
			ReplaceWhiteSpaces(tvtun_cvqt);
		}

		printf(" >> Promociq (Primer: 0/25/50/75/100):\n");
		promo = ValidateInput(0, 100);
		cin.ignore();

		vec_mons.push_back(new Monitor(sn, mrk, mod, cv, de, rs, cena, tip, st, tvtun, tvtun_cvqt, promo));

		if (CountMonitorDupsByMarkaAndModel(vec_mons, mrk, mod, 0) > 1) {
			printf("\n\n[WARNING]: Tozi Monitor veche sushtestvuva v sistemata!...Shte go razlichavate ot drugite po negoviq SERIEN NOMER.\n");
			system("pause");
		}

		if (i < (lenOfMonitorsToAdd - 1) && lenOfMonitorsToAdd > 1) {
			printf("\n Iskate li da produljite s vuvejdaneto na Monitori: (Y/N): ");
			switch (ValidateYNChoice()) {
			case 'N': case 'n': StopAddingMonitors = true; break;
			}
		}

		if (StopAddingMonitors == true) break;
		if (i != (lenOfMonitorsToAdd - 1)) system("cls");
	}

	printf("\n Iskate li da dobavite drugi Monitori: (Y/N): ");
	switch (ValidateYNChoice()) {
	case 'Y': case 'y':
		system("cls");
		printf("\n (?). Kolko Monitora iskate da suzdadete:\n\n");
		SaveDB_Monitors(vec_mons);
		CreateNewMonitors(vec_mons, ValidateInput<int>(1, (MAX_LIMIT - vec_mons.size())));
		break;
	case 'N': case 'n': SaveDB_Monitors(vec_mons); break;
	}
}

void AddMonitorsMenu(vector<Monitor*>& vec_mons) {
	// (1). Dobavqne na novi Monitori(podmenu)
	system("cls");
	printf("\n (*). Dobavqne na novi Monitori:\n\n");
	printf("[INFO]: Vmomenta v sistemata ima zaredeni%s%d/%d Monitora.\n\n", (vec_mons.size() == MAX_LIMIT ? " [FULL] " : " "), vec_mons.size(), MAX_LIMIT);
	if (vec_mons.size() == MAX_LIMIT) {
		printf("[ERROR]: V sistemata nqma mqsto za suzdavane na novi Monitori...!\n");
		system("pause");
	}
	else {
		printf(" (1). Dobavqne na edin nov Monitor.\n");
		printf(" (2). Dobavqne na spisuk s novi Monitori.\n");
		printf(" (0). Obratno v Glavnoto Menu.\n\n");
		switch (ValidateInput(0, 2)) {
		case 1: CreateNewMonitors(vec_mons, 1); break;
		case 2:  system("cls"); printf("\n (?). Kolko Monitora iskate da suzdadete:\n\n");
			CreateNewMonitors(vec_mons, ValidateInput<int>(1, (MAX_LIMIT - vec_mons.size()))); break;
		}
	}
}

void PrintTableHeader() {
	for (int i = 0; i < 210; i++) printf("-");
	printf("\n");
	printf(" Serien Nomer%3s Marka && Model%31s Cvqt%19s", "|", "|", "|");
	printf(" Diagonal na Ekrana%12s Cena(lv) %6s", "|", "|");
	printf(" Tip%11s Status%7s", "|", "|");
	printf(" Vgr.TV tuner | TV tuner Cvqt%7s Promociq (%c)\n", "|", '%');
	for (int i = 0; i < 210; i++) printf("-");
	printf("\n");
}

void PrintTableRow(vector<Monitor*>& vec_mons, int& row, bool promoOrNo) {
	printf(" %-11s%-5s%-20s%-25s ", vec_mons[row]->getSerienNomer().c_str(), " ", vec_mons[row]->getMarka().c_str(), vec_mons[row]->getModel().c_str());
	printf("%-20s%-2s%6.1f\"%-2s%20s%-4s", vec_mons[row]->getCvqt().c_str(), " ", vec_mons[row]->getDiagonalNaEkran(), " ", ("(" + vec_mons[row]->getRazdSposobnost() + ")").c_str(), " ");
	printf("%-12.2f", vec_mons[row]->getCena());
	printf("%-4s%-10s%-5s%-10s%-4s", " ", vec_mons[row]->getTip().c_str(), " ", vec_mons[row]->getStatus().c_str(), " ");
	printf("%-4s%-11s%-16s%-5s", vec_mons[row]->getTVTuner().c_str(), " ", vec_mons[row]->getTVTunerCvqt().c_str(), " ");
	(promoOrNo == 0 ? printf("%-5d", vec_mons[row]->getPromo()) : printf("%-5d(%.2flv)", vec_mons[row]->getPromo(), vec_mons[row]->CalculatePromo()));
	printf("\n");
}

void PrintTableOfAllMonitors(vector<Monitor*>& vec_mons, bool promoOrNo, string msg) {
	system("cls");
	printf("\n (*). %s:\n\n", msg.c_str());
	PrintTableHeader();

	if (vec_mons.size() == 0)
		printf("\n[INFO]: Nqma opisani Monitori...\n");
	else {
		for (int i = 0; i < vec_mons.size(); i++)
			PrintTableRow(vec_mons, i, promoOrNo);
	}
	printf("\n");
}

void PrintAvailableMonitors(vector<Monitor*>& vec_mons) {
	PrintTableHeader();
	for (int i = 0; i < vec_mons.size(); i++)
		if (vec_mons.at(i)->getStatus() == "V_PRODAJBA")
			PrintTableRow(vec_mons, i, 0);
}

void DataCorrectionInputs(vector<Monitor*>& vec_mons, int index, bool StatusCorrection, bool BySerialNumber) {
	// string mrk, mod;
	string cv, rs, tip, st, tvtun_cvqt = "---";
	double de, cena;
	bool tvtun = false;

	system("cls");
	printf("\n (*). Tekushta informaciq za izbraniqt ot vas Monitor:\n\n");

	PrintTableHeader();
	PrintTableRow(vec_mons, index, 0);
	printf("\n (!). Korekciq na Monitor sus Serien Nomer[%s], Marka[%s] i Model [%s]:\n\n", vec_mons.at(index)->getSerienNomer().c_str(), vec_mons.at(index)->getMarka().c_str(), vec_mons.at(index)->getModel().c_str());
	printf("[WARNING] Iskate li da produljite kum redaktirane na dannite za tozi Monitor? (Y/N): ");
	switch (ValidateYNChoice()) { case 'N': case 'n': return; }
	printf("\nVuvedi nova informaciq za:\n\n");
	cin.ignore();

	printf(" >> Cvqt na Monitor: ");
	getline(cin, cv, '\n');
	cv = TrimString(cv);
	ReplaceWhiteSpaces(cv);

	printf(" >> Diagonal na Ekrana (Primer: 23.6): ");
	cin >> de;
	cin.ignore();

	printf(" >> Razdelitelna Sposobnost(Primer: 1920x1080): ");
	getline(cin, rs, '\n');
	rs = ToLowerCase(RemoveWhiteSpaces(rs));

	printf(" >> Originalna Cena (Primer: 324.99): ");
	cin >> cena;

	printf(" >> Tip:\n\t(1). NOV\n\t(2). VTORA RUKA\n");
	tip = (ValidateInput(1, 2) == 1 ? "NOV" : "VTORA_RUKA");

	if (StatusCorrection == 1) {
		printf(" >> Status:\n\t(1). V PRODAJBA\n\t(2). KAPARIRAN\n\t(3). PRODADEN\n");
		int izb_st = ValidateInput(1, 3);
		st = (izb_st == 1 ? "V_PRODAJBA" : (izb_st == 2 ? "KAPARIRAN" : "PRODADEN"));
	}

	printf(" >> TV-Tuner:\n\t(1). IMA\n\t(2). NQMA\n");
	if (ValidateInput(1, 2) == 1) {
		cin.ignore();
		tvtun = true;
		printf(" >> Cvqt na TV-Tunera (Primer: cherveno): ");
		getline(cin, tvtun_cvqt, '\n');
		tvtun_cvqt = TrimString(tvtun_cvqt);
		ReplaceWhiteSpaces(tvtun_cvqt);
	}

	vec_mons.at(index)->setCvqt(cv);
	vec_mons.at(index)->setDiagonalNaEkran(de);
	vec_mons.at(index)->setRazdSposobnost(rs);
	vec_mons.at(index)->setTip(tip);
	vec_mons.at(index)->setCena(cena);
	vec_mons.at(index)->setStatus(st);
	vec_mons.at(index)->setTVTuner(tvtun);
	vec_mons.at(index)->setTVTunerCvqt(tvtun_cvqt);

	if (BySerialNumber == true)
		printf("\nMonitor sus Serien Nomer[%s] veche e s korigiranata informaciq.\n", vec_mons.at(index)->getSerienNomer().c_str());
	else {
		printf("\nMonitor sus Serien Nomer[%s], ", vec_mons.at(index)->getSerienNomer().c_str());
		printf("Marka[%s] i Model[%s] veche e s korigiranata informaciq.\n", vec_mons.at(index)->getMarka().c_str(), vec_mons.at(index)->getModel().c_str());
	}
	system("pause");
}

void CorrectionByMode(vector<Monitor*>& vec_mons, int mode) {
	cin.ignore();
	int index = -1;
	system("cls");
	if (mode == 0) {
		printf("\n (*). Vuvejdane na marka i model i dannite za korekciq\n (*) Spisuk na vsichki nalichni Monitori v sistemata\n\n");
		PrintAvailableMonitors(vec_mons);
		string mod, mrk;
		int sellectedMonitorFromCpys = 0;
		printf("\n Vuvedi informaciq za:\n\n");

		printf(" >> Marka na Monitor: ");
		getline(cin, mrk, '\n');
		mrk = TrimString(mrk);
		ReplaceWhiteSpaces(mrk);

		printf(" >> Model na Monitor: ");
		getline(cin, mod, '\n');
		mod = TrimString(mod);
		ReplaceWhiteSpaces(mod);

		if (CountMonitorDupsByMarkaAndModel(vec_mons, mrk, mod, 1) > 1) {
			string sn;
			printf("\n[WARNING] Povtarqne na Monitori! Vuvedete Serien Nomer na Monitor s Marka[%s] i Model[%s]:\n", mrk.c_str(), mod.c_str());
			while (true) {
				sn = ValidateSerialNumber(0);
				sellectedMonitorFromCpys = SearchSerialNumber(vec_mons, sn);
				if (sellectedMonitorFromCpys != -1) {
					int k = sellectedMonitorFromCpys;
					if (ToUpperCase(vec_mons.at(k)->getMarka()) == ToUpperCase(mrk) && ToUpperCase(vec_mons.at(k)->getModel()) == ToUpperCase(mod)) {
						index = sellectedMonitorFromCpys;
						break;
					}
				}
				printf("Vuvedi Validen Serien Nomer ot Tablicata gore na Monitor s Marka[%s] i Model[%s]...!\n", mrk.c_str(), mod.c_str());
			}
			DataCorrectionInputs(vec_mons, index, 1, 0);
		}
		else if (CountMonitorDupsByMarkaAndModel(vec_mons, mrk, mod, 1) == 1) {
			for (int i = 0; i < vec_mons.size(); i++)
				if (ToUpperCase(vec_mons.at(i)->getMarka()) == ToUpperCase(mrk) && ToUpperCase(vec_mons.at(i)->getModel()) == ToUpperCase(mod)) {
					index = i; break;
				}
			DataCorrectionInputs(vec_mons, index, 1, 0);
		}
		else {
			printf("\n[ERROR]: Monitor s: Marka[%s] i Model[%s] ne beshe nameren ili e PRODADEN/KAPARIRAN.\n", mrk.c_str(), mod.c_str());
			system("pause");
		}
	}
	else if (mode == 1) {
		string sn;
		while (true) {
			PrintTableOfAllMonitors(vec_mons, 0, "Vuvejdane na serien/ni nomer/a i korekciq na tezi Monitori ako sushtestvuvat\n (*). Spisuk na vsichki Monitori v sistemata");
			printf("\n[NOTICE]: Vuvedi 0 kato stoinost za Serien Nomer za da spresh korekciqta i da se vurnesh v Glavnoto Menu.\n");
			printf("\nVuvedi informaciq za:\n\n");
			sn = ValidateSerialNumber(1);
			if (sn.compare("0") == 0)
				break;
			else {
				if (!CheckSerialNumber(vec_mons, sn) == true)
					DataCorrectionInputs(vec_mons, SearchSerialNumber(vec_mons, sn), 1, 1);
				else {
					printf("\n[ERROR]: Monitor sus Serien Nomer[%s] ne beshe nameren ili e PRODADEN/KAPARIRAN.\n", sn.c_str());
					system("pause");
				}
				continue;
			}
			break;
		}
	}
}

void ManageMonitorsDiscount(vector<Monitor*>& vec_mons, int mode) {
	bool IsMonitorValid = false;
	cin.ignore();
	system("cls");
	if (mode == 0) {
		// Opredelqne na promocionalni %ti po Model
		string mod;
		int promo;
		PrintTableOfAllMonitors(vec_mons, 0, "Opredelqne na promocionalni %ti za model Monitori v prodajba\n (*). Spisuk na vsichki Monitori v sistemata");
		printf("Vuvedi informaciq za:\n\n");

		printf(" >> Model na Monitor: ");
		getline(cin, mod, '\n');
		mod = TrimString(mod);
		ReplaceWhiteSpaces(mod);

		printf("\nVuvedi NOV promocionalen %c:\n", '%');
		promo = ValidateInput(0, 100);
		cin.ignore();

		for (int i = 0; i < vec_mons.size(); i++) {
			if (ToUpperCase(vec_mons.at(i)->getModel()) == ToUpperCase(mod)) {
				IsMonitorValid = true;
				break;
			}
		}

		if (IsMonitorValid == true) {
			for (int i = 0; i < vec_mons.size(); i++)
				if (ToUpperCase(vec_mons.at(i)->getModel()) == ToUpperCase(mod) && vec_mons.at(i)->getStatus() == "V_PRODAJBA")
					vec_mons.at(i)->setPromo(promo);
			printf("\n Vsichki Monitori s Model[%s] veche sa s korigiran promocionalen %c - %d%c\n", mod.c_str(), '%', promo, '%');
		}
		else
			printf("\n[ERROR]: Monitor s Model[%s] NE sushtestvuva.\n", mod.c_str());
		system("pause");
	}
	else if (mode == 1) {
		// Opredelqne na promocionalni %ti po Serien Nomer.
		string sn;
		int index, promo;
		system("cls");
		while (true) {
			PrintTableOfAllMonitors(vec_mons, 0, "Opredelqne na promocionalni %ti za opredeleni broiki Monitori po Serien Nomer\n (*). Spisuk na vsichki Monitori v sistemata");
			printf("[NOTICE]: Vuvedi 0 kato stoinost za Serien Nomer za da spresh korekciqta i da se vurnesh v Glavnoto Menu.\n");
			printf("Vuvedi informaciq za:\n\n");
			sn = ValidateSerialNumber(1);

			if (sn.compare("0") != 0) {
				if (!CheckSerialNumber(vec_mons, sn) == true) {
					system("cls");
					cin.ignore();

					index = SearchSerialNumber(vec_mons, sn);
					printf("\n (*). Opredelqne na promocionalni %cti za opredeleni broiki Monitori po Serien Nomer:\n\n", '%');
					printf("\n (*). Tekushta informaciq za izbraniqt ot vas Monitor:\n\n");

					PrintTableHeader();
					PrintTableRow(vec_mons, index, 0);

					printf("\nVuvedi NOV promocionalen %c:\n", '%');
					promo = ValidateInput(0, 100);
					vec_mons.at(index)->setPromo(promo);
					cin.ignore();

					printf("\nMonitor sus Serien Nomer[%s] veche e s korigiran promocionalen %c - %d%c\n", sn.c_str(), '%', promo, '%');
				}
				else
					printf("\n[ERROR]: Monitor sus Serien Nomer[%s] ne beshe nameren.\n", sn.c_str());
				system("pause");
				system("cls");
				continue;
			}
			break;
		}
	}
}

void MonitorsDataCorrectionMenu(vector<Monitor*>& vec_mons) {
	system("cls");
	printf("\n (*). Korekciq na informaciqta na Monitori:\n\n");
	printf(" (1). Vuvejdane na marka i model i dannite za korekciq.\n");
	printf(" (2). Vuvejdane na serien/ni nomer/a i korekciq na tezi Monitori ako sushtestvuvat.\n");
	printf(" (3). Opredelqne na promocionalni %cti za model Monitori ili za opredeleni broiki Monitori po Serien Nomer.\n", '%');
	printf(" (0). Obratno v Glavnoto Menu.\n\n");
	switch (ValidateInput(0, 3)) {
	case 1: CorrectionByMode(vec_mons, 0); break;
	case 2: CorrectionByMode(vec_mons, 1); break;
	case 3:
		printf("\n\t(1). Opredelqne na promocionalni %cti za model Monitori v prodajba.\n", '%');
		printf("\t(2). Opredelqne na promocionalni %cti za opredeleni broiki Monitori po Serien Nomer.\n", '%');
		printf("\t(0). Obratno v Glavnoto Menu.\n\n");
		cin.ignore();
		switch (ValidateInput(0, 2)) {
		case 1: ManageMonitorsDiscount(vec_mons, 0); break;
		case 2: ManageMonitorsDiscount(vec_mons, 1); break;
		case 0: break;
		}
	case 0: break;
	}
	SaveDB_Monitors(vec_mons);
}

void SellOrCopyingMonitor(vector<Monitor*>& vec_mons, int mode) {
	string sn;
	int index = -1, sellectedMonitorFromCpys;
	double cena_kaparo;
	string mrk, mod, st;
	system("cls");
	cin.ignore();
	if (mode == 0) {
		printf("\n (*). Vuvejdane na Model i Marka i izbirane ot nalichnite Monitori v prodajba po Serien Nomer:\n");
		printf(" (*). Nalichni Monitori v prodajba:\n\n");
	}
	else {
		printf("\n (*). Kaparirane na Monitor po Serien Nomer:\n");
		printf(" (*). Nalichni Monitori za kaparirane:\n\n");
	}

	PrintAvailableMonitors(vec_mons);

	if (mode == 0) {
		// Prodavane na Monitor.
		printf("\n Vuvedi informaciq za:\n\n");
		printf(" >> Marka na Monitor: ");
		getline(cin, mrk, '\n');
		mrk = TrimString(mrk);
		ReplaceWhiteSpaces(mrk);

		printf(" >> Model na Monitor: ");
		getline(cin, mod, '\n');
		mod = TrimString(mod);
		ReplaceWhiteSpaces(mod);

		if (CountMonitorDupsByMarkaAndModel(vec_mons, mrk, mod, 1) > 1) {
			printf("\n[WARNING] Povtarqne na Monitori! Vuvedete Serien Nomer na Monitor s Marka[%s] i Model[%s] na koito iskate da napravite korekciq:\n", mrk.c_str(), mod.c_str());
			while (true) {
				sn = ValidateSerialNumber(0);
				sellectedMonitorFromCpys = SearchSerialNumber(vec_mons, sn);
				if (sellectedMonitorFromCpys != -1) {
					int k = sellectedMonitorFromCpys;
					if (ToUpperCase(vec_mons.at(k)->getMarka()) == ToUpperCase(mrk) && ToUpperCase(vec_mons.at(k)->getModel()) == ToUpperCase(mod)) {
						index = sellectedMonitorFromCpys;
						break;
					}
				}
				printf("Vuvedi Validen Serien Nomer ot Tablicata gore...!\n");
			}
		}
		else {
			for (int i = 0; i < vec_mons.size(); i++)
				if (ToUpperCase(vec_mons.at(i)->getMarka()) == ToUpperCase(mrk) && ToUpperCase(vec_mons.at(i)->getModel()) == ToUpperCase(mod))
					if (vec_mons.at(i)->getStatus() == "V_PRODAJBA") { index = i; break; }
		}

		if (index >= 0) {
			char choice = ' ';
			system("cls");
			printf("\n (*). Vuvejdane na Model i Marka i izbirane ot nalichnite Monitori v prodajba po Serien Nomer:\n");
			printf(" (*). Danni na Monitora koito iskate da zakupite:\n\n");
			PrintTableHeader();
			PrintTableRow(vec_mons, index, 0);
			printf("\n Sigurni li ste che iskate da zakupite tozi Monitor? (Y/N): ");
			switch (ValidateYNChoice()) {
			case 'Y': case 'y':
				st = "PRODADEN";
				printf("\n Vie uspeshno ZAKUPIHTE Monitora posochen ot vas...!!!\n");
				vec_mons.at(index)->setStatus(st);
				break;
			case 'N': case 'n':
				printf("\n Vie uspeshno OTKAZAHTE zakupuvaneto na Monitora posochen ot vas.\n");
				break;
			}
			system("pause");
		}
		else {
			printf("\n[ERROR] Monitora koito tursite ne sushtestvuva v sistemata...\n");
			system("pause");
		}
	}
	else if (mode == 1) {
		// Kaparirane na Monitor.
		printf("\n[NOTICE]: Vuvedi 0 kato stoinost za Serien Nomer za da spresh kapariraneto na Monitor i da se vurnesh v Glavnoto Menu.\n");
		printf("\nVuvedi Serien Nomer za da Kaparirash Monitor:\n");
		while (true) {
			sn = ValidateSerialNumber(1);
			if (sn.compare("0") == 0) break;
			else {
				index = SearchSerialNumber(vec_mons, sn);
				if (!CheckSerialNumber(vec_mons, sn) == true && vec_mons.at(index)->getStatus() == "V_PRODAJBA")
					break;
				printf("[ERROR] Vuvedi validen serien nomer ot tablicata gore...\n");
			}
		}

		if (index >= 0) {
			system("cls");
			printf("\n (*). Kaparirane na Monitor po Serien Nomer:\n\n");
			PrintTableHeader();
			PrintTableRow(vec_mons, index, 0);

			if (vec_mons.at(index)->getPromo() == 100) {
				st = "PRODADEN";
				printf("Tozi monitor e bezplaten zashtoto promocionalniqt procent e 100.\nVIE USPESHNO GO ZAKUPIHTE!\n");
				vec_mons.at(index)->setStatus(st);
			}
			else {
				printf("\nVuvejdane na Kaparo:\n");
				cena_kaparo = ValidateInput<double>(1, ceil(vec_mons.at(index)->CalculatePromo()));


				if (vec_mons.at(index)->CalculatePromo() - cena_kaparo <= 0) {
					st = "PRODADEN";
					printf("\nVIE ZAKUPIHTE TOZI Monitor zashtoto Kaparoto e kolkoto Cenata na Monitora!!!\n");
					vec_mons.at(index)->setStatus(st);
				}
				else {
					st = "KAPARIRAN";
					printf("\nVie kaparirahte tozi Monitor USPESHNO!\n\n");
					printf("Cena: %.2f(-%d%c namalenie)\nKaparo: %.2f\n", vec_mons.at(index)->CalculatePromo(), vec_mons.at(index)->getPromo(), '%', cena_kaparo);
					double new_cena = vec_mons.at(index)->CalculatePromo() - cena_kaparo;
					printf("Nova Cena sled prilagane na Kaparoto: %.2f\n\n", new_cena);
					vec_mons.at(index)->setCena(new_cena);
					vec_mons.at(index)->setStatus(st);
				}
			}		
		}
		system("pause");
	}
	SaveDB_Monitors(vec_mons);
}

void MonitorsSellMenu(vector<Monitor*>& vec_mons) {
	system("cls");
	printf("\n (*). Prodajba na Monitori:\n\n");
	if (vec_mons.size() == 0) {
		printf("[ERROR] Nqma vuvedeni Monitori v sistemata...!!!\n");
		system("pause");
	}
	else {
		printf(" (1). Vuvejdane na Model i Marka i izbirane ot nalichnite Monitori v prodajba po Serien Nomer.\n");
		printf(" (2). Kaparirane na Monitor po Serien Nomer.\n");
		printf(" (0). Obratno v Glavnoto Menu.\n");
		switch (ValidateInput(0, 2)) {
		case 1: SellOrCopyingMonitor(vec_mons, 0); break;
		case 2: SellOrCopyingMonitor(vec_mons, 1); break;
		case 0: break;
		}
	}
	SaveDB_Monitors(vec_mons);
}

void SortByMode(const vector<Monitor*>& vec_mons, int mode) {
	vector<Monitor*> sell_vec, sort_vec;
	cin.ignore();

	//Za sortirane na elementite vuv vektora se izpolzva metoda -> BubbleSort.
	// Izvlichane na Monitorite koito sa V PRODAJBA
	for (int i = 0; i < vec_mons.size(); i++) {
		if (vec_mons.at(i)->getStatus() == "V_PRODAJBA")
			sell_vec.push_back(vec_mons.at(i));
	}
	if (mode == 0) {
		// Izvejdane na Monitorite sortirani po Serien Nomer vuv vuzhodqsht red(0-9)
		for (int i = 0; i < sell_vec.size(); i++) {
			for (int r = 0; r < sell_vec.size() - 1 - i; r++)
				if (sell_vec.at(r)->getSerienNomer().size() > sell_vec.at(r + 1)->getSerienNomer().size())
					SwapObjectProperties(*sell_vec.at(r), *sell_vec.at(r + 1));
				else if (sell_vec.at(r)->getSerienNomer().size() == sell_vec.at(r + 1)->getSerienNomer().size())
					if (sell_vec.at(r)->getSerienNomer() > sell_vec.at(r + 1)->getSerienNomer())
						SwapObjectProperties(*sell_vec.at(r), *sell_vec.at(r + 1));
		}
		PrintTableOfAllMonitors(sell_vec, 0, "Spisuk na Monitori v prodajba sortirani po Serien Nomer");
	}
	else if (mode == 1) {
		// Izvejdane na Monitorite na dadena marka sortirani po cena v nizhodqsht red(9-0)
		string mrk;
		printf("\nVuvedi informaciq za:\n\n");
		printf(" >>  Marka na Monitor: ");
		getline(cin, mrk, '\n');
		mrk = TrimString(mrk);
		ReplaceWhiteSpaces(mrk);

		for (int i = 0; i < sell_vec.size(); i++)
			if (ToUpperCase(sell_vec.at(i)->getMarka()) == ToUpperCase(mrk))
				sort_vec.push_back(sell_vec.at(i));

		for (int i = 0; i < sort_vec.size(); i++) {
			for (int r = 0; r < sort_vec.size() - 1 - i; r++)
				if (sort_vec.at(r)->getCena() < sort_vec.at(r + 1)->getCena())
					SwapObjectProperties(*sort_vec.at(r), *sort_vec.at(r + 1));
		}
		PrintTableOfAllMonitors(sort_vec, 0, ("Spisuk na Monitori s marka(" + ToUpperCase(mrk) + ") v prodajba sortirani po Cena v namalqvasht red"));
	}
	else if (mode == 2) {
		// Izvejdane na Monitorite koito imat promocionalen % > 0 sortirani po cena v nizhodqsht red(9-0)
		for (int i = 0; i < sell_vec.size(); i++)
			if (sell_vec.at(i)->getPromo() > 0)
				sort_vec.push_back(sell_vec.at(i));

		for (int i = 0; i < sort_vec.size(); i++) {
			for (int r = 0; r < sort_vec.size() - 1 - i; r++)
				if (sort_vec.at(r)->CalculatePromo() < sort_vec.at(r + 1)->CalculatePromo())
					SwapObjectProperties(*sort_vec.at(r), *sort_vec.at(r + 1));
		}
		PrintTableOfAllMonitors(sort_vec, 1, "Spisuk na Monitori v prodajba i promociq sortirani po Cena v namalqsht red");
	}
	else if (mode == 3) {
		// Izvejdane na Monitorite s harakteristiki po golemi ot vuvedenite stoinosti: razdelitelna sposobnost, diagonal na ekrana i vgraden tv tuner(IMA / NQMA)
		string rs;
		double de;
		bool tvtun, isRSBigger;

		printf("\nVuvedi informaciq za:\n\n");
		printf(" >> Diagonal na Ekrana (Primer: 23.6): ");
		cin >> de;
		cin.ignore();

		printf(" >> Razdelitelna Sposobnost (Primer: 1920x1080): ");
		getline(cin, rs, '\n');
		rs = ToLowerCase(RemoveWhiteSpaces(rs));

		printf(" >> TV-Tuner:\n\t(1). IMA\n\t(2). NQMA\n");
		(ValidateInput(1, 2) == 1 ? tvtun = true : tvtun = false);

		/*
			Ako se nameri obekt vuv vektora chrez indexa mu([i]) koito ima kato stoinost za
			diagonal na ekrana po-golqma ot vuvedenata ot vhodniq bufer za de i
			stoinostta na tv tuner suvpada s vuvedenata ot vhodniq bufer za tvtun
			shte se proveri dali duljinata na niza ot obekta - razd. sposobnost e po golqma
			ot duljinata na vuvedenata ot vhodniq bufer razd. sposobnost (rs) tova oznachava che tozi
			obekt(monitor) e s po-golemi harakteristiki ot vuvedenite ot vhodniq bufer za spravka.
			V Protiven sluchai ako ASCII kodovete na razd. sposobnost ot obekta(monitor) sa po-golemi
			ot tezi na vuvedenata razd. sposobnost ot vhodniq bufer(rs) oznachava che e s po golemi harakteristiki
			ot vuvedenite ot vhodniq bufer za spravka.
		*/

		for (int i = 0; i < sell_vec.size(); i++) {
			isRSBigger = false;
			if (sell_vec.at(i)->getDiagonalNaEkran() > de && (sell_vec.at(i)->getTVTuner() == "IMA" ? true : false) == tvtun) {
				if (sell_vec.at(i)->getRazdSposobnost().size() > rs.size())
					isRSBigger = true;
				else
					if (sell_vec.at(i)->getRazdSposobnost() > rs)
						isRSBigger = true;
			}
			// Ako obekta na poziciq [i] e s po golemi harakteristiki ot vuvedenite za spravka to toi shte se dobavi vuv vektora sort_vec
			if (isRSBigger == true)
				sort_vec.push_back(sell_vec.at(i));
		}


		for (int i = 0; i < sort_vec.size(); i++) {
			for (int r = 0; r < sort_vec.size() - 1 - i; r++)
				if (ToUpperCase(sort_vec.at(i)->getMarka()) > ToUpperCase(sort_vec.at(i + 1)->getMarka()))
					SwapObjectProperties(*sort_vec.at(i), *sort_vec.at(i + 1));
		}
		PrintTableOfAllMonitors(sort_vec, 0, "Spisuk na Monitori v prodajba koito imat specifikacii po-golemi ot vuvedenite danni");
	}
	ClearVector(sell_vec);
	ClearVector(sort_vec);
	system("pause");
}

void PrintSpecificMonitorsMenu(vector<Monitor*>& vec_mons) {

	//(5). Odit/Spisuk na Monitori v nalichnost.

	system("cls");
	printf("\n(*). Odit s nalichnite Monitori v sistemata:\n\n");
	printf(" (1). Izvejdane na Monitori v podreden red po Serien Nomer.\n");
	printf(" (2). Izvejdane na Monitori po kriterii.\n");
	printf(" (0). Obratno v Glavnoto Menu.\n\n");
	switch (ValidateInput(0, 2)) {
	case 1: SortByMode(vec_mons, 0); break;
	case 2:
		printf("\n\t(1). Izvejdane na dadena Marka Monitori sortirani po cena v nizhodqsht red (9 - 0).\n");
		printf("\t(2). Izvejdane na Monitori v promociq sortirani po cena v nizhodqsht red (9 - 0).\n");
		printf("\t(3). Izvejdane na Monitori s po-golemi kriterii ot zadadeni.\n");
		printf("\t(0). Obratno v Glavnoto Menu.\n\n");
		switch (ValidateInput(0, 3)) {
		case 1: SortByMode(vec_mons, 1); break;
		case 2: SortByMode(vec_mons, 2); break;
		case 3: SortByMode(vec_mons, 3); break;
		}
	}
	system("cls");
}

void PrintMainMenu() {
	// Funkciq za izvejdane na glavnoto menu.
	printf("\n+======================================================+\n");
	printf("   > INFORMACIONNA SISTEMA ZA PRODAVANE NA Monitori <    \n");
	printf("+======================================================+\n\n");
	printf(" (1). Dobavqne na novi Monitori.\n");
	printf(" (2). Izvejdane na spisuk s vsichki Monitori.\n");
	printf(" (3). Korekciq na informaciqta na Monitori.\n");
	printf(" (4). Prodajba na Monitori.\n");
	printf(" (5). Spisuk na Monitori v nalichnost.\n");
	printf(" (0). Izhod...\n\n");
}

int main() {
	vector<Monitor*> listOfMonitors;
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	LoadDB_Monitors(listOfMonitors);
	while (true) {
		system("cls");
		PrintMainMenu();
		switch (ValidateInput<int>(0, 5)) {
		case 1: AddMonitorsMenu(listOfMonitors); break;
		case 2: PrintTableOfAllMonitors(listOfMonitors, 0, "Izvejdane na spisuk s vsichki Monitori"); system("pause"); break;
		case 3: MonitorsDataCorrectionMenu(listOfMonitors); break;
		case 4: MonitorsSellMenu(listOfMonitors);  break;
		case 5: PrintSpecificMonitorsMenu(listOfMonitors); break;
		case 0: SaveDB_Monitors(listOfMonitors); ClearVector(listOfMonitors); exit(0);
		}
	}
	return 0;
}