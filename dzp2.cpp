#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Graf {
private:
	int incedes[11];
	string lokacije[11];
	int prov[11];
	int edges[100];
	int num;
	int cena[11][11];
	int brg = 0;
public:
	Graf() {
		for (int i = 1; i < 11; i++)
			incedes[i] = 0;
		for (int i = 1; i < 11; i++) {
			prov[i] = 0;
			for (int j = 1; j < 11; j++)
				cena[i][j] = 0;
		}
		for (int i = 1; i < 100; i++)
			edges[i] = 0;
	}
	int dohvNum() {
		return num;
	}
	void kreiraj(int n) {
		for (int i = 1; i <= n; i++) {
			incedes[i] = i;
		}
		num = n;
		incedes[0] = 0;
		incedes[n + 1] = n + 1;
		for (int i = 1; i <= num; i++) {
			getline(cin, lokacije[i]);
		}
	}
	void brisi() {
		for (int i = 1; i < 100; i++)
			edges[i] = 0;
		for (int i = 1; i < 11; i++)
			incedes[i] = 0;
		for (int i = 1; i < 11; i++) {
			prov[i] = 0;
			for (int j = 1; j < 11; j++)
				cena[i][j] = 0;
		}
		cout << "Graf obrisan" << endl;
	}

	void brisi2() {
		for (int i = 1; i < 100; i++)
			edges[i] = 0;
		for (int i = 1; i < 11; i++)
			incedes[i] = i;
		for (int i = 1; i < 11; i++) {
			prov[i] = 0;
			for (int j = 1; j < 11; j++)
				cena[i][j] = 0;
		}
	}

	void dodajCvor(string str1) {
		int tmp = incedes[num] + prov[num];
		num++;
		if (prov[num - 1] != 0) {
			incedes[num] = tmp;
		}
		else {
			incedes[num] = incedes[num - 1] + 1;
		}
		lokacije[num] = str1;
	}
	void ispis() {
		cout << "Lokacije : " << endl;
		for (int i = 1; i <= num; i++) {
			cout << lokacije[i] << " : ";
			for (int j = incedes[i]; j < incedes[i + 1]; j++) {
				if (incedes[i + 1] - j > 1)
					cout << lokacije[edges[j]] << ",";
				else if (incedes[i + 1] - j == 1)
					cout << lokacije[edges[j]];
				else
					break;
			}	
			cout << endl;
		}
		cout << endl;
		for (int i = 1; i <= num; i++) {
			for (int j = 1; j <= num; j++)
				cout << cena[i][j] << " ";
			cout << endl;
		}
	}
	void dodajGranu(string str1, string str2, int cen, int oc) {
		int p, q;
		for (int i = 1; i <= num; i++) {
			if (str1.compare(lokacije[i]) == 0) {
				p = i;
				break;
			}
		}
		for (int i = 1; i <= num; i++) {
			if (str2.compare(lokacije[i]) == 0) {
				q = i;
				break;
			}
		}
		if (oc == 1) {
			cena[p][q] = cen;
			cena[q][p] = cen;
		}
		if (oc == 2) {
			cena[p][q] = -cen;
			cena[q][p] = -cen;
		}
		if (prov[p] == 0) {

			prov[p]++;
			edges[incedes[p]] = q;
			brg++;
		}
		else {
			for (int i = 99; i > (incedes[p] + prov[p] - 1); i--)
				edges[i] = edges[i - 1];
			edges[incedes[p] + prov[p]] = q;
			for (int i = p + 1; i <= num + 1; i++)
				incedes[i] = incedes[i] + 1;
			brg++;
			prov[p]++;
		}
		if (prov[q] == 0) {

			prov[q]++;
			edges[incedes[q]] = p;
			brg++;
		}
		else {
			for (int i = 99; i > (incedes[q] + prov[q] - 1); i--)
				edges[i] = edges[i - 1];
			edges[incedes[q] + prov[q]] = p;
			for (int i = q + 1; i <= num + 1; i++)
				incedes[i] = incedes[i] + 1;
			brg++;
			prov[q]++;
		}
	}
	void ukloniGranu(string str1, string str2) {
		int i;
		int p, q;
		for (int i = 1; i <= num; i++) {
			if (str1.compare(lokacije[i]) == 0) {
				p = i;
				break;
			}
		}
		for (int i = 1; i <= num; i++) {
			if (str2.compare(lokacije[i]) == 0) {
				q = i;
				break;
			}
		}
		cena[p][q] = 0;
		cena[q][p] = 0;
		for (i = incedes[p]; i < incedes[p + 1]; i++) {
			if (edges[i] == q) {
				edges[i] = 0;
				if (prov[p] != 1)
					for (int j = i; j < 99; j++)
						edges[j] = edges[j + 1];
				for (int j = p + 1; j <= num; j++)
					if (prov[p] != 1)
						incedes[j]--;
				prov[p]--;
			}
		}
		for (i = incedes[q]; i < incedes[q + 1]; i++) {
			if (edges[i] == p) {
				edges[i] = 0;
				if (prov[q] != 1)
					for (int j = i; j < 99; j++)
						edges[j] = edges[j + 1];
				for (int j = q + 1; j <= num; j++)
					if (prov[q] != 1)
						incedes[j]--;
				prov[q]--;
			}
		}
	}
	void ukloniCvor(int p) {
		for (int i = (incedes[p + 1] - 1); i >= incedes[p]; i--) {
			edges[i] = 0;
			if (prov[p] != 1)
				for (int j = i; j < 99; j++)
					edges[j] = edges[j + 1];
			if (prov[p] != 1)
				for (int j = p + 1; j <= num; j++)
					incedes[j]--;
			prov[p]--;
		}
		for (int i = 1; i < 100; i++)
			if (edges[i] == p) {
				int tmp;
				edges[i] = 0;
				for (int j = 1; j <= num; j++)
					if (incedes[j + 1] > i) {
						tmp = j;
						break;
					}
				if (prov[tmp] != 1) {
					for (int j = i; j < 99; j++)
						edges[j] = edges[j + 1];
					for (int j = tmp + 1; j <= num; j++)
						incedes[j]--;
				}
				prov[tmp]--;
			}
	}

	void minCena() {
		int min, i, mincena = 0;
		int kontrolni[11];
		for (i = 1; i < 11; i++)
			kontrolni[i] = -1;
		i = 1;
		kontrolni[1] = 0;
		for (int ct = 1; ct < num; ct++) {
			min = 100;
			if (ct == 1)
				for (int j = incedes[i]; j < incedes[i] + prov[i]; j++)
					kontrolni[edges[j]] = cena[i][edges[j]];
			else 
				for (int j = incedes[i]; j < incedes[i] + prov[i]; j++) {
					if (cena[i][edges[j]] < kontrolni[edges[j]] && kontrolni[edges[j]] != 0)
						kontrolni[edges[j]] = cena[i][edges[j]];
					if (kontrolni[edges[j]] == -1)
						kontrolni[edges[j]] = cena[i][edges[j]];
				}
			for (int j = 1; j <= num; j++) {
				if (kontrolni[j] == 0 || kontrolni[j] == -1)
					continue;
				else {
					if (kontrolni[j] < min) {
						min = kontrolni[j];
						i = j;
					}
				}
			}
			kontrolni[i] = 0;
			mincena = mincena + min;
		}
		cout << "Minimalna cena izgradnje metroa je : " << mincena << endl;
	}

	void Dijkstra(string str1) {
		int poc, min, i;
		int d[22] = {};
		for (int i = 1; i <= 21; i++) {
			if (i <= num)
				d[i] = std::numeric_limits<int>::max();
			else if (i > num)
				d[i] = 0;
		}
		int skup[11] = {};
		for (int i = 1; i <= num; i++) 
			if (str1.compare(lokacije[i]) == 0) {
				poc = i;
				break;
			}
		skup[poc] = 1;
		for (int i = 1; i <= num; i++)
			if (i != poc) {
				if (cena[poc][i] > 0) 
					d[i] = cena[poc][i];
				else if (cena[poc][i] < 0) {
					d[i] = -cena[poc][i];
					d[i + num] = -cena[poc][i];
				}
				else if (cena[poc][i] == 0)
					d[i] = std::numeric_limits<int>::max();
			}
		int prev;
		for (int k = 1; k <= num - 1; k++) {
			if (k == 1)
				prev = poc;
			else
				prev = i;
			double min = std::numeric_limits<int>::max();
			for (int j = 1; j <= num; j++)
				if (skup[j] != 1)
					if (d[j] != std::numeric_limits<int>::max())
						if (d[j] < min) {
							min = d[j];
							i = j;
						}
			skup[i] = 1;
			for (int j = 1; j <= num; j++)
				if (skup[j] != 1)
					if (d[i] + abs(cena[i][j]) < d[j]) {
						if (cena[i][j] > 0) {
							d[j] = d[i] + cena[i][j];
							d[j + num] = d[i + num];
						}
						else if (cena[i][j] < 0) {
							d[j] = d[i] + abs(cena[i][j]);
							d[j + num] = d[i + num] + abs(cena[i][j]);
						}
					}
		}
		for (int j = 1; j <= num; j++)
			if (j != poc)
				cout << "Najmanja udaljenost izmedju " << lokacije[poc] << " i " << lokacije[j] << " je " << "UKUPNO : " << d[j]
				<< endl << "IZGRADJENO : " << d[j] - d[j + num] << endl << "NEIZGRADJENO : " << d[j + num] << endl << endl;
	}
};

