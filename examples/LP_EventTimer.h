/*
  LP_EventTimer.h
*/
#include "Arduino.h"
#ifndef LP_EventTimer
#define LP_EventTimer


// == Header ===================================================================
class EventTimer
{
private:
 long t_inicio = 0;
 unsigned long T_duracion = 0; // en ms
 char tunit;

public:
  // Tipo de tiempos:
  //  'm': milisegundos
  //  's': segundos
  //  'M': minutos
  //  'h': horas
  EventTimer(unsigned long T, char tunit = 'm');

  // Llamar dentro de UpdateTimers para comprobar si hay que ejecutar
  // la accion o no.
  // Si on_rise_only = false
  //   Solo comprueba si delta_t > Duracion.
  // Si on_rise_only = true
  //   Solo devuelve 1 una vez despues de que haya pasado el tiempo.
  //   Util para eventos que solo se hace una accion al acabar/duracion
  bool CheckTimer(bool on_rise_only = true);

  // Llamar par iniciar Timer.
  // Si no se ha llamado, CheckTimer devolvera 0
  // T por si se quiere cambiar la duracion en cualquier momento.
  //    si 0, se mantendra el anterior
  void StartTimer(unsigned long T = 0);

  // Para timer aunque haya pasado el tiempo. No lo activa
  void StopTimer();

};


// == Constructor ==============================================================
EventTimer::EventTimer(unsigned long T, char tunit){
  this->t_inicio = -1;
  this->tunit = tunit;
  if(tunit == 'm')       this->T_duracion = T;            // milisegundos
  else if(tunit == 's')  this->T_duracion = T*1000;       // segundos
  else if(tunit == 'M')  this->T_duracion = T*1000*60;    // minutos
  else if(tunit == 'h')  this->T_duracion = T*1000*60*60; // horas
}

void EventTimer::StartTimer(unsigned long T){
  // Actualzar la duraicon
  if(T != 0 ) this->T_duracion = T;

  // Iniciar timer
  this->t_inicio = millis();
}

void EventTimer::StopTimer(){
  this->t_inicio = -1;
}

bool EventTimer::CheckTimer(bool on_rise_only){
  // Si desactivado, devolver 0
  if (this->t_inicio == -1) return 0;

  // Timer Activado:
  unsigned long delta_t = millis() - t_inicio;
  if(delta_t >= this->T_duracion){
    if(on_rise_only){
      this->StopTimer();
    }
    return 1;
  } else {
    return 0;
  }

}



#endif
