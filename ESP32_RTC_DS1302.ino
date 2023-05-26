/** GetDateTime.cpp
 *
 * Example of getting the date and time from the RTC.
 *
 * @version 1.0.1
 * @author Rafa Couto <caligari@treboada.net>
 * @license GNU Affero General Public License v3.0
 * @see https://github.com/Treboada/Ds1302
 *
 *
 * Modificado por JToobe para sus alumnos
 *
 */


#include <Ds1302.h>


// DS1302 instancia RTC
//     rtc(RESET,CLK,DAT)
Ds1302 rtc(16, 14, 12);

// modificar a true para poner en hora
bool poneEnHora = false;


const static char* WeekDays[] = {
  "Lunes",
  "Martes",
  "Miercoles",
  "Jueves",
  "Viernes",
  "Sabado",
  "Domingo"
};


void setup() {
  Serial.begin(115200);

  // inicializa RTC
  rtc.init();

  // cambio/establecimiento hora en RTC 
  if (poneEnHora) {
    Serial.println("Seteo de Hora inicial!");

    Ds1302::DateTime dt = {
      .year = 23,
      // en la sentencia siguiente reemplazar _MAY por el mes correcto
      .month = Ds1302::MONTH_MAY,
      .day = 26,
      .hour = 12,
      .minute = 40,
      .second = 30,
      // en la sentencia siguiente reemplazar _MAY por el dia correcto
      .dow = Ds1302::DOW_FRI
    };

    rtc.setDateTime(&dt);
  }
}


void loop() {

  if (poneEnHora) { Serial.println("Seteo de hora inicial activado !!! modificar el codigo"); }

  // leo la hora actual
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  static uint8_t last_second = 0;
  if (last_second != now.second) {
    last_second = now.second;

    Serial.print("20");
    Serial.print(now.year);  // 00-99
    Serial.print('-');
    if (now.month < 10) Serial.print('0');
    Serial.print(now.month);  // 01-12
    Serial.print('-');
    if (now.day < 10) Serial.print('0');
    Serial.print(now.day);  // 01-31
    Serial.print(' ');
    Serial.print(WeekDays[now.dow - 1]);  // 1-7
    Serial.print(' ');
    if (now.hour < 10) Serial.print('0');
    Serial.print(now.hour);  // 00-23
    Serial.print(':');
    if (now.minute < 10) Serial.print('0');
    Serial.print(now.minute);  // 00-59
    Serial.print(':');
    if (now.second < 10) Serial.print('0');
    Serial.print(now.second);  // 00-59
    Serial.println();
  }

  delay(100);
}
