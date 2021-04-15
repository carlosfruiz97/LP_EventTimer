/* ===============================================================
 * EJEMPLO DE GESTOR DE EVENTOS DESACOPLADOS
 * 
 * Estructura para gestionar eventos sin delays y de manera 
 * ordenada
 *          
    DOCUMENTACION:
    // Tipo de tiempos:
    //  'm': milisegundos
    //  's': segundos
    //  'M': minutos
    //  'h': horas
 *  EventTimer(unsigned long T, char tunit = 'm');
  
    // Llamar dentro de UpdateTimers para comprobar si hay que ejecutar
    // la accion o no.
    // Si on_rise_only = false
    //   Solo comprueba si delta_t > Duracion.
    // Si on_rise_only = true
    //   Solo devuelve 1 una vez despues de que haya pasado el tiempo.
    //   Util para eventos que solo se hace una accion al acabar/duracion
 *  bool CheckTimer(bool on_rise_only = true);
  
    // Llamar par iniciar Timer.
    // Si no se ha llamado, CheckTimer devolvera 0
    // T por si se quiere cambiar la duracion en cualquier momento.
    //    si 0, se mantendra el anterior
 *  void StartTimer(unsigned long T = 0);
  
    // Para timer aunque haya pasado el tiempo. No lo activa
 *  void StopTimer();
 *    
 * Propiedad de @logicprops
 * ===============================================================
 */

#define DEBUG     1
#if DEBUG == 1
 #define LOGN(x) Serial.println(x)
 #define LOG(x)  Serial.print(x)
#else
 #define LOG(x)
 #define LOGN(x)
#endif

// ==== LIBRERIAS EXTERNAS =======================================
#include <LP_EventTimer.h>

// ==== TIMERS ===================================================
EventTimer evento1(2000); // m
EventTimer evento2(5, 's');
EventTimer evento3(10, 'M');
EventTimer evento4(1, 'h');

// ==== FUNCIONES ================================================
void updateTimers();
void ParpadearLed();

// ===============================================================
//            SETUP
// ===============================================================
void setup()
{
    // -- Serial --
#if DEBUG == 1
      Serial.begin(115200);
      delay(50);
      LOGN("\n\n----------------------------\n\tEMPEZAMOS\n");
#endif

    // -- Iniciar Led
    pinMode(LED_BUILTIN, OUTPUT);

    // -- Empezar Timers al iniciar 
    evento1.StartTimer();
    evento2.StartTimer();
    evento3.StartTimer();
    evento4.StartTimer();
}

// ===============================================================
//            LOOP
// ===============================================================
void loop()
{
  updateTimers();
}

void ParpadearLed(){
  digitalWrite(LED_BUILTIN, HIGH); delay(500);
  digitalWrite(LED_BUILTIN, HIGH); 
}

// ==== TIMERS ===================================================
void updateTimers(){
  if(evento1.CheckTimer()){
    LOGN("EVENTO 1"); ParpadearLed();
  }
  
  if(evento2.CheckTimer()){
    LOGN("EVENTO 2"); ParpadearLed();
  }
  
  if(evento3.CheckTimer()){
    LOGN("EVENTO 3"); ParpadearLed();
  }
  
  if(evento4.CheckTimer()){
    LOGN("EVENTO 4"); ParpadearLed();
  }
}
