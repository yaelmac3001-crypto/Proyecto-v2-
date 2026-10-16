// proyectoV2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <string>
using namespace std;

struct Alumno { string nombre; string matricula; float calif[3]; int grupo; };
struct Maestro { string nombre; string materia; };
struct Grupo { string nombre; string carrera; };

const int MAX = 100;  

float pedir(const char* msg, float a, float b) {
    float x;
    while (cout << msg, !(cin >> x) || x < a || x > b) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  Valor invalido (" << a << " a " << b << ")\n";
    }
    cin.ignore(1000, '\n'); 
    return x;
}


string texto(const char* msg) {
    string s;
    do { cout << msg; getline(cin, s); } while (s.empty());
    return s;
}

int main() {
    Alumno  al[MAX];  int nA = 0;
    Grupo   gr[MAX];  int nG = 0;
    Maestro ma[MAX];  int nM = 0;
    int op;

    cout.setf(ios::fixed);
    cout.precision(2);

    do {
        cout << "\n1. Capturar alumnos\n2. Capturar grupos y carreras\n"
            "3. Capturar maestros\n4. Reportes\n5. Salir\n";
        op = (int)pedir("Opcion: ", 1, 5);

        if (op == 1) {
            if (nG == 0) { cout << "Primero captura grupos (opcion 2)\n"; continue; }
            int n = (int)pedir("Cuantos alumnos? ", 1, MAX - nA);
            for (int i = 0; i < n; i++, nA++) {
                cout << "\nAlumno " << nA + 1 << "\n";
                al[nA].nombre = texto("  Nombre: ");
                al[nA].matricula = texto("  Matricula: ");
                for (int j = 0; j < 3; j++) {
                    cout << "  Calificacion " << j + 1 << " (0-100)";
                    al[nA].calif[j] = pedir(": ", 0, 100);
                }
                for (int g = 0; g < nG; g++) cout << "  " << g + 1 << ". " << gr[g].nombre << "\n";
                al[nA].grupo = (int)pedir("  Grupo: ", 1, nG) - 1;
            }
        }
        else if (op == 2) {
            int n = (int)pedir("Cuantos grupos? ", 1, MAX - nG);
            for (int i = 0; i < n; i++, nG++) {
                cout << "\nGrupo " << nG + 1 << "\n";
                gr[nG].nombre = texto("  Nombre del grupo: ");
                gr[nG].carrera = texto("  Carrera: ");
            }
        }
        else if (op == 3) {
            int n = (int)pedir("Cuantos maestros? ", 1, MAX - nM);
            for (int i = 0; i < n; i++, nM++) {
                cout << "\nMaestro " << nM + 1 << "\n";
                ma[nM].nombre = texto("  Nombre: ");
                ma[nM].materia = texto("  Materia: ");
            }
        }
        else if (op == 4) {
            if (nA == 0) { cout << "No hay alumnos\n"; continue; }

            int mejor[MAX], cuenta[MAX];
            float prom[MAX];                      
            for (int g = 0; g < nG; g++) { mejor[g] = -1; cuenta[g] = 0; prom[g] = -1; }

            cout << "\n-- Promedio por alumno --\n";
            for (int i = 0; i < nA; i++) {       
                float p = (al[i].calif[0] + al[i].calif[1] + al[i].calif[2]) / 3;
                int g = al[i].grupo;
                cout << al[i].matricula << " " << al[i].nombre << ": " << p << "\n";
                cuenta[g]++;
                if (p > prom[g]) { prom[g] = p; mejor[g] = i; }
            }

            cout << "\n-- Mejor promedio por grupo --\n";
            for (int g = 0; g < nG; g++) {
                cout << gr[g].nombre << ": ";
                if (mejor[g] < 0) cout << "sin alumnos\n";
                else cout << al[mejor[g]].nombre << " (" << prom[g] << ")\n";
            }

            cout << "\n-- Alumnos por carrera --\n";
            for (int g = 0; g < nG; g++) {
                bool vista = false;
                int total = 0;
                for (int j = 0; j < nG; j++)
                    if (gr[j].carrera == gr[g].carrera) {
                        if (j < g) vista = true;
                        total += cuenta[j];
                    }
                if (!vista) cout << gr[g].carrera << ": " << total << "\n";
            }

            if (nM > 0) {
                cout << "\n-- Maestros --\n";
                for (int i = 0; i < nM; i++) cout << ma[i].nombre << " - " << ma[i].materia << "\n";
            }
        }
    } while (op != 5);

    return 0;
}



// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