int main() {
	int izbor, n, brg = 0, p, q, flag = 0, cen, oc, flag2 = 0;
	Graf g;
	string djubre, str1, str2;
	while (1) {
		cout << "Meni :" << endl << "1. Kreiranje grafa" << endl << "2. Dodavanje lokacije" << endl << "3. Uklanjanje lokacije" << endl
			<< "4. Dodavanje moguce linije metroa izmedju dve lokacije" << endl << "5. Uklanjanje moguce linije metroa izmedju dve lokacije" << endl
			<< "6. Ispis grafa" << endl << "7. Brisanje grafa" << endl << "8. Minimalna cena gradnje metroa"  << endl << "9. Dodavanje puta izmedju lokacija"
			<< endl << "10. Minimalni put vatrogasnih kola" << endl  << "0. Izlaz iz programa" << endl;
		cin >> izbor;
		switch (izbor) {

			// KREIRANJE GRAFA LOKACIJA
		case 1:
			cout << "Unesite broj kljucnih lokacija u gradu (Maksimalno 9)" << endl;
			cin >> n;
			getline(cin,djubre);
			cout << "Unesite imena kljucnih lokacija u gradu :" << endl;
			if (n > 9)
				break;
			g.kreiraj(n);
			flag = 1;
			break;

			// DODAVANJE LOKACIJE
		case 2:
			n = g.dohvNum();
			if (n < 9) {
				cout << "Unesite ime lokacije koju zelite da dodate" << endl;
				cin >> str1;
				g.dodajCvor(str1);
			}
			else
				cout << "Nema vise mesta za lokacije." << endl;
			break;

			// UKLANJANJE CVORA
		case 3:
			cout << "Koji cvor zelite da uklonite?" << endl;
			cin >> p;
			g.ukloniCvor(p);
			break;

			// DODAVANJE LINIJE METROA
		case 4:
			if (flag == 1) {
				cout << "Unesite lokacije izmedju kojih zelite da dodate liniju metroa" << endl;
				getline(cin, djubre);
				getline(cin, str1);
				getline(cin, str2);
				oc = 1;
				cout << "Unesite cenu za izgradnju linije izmedju te dve lokacije" << endl;
				cin >> cen;
				g.dodajGranu(str1, str2, cen, oc);
			}
			else
				cout << "Ne postoji nijedan graf!" << endl << endl;
			break;

			// BRISANJE LINIJE METROA
		case 5:
			cout << "Unesite lokacije izmedju kojih zelite da uklonite liniju metroa" << endl;
			getline(cin, djubre);
			getline(cin, str1);
			getline(cin, str2);
			g.ukloniGranu(str1, str2);
			break;

			// ISPISIVANJE REPREZENTACIJE GRAFA LOKACIJA
		case 6:
			if (flag == 1)
				g.ispis();
			else
				cout << "Ne postoji nijedan graf!" << endl << endl;
			break;

			// BRISANJE GRAFA LOKACIJA
		case 7:
			if (flag == 1)
				g.brisi();
			else
				cout << "Ne postoji nijedan graf!" << endl;
			flag = 0;
			flag2 = 0;
			brg = 0;
			break;

			// ISPIS MINIMALNE CENE GRADNJE METROA
		case 8:
			g.minCena();
			break;

			// DODAVANJE PUTEVA IZMEDJU LOKACIJA
		case 9:
			if (flag2 == 0)
				g.brisi2();
			if (flag == 1) {
				cout << "Unesite 1 ako je put vec izgradjen, a 2 ukoliko nije" << endl;
				cin >> oc;
				cout << "Unesite lokacije izmedju kojih zelite da dodate liniju metroa" << endl;
				getline(cin, djubre);
				getline(cin, str1);
				getline(cin, str2);
				cout << "Unesite cenu za izgradnju linije izmedju te dve lokacije" << endl;
				cin >> cen;
				g.dodajGranu(str1, str2, cen, oc);
			}
			else
				cout << "Ne postoji nijedan graf!" << endl << endl;
			flag2 = 1;
			break;

			// NAJKRACI PUT DO SVAKE LOKACIJE
		case 10:
			cout << "Unesite lokaciju na kojoj su parkirana vatrogasna kola :" << endl;
			getline(cin, djubre);
			getline(cin, str1);
			g.Dijkstra(str1);
			break;

			// IZLAZ IZ PROGRAMA
		case 0:
			exit(1);
			break;
		}
	}
}