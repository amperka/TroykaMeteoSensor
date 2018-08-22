// библиотека для работы с метео сенсором
#include <TroykaMeteoSensor.h>

// создаём объект для работы с датчиком
// адрес модуля по умолчанию «0x44» — перемычка на запаяна
TroykaMeteoSensor meteoSensorOne(JUMPER_OFF);

// создаём объект для работы с датчиком
// адрес модуля 0x45 — перемычка запаяна
TroykaMeteoSensor meteoSensorTwo(JUMPER_ON);

void setup() {
  // открываем последовательный порт
  Serial.begin(115200);
  // ждём открытия порта
  while(!Serial) {
  }
  // печатаем сообщение об успешной инициализации Serial-порта
  Serial.println("Serial init OK");
  // начало работы с первым датчиком
  meteoSensorOne.begin();
  Serial.println("Meteo Sensor One init OK");
  // начало работы со вторым датчиком
  meteoSensorTwo.begin();
  Serial.println("Meteo Sensor Two init OK");
  // ждём одну секунду
  delay(1000);
}

void loop() {
  // считываем данные с первого датчика
  int stateSensorOne = meteoSensorOne.read();
  // считываем данные со второго датчика
  int stateSensorTwo = meteoSensorTwo.read();

  // проверяем состояние данных первого датчика
  switch (stateSensorOne) {
    case SHT_OK:
      // выводим показания влажности и температуры
      Serial.println("Data sensor One is OK");
      Serial.print("Temperature = ");
      Serial.print(meteoSensorOne.getTemperatureC());
      Serial.println(" C \t");
      Serial.print("Temperature = ");
      Serial.print(meteoSensorOne.getTemperatureK());
      Serial.println(" K \t");
      Serial.print("Temperature = ");
      Serial.print(meteoSensorOne.getTemperatureF());
      Serial.println(" F \t");
      Serial.print("Humidity = ");
      Serial.print(meteoSensorOne.getHumidity());
      Serial.println(" %\r\n");
      break;
    // ошибка данных или сенсор не подключён
    case SHT_ERROR_DATA:
      Serial.println("Data error or sensor One not connected\r\n");
      break; 
    // ошибка контрольной суммы
    case SHT_ERROR_CHECKSUM:
      Serial.println("Checksum of sensor One is error\r\n");
      break;
  }


  // проверяем состояние данных второго датчика
  switch (stateSensorTwo) {
    case SHT_OK:
      // выводим показания влажности и температуры
      Serial.println("Data sensor Two is OK");
      Serial.print("Temperature = ");
      Serial.print(meteoSensorTwo.getTemperatureC());
      Serial.println(" C \t");
      Serial.print("Temperature = ");
      Serial.print(meteoSensorTwo.getTemperatureK());
      Serial.println(" K \t");
      Serial.print("Temperature = ");
      Serial.print(meteoSensorTwo.getTemperatureF());
      Serial.println(" F \t");
      Serial.print("Humidity = ");
      Serial.print(meteoSensorTwo.getHumidity());
      Serial.println(" %\r\n");
      break;
    // ошибка данных или сенсор не подключён
    case SHT_ERROR_DATA:
      Serial.println("Data error or sensor Two not connected\r\n");
      break; 
    // ошибка контрольной суммы
    case SHT_ERROR_CHECKSUM:
      Serial.println("Checksum of sensor Two is error\r\n");
      break;
  }

  // ждём одну секунду
  delay(1000);
}
