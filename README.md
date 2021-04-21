Librería de Arduino para gestionar eventos sin delays y de manera ordenada.
La librería se basa en la clase **EventTimer**.

# Clase EventTimer y metodos
Lista completa de los metodos de esta clase:



```cpp
EventTimer(unsigned long T, char tunit = 'm');
// ej: EventTimer timer(2, 's');

// Alternativa:
EventTimer();
// ej: EventTimer timer; // inicializar con SetupTimer
```

**Decripción:** Constructor de la clase.

*  `unsigned long T` Duración del evento
*  `char tunit  ` Unidades de tiempo usadas en `T`
    *  `tunit= 'm'` : milisegundos
    *  `tunit= 's'` : segundos
    *  `tunit= 'M'` : minutos
    *  `tunit= 'h'` : horas


Si queremos inicializar el timer despues:
```cpp
void SetupTimer(unsigned long T, char tunit = 'm');
//  EventTimer timer;
//  timer.SetupTimer(1,'s');
```

---
```cpp
void StartTimer(unsigned long T = 0, char new_tunit = 'N');
```

**Decripción:** Llamar para inciar el Timer. Si no se llama, __CheckTimer__ devolverá __false__.

* `unsigned long T` Nuevo tiempo por si se queiere cambiar.
* `char new_tunit = 'm'` Por si se quiere cambiar tambien la unidad.
'N' indica que se mantiene la original

---
```cpp
void StopTimer();
```
__Descripción:__ Para el timer.

---

```cpp
bool CheckTimer(bool on_rise_only = true);
```

**Decripción:**
Llamar para comprobar si el tiempo ha pasado o no.

Se recomienda poner todos los
eventos dentro de una función llamada **UpdateTimers**, donde se llame el metodo
**CheckTimer** de cada evento y se ejecute una función acorde.

*  `bool on_rise_only` ¿Configura si la función devolverá *true* solo una vez al
pasar el tiempo? ¿o continuamente *true* si ha pasado el tiempo?
  * Si `on_rise_only = false`
    * Solo comprueba si delta_t > Duracion.
  * Si `on_rise_only = true`
    *  Solo devuelve 1 una vez despues de que haya pasado el tiempo.
       Útil para eventos que solo se hace una accion al acabar/duracion

# Ejemplo

Parpadeamos un led cuando pasa un tiempo. Se pueden hacer otras cosas mientras se espera al evento

```cpp
#include <LP_EventTimer.h>
EventTimer evento1(2000); // ms

void setup()
{
  // -- Serial --
  Serial.begin(9600);

  // -- Iniciar Led
  pinMode(LED_BUILTIN, OUTPUT);

  // -- Empezar Timers al iniciar
  evento1.StartTimer();
}


void loop()
{
  updateTimers();

  // do something else here ...
}

void updateTimers(){
  if( evento1.CheckTimer() )
  {
    Serial.println("EVENTO 1");
    ParpadearLed();
  }
}

void ParpadearLed(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
}
```
