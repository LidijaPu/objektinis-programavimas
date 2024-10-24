#include "mylib.h"
#include "stud.h"
#include "failai.h"
#include "listai.h"

int main() {
    vector<Studentas> studentai;
    list<Studentas> studentaiList;
    int n, pasirinkimas, konteinerioPasirinkimas;
    string name = "studentai.txt";

    cout << "Pasirinkite konteineri: vector (1), list (2): ";
    while (!(cin >> konteinerioPasirinkimas) || (konteinerioPasirinkimas != 1 && konteinerioPasirinkimas != 2)) {
        cout << "Klaida: Prasome ivesti 1 arba 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (konteinerioPasirinkimas == 1) {
        vector<Studentas> studentai;
        cout << "Pasirinkite: rankinis ivestis (1), skaitymas is failo (2), generavimas ir laiko matavimas (3): ";
        while (!(cin >> pasirinkimas) || (pasirinkimas < 1 || pasirinkimas > 3)) {
            cout << "Klaida: Prasome ivesti 1, 2 arba 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (pasirinkimas == 1) {
            int n;
            cout << "Iveskite studentu skaiciu: ";
            while (!(cin >> n) || n <= 0) {
                cout << "Klaida: Prasome ivesti teisinga skaiciu: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            for (int i = 0; i < n; i++) {
                Studentas s;
                cout << "Iveskite studento " << i + 1 << " varda: ";
                cin >> s.vardas;
                cout << "Iveskite studento " << i + 1 << " pavarde: ";
                cin >> s.pavarde;

                cout << "Iveskite namu darbu balus (ivesti neigiama skaiciu, norint baigti):" << endl;
                while (true) {
                    int rezultatas;
                    cout << "Namu darbu balas: ";
                    cin >> rezultatas;
                    if (rezultatas < 0) break;
                    if (rezultatas >= 1 && rezultatas <= 10) s.namu_darbai.push_back(rezultatas);
                    else cout << "Klaida: Prasome ivesti skaiciu tarp 1 ir 10." << endl;
                }
                cout << "Iveskite egzamino bala: ";
                while (!(cin >> s.egzaminas) || s.egzaminas < 1 || s.egzaminas > 10) {
                    cout << "Klaida: Prasome ivesti teisinga egzamino bala (nuo 1 iki 10): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                studentai.push_back(s);
            }

            int galutinis;
            cout << "Ar norite skaiciuoti galutini bala pagal vidurki (1) ar mediana (2)? ";
            while (!(cin >> galutinis) || (galutinis != 1 && galutinis != 2)) {
                cout << "Klaida: Prasome ivesti 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            rusiavimas(studentai);
            isvestis(studentai, galutinis);
        }
        else if (pasirinkimas == 2) {
            string failoPavadinimas;
            cout << "Iveskite failo pavadinima: ";
            cin >> failoPavadinimas;
            nuskaitytiIsFailo(failoPavadinimas, studentai);

            int galutinis;
            cout << "Ar norite skaiciuoti galutini bala pagal vidurki (1) ar mediana (2)? ";
            while (!(cin >> galutinis) || (galutinis != 1 && galutinis != 2)) {
                cout << "Klaida: Prasome ivesti 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            rusiavimas(studentai);
            isvestis(studentai, galutinis);
        }
        else if (pasirinkimas == 3) {
            int failoPasirinkimas;
            cout << "Ar norite generuoti naujus failus (1) ar naudoti jau sugeneruotus failus (2)? ";
            while (!(cin >> failoPasirinkimas) || (failoPasirinkimas != 1 && failoPasirinkimas != 2)) {
                cout << "Klaida: Prasome ivesti 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            vector<int> kiekiai = { 1000, 10000, 100000, 1000000, 10000000 };

            cout << "Ar norite skaiciuoti galutini bala pagal vidurki (1) ar mediana (2)? ";
            while (!(cin >> pasirinkimas) || (pasirinkimas != 1 && pasirinkimas != 2)) {
                cout << "Klaida: Prasome ivesti 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            int rusiuotiPagal;
            cout << "Ar norite rusiuoti studentus pagal varda (1), pavarde (2) ar pazymi (3)? \n";
            while (!(cin >> rusiuotiPagal) || (rusiuotiPagal < 1 || rusiuotiPagal > 3)) {
                cout << "Klaida: Prasome ivesti 1, 2 arba 3: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            for (int kiekis : kiekiai) {
                string failoPavadinimas = "studentai_" + to_string(kiekis) + ".txt";

                if (failoPasirinkimas == 1) {
                    auto start = high_resolution_clock::now();
                    generuotiStudentuDuomenis(failoPavadinimas, kiekis);
                    auto end = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(end - start).count() / 1e6;
                    cout << "Failo generavimas '" << failoPavadinimas << "' uztruko: " << fixed << setprecision(6) << duration << "s\n";
                }
                matuotiVeikimoGreiti(failoPavadinimas, kiekis, pasirinkimas, rusiuotiPagal);
            }
        }
    }
    else if (konteinerioPasirinkimas == 2) {
        list<Studentas> studentaiList;
        cout << "Pasirinkite: rankinis ivestis (1), skaitymas is failo (2), generavimas ir laiko matavimas (3): ";
        while (!(cin >> pasirinkimas) || (pasirinkimas < 1 || pasirinkimas > 3)) {
            cout << "Klaida: Prasome ivesti 1, 2 arba 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (pasirinkimas == 1) {
            int n;
            cout << "Iveskite studentu skaiciu: ";
            while (!(cin >> n) || n <= 0) {
                cout << "Klaida: Prasome ivesti teisinga skaiciu: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            for (int i = 0; i < n; i++) {
                Studentas sl;
                cout << "Iveskite studento " << i + 1 << " varda: ";
                cin >> sl.vardas;
                cout << "Iveskite studento " << i + 1 << " pavarde: ";
                cin >> sl.pavarde;

                cout << "Iveskite namu darbu balus (ivesti neigiama skaiciu, norint baigti):" << endl;
                while (true) {
                    int rezultatas;
                    cout << "Namu darbu balas: ";
                    cin >> rezultatas;
                    if (rezultatas < 0) break;
                    if (rezultatas >= 1 && rezultatas <= 10) sl.namu_darbai.push_back(rezultatas);
                    else cout << "Klaida: Prasome ivesti skaiciu tarp 1 ir 10." << endl;
                }

                cout << "Iveskite egzamino bala: ";
                while (!(cin >> sl.egzaminas) || sl.egzaminas < 1 || sl.egzaminas > 10) {
                    cout << "Klaida: Prasome ivesti teisinga egzamino bala (nuo 1 iki 10): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                studentaiList.push_back(sl);
            }


            int galutinis;
            cout << "Ar norite skaiciuoti galutini bala pagal vidurki (1) ar mediana (2)? ";
            while (!(cin >> galutinis) || (galutinis != 1 && galutinis != 2)) {
                cout << "Klaida: Prasome ivesti 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            rusiavimasList(studentaiList);
            isvestisList(studentaiList, galutinis);
        }
        else if (pasirinkimas == 2) {
            string failoPavadinimas;
            cout << "Iveskite failo pavadinima: ";
            cin >> failoPavadinimas;
            nuskaitytiIsFailoList(failoPavadinimas, studentaiList, pasirinkimas);

            int galutinis;
            cout << "Ar norite skaiciuoti galutini bala pagal vidurki (1) ar mediana (2)? ";
            while (!(cin >> galutinis) || (galutinis != 1 && galutinis != 2)) {
                cout << "Klaida: Prasome ivesti 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            rusiavimasList(studentaiList);
            isvestisList(studentaiList, galutinis);
        }
        else if (pasirinkimas == 3) {
            int failoPasirinkimas;
            cout << "Ar norite generuoti naujus failus (1) ar naudoti jau sugeneruotus failus (2)? ";
            while (!(cin >> failoPasirinkimas) || (failoPasirinkimas != 1 && failoPasirinkimas != 2)) {
                cout << "Klaida: Prasome ivesti 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            list<int> kiekiai = { 1000, 10000, 100000, 1000000, 10000000 };

            cout << "Ar norite skaiciuoti galutini bala pagal vidurki (1) ar mediana (2)? ";
            while (!(cin >> pasirinkimas) || (pasirinkimas != 1 && pasirinkimas != 2)) {
                cout << "Klaida: Prasome ivesti 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            int rusiuotiPagal;
            cout << "Ar norite rusiuoti studentus pagal varda (1), pavarde (2) ar pazymi (3)? \n";
            while (!(cin >> rusiuotiPagal) || (rusiuotiPagal < 1 || rusiuotiPagal > 3)) {
                cout << "Klaida: Prasome ivesti 1, 2 arba 3: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            for (int kiekis : kiekiai) {
                string failoPavadinimas = "studentai_" + to_string(kiekis) + ".txt";

                if (failoPasirinkimas == 1) {
                    auto start = high_resolution_clock::now();
                    generuotiStudentuDuomenis(failoPavadinimas, kiekis);
                    auto end = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(end - start).count() / 1e6;
                    cout << "Failo generavimas '" << failoPavadinimas << "' uztruko: " << fixed << setprecision(6) << duration << "s\n";
                }
                matuotiVeikimoGreitiList(failoPavadinimas, kiekis, pasirinkimas, rusiuotiPagal);
            }
        }
    }

    return 0;
}
