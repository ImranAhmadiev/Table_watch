#include <Wire.h>
///////------------------------------------------------------- RANDOM THREAD -------------------------------------------------------///////

#include <avr/pgmspace.h>
#define EMPTY_LINE "                "

#define POWER_OFF 0
#define STREET_PARAMETRS 1
#define RANDOM_THREAD 2
#define TIME_SETTINGS 3

const String SETTINGS[] PROGMEM = {"Power Off","Outside Weather","Citata","Time Settings"};

/////---Цитаты, выводимые на дисплей---//////
const char s0[] PROGMEM = "";
const char s1[] PROGMEM = "Brat 3a Brata - 3a OcH0By B3yaT0";
const char s2[] PROGMEM = "-Sosi XYZ, RENE DECART";
const char s3[] PROGMEM = "Ya - NaEt'(Ebanat Natriya)'";
const char s4[] PROGMEM = "if i ever become a 'Krisoy', than i will be 'Uchitelem Splinterom'";
const char s5[] PROGMEM = "Tobi Pi3da";
const char s6[] PROGMEM = "IF your Life Doroga tebe, To S'ebis' OTCyda kak Molniya Mcqeen";
const char s7[] PROGMEM = "*** --- *** ** **** **- **";
const char s8[] PROGMEM = "Ebat' ya DOWN";
const char s9[] PROGMEM = "-Na 0bortazh. Captain Crabs";  
const char s10[] PROGMEM = "-3HaeT Kazhdiy EbaHaT E=MC^2. Albert Einstein";

const char s11[] PROGMEM = "This soft Craeated by Agent MeTp57";
const char s12[] PROGMEM = "Call Me: Chilly Willy";
const char s13[] PROGMEM = "Lybe, Pivas and Tanki, I Nazivayu eto - classica";
const char s14[] PROGMEM = "-Semerka on the table, 9 za oknom. Shavrole Le Baltica";
const char s15[] PROGMEM = "Ebat' Kopat'. -Kopatych";   
const char s16[] PROGMEM = "Ne Pizdi, YA Mogu i Yobnut'";
const char s17[] PROGMEM = "Gorox - Brat Moy";
const char s18[] PROGMEM = "Call Me: Chilly Willy";
const char s19[] PROGMEM = "Zahaval Nesquick";
const char s20[] PROGMEM = "My English - very wall";

const char s21[] PROGMEM = "Chill - sounds brilliant";  
const char s22[] PROGMEM = "A B C D - XYZ SOSI";
const char s23[] PROGMEM = "Ne Xo4y Sgnit' Na Zavode";
const char s24[] PROGMEM = "dx/d4t : 4-uscorenie";
const char s25[] PROGMEM = "YA - Nichtozhestvo -March 2019";
const char s26[] PROGMEM = "Oy Blyya, zavtra na Paryi";
const char s27[] PROGMEM = "Godi Shli, a ya Ne Ros";
const char s28[] PROGMEM = "My Weight: 50KG, 55 with Backpack";
const char s29[] PROGMEM = "Iam like Bird-GOVORUN: Otlichaus' YMOM i Soobrazitelnostu";
const char s30[] PROGMEM = "Blya Budu : Salvador - Ganduras   - Nikaragua Ryadom";

const char s31[] PROGMEM = "Eto Ya Pridumal KOROTKOE zamykanie";  
const char s32[] PROGMEM = "Go Short, Man, FCK U, Im not So SHORT. 1,5 - good";
const char s33[] PROGMEM = "Suka, Nazovesh' Menya-Poltorashka, Povidaehsya S Dalnimi Rodstvennikami";
const char s34[] PROGMEM = "WALLE Nahui Otsuda";
const char s35[] PROGMEM = "Yo, I have finished THE MAIN Idea of this Soft 18.07.19. I Think";
const char s36[] PROGMEM = "SovtVare INTGearNear";
const char s37[] PROGMEM = "Chiki-Briki";
const char s38[] PROGMEM = "Wolf, means VOLK, means Doblest'";
const char s39[] PROGMEM = "4O ya To blya srazy?! Nahui Proydite";
const char s40[] PROGMEM = "YO Banana Rot,";

const char s41[] PROGMEM = "Kak Uebu, BOYS'A";  
const char s42[] PROGMEM = "S Levoy Marsh! S Pravoy V Ebalo";
const char s43[] PROGMEM = "Esli ne Znal-Znay : Vtornik - Skidki v Pyaterochke";
const char s44[] PROGMEM = "-OXOTA? DA NU EE v Pizdu. Shavrole Le Baltica";
const char s45[] PROGMEM = "OY BLYAAAAAAAAAAAAAAAAAAAAAAAAAA";
const char s46[] PROGMEM = "";
const char s47[] PROGMEM = "";
const char s48[] PROGMEM = "";
const char s49[] PROGMEM = "";
const char s50[] PROGMEM = "";

