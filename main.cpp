#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#define name "CERVEZA BUDWEISER 6 PACK BOTELLA 343ML"
using namespace std;

int main() {
    int compras = 0, cont = 0, registros = 0, montoI = 0, montoF = 0, comprasProd = 0;
    string sku, nombre, monto, descuento, fecha, hora, estado, wes, fechaF, fechaI;

    struct sPro{
        string vSKU="nada";
        vector<int> vMes={0,0,0,0,0,0,0,0,0,0,0,0};
    };
    vector<sPro> arPro;

    string dbSuper = "supermercado.csv";
    ifstream allData;
    allData.open(dbSuper);
    if (allData.fail()) {
        cout << "Error al abrir el archivo: " << dbSuper << endl;
        return 0;
    }
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
                    fecha = fecha.substr(0, 7);//ano y mes
                    fecha = fecha.substr(5, 7);// mes
                    getline(fetcha, hora, 'Z');
                } else
                    estado = records;
                //cout << "contador: "<< cont << endl;
                cont++;
            }

        if (cont == 6) {//una vez almacena los datos de la operacion
            cont = 0;
            registros++;
            if (estado == "AUTHORIZED" || estado == "FINALIZED") {
                int ind=0;
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

                for(int i=0; i<arPro.size();i++){
                    if(arPro[i].vSKU==sku){
                        arPro[i].vMes[stoi(fecha)]= stoi(monto);
                        ind=1;
                    }
                }
                if(ind==0){
                    vector<int> arxu={0,0,0,0,0,0,0,0,0,0,0,0};
                    arxu[stoi(fecha)]=stoi(monto);
                    sPro aux{sku,arxu};
                    arPro.push_back(aux);
                    //cout << " * skuss = " <<sku << endl;
                }

                /*
                if (nombre == name) {
                    comprasProd++;
                    if (montoI == 0) {
                        montoI = stoi(monto);
                        fechaI = fecha;
                    } else {
                        montoF = stoi(monto);
                        fechaF = fecha;
                    }
                } */
                cout << " * largo = " << arPro.size()<< endl;
                cout << " * compras = " <<compras << endl;
            }
        }
    }

    float inflacion = (((float) montoF - (float) montoI) / (float) montoI) * 100;

    allData.close();
    /*
    cout << " * Nombre : " << name << endl;
    cout << " * Valor al dia de " << stoi(fechaI) << " = $ " << montoI << endl;
    cout << " * Valor al dia de " << stoi(fechaF) << " = $ " << montoF << endl;
    cout << " * Inflacion = " << inflacion << " %." << endl;
    cout << " * Total de compras de " << name << " = " << comprasProd << endl;
    cout << " * Total de compras = " << compras << endl;
    cout << " * Total de regitros = " << registros << endl;
 */
    cout << " * largo = " << arPro.size()<< endl;

    for(int i=0; i<arPro.size();i++){
            cout << " * Marca = " << arPro[i].vSKU << endl;
    }

    return 1;
}