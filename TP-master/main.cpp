#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace std;

struct cuenta
{
   int cuentaID;
   int fechaCreacion;
   bool activa;
   float saldo;
   int nroCliente;
};

struct movimiento
{
    int movimientoID;
    long long fechaHora;
    float monto;
    int cuentaID;
};

void menu()
{
    cout << "Seleccione una opcion:" << endl;
    cout << "1. Levantar las cuentas del archivo Cuentas.BIC" << endl;
    cout << "2. Cargar una nueva cuenta." << endl;
    cout << "3. Desactivar una cuenta existente." << endl;
    cout << "4. Buscar una cuenta por ID o por nro de cliente." << endl;
    cout << "5. Listar todas las cuentas activas ordenadas por saldo descendente." << endl;
    cout << "6. Procesar un lote de movimientos." << endl;
    cout << "7. Finalizar jornada (sobreescribir Cuentas.BIC)" << endl;
    cout << "ESC. Salir del programa" << endl;
}

void levantar(cuenta cuentas[])
{
    FILE *p1;
    int i=0;
    cuenta aux;
    if( p1 = fopen("cuentas.bic", "rb+"))
    {
        cout << endl << "Se han levantado las cuentas exitosamente" << endl << endl;
        while(fread(&aux,sizeof(cuenta),1,p1))
        {
            cuentas[i]=aux;
            i++;
        }
    }
    else
    {
        cout<<"El archivo no puede ser encontrado o es inexistente.";
    }
    fclose(p1);

    return;
}

int cant_cuentas()
{
    FILE *p1;
    cuenta x;
    int i=0;
    if(p1=fopen("cuentas.bic","rb"))
    {
        fread(&x,sizeof(cuenta),1,p1);
        while(!feof(p1))
        {
            i++;
            fread(&x,sizeof(cuenta),1,p1);
        };
    }
    return i;
}

int cant_movimientos()
{
    FILE *mov;
    movimiento x;
    int i = 0;
    if(mov = fopen("movimientos.bic","rb"))
    {
        while(fread(&x,sizeof(movimiento),1,mov))
        {
            i++;
        };
    };
    return i;
}

void cargar_cuenta(cuenta cuentas[],int &cant)
{
    cuenta c;
    cout << endl;
    cout <<  "Ingrese el ID de la cuenta: ";
    cin >> c.cuentaID;
    cout << "Ingrese fecha de creacion (AAAAMMDD): ";
    cin >> c.fechaCreacion;
    cout << "Ingrese el saldo: ";
    cin >> c.saldo;
    cout << "Ingrese numero de cliente: ";
    cin >> c.nroCliente;
    c.activa = true;
    cout << "********** Cuenta " << c.cuentaID << " agregada **********" << endl << endl;
    cuentas[cant] = c;
    cant++;

    return;
}

void estado_cuenta(cuenta cuentas[], int cant)
{
    cuenta tarjeta;
    int ID;
    bool encontrado = false;
    bool cliente = false; //Es para saber si paso al else if del for :)
    cout << endl << "Ingrese el ID de la cuenta o el Nro de cliente: ";
    cin >> ID;
    cout << endl;

    for(int i = 0; i < cant; i++)
    {
        if(!encontrado && ID == cuentas[i].cuentaID)
        {
            cuentas[i].activa = false;
            encontrado = true;
            cout << "***** Se ha desactivado la cuenta " << cuentas[i].cuentaID << " *****" << endl << endl;
        } else if(!encontrado && ID == cuentas[i].nroCliente)
        {
            cuentas[i].activa = false;
            cliente = true;
            cout << "***** Se han desactivado todas las cuentas del cliente " << cuentas[i].nroCliente << " *****" << endl << endl;
        }
    };

    if(cliente)
    {
        encontrado = true;
    };
    if(!encontrado)
    {
        cout << "**** Por favor, ingrese un ID de cuenta o Nro de cliente valido *****" << endl << endl;
    };

    return;
}

void id_search(cuenta cuentas[], int cant)
{
    int ID,anio,mes,dia;
    bool encontrado = false;
   //bool cliente = false; //Es para saber si paso al else if del for :)
    cout << endl << "Ingrese el ID de la cuenta o el Nro de cliente de la/s cuenta/s a buscar: ";
    cin >> ID;
    cout << endl;
    cout << "Cliente | Cuenta | Saldo | Fecha de creacion" << endl;
    for(int i = 0; i < cant; i++)
    {
        if(!encontrado)
        {
            anio = cuentas[i].fechaCreacion / 10000;
            mes = cuentas[i].fechaCreacion % 10000 / 100;
            dia = cuentas[i].fechaCreacion % 100;
            if(ID == cuentas[i].cuentaID || ID == cuentas[i].nroCliente)
            {
                cout << cuentas[i].nroCliente << "    | " << cuentas[i].cuentaID << "  |";
                cout << cuentas[i].saldo << "| " << dia << "/" << mes << "/" << anio << endl;
                encontrado = true;
            }
        }
    }
    if(!encontrado)
    {
        cout << "**** Por favor, ingrese un ID de cuenta o Nro de cliente valido *****" << endl << endl;
    }
    cout << endl;
    return;
}

