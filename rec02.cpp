// Zoe Dauphinee, recitation 2

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


struct MolecularFormula {
    vector<string> names;
    int num_carbons;
    int num_hydrogens;
};


void open_file(ifstream& file);

void fill_vector(vector<MolecularFormula>& formulas, ifstream& file);

void print_vector(const vector<MolecularFormula>& formulas);

void sort_vector(vector<MolecularFormula>& formulas);

void insert_info(vector<MolecularFormula>& formulas, const string& name, int carbons, int hydrogens);

size_t find_formula(const vector<MolecularFormula>& formulas, int carbons, int hydrogens);

void print_formula(const MolecularFormula& formula);


int main() {
    ifstream hydrocarb_file;
    vector<MolecularFormula> formulas;

    open_file(hydrocarb_file);
    fill_vector(formulas, hydrocarb_file);
    cout << "Unsorted:\n";
    print_vector(formulas);
    cout << "\nSorted:\n";
    sort_vector(formulas);
    print_vector(formulas);

    hydrocarb_file.close();
}


void open_file(ifstream& hydrocarb_file) {
    string file_name;
    do { 
        cout << "enter a file name: ";
        cin >> file_name;
        hydrocarb_file.open(file_name);
    }
    while (!hydrocarb_file);
}

void fill_vector(vector<MolecularFormula>& formulas, ifstream& hydrocarb_file) {
    string name;
    char carbon;
    int num_carbons;
    char hydrogen;
    int num_hydrogens;
    while (hydrocarb_file >> name >> carbon >> num_carbons >> hydrogen >> num_hydrogens) {
        insert_info(formulas, name, num_carbons, num_hydrogens);
    }
}

void print_vector(const vector<MolecularFormula>& formulas) {
    for (size_t index = 0; index < formulas.size(); ++index) {
        print_formula(formulas[index]);
    }
}

void sort_vector(vector<MolecularFormula>& formulas) {
    for (size_t index = 0; index < formulas.size(); ++index) {
        bool done = true;
        for (size_t index2 = 0; index2 < (formulas.size() - index - 1); ++index2) {
            if (formulas[index2].num_carbons >= formulas[index2 + 1].num_carbons) {
                swap(formulas[index2], formulas[index2 + 1]);
                if (formulas[index2].num_hydrogens > formulas[index2 + 1].num_hydrogens) {
                    swap(formulas[index2], formulas[index2 + 1]);
                }
                done = false;
            }
        }
    }
}

void insert_info(vector<MolecularFormula>& formulas, const string& name, int carbons, int hydrogens) {
    size_t index = find_formula(formulas, carbons, hydrogens);
    if (index == formulas.size()) {
        MolecularFormula formula;
        formula.names.push_back(name);
        formula.num_carbons = carbons;
        formula.num_hydrogens = hydrogens;
        formulas.push_back(formula);
    }
    else {
        formulas[index].names.push_back(name);
    }
}

size_t find_formula(const vector<MolecularFormula>& formulas, int carbons, int hydrogens) {
    for (size_t index = 0; index < formulas.size(); ++index) {
        if (formulas[index].num_carbons == carbons && formulas[index].num_hydrogens == hydrogens) {
            return index;
        }
    }
    return formulas.size();
}

void print_formula(const MolecularFormula& formula) {
    cout << "C" << formula.num_carbons << "H" << formula.num_hydrogens << " ";
    for (size_t index = 0; index < formula.names.size(); ++index) {
        cout << formula.names[index] << " ";
    }
    cout << endl;
}