// Массив со ссылками на цитаты
const char* const _words[] PROGMEM = {
                                        s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,
                                        s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,
                                        s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,
                                        s31,s32,s33,s34,s35,s36,s37,s38,s39,s40,
                                        s41,s42,s43,s44,s45
                                      };
// Массив последних 10 цитат 
// (чтобы исключить уже использованные знаения при рандоме)
byte last_words[10];

///////------------------------------------------------------- DEVICES -------------------------------------------------------///////

#define PHOTO_PIN 0
#define BUTTON 4

// Дисплей(1)     ----------------------------------------------------
#include <LiquidCrystal_I2C.h>
//#define LCD_BL 3 // Пин D3 - регулировка яркости  Подключать к верхнему выходу  I2C:[SDA-A4 SDL-A5]
// Первый номер дисплея (0x27) определяется с помощью утилиты | 16,2 - длина, ширина матрицы 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Время(2)     ------------------------------------------------------
#include "RTClib.h"
RTC_DS3231 rtc; // D-A4; C-A5

/*  Время и дата устанавливаются автоматически при загрузке прошивки (такие как на компьютере)
  В модуле реального времени стоит батарейка, которая продолжает отсчёт времени после выключения/сброса питания
  Как настроить время на часах. У нас есть возможность автоматически установить время на время загрузки прошивки, поэтому:
  - Ставим настройку RESET_CLOCK на 1
  - Прошиваемся
  - Сразу ставим RESET_CLOCK 0
  - И прошиваемся ещё раз
*/
 // сброс часов на время загрузки прошивки (для модуля с несъёмной батарейкой). 
 // Не забудь поставить 0 и прошить ещё раз!
 #define RESET_CLOCK 0
 
 DateTime now;
#define HOURS 0
#define MINUTES 1
#define SECONDS 2

byte _time[3];

// Барометр(3)    ----------------------------------------------------
#include <SPI.h>
#include <Adafruit_BMP280.h> //#include <Adafruit_Sensor.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10     //    SS

Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK); 

// Влажность(4)   ---------------------------------------------------
//#include "DHT.h"
//#define DHTPIN D3        //  D2
//DHT dht(DHTPIN, DHT11); //  Инициализация датчика

// -
#define HOME_TEMPERATURE 0
#define PRESSURE 1
#define OUTSIDE_TEMPERATURE 2
#define OUTSIDE_HUMIDITY 3
float _meteo[4];

///////------------------------------------------------------- functions -------------------------------------------------------///////
void _click();
void _clock();
void _shutdown();
void dots();
void screen_update();
void meteo();

void _random_thread(); // Выводит случайную фразу из массива 
int _get_element();    // Генерирует случайный элемен массива

///////------------------------------------------------------- Code -------------------------------------------------------///////

