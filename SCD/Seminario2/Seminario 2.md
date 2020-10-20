## Seminario 2

###### Salvador Romero Cortés

#### Parte 1

Compilar y ejecutar `monitor_em.cpp`

![](/home/salva/2Info/SCD/Seminario2/img/1-1.png)

Vemos que se verifican los resultados esperados.

Ahora quitamos el `unlock` de `MContador2::incrementa`

![](/home/salva/2Info/SCD/Seminario2/img/1-2.png)

Vemos que se produce interbloqueo y no avanza.

#### Parte 2

La hebra que entra la última es la hebra que sale primero porque es la hebra que da la señal al resto para continuar. Es la primera en ejecutar el código de salida. Mientras ejecuta el código de salida, el resto de hebras están esperando a la cola para poder continuar. Es decir, la hebra señaladora continúa su ejecución, y las hebras señaladas esperan a la cola del monitor.



El orden en el que las hebras señaladas logran entrar de nuevo al monitor no siempre coincide con el orden de salida de wait porque C++ no sigue ningún criterio específico para la cola de hebras señaladas.



El constructor de la clase no necesita ejecutarse en exclusión mutua porque el constructor se ejecuta siempre antes que cualquier otro código de la clase (se ejecuta al crear el objeto). De esta manera, no es necesario preocuparse por la ejecución en exclusión mutua.



Ejecutando con `notify_one`

![](/home/salva/2Info/SCD/Seminario2/img/2-notifyone.png)

Ejecutando con `notify_all`

![](/home/salva/2Info/SCD/Seminario2/img/2-notifyall.png)

No se observa ningún cambio con respecto a las ejecuciones.

**Barrera parcial** - Ejecución

![](/home/salva/2Info/SCD/Seminario2/img/barrera2.png)