#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#define fMES  "03"//inflacion al ultimo dia del mes
#define name "CERVEZA BUDWEISER 6 PACK BOTELLA 343ML"

using namespace std;


int main(int argc, char *argv[]) {

    /*
    if(argv[1]!= NULL)//Comprueba si se ingreso el polinomio
        cout  << endl<< "Inflacion al mes de : " << argv[1] << endl << endl;
    else{
        cout  << endl<< "Parametro ingresado no valido, intente nuevamente."<< endl << endl;
        return 0;
    } */
    double montoI = 0, montoF = 0;
    int compras = 0, cont = 0, fechaF=stoi(fMES), fechaI = 0;
    //int registros = 0,comprasProd = 0,
    string sku, monto, fecha = "0",  estado, wes;
    //string nombre,descuento,hora;
    struct sPro {
        string vsku = "nada";
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
    while (allData.peek() != EOF) {//EOF==-1, no tocar while
        string records;
        getline(allData, records, '"');
        //cout << "*" << records << "*" <<endl;

        if (records != ";" && records != "\n")//omite los saltos de linea y ;
            if (records != "SKU" && records != "NOMBRE" && records != "MONTO" && records != "DESCUENTO" &&
                records != "FECHA" && records != "ESTADO") {//omite la primera linea
                if (cont == 0)
                    sku = records;
                    //else if (cont == 1)
                    //nombre = records;
                else if (cont == 2)
                    monto = records;
                    //else if (cont == 3)
                    //descuento = records;
                else if (cont == 4) {
                    stringstream fetcha(records);
                    getline(fetcha, fecha, 'T');
                    fecha = fecha.substr(0, 7);//ano y mes
                    fecha = fecha.substr(5, 7);// mes
                   // getline(fetcha, hora, 'Z');
                } else
                    estado = records;
                //cout << "contador: "<< cont << endl;
                cont++;
            }

        if (cont == 6) {//una vez almacena los datos de la operacion
            cont = 0;
            //registros++;
            if ( stoi(fMES) < stoi(fecha))
                allData.close();
            else if (fecha == "01" || stoi(fecha) == stoi(fMES)) {
                if (estado == "AUTHORIZED" || estado == "FINALIZED") {
                    int ind = 0, auxstoi=stoi(fecha);
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
                     cout << "Precione enter para continuar ...";
                     cin.get();
                      */

                    for (int i = 0; i < arPro.size(); i++) {//busca si el producto esta en el struct
                        if (arPro[i].vsku == sku) {
                            if (!arPro[i].vMes[auxstoi - 1] && arPro[i].vMes[0] &&  1!= auxstoi){
                                arPro[i].vMes[auxstoi - 1] = stoi(monto);
                                //cout << " * sku EXISTE= " << arPro[i].vsku << " * mes = " << stoi(fecha)<< " * valor = " << arPro[i].vMes[stoi(fecha) - 1] << endl;
                                if (arPro[i].vMes[0] && arPro[i].vMes[auxstoi- 1] ) {
                                    //cout << " * SKU = " << arPro[i].vsku << " * Valor enero = "<< arPro[i].vMes[0] << " * valor X = " << arPro[i].vMes[stoi(fMES)- 1] << endl;
                                    montoI += double(arPro[i].vMes[0]);
                                    montoF += double(arPro[i].vMes[auxstoi-1]);
                                }
                            } else
                                //cout << " * MONTO DEL MES YA REGISTRADO *" << endl;
                            ind = 1;
                            i = arPro.size();
                        }
                    }

                    if (!ind && auxstoi == 1) {//si el producto no esta lo agrega
                        vector <int> arxu = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                        arxu[auxstoi - 1] = stoi(monto);
                        sPro aux{sku, arxu};
                        arPro.push_back(aux);
                        /*
                        cout << " * sku NUEVA = " << arPro[i].vsku << " * mes = "<< stoi(fecha) << " * valor = " << arPro[arPro.size() - 1].vMes[stoi(fecha) - 1] << endl;

                        cout << "Precione enter para continuar ...";
                        cin.get();
                        cout << endl;

                         */
                    } /*
 *
                    if (nombre == name) {
                        comprasProd++;
                        if (montoI == 0) {
                            montoI = stoi(monto);
                            int aux = stoi(fecha);
                            fechaI = aux - 1;
                        } else {
                            montoF = (stoi(monto));
                            int aux = stoi(fecha);
                            fechaF = aux - 1;
                        }
                    }*/

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
 */



/*
    for (int i = 0; i < arPro.size(); i++) {
        cout << " * Marca = " << arPro[i].vsku;
        for (int j = 0; j < 12; j++) {
            cout << " * montos = " << arPro[i].vMes[j];
        }
        cout << endl;
        cout << "Precione enter para continuar ...";
        cin.get();


    }

    for (int i = 0; i < arPro.size(); i++) {
        if (arPro[i].vMes[0] && arPro[i].vMes[stoi(fMES)- 1] ) {
            cout << " * SKU = " << arPro[i].vsku << " * Valor enero = "<< arPro[i].vMes[0] << " * valor X = " << arPro[i].vMes[stoi(fMES)- 1] << endl;
            montoI += double(arPro[i].vMes[0]);
            montoF += double(arPro[i].vMes[stoi(fMES)- 1]);
            fechaF = stoi(fMES);
        }
    }
    */

    double inflacion = ((montoF - montoI) / montoI) * 100;
    cout << " * N de productos " << arPro.size() << endl;
    cout << montoF << " / " << montoI << endl;
    cout << " * Inflacion entre " << fechaI << " y " << fechaF << " es igual a " << inflacion << " %." << endl;

    return 1;
}