### Estudio del comportamiento del Programa de barrera parcial con Monitor SC modificado

###### Salvador Romero Cortés

---

**Programa Barrera Original: **

```pascal
Monitor BP
var cola 	 : condition;
	contador : integer;
procedure cita() ;
begin
	contador := contador+1;
	if contador < n then
		cola.wait();
	contador := contador-1;
	print("salgo de la cita")
	if contador > 0 then
		cola.signal();
	end
begin
	contador := 0 ;
end
```

**Programa Barrera Modificado:**

```pascal
Monitor BP
var cola 	 : condition;
	contador : integer;
procedure cita() ;
begin
	contador := contador+1;
	if contador < n then
		cola.wait();
	contador := contador-1;
	if contador > 0 then
		cola.signal();
    print("salgo de la cita")
	end
begin
	contador := 0 ;
end
```

Se trata de un monitor con la semántica SC (Señalar y Continuar). Con esta semántica, los procesos señaladores continuan inmediatamenter su ejecución tras hacer el `signal`.  Los procesos señalados abandonan la cola condición y esperan en la cola del monitor hasta readquirir la exclusión mutua y ejecutar código tras `wait`. 

Cuando llega un grupo de hebras al monitor entran a la cola de este y a medida que el monitor se lo permite van entrando al procedimiento `cita()` . Una vez van entrando se quedan esperando hasta que lleguen todas las hebras del grupo.

Cuando la última hebra llega, esta hace un `signal()` al resto de hebras del grupo que habían llegado antes. Sin embargo, como la sentencia `print` se encuentra tras el signal, no se garantiza la exclusión mutua entre grupos de hebras. Esto ocurre debido a que las hebras señaladas vuelven a la cola del monitor donde puede que haya otro grupo de hebras esperando antes que ellas y por tanto entre este grupo, mezclando las trazas de los distintos grupos de hebras.

**Ejemplos**

Dos grupos:

* Grupo 1: h1, h2, h3
* Grupo 2: h4, h5, h6

1. Llega el grupo 1 al monitor. Consiguen EM y entran al procedimiento cita en orden.
2. h1 y h2 esperan. h3 les hace signal
3. Mientras tanto, el grupo 2 espera en la cola del monitor
4. h1 y h2 esperan la cola del monitor después del grupo 2
5. h3 ejecuta "salgo de la cita".
6. El grupo 2 llega al monitor
7. h4, h5 y h6 no hacen la espera puesto que el contador se lo permite
8. h4, h5 y h6 ejecutan "salgo de la cita"
9. h1 y h2 llegan al monitor y ejecutan "salgo de la cita"

Por tanto la salida de esta ejecución sería erronea puesto que se estarían  entrelazando las salidas de los distintos grupos. La salida sería

h3, h4, h5, h6, h1, h2

Un ejemplo en el que sería correcto (muy poco probable) sería en el que las hebras del grupo 1 sean mucho más rápidas que las del grupo 2 y entren a la cola del monitor siempre antes que las del grupo 2. De esta manera la salida sería ordenadada.

Es posible tambíen que las hebras no entren en orden al procedimiento cita. En este caso también se entremezclarían las salidas.

La mayoria de posibilidades consisten en permutaciones de las hebras de los ejemplos anteriores.

