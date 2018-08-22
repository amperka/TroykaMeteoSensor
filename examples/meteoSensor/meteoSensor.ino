// библиотека для работы с метео сенсором
#include <TroykaMeteoSensor.h>

// создаём объект для работы с датчиком
TroykaMeteoSensor meteoSensor;

void setup() {
  // открываем последовательный порт
  Serial.begin(115200);
  // ждём открытия порта
  while(!Serial) {
  }
  // печатаем сообщение об успешной инициализации Serial-порта
  Serial.println("Serial init OK");
  // начало работы с датчиком
  meteoSensor.begin();
  Serial.println("Meteo Sensor init OK");
  // ждём одну секунду
  delay(1000);
}

void loop() {
  // считываем данные с датчика
  int stateSensor = meteoSensor.read();
  // проверяем состояние данных
  switch (stateSensor) {
    case SHT_OK:
      // выводим показания влажности и температуры
      Serial.println("Data sensor is OK");
      Serial.print("Temperature = ");
      Serial.print(meteoSensor.getTemperatureC());
      Serial.println(" C \t");
      Serial.print("Temperature = ");
      Serial.print(meteoSensor.getTemperatureK());
      Serial.println(" K \t");
      Serial.print("Temperature = ");
      Serial.print(meteoSensor.getTemperatureF());
      Serial.println(" F \t");
      Serial.print("Humidity = ");
      Serial.print(meteoSensor.getHumidity());
      Serial.println(" %\r\n");
      break;
    // ошибка данных или сенсор не подключён
    case SHT_ERROR_DATA:
      Serial.println("Data error or sensor not connected");
      break; 
    // ошибка контрольной суммы
    case SHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
  }
  // ждём одну секунду
  delay(1000);
}
