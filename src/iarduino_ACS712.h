//	Библиотека для работы Trema-модулем на базе аналогового датчика тока ACS712 (Analog Current Sensor) ...: http://
//  Версия: 1.0.0
//  Последнюю версию библиотеки Вы можете скачать по ссылке: http://
//  Подробное описание функции бибилиотеки доступно по ссылке: http://
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_ACS712_h
#define iarduino_ACS712_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define ADC_SCALE	1024.0f			//	Диапазон измерений АЦП Arduino
#define VREF		5.0f			//	Опорное напряжение АЦП Arduino

class iarduino_ACS712{
	public:			iarduino_ACS712	(uint8_t);				//	Объявление экземпляра класса																(Аргумент: номер вывода модуля)
	/**	пользовательские функции **/
		float		readDC			(uint8_t=0);			//	Чтение постоянного тока																		(Аргумент: коэффициент сглаживания показаний)
		float		readAC			(uint8_t=0);			//	Чтение переменного тока																		(Аргумент: коэффициент сглаживания показаний)
		float		getZeroVDC		(void);					//	Чтение постоянного напряжения на выходе модуля при отсутствии тока							(Аргументы отсутствуют)
		float		getZeroVAC		(void);					//	Чтение переменного напряжения на выходе модуля при отсутствии тока							(Аргументы отсутствуют)
		void		setZeroVDC		(float);				//	Установка коррекции смещения нуля для постоянного тока										(Аргумент: постоянное напряжение на выходе модуля при отсутсвии тока)
		void		setZeroVAC		(float);				//	Установка коррекции смещения нуля для переменного тока										(Аргумент: переменное напряжение на выходе модуля при отсутсвии тока)
		void		calibrationDC	(uint16_t);				//	Калибровка показаний модуля для постоянного тока											(Аргумент: коэффициент от 0 до 1023 для корректировки показаний)
		void		calibrationAC	(uint16_t);				//	Калибровка показаний модуля для переменного тока											(Аргумент: коэффициент от 0 до 1023 для корректировки показаний)
	private:
	/**	внутренние переменные **/
		uint8_t		pinSensor;
		uint32_t	timeDC		=	0;						//	Время последнего чтения показаний постоянного тока											(для определения коэффициента сглаживания показаний если он не указан)
		uint32_t	timeAC		=	0;						//	Время последнего чтения показаний переменного тока											(для определения коэффициента сглаживания показаний если он не указан)
		float		sensDC		=	0.1307f;				//	Чуствительность датчика к постоянному току: 1A = 130.7 мВ									(значение переменной меняется через функцию calibrationDC();)
		float		sensAC		=	0.1307f * 0.5665f;		//	Чуствительность датчика к переменному току: 1A = 130.7 мВ * коэффициент RC фильтра 0.5665	(значение переменной меняется через функцию calibrationAC();)
		float		voltageCDC	=	ADC_SCALE/2;			//	Напряжение на выходе модуля при отсутствии постоянного тока на входе датчика				(значение переменной присваивается через функцию setZeroVDC();)
		float		voltageCAC	=	0;						//	Напряжение на выходе модуля при отсутствии переменного тока на входе датчика				(значение переменной присваивается через функцию setZeroVAC();)
		float		voltageDC	=	0;						//	Напряжение на выходе модуля при измерении постоянного тока на входе датчика					(значение переменной присваивается через функцию readVDC();)
		float		voltageAC	=	0;						//	Напряжение на выходе модуля при измерении переменного тока на входе датчика					(значение переменной присваивается через функцию readVAC();)
	/**	внутренние функции **/
		void		readVDC			(uint8_t,uint8_t=10);	//	Чтение постоянного напряжения																(Аргументы: коэффициент сглаживания показаний, количество выборок показаний)
		void		readVAC			(uint8_t,uint8_t=3);	//	Чтение переменного напряжения																(Аргументы: коэффициент сглаживания показаний, количество выборок показаний)
};

#endif