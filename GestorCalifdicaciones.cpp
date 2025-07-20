/*
Fecha: 10/07/2025
Autor: [Jorge]
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;

// Estructura para almacenar datos del estudiante
struct Estudiante {
    string id; // 10 dígitos
    string nombreCompleto;
    string provincia;
    string canton;
    string distrito;
    int edad;
    string genero;
};

// Estructura para almacenar las notas de un estudiante en una materia
struct Nota {
    string id; // Relaciona con estudiante
    string materia;
    float proyecto1;
    float proyecto2;
    float ensayo;
    float foro;
    float defensa;
    float promedio;
    string estado;
};

// Funciones de utilidad
bool esNumero(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

string toUpper(const string& str) {
    string res = str;
    transform(res.begin(), res.end(), res.begin(), ::toupper);
    return res;
}

// Validar entrada S/N
bool validarSN(const string& entrada) {
    string e = toUpper(trim(entrada));
    return (e == "S" || e == "N");
}

// Cargar estudiantes desde archivo
void cargarEstudiantes(vector<Estudiante>& estudiantes) {
    estudiantes.clear();
    ifstream archivo("estudiantes.txt");
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        Estudiante est;
        getline(iss, est.id, '|');
        getline(iss, est.nombreCompleto, '|');
        getline(iss, est.provincia, '|');
        getline(iss, est.canton, '|');
        getline(iss, est.distrito, '|');
        string edadStr;
        getline(iss, edadStr, '|');
        est.edad = stoi(edadStr);
        getline(iss, est.genero, '|');
        estudiantes.push_back(est);
    }
    archivo.close();
}

// Guardar estudiantes a archivo
void guardarEstudiantes(const vector<Estudiante>& estudiantes) {
    ofstream archivo("estudiantes.txt");
    for (const auto& est : estudiantes) {
        archivo << est.id << '|'
                << est.nombreCompleto << '|'
                << est.provincia << '|'
                << est.canton << '|'
                << est.distrito << '|'
                << est.edad << '|'
                << est.genero << '\n';
    }
    archivo.close();
}

// Cargar notas desde archivo
void cargarNotas(vector<Nota>& notas) {
    notas.clear();
    ifstream archivo("notas.txt");
    if (!archivo.is_open()) return;
    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        Nota n;
        string temp;
        getline(iss, n.id, '|');
        getline(iss, n.materia, '|');
        getline(iss, temp, '|'); n.proyecto1 = stof(temp);
        getline(iss, temp, '|'); n.proyecto2 = stof(temp);
        getline(iss, temp, '|'); n.ensayo = stof(temp);
        getline(iss, temp, '|'); n.foro = stof(temp);
        getline(iss, temp, '|'); n.defensa = stof(temp);
        getline(iss, temp, '|'); n.promedio = stof(temp);
        getline(iss, n.estado, '|');
        notas.push_back(n);
    }
    archivo.close();
}

// Guardar notas a archivo
void guardarNotas(const vector<Nota>& notas) {
    ofstream archivo("notas.txt");
    for (const auto& n : notas) {
        archivo << n.id << '|'
                << n.materia << '|'
                << fixed << setprecision(2)
                << n.proyecto1 << '|'
                << n.proyecto2 << '|'
                << n.ensayo << '|'
                << n.foro << '|'
                << n.defensa << '|'
                << n.promedio << '|'
                << n.estado << '\n';
    }
    archivo.close();
}

// Buscar estudiante por ID
int buscarEstudiante(const vector<Estudiante>& estudiantes, const string& id) {
    for (size_t i = 0; i < estudiantes.size(); ++i) {
        if (estudiantes[i].id == id) return i;
    }
    return -1;
}

// Buscar notas por ID y materia
int buscarNota(const vector<Nota>& notas, const string& id, const string& materia) {
    for (size_t i = 0; i < notas.size(); ++i) {
        if (notas[i].id == id && toUpper(notas[i].materia) == toUpper(materia)) return i;
    }
    return -1;
}

// Calcular promedio y estado
void calcularPromedioYEstado(Nota& n) {
    n.promedio = n.proyecto1 * 0.01f + n.proyecto2 * 0.02f +
                 n.ensayo * 0.03f + n.foro * 0.01f + n.defensa * 0.03f;
    if (n.promedio >= 70.0f) n.estado = "Aprobó";
    else if (n.promedio >= 50.0f) n.estado = "Reposición";
    else n.estado = "Reprobó";
}

// Función para validar entrada numérica
float leerNota(const string& mensaje) {
    float valor;
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        try {
            if (entrada.empty()) throw runtime_error("Campo vacío.");
            valor = stof(entrada);
            if (valor < 0.0f || valor > 100.0f) throw out_of_range("La nota debe estar entre 0 y 100.");
            break;
        } catch (exception& e) {
            cout << "Entrada inválida: " << e.what() << endl;
        }
    }
    return valor;
}

// Registrar estudiante
void registrarEstudiante(vector<Estudiante>& estudiantes) {
    cout << "\n--- REGISTRO DE ESTUDIANTE ---\n";
    Estudiante est;
    // ID
    while (true) {
        cout << "Ingrese cédula (10 dígitos): ";
        getline(cin, est.id);
        if (est.id.length() != 10 || !esNumero(est.id)) {
            cout << "La cédula debe contener exactamente 10 dígitos numéricos.\n";
            continue;
        }
        if (buscarEstudiante(estudiantes, est.id) != -1) {
            cout << "Ya existe un estudiante con esa cédula.\n";
            continue;
        }
        break;
    }
    // Nombre
    while (true) {
        cout << "Nombre completo (nombre y dos apellidos): ";
        getline(cin, est.nombreCompleto);
        if (trim(est.nombreCompleto).empty()) cout << "No puede dejar este campo vacío.\n";
        else break;
    }
    // Residencia
    while (true) {
        cout << "Provincia: ";
        getline(cin, est.provincia);
        if (trim(est.provincia).empty()) { cout << "No puede dejar este campo vacío.\n"; continue; }
        cout << "Cantón: ";
        getline(cin, est.canton);
        if (trim(est.canton).empty()) { cout << "No puede dejar este campo vacío.\n"; continue; }
        cout << "Distrito: ";
        getline(cin, est.distrito);
        if (trim(est.distrito).empty()) { cout << "No puede dejar este campo vacío.\n"; continue; }
        break;
    }
    // Edad
    while (true) {
        string edadStr;
        cout << "Edad (18-100): ";
        getline(cin, edadStr);
        try {
            if (edadStr.empty()) throw runtime_error("Campo vacío.");
            est.edad = stoi(edadStr);
            if (est.edad < 18 || est.edad > 100) throw out_of_range("Edad fuera de rango.");
            break;
        } catch (exception& e) {
            cout << "Entrada inválida: " << e.what() << endl;
        }
    }
    // Género
    vector<string> generos = {"Femenino", "Masculino", "Otro"};
    while (true) {
        cout << "Seleccione género:\n";
        for (size_t i = 0; i < generos.size(); ++i)
            cout << i+1 << ". " << generos[i] << endl;
        string op;
        getline(cin, op);
        if (op == "1" || op == "2" || op == "3") {
            est.genero = generos[stoi(op)-1];
            break;
        } else {
            cout << "Opción inválida.\n";
        }
    }
    estudiantes.push_back(est);
    guardarEstudiantes(estudiantes);
    cout << "Registro guardado satisfactoriamente.\n";
}

// Ingresar calificaciones
void ingresarCalificaciones(const vector<Estudiante>& estudiantes, vector<Nota>& notas) {
    cout << "\n--- INGRESAR CALIFICACIONES ---\n";
    string id;
    while (true) {
        cout << "Ingrese cédula del estudiante: ";
        getline(cin, id);
        if (id.length() != 10 || !esNumero(id)) {
            cout << "La cédula debe contener exactamente 10 dígitos numéricos.\n";
            continue;
        }
        int idx = buscarEstudiante(estudiantes, id);
        if (idx == -1) {
            cout << "Estudiante no registrado.\n¿Desea ingresar otra identificación? (S/N): ";
            string resp; getline(cin, resp);
            if (toUpper(trim(resp)) == "S") continue;
            else return;
        }
        // Materia
        string materia;
        while (true) {
            cout << "Materia que cursa: ";
            getline(cin, materia);
            if (trim(materia).empty()) cout << "No puede dejar este campo vacío.\n";
            else break;
        }
        if (buscarNota(notas, id, materia) != -1) {
            cout << "Ya existen notas para esta materia y estudiante.\n";
            return;
        }
        Nota n;
        n.id = id;
        n.materia = materia;
        n.proyecto1 = leerNota("Nota Proyecto 1 (0-100): ");
        n.proyecto2 = leerNota("Nota Proyecto 2 (0-100): ");
        n.ensayo    = leerNota("Nota Ensayo (0-100): ");
        n.foro      = leerNota("Nota Foro (0-100): ");
        n.defensa   = leerNota("Nota Defensa (0-100): ");
        calcularPromedioYEstado(n);
        notas.push_back(n);
        guardarNotas(notas);
        cout << "Notas registradas correctamente.\n";
        break;
    }
}

// Modificar datos de estudiante (solo edad y residencia)
void modificarDatosEstudiante(vector<Estudiante>& estudiantes) {
    cout << "\n--- MODIFICAR DATOS DE ESTUDIANTE ---\n";
    string id;
    cout << "Ingrese cédula del estudiante: ";
    getline(cin, id);
    int idx = buscarEstudiante(estudiantes, id);
    if (idx == -1) {
        cout << "Estudiante no registrado.\n";
        return;
    }
    // Edad
    while (true) {
        string edadStr;
        cout << "Nueva edad (18-100): ";
        getline(cin, edadStr);
        try {
            if (edadStr.empty()) throw runtime_error("Campo vacío.");
            int edad = stoi(edadStr);
            if (edad < 18 || edad > 100) throw out_of_range("Edad fuera de rango.");
            estudiantes[idx].edad = edad;
            break;
        } catch (exception& e) {
            cout << "Entrada inválida: " << e.what() << endl;
        }
    }
    // Residencia
    while (true) {
        cout << "Nueva provincia: ";
        getline(cin, estudiantes[idx].provincia);
        if (trim(estudiantes[idx].provincia).empty()) { cout << "No puede dejar este campo vacío.\n"; continue; }
        cout << "Nuevo cantón: ";
        getline(cin, estudiantes[idx].canton);
        if (trim(estudiantes[idx].canton).empty()) { cout << "No puede dejar este campo vacío.\n"; continue; }
        cout << "Nuevo distrito: ";
        getline(cin, estudiantes[idx].distrito);
        if (trim(estudiantes[idx].distrito).empty()) { cout << "No puede dejar este campo vacío.\n"; continue; }
        break;
    }
    guardarEstudiantes(estudiantes);
    cout << "Datos modificados correctamente.\n";
}

// Modificar notas de estudiante
void modificarNotas(vector<Nota>& notas, const vector<Estudiante>& estudiantes) {
    cout << "\n--- MODIFICAR NOTAS DE ESTUDIANTE ---\n";
    string id;
    cout << "Ingrese cédula del estudiante: ";
    getline(cin, id);
    int idxEst = buscarEstudiante(estudiantes, id);
    if (idxEst == -1) {
        cout << "Estudiante no registrado.\n¿Desea buscar otra identificación? (S/N): ";
        string resp; getline(cin, resp);
        if (toUpper(trim(resp)) == "S") modificarNotas(notas, estudiantes);
        return;
    }
    // Mostrar materias registradas
    vector<string> materias;
    for (const auto& n : notas) {
        if (n.id == id) materias.push_back(n.materia);
    }
    if (materias.empty()) {
        cout << "No hay materias registradas para este estudiante.\n";
        return;
    }
    cout << "Materias registradas:\n";
    for (size_t i = 0; i < materias.size(); ++i)
        cout << i+1 << ". " << materias[i] << endl;
    int op = 0;
    while (true) {
        cout << "Seleccione la materia a modificar: ";
        string opStr; getline(cin, opStr);
        try {
            op = stoi(opStr);
            if (op < 1 || op > (int)materias.size()) throw out_of_range("Opción fuera de rango.");
            break;
        } catch (exception& e) {
            cout << "Entrada inválida: " << e.what() << endl;
        }
    }
    int idxNota = buscarNota(notas, id, materias[op-1]);
    if (idxNota == -1) {
        cout << "Error interno: nota no encontrada.\n";
        return;
    }
    // Mostrar notas originales
    Nota& n = notas[idxNota];
    cout << fixed << setprecision(2);
    cout << "Notas actuales:\n";
    cout << "Proyecto 1: " << n.proyecto1 << "\nProyecto 2: " << n.proyecto2
         << "\nEnsayo: " << n.ensayo << "\nForo: " << n.foro << "\nDefensa: " << n.defensa << endl;
    // Ingresar nuevas notas
    n.proyecto1 = leerNota("Nueva nota Proyecto 1 (0-100): ");
    n.proyecto2 = leerNota("Nueva nota Proyecto 2 (0-100): ");
    n.ensayo    = leerNota("Nueva nota Ensayo (0-100): ");
    n.foro      = leerNota("Nueva nota Foro (0-100): ");
    n.defensa   = leerNota("Nueva nota Defensa (0-100): ");
    calcularPromedioYEstado(n);
    guardarNotas(notas);
    cout << "Actualización exitosa.\n";
}

// Eliminar registro de estudiante y sus notas
void eliminarRegistro(vector<Estudiante>& estudiantes, vector<Nota>& notas) {
    cout << "\n--- ELIMINAR REGISTRO DE ESTUDIANTE ---\n";
    while (true) {
        string id;
        cout << "Ingrese cédula del estudiante a eliminar: ";
        getline(cin, id);
        int idx = buscarEstudiante(estudiantes, id);
        if (idx == -1) {
            cout << "Estudiante no encontrado.\n";
        } else {
            cout << "¿Está seguro que desea eliminar el registro? (S/N): ";
            string resp; getline(cin, resp);
            if (toUpper(trim(resp)) == "S") {
                estudiantes.erase(estudiantes.begin() + idx);
                // Eliminar notas relacionadas
                notas.erase(remove_if(notas.begin(), notas.end(),
                    [id](const Nota& n){ return n.id == id; }), notas.end());
                guardarEstudiantes(estudiantes);
                guardarNotas(notas);
                cout << "Registro eliminado correctamente.\n";
            }
        }
        cout << "¿Desea eliminar otro estudiante? (S/N): ";
        string otro; getline(cin, otro);
        if (toUpper(trim(otro)) != "S") break;
    }
}

// Reporte de estudiantes
void reporte(const vector<Estudiante>& estudiantes, const vector<Nota>& notas) {
    cout << "\nREPORTE DE ESTUDIANTES - NOTAS FINALES\n";
    cout << left << setw(12) << "ID"
         << setw(30) << "Nombre"
         << setw(20) << "Materia"
         << setw(10) << "Promedio"
         << setw(12) << "Estado" << endl;
    cout << string(84, '-') << endl;
    for (const auto& n : notas) {
        int idx = buscarEstudiante(estudiantes, n.id);
        string nombre = (idx != -1) ? estudiantes[idx].nombreCompleto : "Desconocido";
        cout << left << setw(12) << n.id
             << setw(30) << nombre
             << setw(20) << n.materia
             << setw(10) << fixed << setprecision(2) << n.promedio
             << setw(12) << n.estado << endl;
    }
}

// Menú principal
void menu() {
    vector<Estudiante> estudiantes;
    vector<Nota> notas;
    cargarEstudiantes(estudiantes);
    cargarNotas(notas);
    string opcion;
    do {
        cout << "\n========= MENÚ PRINCIPAL =========\n";
        cout << "1. Registrar Estudiante\n";
        cout << "2. Ingresar Calificaciones\n";
        cout << "3. Modificar Datos Estudiante\n";
        cout << "4. Modificar Registro de Notas por Estudiante\n";
        cout << "5. Eliminar Registro de Estudiante\n";
        cout << "6. Reporte de Estudiantes, promedios y estado\n";
        cout << "7. Salir del programa\n";
        cout << "Seleccione una opción: ";
        getline(cin, opcion);
        if (opcion == "1") {
            registrarEstudiante(estudiantes);
        } else if (opcion == "2") {
            ingresarCalificaciones(estudiantes, notas);
        } else if (opcion == "3") {
            modificarDatosEstudiante(estudiantes);
        } else if (opcion == "4") {
            modificarNotas(notas, estudiantes);
        } else if (opcion == "5") {
            eliminarRegistro(estudiantes, notas);
        } else if (opcion == "6") {
            reporte(estudiantes, notas);
        } else if (opcion == "7") {
            string salir;
            cout << "¿Está seguro que desea salir? (S/N): ";
            getline(cin, salir);
            if (toUpper(trim(salir)) == "S") break;
        } else {
            cout << "Opción inválida, vuelva a intentarlo.\n";
        }
        string volver;
        do {
            cout << "¿Desea volver al menú principal? (S/N): ";
            getline(cin, volver);
            if (!validarSN(volver)) cout << "Opción inválida.\n";
        } while (!validarSN(volver) || toUpper(trim(volver)) != "S");
    } while (true);
}

int main() {
    cout << "Fecha: 10/07/2025\n";
    cout << "Autor: [Jorge Chaves]\n";
    cout << "Sistema de gestión de calificaciones estudiantiles.\n";
    cout << "Funcionamiento bajo Requisitos proporcionados por la asignatura.\n";
    menu();
    cout << "Programa finalizado.\n";
    return 0;
}