void active_list(cuenta cuentas[], int cant)
{
    cuenta aux;
    cuenta aux2[cant];
    int k = 0;

    for(int h = 0; h < cant; h++)
    {
        if(cuentas[h].activa==true)
        {
            aux2[k]=cuentas[h];
            k++;
        };
    };

    for(int i = 0; i < cant; i++)
    {
        for(int j = 0; j < cant; j++)
        {
            if(aux2[j].saldo < aux2[j+1].saldo)
            {
                aux = aux2[j+1];
                aux2[j+1] = aux2[j];
                aux2[j] = aux;
            };
        };
    };

    int anio,mes,dia;
    cout << endl << "Cliente | Cuenta | Saldo | Fecha de creacion" << endl;

    for(int i = 0; i < k; i++)
    {
        anio = aux2[i].fechaCreacion / 10000;
        mes = aux2[i].fechaCreacion % 10000 / 100;
        dia = aux2[i].fechaCreacion % 100;

        cout << " " << aux2[i].nroCliente << "   | " << aux2[i].cuentaID << "  |";
        cout << aux2[i].saldo << "| " << dia << "/" << mes << "/" << anio << endl;
    };
    cout << endl;

    return;
}

void lote_proceso(cuenta cuentas[], int cant)
{
    FILE *lote;
    FILE *procesados;

    movimiento tarjeta; //Adquirira los datos de cada movimiento con el fread
    bool encontrados = false;
    int cantMov = cant_movimientos(); //Cantidad de saldos que debe actualizar
    int mov = 0; //Cantidad de saldos actualizados

    lote = fopen("movimientos.bic","rb");
    procesados = fopen("procesados.bic","ab");

    if(lote != NULL && procesados != NULL)
    {
        cout << endl;
        while(!encontrados & fread(&tarjeta, sizeof(movimiento),1,lote))
        {
            for(int i = 0; i < cant; i++) //Recorre todo el array de cuentas
            {
                if(cuentas[i].cuentaID == tarjeta.cuentaID)//Verifica si la cuenta es la misma que la que esta asociada al movimiento
                {
                    cuentas[i].saldo += tarjeta.monto;
                    mov++;
                    fwrite(&cuentas[i], sizeof(movimiento), 1, procesados); //Agrega la cuenta a procesados.bic
                    if(mov == cantMov) //Si se procesaron todos los movimientos
                    {
                        encontrados = true; //Se terminan el
                        i = cant;           //while y el for
                    };
                };
            };
        };
    } else
    {
        cout << endl << "Ha ocurrido un error procesando el lote de movimientos" << endl << endl;;
    };
    fclose(lote);
    fclose(procesados);

    if(encontrados) //Si todos los movimientos encontraron su cuenta asociada
    {
        cout << "***** Procesamiento del lote exitoso *****" << endl << endl;
    } else
    {
        cout << "Se encontraron movimientos de cuentas inexistentes" << endl << endl;
    };

    return;
}

void fin_jornada(cuenta cuentas[], int cant)
{
    FILE *f;
    cuenta aux[cant];
    int k = 0;
    for(int i = 0; i < cant; i++)
    {
        if(cuentas[i].activa == true)
        {
            aux[k] = cuentas[i];
            k++;
        };
    };
    cuenta aux2[k];

    for(int i = 0; i < k; i++)
    {
        aux2[i] = aux[i];
    };

    f = fopen("cuentas.bic","wb");
    fwrite(aux2,sizeof(cuenta),k,f);
    fclose(f);
    cout << endl << "********* JORNADA FINALIZADA **********" << endl << endl;
/*   FILE *auxiliar; ESTO NO FUNCIONANAAAAA

    cuenta aux;
    auxiliar = fopen("auxiliar.bic","ab");

    for(int i = 0; i < cant; i++)
    {
        if(cuentas[i].activa == true)
        {
            fwrite(&aux, sizeof(cuenta),1,auxiliar);
        };
    };
    fclose(auxiliar);

    if(!remove("cuentas.bic"))
    {
        cout << endl << "No borrado" << endl << endl;
    } else if(!rename("auxiliar.bic","cuentas.bic"))
    {
        cout << endl << endl << "No renombrado" << endl << endl;
        cout << endl << "********** JORNADA FINALIZADA **********" << endl << endl;
    } else
    {
        cout << endl << "No se pudo reescribir el archivo" << endl << endl;
    };*/

    return;
}

int main()
{
    int cant = cant_cuentas();
    cuenta cuentas[cant+10];
    int opcion;
    do
    {
      menu();
    do
    {
     opcion=getch();

    }while(opcion>='8');

     switch(opcion)
     {
      case '1':/*Levanta las cuentas del archivo.*/
        levantar(cuentas);
      break;
      case '2':/*cargar cuenta*/
         cargar_cuenta(cuentas,cant);
      break;
      case '3':/*Desactivar una cuenta existente.*/
        estado_cuenta(cuentas,cant);
      break;
      case '4':/*Buscar una cuenta por id.*/
        id_search(cuentas,cant);
      break;
      case '5':/*Listar todas las cuentas activas por saldo*/
        active_list(cuentas,cant);
      break;
      case '6':/*Procesar lote de moviemientos*/
        lote_proceso(cuentas, cant);
      break;
      case '7':/*Finalizar jornada.*/
       fin_jornada(cuentas, cant);
      break;
     }
    }while(opcion!=27);

    return 0;
  }
