# On-board_computer
Komputer pokładowy dla motocykla

Projekt Arduino

Część techniczna:
- Arduino Nano Atmega328p
- Wyświetlacz ST7920 128x64 
- Czujnik temperatury DS18B20
- Moduł zegara DS3231
- Odbiornik GPS RGM-3550
- Przetwornica Step-down
- Kilka rezystorów
- Przycisk

Funkcje urządzenia:
- Wyświetlanie logo producenta motocykla podczas uruchomienia
- Wyświetlanie daty i godziny
- Wyświetlanie temperatury zewnętrznej wraz z "animowaną ikoną"
- Wyświetlanie napięcia akumulatora wraz z "animowaną ikoną"
- Wyświetlanie aktualnej prędkości pojazdu 
- Wyświetlanie aktualnej wysokości nad poziomem morza
- Wyświetlanie aktualnej odległości od domu w linii prostej 
- Wyświetlanie przejechanego dystansu z zapisem do pamięci mikro kontrolera i możliwością kasowania go
- Zapis aktualnie wybranej zakładki GPS
- Prosty system samo diagnostyki ?

Do dyspozycji użytkownika będzie przycisk, który będzie służył do zmieniania funkcji w zakładce GPS.
Podawane informacje mają być możliwe jak najbardziej czytelne, aby nie było problemu z odczytem ich podczas jazdy.
