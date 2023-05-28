#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define name "CERVEZA BUDWEISER 6 PACK BOTELLA 343ML"
using namespace std;

int main() {
    string dbSuper = "supermercado.csv";
    ifstream allData;
    allData.open(dbSuper);
    if (allData.fail()) {
        cout << "Error al abrir el archivo: " << dbSuper << endl;
        return 0;
    }

    int compras = 0, cont = 0, registros = 0, montoI = 0, montoF = 0, comprasProd=0;
    string sku, nombre, monto, descuento, fecha, hora, estado, wes, fechaF, fechaI;
    string nomInf = name;

    getline(allData, wes, '"');

    while (allData.peek() != -1) {//EOF==-1
        string records;
        getline(allData, records, '"');
        //cout << "*" << records << "*" <<endl;

        if (records != ";" && records != "\n")//omite los saltos de linea y ;
            if (records != "SKU" && records != "NOMBRE" && records != "MONTO" && records != "DESCUENTO" &&
                records != "FECHA" && records != "ESTADO") {//omite la primera linea
                if (cont == 0)
                    sku = records;
                else if (cont == 1)
                    nombre = records;
                else if (cont == 2)
                    monto = records;
                else if (cont == 3)
                    descuento = records;
                else if (cont == 4) {
                    stringstream fetcha(records);
                    getline(fetcha, fecha, 'T');
                    getline(fetcha, hora, 'Z');
                } else
                    estado = records;
                //cout << "contador: "<< cont << endl;
                cont++;
            }

        if (cont == 6) {//una vez almacena los datos de la operacion
            cont = 0;
            registros++;
            if (estado == " AUTHORIZED" || estado == "FINALIZED") {
                compras++;
                /*
                 cout << "\nsku: " << sku << endl;
                 cout << "nombre: " << nombre << endl;
                 cout << "monto: " << monto << endl;
                 cout << "descuento: " << descuento << endl;
                 cout << "fecha: " << fecha << endl;
                 cout << "hora: " << hora << endl;
                 cout << "estado: " << estado << endl;
                 cout << " * Total de compras= " << compras << endl;

                 std::cout << "Precione enter para continuar ...";
                 std::cin.get();

                 */
                if (nombre == nomInf) {
                    comprasProd++;
                    if (montoI == 0) {
                        montoI = stoi(monto);
                        fechaI = fecha;
                    }
                    else {
                        montoF = stoi(monto);
                        fechaF = fecha;
                    }
                }
            }
        }
    }

    float inflacion = (((float) montoF - (float) montoI) / (float) montoI) * 100;

    allData.close();
    cout << " * Nombre : " << nomInf << endl;
    cout << " * Valor al dia de "<<fechaI<<" = $ "<< montoI << endl;
    cout << " * Valor al dia de "<<fechaF<<" = $ "<< montoF << endl;
    cout << " * Inflacion = " << inflacion << " %." << endl;
    cout << " * Total de compras de "<< nomInf<<" = "<< comprasProd << endl;
    cout << " * Total de compras = " << compras << endl;
    cout << " * Total de regitros = " << registros << endl;
    return 1;
}