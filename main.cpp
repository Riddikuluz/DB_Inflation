#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
//#define name "CERVEZA BUDWEISER 6 PACK BOTELLA 343ML"

using namespace std;

int main() {
    int cont = 0;
    string sku, monto, fecha, descuento, estado, wes, nombre, hora;
    struct sPro {
        string vNombre = "nProd";
        vector<int> vMes = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        vector<int> vCant = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    };
    vector<sPro> arPro;

    string dbSuper = "supermercado.csv";// supermercado - prueba1
    ifstream allData;
    allData.open(dbSuper);
    if (allData.fail()) {
        cout << "Error al abrir el archivo: " << dbSuper << endl;
        return 0;
    }
    getline(allData, wes, '"');
    for (; allData.peek() != EOF;) {//EOF==-1  for(;allData.peek() != EOF;);while (allData.peek() != EOF);
        string records;
        getline(allData, records, '"');
        //cout << "*" << records << "*" <<endl;
        if (records != ";" && records != "\n") {
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
                //getline(fetcha, hora, 'Z');
            } else
                estado = records;
            //cout << "contador: " << cont << endl;
            cont++;
        }
        if (cont > 5) {//una vez almacena todos los datos de la operacion
            cont = 0;
            if ((estado == "AUTHORIZED" || estado == "FINALIZED") && sku != "0" && monto != "0" && descuento != "DESCUENTO"){
                bool encontrado = false;
                int auxstoi = stoi(fecha), valorF = stoi(monto);

                /*cout << "\nsku: " << sku << endl;
                cout << "nombre: " << nombre << endl;
                cout << "monto: " << monto << endl;
                cout << "descuento: " << descuento << endl;
                cout << "fecha: " << fecha << endl;
                cout << "hora: " << hora << endl;
                cout << "estado: " << estado << endl;
                cout << "Presione enter para continuar ...";
                cin.get();
               */
                for (int i = 0; i < arPro.size() && !encontrado; i++) {//busca si el producto esta en el struct
                    if (arPro[i].vNombre == nombre) {
                        encontrado = true;
                        arPro[i].vCant[auxstoi - 1]++;
                        if (arPro[i].vMes[auxstoi - 1] == 0)
                            arPro[i].vMes[auxstoi - 1] = valorF;
                        //cout << " * sku EXISTE= " << arPro[i].vsku << " * mes = " << auxstoi << " * valor = "<< arPro[i].vMes[auxstoi - 1] << endl;
                        // else
                        // cout << " * MONTO DEL MES YA REGISTRADO *" << endl;
                    }
                }
                if (!encontrado) {//si el producto no esta, lo agrega al struct
                    vector<int> arrMonto = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                    vector<int> arrCant = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                    arrMonto[auxstoi - 1] = valorF;
                    arrCant[auxstoi - 1]=1;
                    sPro aux{nombre, arrMonto, arrCant};
                    arPro.push_back(aux);
                    //cout << " * sku NUEVA = " << arPro[arPro.size() - 1].vsku << " * mes = " << auxstoi << " * valor = "<< arPro[arPro.size() - 1].vMes[stoi(fecha) - 1] << endl;
                }
            }
        }
    }

    allData.close();

    //cout<< "N de productos = "<< arPro.size()<< endl;
    vector<double> sMes = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < arPro.size(); i++) {//en cada producto
        bool vacio = false;
        //cout << arPro[i].vNombre<< endl;
        for (int j = 0; j < 12 && !vacio; j++) {//busca que este registrado todos los meses
            //cout << arPro[i].vMes[j]<<" - ";
            if (!arPro[i].vMes[j]) {
                vacio = true;
            }
        }
        if (!vacio){//si hay registro en los 12 meses
            //cout << arPro[i].vNombre<< endl;
            for (int k = 0; k < 12; k++) { // se suma al total de cada mes
                //cout << " * cantidad " << arPro[i].vMes[k]<< endl;;
                sMes[k] = sMes[k] + arPro[i].vMes[k] * arPro[i].vCant[k];
            }
            //cout << "Presione enter para continuar ...";
            //cin.get();
        }
    }


    cout <<" * Variacion mensual"<< endl;
    double sInflacion=0;
    vector<string> dMeses = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    for (int i = 0; i < 11; i++){
        //cout << " * Suma total de los valores del mes de " << i+1 << " = " << sMes[i] << endl;
        cout << " * Indice del mes de " << dMeses[i+1] << " respecto del mes de " << dMeses[i] << " es igual a " << (sMes[i+1] / sMes[i]-1) * 100 << " %." << endl;
        sInflacion+=(sMes[i+1] / sMes[i]-1) * 100;
    }

    cout << " * Inflacion mensual acumulada es igual a " << sInflacion << " %." << endl;

    //cout << " * Indice del mes de " << dMeses[11] << " respecto del mes de " << dMeses[0] << " es igual a " << (sMes[11] / sMes[0]-1) * 100 << " %." << endl;
    //double inflacion = ((montoF - montoI) / montoI) * 100;
    //cout << " * N de productos " << arPro.size() << endl;
    //cout << montoF << " / " << montoI << endl;
    //cout << " * Inflacion entre " << fechaI << " y " << fechaF << " es igual a " << inflacion << " %." << endl;

    return 0;
}
