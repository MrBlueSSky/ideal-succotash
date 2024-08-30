#include <iostream>
#include <string>
using namespace std;

struct NodoVentas {
    int ventas;
    NodoVentas* siguiente;

    // Constructor
    NodoVentas(int v) : ventas(v), siguiente(nullptr) {}
};

struct NodoVendedor {
    NodoVendedor* siguiente;
    string nombreEmpleado;
    int sumatoriaVendedor;
    NodoVentas* ventas;

    // Constructor
    NodoVendedor(string nombre)
        : siguiente(nullptr), nombreEmpleado(nombre), sumatoriaVendedor(0), ventas(nullptr) {}
};

struct NodoPiso {
    NodoPiso* siguiente;
    NodoPiso* anterior;
    int sumatoria;
    string nombrePiso;
    NodoVendedor* vendedor;

    // Constructor
    NodoPiso(string nombre)
        : siguiente(nullptr), anterior(nullptr), sumatoria(0), nombrePiso(nombre), vendedor(nullptr) {}
};

// Insertar NodoPiso ordenado por nombrePiso
void insertarPiso(NodoPiso*& cabeza, NodoPiso* nuevo) {
    if (cabeza == nullptr || cabeza->nombrePiso > nuevo->nombrePiso) {
        nuevo->siguiente = cabeza;
        if (cabeza != nullptr) {
            cabeza->anterior = nuevo;
        }
        cabeza = nuevo;
    }
    else {
        NodoPiso* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->nombrePiso < nuevo->nombrePiso) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        if (actual->siguiente != nullptr) {
            actual->siguiente->anterior = nuevo;
        }
        actual->siguiente = nuevo;
        nuevo->anterior = actual;
    }
}

