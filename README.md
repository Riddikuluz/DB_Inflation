# ## Programa: Análisis de Inflación Mensual

Este programa realiza un análisis de inflación mensual utilizando datos de ventas de productos de un supermercado. Lee los datos de un archivo CSV y procesa la información para calcular la variación mensual de precios y la inflación mensual acumulada.

### Dependencias:

El programa utiliza las siguientes bibliotecas de C++:

- iostream: para operaciones de entrada y salida.
- fstream: para leer el archivo CSV.
- string: para manipular cadenas de texto.
- sstream: para realizar operaciones de lectura y escritura en cadenas de texto.
- vector: para almacenar y manipular colecciones de elementos.
- omp: para habilitar la programación paralela (OpenMP).
- iomanip: para manipulación de formatos de salida.

### Estructuras de datos:

El programa define una estructura `sPro` que representa un producto y su información relacionada:

```cpp
struct sPro {
    string vNombre = "nProd";
    vector<int> vMes = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> vCant = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
};
```

- `vNombre` es una cadena de texto que almacena el nombre del producto.
- `vMes` es un vector de enteros que almacena los montos de venta del producto para cada mes.
- `vCant` es un vector de enteros que almacena las cantidades vendidas del producto para cada mes.

El programa también define un vector `arPro` para almacenar todos los productos.

### Funciones:

El programa incluye varias funciones para realizar diferentes tareas:

#### `ipc`

```cpp
void ipc(vector<double> sMes)
```

Esta función calcula la variación mensual de precios y la inflación mensual acumulada a partir de los montos de venta mensuales dados como parámetro. Imprime los resultados en la salida estándar.

#### `producto_vacio`

```cpp
void producto_vacio(vector<sPro> arPro)
```

Esta función busca productos que tienen datos de venta registrados en los 12 meses y calcula la variación mensual de precios y la inflación mensual acumulada. Llama a la función `ipc` para imprimir los resultados.

#### `correctData`

```cpp
bool correctData(string estado, string sku, string monto, string descuento)
```

Esta función verifica si los datos de una operación de venta son válidos. Verifica que el estado sea "AUTHORIZED" o "FINALIZED", y que el SKU, monto y descuento no sean "0" o "DESCUENTO" respectivamente. Retorna `true` si los datos son válidos, de lo contrario, retorna `false`.

#### `fechaMes`

```cpp
string fechaMes(string records)
```

Esta función extrae el mes de una fecha dada en formato "AAAA-MM-DD". Retorna el mes en formato de cadena de texto.

#### `opencsv`

```cpp
ifstream opencsv()
```

Esta función abre y devuelve un objeto de flujo de archivo para el archivo CSV que contiene los datos de ventas. Si el archivo se abre correctamente, retorna el objeto de flujo de archivo; de lo contrario, imprime un mensaje de error y retorna`0`.

#### `addProduct`

```cpp
void addProduct(vector<sPro> &arPro, string fecha, string monto, string nombre)
```

Esta función agrega un producto al vector `arPro` si el producto no existe, o actualiza los datos del producto si ya está registrado. Recibe como parámetros el vector `arPro`, la fecha, el monto de venta y el nombre del producto.

### Función principal:

La función `main` es la función principal del programa. Realiza las siguientes tareas:

1. Abre el archivo CSV utilizando la función `opencsv` y obtiene un objeto de flujo de archivo.
2. Lee cada línea del archivo CSV y extrae los datos de cada operación de venta.
3. Verifica la validez de los datos utilizando la función `correctData`.
4. Agrega los productos y sus datos al vector `arPro` utilizando la función `addProduct`.
5. Cierra el archivo CSV.
6. Llama a la función `producto_vacio` para calcular la variación mensual de precios y la inflación mensual acumulada para los productos que tienen datos de venta registrados en los 12 meses.

### Uso:

1. Asegúrate de tener los archivos de encabezado requeridos en el mismo directorio que el archivo fuente.
2. Compila y ejecuta el programa.
3. El programa leerá los datos del archivo CSV y calculará la variación mensual de precios y la inflación mensual acumulada para los productos que tienen datos de venta registrados en los 12 meses.
4. Los resultados se imprimirán en la salida estándar.
