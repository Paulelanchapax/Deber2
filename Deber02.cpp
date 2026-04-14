#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <sstream>
#include <limits>

using namespace std;

bool codigoValido(const string& cod) {
    if (cod.size() != 3) return false;
    for (char c : cod) {
        if (!isalpha(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

string formatearMonto(double valor) {
    ostringstream oss;
    oss << fixed << setprecision(2) << (valor < 0 ? -valor : valor);
    string s = oss.str();                
    
    
	size_t p = s.find('.');
    
	string ent = s.substr(0, p);
    
	string dec = s.substr(p);            
	
    for (int i = static_cast<int>(ent.size()) - 3; i > 0; i -= 3) {
        ent.insert(i, ",");
    }
    if (valor < 0) ent = "-" + ent;
    return ent + dec;
}

double leerDoublePositivo(const string& prompt, const string& errorMsg) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x && x > 0) return x;

        cout << errorMsg << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    char continuar;

    do {
        string base, cotizada;
        double tasa, montoBase, montoConvertido;
        string timestamp;

        
        do {
            cout << "Ingrese divisa base (3 letras): ";
            cin >> base;
            if (!codigoValido(base)) cout << "Error: debe tener 3 letras y solo letras (ej: USD).\n";
        } while (!codigoValido(base));

        // Divisa cotizada
        do {
            cout << "Ingrese divisa cotizada (3 letras): ";
            cin >> cotizada;
            if (!codigoValido(cotizada)) cout << "Error: debe tener 3 letras y solo letras (ej: EUR).\n";
        } while (!codigoValido(cotizada));

        cout << "Par seleccionado: " << base << "/" << cotizada << "\n";

        
        tasa = leerDoublePositivo("Ingrese tasa de cambio (> 0): ",
                                  "Error: la tasa debe ser un numero mayor que 0.");
        montoBase = leerDoublePositivo("Ingrese monto base (> 0): ",
                                       "Error: el monto debe ser un numero mayor que 0.");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ingrese timestamp del snapshot: ";
        getline(cin, timestamp);

        
        montoConvertido = montoBase * tasa;

        
        cout << "\n====================================\n";
        cout << "        MARKET SNAPSHOT - QuantaFX\n";
        cout << "====================================\n";
        cout << "Par de divisas : " << base << "/" << cotizada << "\n";
        cout << "Timestamp     : " << timestamp << "\n";

        cout << fixed << setprecision(5);
        cout << "Tasa          : 1 " << base << " = " << tasa << " " << cotizada << "\n";

        cout << "Monto base    : " << base << " " << formatearMonto(montoBase) << "\n";
        cout << "Monto final   : " << cotizada << " " << formatearMonto(montoConvertido) << "\n";
        cout << "====================================\n";

        cout << "¿Desea realizar otra conversion? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    return 0;
}