# E-paperSmartwatch

### Overview:
Projekt zakłada stworzenie smartwacha, który za pomocą modułu Bluetooth będzie komunikował się z telefonem i wyświetlał pobrane informacje na wyświetlaczu. Przełączanie ekranów występujące w prawdziwym smartwachu symulować będzie 8-przyciskowy panel.

### Description:
Na potrzeby projektu stworzona została aplikacja na Androida o nazwie EWatch. Pozwala ona na połączenie się z płytką STM32F407G-DISCOVERY za pomocą Bluetooth oraz odpowiada za cały proces przesyłania danych pomiędzy smartfonem a modułem Bluetooth HC-05. Moduł ten z kolei odpowiada za przesyłanie tych danych do płytki poprzez USART(?). Wyświetlacz HD44780 LCD z kolei komunikuję się z płytką za pomocą SPI. Działanie wyświetlacza jest oparte głównie na bibliotece HD44780 Library.
Schemat działania jest następujący: po połączeniu telefonu z modułem Bluetooth (przycisk „Open” w aplikacji) aplikacja odbiera od płytki wysyłane sygnały. W zależności od wysyłanego sygnału aplikacja zwraca inne dane (np. godzinę, stan baterii, ilość powiadomień). Zmiana sygnału zachodzi poprzez wciśnięcie odpowiedniego przycisku na panelu.

### Tools: 
•	System Workbench for STM32
•	Android Studio

### How to run:
W wypadku gdy program jest już wgrany na płytkę wystarczy pobrać aplikację na telefon a następnie uruchomić ją i połączyć się przez bluetooth z płytką (przycisk „open”). Wyboru wyświetlanych danych dokonujemy przez zmianę ekranu za pomocą przycisków K0 i K1 na panelu.
Schemat podłączenia:

Wyświetlacz:
VSS -> GND
VCC -> 5V
V0 -> ADC2 (potencjometr)
RS -> PB2
RW -> GND
E -> PB7
D4 -> PC12
D5 -> PC13
D6 -> PB12
D7 -> PB13
A -> 3V
K -> GND

Potencjometr:
GND -> GND
ADC2 -> V0 (wyświetlacz)

Bluetooth:
VCC -> 3V
GND ->GND
RxD ->PC10
TxD -> PC11

Przyciski:
G -> GND
K0 -> PA3
K1 -> PA1
K2 -> PA2

### How to compile:
Pobrać projekt, z folderu STM uruchomić plik .cproject, wgrać program na płytkę.

### Atributions: 
HD44780 Library: https://stm32f4-discovery.net/2014/06/library-16-interfacing-hd44780-lcd-controller-with-stm32f4/

### Future improvements:
•	dodanie wyświetlania informacji o nowym powiadomieniu
•	zmiana wyświetlacza na OLED/e-papierowy
•	dodanie głośnika
•	zoptymalizowanie aplikacji

### Licence:
MIT

### Credits:

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor: Tomasz Mańkowski
