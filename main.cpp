#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//#define name "CERVEZA BUDWEISER 6 PACK BOTELLA 343ML"

using namespace std;

int main() {
    //int compras = 0;
    int cont = 0;
    string sku, monto, fecha, descuento, estado, wes, nombre, hora;

    struct sPro {
        string vsku = "cod";
        vector<int> vMes = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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
    while (allData.peek() != EOF &&compras<1800000){//EOF==-1
        string records;
        getline(allData, records, '"');
        //cout << "*" << records << "*" <<endl;
        if (records != ";" && records != "\n"){
                if (cont == 0)
                    sku = records;//else if (cont == 1)//nombre = records;
                else if (cont == 2)
                    monto = records;
                else if (cont == 3)
                    descuento = records;
                else if (cont == 4) {
                    stringstream fetcha(records);
                    getline(fetcha, fecha, 'T');
                    fecha = fecha.substr(0, 7);//ano y mes
                    fecha = fecha.substr(5, 7);// mes
                    //getline(fetcha, hora, 'Z');
                } else
                    estado = records;
                //cout << "contador: " << cont << endl;
                cont++;
            }
        if (cont == 6) {//una vez almacena los datos de la operacion
            cont = 0;
            if ((estado == "AUTHORIZED" || estado == "FINALIZED") && sku != "0" && monto != "0" && descuento!="DESCUENTO"){
                //compras++;
                bool encontrado = false;
                int auxstoi = stoi(fecha), valorF = stoi(monto) - stoi(descuento);
/*
                 cout << "\nsku: " << sku << endl;
                 cout << "nombre: " << nombre << endl;
                 cout << "monto: " << monto << endl;
                 cout << "descuento: " << descuento << endl;
                 cout << "fecha: " << fecha << endl;
                 cout << "hora: " << hora << endl;
                cout << "estado: " << estado << endl;
                cout << "Precione enter para continuar ...";
                cin.get();
                */
                for (int i = 0; i < arPro.size() && !encontrado; i++) {//busca si el producto esta en el struct
                    if (arPro[i].vsku == sku) {
                        encontrado = true;
                        if (arPro[i].vMes[auxstoi - 1] == 0) {//comprueba si ya esta registrado el monto
                            arPro[i].vMes[auxstoi - 1] = valorF;
                            //cout << " * sku EXISTE= " << arPro[i].vsku << " * mes = " << auxstoi << " * valor = "<< arPro[i].vMes[auxstoi - 1] << endl;
                        } //else
                        // cout << " * MONTO DEL MES YA REGISTRADO *" << endl;
                    }
                }
                if (!encontrado) {//si el producto no esta lo agrega
                    vector<int> arxu = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                    arxu[auxstoi - 1] = valorF;
                    sPro aux{sku, arxu};
                    arPro.push_back(aux);
                    //cout << " * sku NUEVA = " << arPro[arPro.size() - 1].vsku << " * mes = " << auxstoi << " * valor = "<< arPro[arPro.size() - 1].vMes[stoi(fecha) - 1] << endl;

                }
            }
        }
    }
    allData.close();

/*

    cout << " * Nombre : " << name << endl;
    cout << " * Valor al dia de " << fechaI<< " = $ " << montoI << endl;
    cout << " * Valor al dia de " << fechaF<< " = $ " << montoF << endl;
    cout << " * Inflacion = " << inflacion << " %." << endl;
    cout << " * N de productos " << arPro.size() << endl;
    cout << " * Total de compras de " << name << " = " << comprasProd << endl;
    cout << " * Total de compras = " << compras << endl;
    cout << " * Total de regitros = " << registros << endl;

    double inflacion = ((montoF - montoI) / montoI) * 100;
    cout << " * N de productos " << arPro.size() << endl;
    cout << montoF << " / " << montoI << endl;
    cout << " * Inflacion entre " << fechaI << " y " << fechaF << " es igual a " << inflacion << " %." << endl;

 */

    vector<double> sMes = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < arPro.size(); i++) {
        bool vacio = false;
        for (int j = 0; j < 12 && !vacio; j++) {
            if (!arPro[i].vMes[j]) {
                vacio = true;
            }
        }
        if (vacio == false)
            for (int k = 0; k < 12; k++)
                sMes[k] = sMes[k] + arPro[i].vMes[k];
    }

    for (int i = 0; i < 12; i++) {
        cout << " * Suma total valor del mes de " << i << " = " << sMes[i] << endl;}

    cout << " * Inflacion entre enero y febrero es igual a " << ((sMes[1] - sMes[0]) / sMes[0]) * 100 << " %." << endl;
    cout << " * Inflacion entre febrero y marzo es igual a " << ((sMes[2] - sMes[1]) / sMes[1]) * 100 << " %." << endl;
    cout << " * Inflacion entre marzo y abril es igual a " << ((sMes[3] - sMes[2]) / sMes[2]) * 100 << " %." << endl;
    cout << " * Inflacion entre abril y mayo es igual a " << ((sMes[4] - sMes[3]) / sMes[3]) * 100 << " %." << endl;
    cout << " * Inflacion entre mayo y junio es igual a " << ((sMes[5] - sMes[4]) / sMes[4]) * 100 << " %." << endl;
    cout << " * Inflacion entre junio y julio es igual a " << ((sMes[6] - sMes[5]) / sMes[5]) * 100 << " %." << endl;
    cout << " * Inflacion entre julio y agosto es igual a " << ((sMes[7] - sMes[6]) / sMes[6]) * 100 << " %." << endl;
    cout << " * Inflacion entre agosto y septiembre es igual a " << ((sMes[8] - sMes[7]) / sMes[7]) * 100 << " %."
         << endl;
    cout << " * Inflacion entre septiembre y octubre es igual a " << ((sMes[9] - sMes[8]) / sMes[8]) * 100 << " %."
         << endl;
    cout << " * Inflacion entre octubre y noviembre es igual a " << ((sMes[10] - sMes[9]) / sMes[9]) * 100 << " %."
         << endl;
    cout << " * Inflacion entre noviembre y diciembre es igual a " << ((sMes[11] - sMes[10]) / sMes[10]) * 100 << " %."
         << endl;



    //double inflacion = ((montoF - montoI) / montoI) * 100;
    //cout << " * N de productos " << arPro.size() << endl;
    //cout << montoF << " / " << montoI << endl;
    //cout << " * Inflacion entre " << fechaI << " y " << fechaF << " es igual a " << inflacion << " %." << endl;

    return 0;
}