void setup() 
{
    // Последовательный порт
    Serial.begin(9600); 

    // КНОПКА D4
    pinMode(BUTTON,INPUT);
    //pinMode(3,INPUT);  

    // ЭКРАН  2-Подсветка 4- Курсор в начало
    lcd.begin(); lcd.setBacklight(1);  lcd.home(); 
    //analogWrite(LCD_BL,50);

    // ЧАСЫ
    rtc.begin();                                
    if (RESET_CLOCK || rtc.lostPower())
    {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    _clock();

    // БАРОМЕТР  
    bme.begin();

  
    // СИМВОЛЫ
    uint8_t tempreture_symbol[8] = {B11000,B11000,B000010,B00101,B00100,B00101,B00010,B00000};
    uint8_t mr[8] = {B11010,B10101,10101,B00000,B00111,B00101,B00110,B00101};
    uint8_t ms[8] = {B11010,B10101,10101,B00000,B00111,B01100,B00010,B11100};
    uint8_t clock_symbol[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
    uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
    uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
    uint8_t check[8] = {0x0, 0x1 ,0x3, 0x16, 0x1c, 0x8, 0x0};
    uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
    
    lcd.createChar(0,tempreture_symbol);
    lcd.createChar(1, mr);
    lcd.createChar(2, ms);
    lcd.createChar(3, clock_symbol);
    lcd.createChar(4, duck);
    lcd.createChar(5, check);
    lcd.createChar(6, heart);
    lcd.createChar(7, cross);

    // Выставляем параметры времни
    now = rtc.now();
    _time[HOURS] = now.hour();  
    _time[MINUTES] = now.minute();
    meteo();
    screen_update();

    // Уставнавливаем значения
    // Генератора случайных чисел
    randomSeed(analogRead(0));
}


int t=0;
void loop()
{
    if(digitalRead(BUTTON))
    {
        _click();
    }
    _clock();
}


// Проверка подсветки
void _lcd_backlight()
{ 
    Serial.print(analogRead(PHOTO_PIN));// map(analogRead(PHOTO_PIN), 0, 1023, 0, 254));
    Serial.print(" ");
    Serial.println(map(analogRead(PHOTO_PIN), 50, 400, 10, 200));
/* 
    if(t==0)
    {
        analogWrite(LCD_BL,100);
        delay(1000);
    }
    else if(t==2){  analogWrite(LCD_BL,10);}
    else if(t==3){  analogWrite(LCD_BL,100);}
    else if(t==4){analogWrite(LCD_BL,150);}
    else if(t==5){analogWrite(LCD_BL,200);}
    
    delay(1000);
    analogWrite(LCD_BL,50);
    delay(1000);
    analogWrite(LCD_BL,100);
    delay(1000);
    analogWrite(LCD_BL,150);
    delay(1000);
    analogWrite(LCD_BL,200);
    delay(1000);
    analogWrite(LCD_BL,250);
    lcd.setBacklight(0);
    delay(1000);
*/
}


void _click()
{
    byte action = 0;   
    while(digitalRead(BUTTON))
    {
        if(action < 3 )
        {
          action++;
        }else
        {
          action = 0;
        }
        lcd.clear();lcd.home();lcd.print(SETTINGS[action]);
        delay(750);
    }

    if(action == STREET_PARAMETRS)
    {
        delay(1000);
    }else if(action == RANDOM_THREAD)
    {
        _random_thread();
        screen_update();
    }else if(action == TIME_SETTINGS)
    {
        _time_settings();
    }else if(action == POWER_OFF )
    {
        _shutdown();
    }
    
    screen_update();
}
  
void _shutdown()
{
    lcd.noDisplay();
    lcd.noBacklight();
    
    while(!digitalRead(BUTTON)){ }
    
    lcd.display();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(3,0);lcd.print("Turn ON");
    delay(1000);
}

void _time_settings()
{
    lcd.clear();
    
    int time_now = millis();
    
    while(millis() - time_now < 10000)
    {
        if(digitalRead(BUTTON))
        {
            // Если тукущий час меньше 23 прибоваляем
            // Иначе сбрасываем счетчик на 0 часов
            if(_time[HOURS]<23)
            {
                _time[HOURS] = _time[HOURS] + 1;
            }else
            {
                _time[HOURS] = 0;
            }
            
            lcd.setCursor(0,0);
            if(_time[HOURS] < 9)
            {
                lcd.print(0);
                lcd.print(_time[HOURS]);
            } else 
            {
                lcd.print(_time[HOURS]);
            }
            delay(100);
        }
    }
    
    lcd.print(":");
    time_now = millis();
    
    while(millis() - time_now < 10000)
    {
        if(digitalRead(BUTTON))
        {
            // Если тукущее значение минут меньше 59 прибоваляем
            // Иначе сбрасываем счетчик на 0 минут
            if(_time[MINUTES] < 59)
            {
                _time[MINUTES] = _time[MINUTES] + 1;
            }else
            {
                _time[MINUTES] = 0;
            }
            
            lcd.setCursor(3,0);
            if(_time[MINUTES] < 9)
            {
                lcd.print(0);
                lcd.print(_time[MINUTES]);
            } else
            {
                lcd.print(_time[MINUTES]);
            }
            delay(100);
        }
     }
    
    char tt[] = "12:13:00";
    tt[1] = _time[HOURS]%10;
    tt[0] = (_time[HOURS] - _time[HOURS]%10)/10;
    tt[4] = _time[MINUTES]%10;
    tt[3] = (_time[MINUTES] - _time[MINUTES]%10)/10;
    
    const char datee[] = "Dec 29 2006";
    // rtc.adjust(DateTime(datee,tt));
    _clock();
}


void _clock()
{
    now = rtc.now();
    
    // Мигаем точками (:)
    if(now.second() - _time[SECONDS] >= 1)
    {
      dots();
    }
    _time[SECONDS] = now.second();
    
    
    if(now.minute()-_time[MINUTES] != 0)
    {
        _time[MINUTES] = now.minute();
        _time[HOURS]   = now.hour();
        
        meteo();
        screen_update();

        // Каждые 10 минут выводим цитату
        if(_time[MINUTES]%10 == 0)
        {
            lcd.setCursor(2,0);lcd.print(':');
            _random_thread();
            screen_update();
        }
    }
}


// Мигание (:)
void dots()
{
    lcd.setCursor(2,0);
    lcd.print(":");
    delay(300);
    lcd.setCursor(2,0);lcd.print(" ");
}


// Проверка
void symbols()
{
    lcd.setCursor(0,1);
    for (int j = 0; j < 16; j++) 
    {
        lcd.write(j);
        delay(1000);
    } 
}


// Обновление значений, выводимых на экран
void screen_update()
{
    lcd.clear();
    lcd.home();  

    // Выводим время
    lcd.setCursor(0,0);
    if(_time[HOURS]<10)lcd.print("0");    lcd.print(_time[HOURS]); // Часы (09 или 11)
    lcd.setCursor(3,0);
    if(_time[MINUTES]<10)lcd.print("0");  lcd.print(_time[MINUTES]); // Минуты (03 или 55)
    
    // В комнате
    lcd.setCursor(7,0);lcd.print("[T="); lcd.print(_meteo[HOME_TEMPERATURE]);  lcd.setCursor(14,0); lcd.write(0); lcd.print("]");
    lcd.setCursor(7,1);lcd.print("P=");  lcd.print(_meteo[PRESSURE]);          lcd.setCursor(14,1); lcd.write(1); lcd.write(2);
      
    // Улица (не подключен датчик)
    //lcd.setCursor(7,0);lcd.print("[T=");lcd.print());lcd.setCursor(14,0);lcd.write(0);
    //lcd.setCursor(7,1);lcd.print();lcd.setCursor(10,1);lcd.write(1);lcd.write(2);
 }


void meteo()
{
    _meteo[HOME_TEMPERATURE] = bme.readTemperature();
    _meteo[PRESSURE] = bme.readPressure()/133.3;     // PПаскаль
    // Улица (не подключен датчик)
    //_meteo[OUTSIDE_TEMPERATURE] = 
    //_meteo[OUTSIDE_HUMIDITY] = 
}


// Случайная цитата
void _random_thread()
{
    char base[100];
    String txt, running_line;
    byte txt_length, counter, itteration;
    int i,element;
  
    element = _get_element();
    
    // необходимые функции и расшифровки (просто скопируйте)
    strcpy_P(base, (char*)pgm_read_word(&(_words[element])));
    
    txt = base;
    txt_length = txt.length();
    
    // Первоначалные параметры
    lcd.setCursor(0,1);lcd.print(EMPTY_LINE); 
    counter = 0;
    running_line = EMPTY_LINE;

    // Анимация экрана (16x2 ячееки)
    for(i=15; i>=0; i--)
    {
        lcd.setCursor(i,1);
        
        if(i<txt_length)
        {
            running_line = txt[i];
            lcd.print(running_line); delay(random(10,500));
        }else{ 
            running_line+=" ";
            lcd.print(running_line);delay(300);
        }
    }

    for(i=0; i<txt_length; i++)
    {
        lcd.setCursor(0,1);
        for(int j=i; j<txt_length; j++)
        {
            running_line[counter] = txt[j];
            counter++;
        }
        lcd.print(running_line);
        
        counter = 0;
        running_line = EMPTY_LINE;
        delay(300);
        
        lcd.setCursor(0,1); lcd.print(EMPTY_LINE);delay(100);
    }
 
    itteration = 0; 
    while(itteration < txt_length)
    {
        counter = 0; 
        running_line = EMPTY_LINE;
        
        for(i=itteration; i<itteration+16; i++)
        {
            if(i<txt_length)
            {
                running_line[counter] = txt[i];
                counter++;
            } 
        }
        lcd.setCursor(0,1);lcd.print(running_line);delay(2500);
        itteration+=16;
    }
}


int _get_element()
{
    int i;
    int num;
    boolean again = true;
    
    while(again == true)
    {
        again = false;
        // Кол-во элементов массива: 
        //sizeof(_words) / sizeof(_words[0])
        num = random(0,(sizeof(_words) / sizeof(_words[0])));
        
        for(i=0; i<10; i++)
        {
            if(num == last_words[i])
            {
                again = true; 
            }
        }
    }
    
    for(i=0; i<9; i++)
    {
        last_words[i] = last_words[i+1];
    }
    last_words[9] = num;
    
    return num;
}  