// Insertar NodoVendedor ordenado por nombreEmpleado
void insertarVendedor(NodoVendedor*& cabeza, NodoVendedor* nuevo) {
    if (cabeza == nullptr || cabeza->nombreEmpleado > nuevo->nombreEmpleado) {
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }
    else {
        NodoVendedor* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->nombreEmpleado < nuevo->nombreEmpleado) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

// Insertar NodoVentas ordenado de forma descendente por ventas
void insertarVenta(NodoVentas*& cabeza, NodoVentas* nuevo) {
    if (cabeza == nullptr || cabeza->ventas < nuevo->ventas) {
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }
    else {
        NodoVentas* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->ventas > nuevo->ventas) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

// Mostrar datos de ventas
void mostrarVentas(NodoVentas* cabeza) {
    NodoVentas* actual = cabeza;
    while (actual != nullptr) {
        cout << "    Venta: " << actual->ventas << endl;
        actual = actual->siguiente;
    }
}

// Mostrar datos de vendedores
void mostrarVendedores(NodoVendedor* cabeza) {
    NodoVendedor* actual = cabeza;
    while (actual != nullptr) {
        cout << "  Vendedor: " << actual->nombreEmpleado
            << " | Sumatoria Vendedor: " << actual->sumatoriaVendedor << endl;
        mostrarVentas(actual->ventas);
        actual = actual->siguiente;
    }
}

// Mostrar datos de pisos
void mostrarPisos(NodoPiso* cabeza) {
    NodoPiso* actual = cabeza;
    while (actual != nullptr) {
        cout << "Piso: " << actual->nombrePiso
            << " | Sumatoria Piso: " << actual->sumatoria << endl;
        mostrarVendedores(actual->vendedor);
        actual = actual->siguiente;
    }
}

// Mostrar datos de un piso específico
void mostrarDatosPiso(NodoPiso* cabeza, const string& nombrePiso) {
    NodoPiso* actual = cabeza;
    while (actual != nullptr) {
        if (actual->nombrePiso == nombrePiso) {
            cout << "Piso: " << actual->nombrePiso
                << " | Sumatoria Piso: " << actual->sumatoria << endl;
            mostrarVendedores(actual->vendedor);
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Piso no encontrado." << endl;
}

// Verificar sumatorias
void verificarSumatorias(NodoPiso* cabezaPiso) {
    NodoPiso* actualPiso = cabezaPiso;

    while (actualPiso != nullptr) {
        int sumatoriaPiso = 0;
        NodoVendedor* actualVendedor = actualPiso->vendedor;

        while (actualVendedor != nullptr) {
            int sumatoriaVentas = 0;
            NodoVentas* actualVenta = actualVendedor->ventas;

            while (actualVenta != nullptr) {
                sumatoriaVentas += actualVenta->ventas;
                actualVenta = actualVenta->siguiente;
            }

            if (sumatoriaVentas != actualVendedor->sumatoriaVendedor) {
                cout << "Error en la sumatoria del vendedor " << actualVendedor->nombreEmpleado
                    << " en el piso " << actualPiso->nombrePiso
                    << ". Sumatoria esperada: " << sumatoriaVentas
                    << ", sumatoria registrada: " << actualVendedor->sumatoriaVendedor << endl;
            }

            sumatoriaPiso += sumatoriaVentas;
            actualVendedor = actualVendedor->siguiente;
        }

        if (sumatoriaPiso != actualPiso->sumatoria) {
            cout << "Error en la sumatoria del piso " << actualPiso->nombrePiso
                << ". Sumatoria esperada: " << sumatoriaPiso
                << ", sumatoria registrada: " << actualPiso->sumatoria << endl;
        }

        actualPiso = actualPiso->siguiente;
    }
}

// Menú principal
void menu(NodoPiso*& cabezaPiso) {
    int opcion;

    do {
        cout << "==== Menú Principal ====" << endl;
        cout << "1. Consultar todos los datos" << endl;
        cout << "2. Consultar datos de un piso específico" << endl;
        cout << "3. Agregar un nuevo piso" << endl;
        cout << "4. Agregar un nuevo vendedor a un piso existente" << endl;
        cout << "5. Agregar una nueva venta a un vendedor existente" << endl;
        cout << "6. Verificar sumatorias" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            system("cls");
            mostrarPisos(cabezaPiso);
            break;
        case 2: {
            system("cls");
            string nombrePiso;
            cout << "Ingrese el nombre del piso a consultar: ";
            cin.ignore();
            getline(cin, nombrePiso);
            mostrarDatosPiso(cabezaPiso, nombrePiso);
            break;
        }
        case 3: {
            system("cls");
            string nombrePiso;
            cout << "Ingrese el nombre del nuevo piso: ";
            cin.ignore();
            getline(cin, nombrePiso);
            NodoPiso* nuevoPiso = new NodoPiso(nombrePiso);
            insertarPiso(cabezaPiso, nuevoPiso);
            break;
        }
        case 4: {
            system("cls");
            string nombrePiso, nombreVendedor;
            cout << "Ingrese el nombre del piso: ";
            cin.ignore();
            getline(cin, nombrePiso);
            NodoPiso* actualPiso = cabezaPiso;
            while (actualPiso != nullptr && actualPiso->nombrePiso != nombrePiso) {
                actualPiso = actualPiso->siguiente;
            }
            if (actualPiso == nullptr) {
                cout << "Piso no encontrado." << endl;
            }
            else {
                cout << "Ingrese el nombre del nuevo vendedor: ";
                getline(cin, nombreVendedor);
                NodoVendedor* nuevoVendedor = new NodoVendedor(nombreVendedor);
                insertarVendedor(actualPiso->vendedor, nuevoVendedor);
            }
            break;
        }
        case 5: {
            system("cls");
            string nombrePiso, nombreVendedor;
            int cantidadVentas;
            cout << "Ingrese el nombre del piso: ";
            cin.ignore();
            getline(cin, nombrePiso);
            NodoPiso* actualPiso = cabezaPiso;
            while (actualPiso != nullptr && actualPiso->nombrePiso != nombrePiso) {
                actualPiso = actualPiso->siguiente;
            }
            if (actualPiso == nullptr) {
                cout << "Piso no encontrado." << endl;
            }
            else {
                cout << "Ingrese el nombre del vendedor: ";
                getline(cin, nombreVendedor);
                NodoVendedor* actualVendedor = actualPiso->vendedor;
                while (actualVendedor != nullptr && actualVendedor->nombreEmpleado != nombreVendedor) {
                    actualVendedor = actualVendedor->siguiente;
                }
                if (actualVendedor == nullptr) {
                    cout << "Vendedor no encontrado." << endl;
                }
                else {
                    cout << "Ingrese la cantidad de ventas: ";
                    cin >> cantidadVentas;
                    NodoVentas* nuevaVenta = new NodoVentas(cantidadVentas);
                    insertarVenta(actualVendedor->ventas, nuevaVenta);
                    actualVendedor->sumatoriaVendedor += cantidadVentas;
                    actualPiso->sumatoria += cantidadVentas;
                }
            }
            break;
        }
        case 6:
            system("cls");
            verificarSumatorias(cabezaPiso);
            break;
        case 7:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }
    } while (opcion != 7);
}

int main() {
    NodoPiso* cabezaPiso = nullptr;
    // Crear algunos pisos
    NodoPiso* piso1 = new NodoPiso("Piso 1");
    NodoPiso* piso2 = new NodoPiso("Piso 2");
    NodoPiso* piso3 = new NodoPiso("Piso 3");

    // Insertar los pisos en la lista
    insertarPiso(cabezaPiso, piso1);
    insertarPiso(cabezaPiso, piso2);
    insertarPiso(cabezaPiso, piso3);

    // Crear algunos vendedores y asociarlos a los pisos
    NodoVendedor* vendedor1 = new NodoVendedor("Ana");
    NodoVendedor* vendedor2 = new NodoVendedor("Carlos");
    NodoVendedor* vendedor3 = new NodoVendedor("Beatriz");

    insertarVendedor(piso1->vendedor, vendedor1);
    insertarVendedor(piso1->vendedor, vendedor2);
    insertarVendedor(piso2->vendedor, vendedor3);

    // Crear algunas ventas y asociarlas a los vendedores
    NodoVentas* venta1 = new NodoVentas(100);
    NodoVentas* venta2 = new NodoVentas(200);
    NodoVentas* venta3 = new NodoVentas(150);

    insertarVenta(vendedor1->ventas, venta1);
    insertarVenta(vendedor1->ventas, venta2);
    vendedor1->sumatoriaVendedor += 300;  // Sumatoria de las ventas del vendedor1
    piso1->sumatoria += 300;  // Actualizar sumatoria del piso1

    insertarVenta(vendedor2->ventas, venta3);
    vendedor2->sumatoriaVendedor += 150;  // Sumatoria de las ventas del vendedor2
    piso1->sumatoria += 150;  // Actualizar sumatoria del piso1
    menu(cabezaPiso);

    return 0;
}
