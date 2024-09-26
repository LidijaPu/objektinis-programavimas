#include "stud.h"


double galutinisVidurkis(const vector<int>& namu_darbai, int egzaminas) {
    if (namu_darbai.empty()) return 0.0;
    double sum = accumulate(namu_darbai.begin(), namu_darbai.end(), 0);
    double vidurkis = sum / namu_darbai.size();
    return 0.4 * vidurkis + 0.6 * egzaminas;
}

double galutineMediana(vector<int> namu_darbai, int egzaminas) {
    if (namu_darbai.empty()) return 0.0;
    sort(namu_darbai.begin(), namu_darbai.end());
    double mediana;
    int dydis = namu_darbai.size();

    if (dydis % 2 == 0) {
        mediana = (namu_darbai[dydis / 2 - 1] + namu_darbai[dydis / 2]) / 2.0;
    }
    else {
        mediana = namu_darbai[dydis / 2];
    }

    return 0.4 * mediana + 0.6 * egzaminas;
}

void generuotiAtsitiktiniusRezultatus(Studentas& s) {
    int namuDarbaiCount = rand() % 10 + 1;
    cout << "Sugeneruoti " << namuDarbaiCount << " nam darbu balai: \n";
    for (int i = 0; i < namuDarbaiCount; i++) {
        int balas = rand() % 10 + 1;
        s.namu_darbai.push_back(balas);
        cout << balas << " ";
    }
    cout << endl;

    s.egzaminas = rand() % 10 + 1;
    cout << "Sugeneruotas egzamino ivertinimas: " << s.egzaminas << endl;
}

void nuskaitytiIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai) {
    ifstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo!");
    }

    string eilute;
    getline(failas, eilute);  

    string vardas, pavarde;
    while (failas >> vardas >> pavarde) {
        Studentas s;
        s.vardas = vardas;
        s.pavarde = pavarde;

        int balas;
        vector<int> namuDarbai;

        
        while (failas >> balas) {
            if (balas == -1) { 
                break;
            }
            namuDarbai.push_back(balas);
        }

        if (!namuDarbai.empty()) {
            s.egzaminas = namuDarbai.back();  
            namuDarbai.pop_back();  
        }
        else {
            throw runtime_error("Klaida faile: nerasta namu darbu arba egzamino balo.");
        }

        s.namu_darbai = namuDarbai;
        studentai.push_back(s);

        
        failas.clear();
    }

    failas.close();
}


bool palyginimas(const Studentas& a, const Studentas& b) {
    if (a.pavarde == b.pavarde) {
        return a.vardas < b.vardas;
    }
    return a.pavarde < b.pavarde;
}

void rusiavimas(vector<Studentas>& studentai) {
    sort(studentai.begin(), studentai.end(), palyginimas);
}
