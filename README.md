# Tester LED

Tester bardzo prosty i bazuje na ESP32. Używa biblioteki FastLED (jest w folderze lib pobrana lokalnie, więc nie musisz się przejmować jej pobieraniem w odpowiedniej wersji).
Jako wyjście danych używam pinu 5 i 18. Wybierz obojętnie który, a możesz używać dwóch na raz.


## Użycie
Po podłączeniu paska do ESP32 podłączamy ESP32 do zasilania. Pasek od razu powinien się zaświecić. Program ma kilka trybów, żeby w pełni sprawdzić każdą diodę:

- full white - sprawdzenie współpracy wszystkich 3 kolorów
- full red - sprawdzenie składowej czerwonej czy na pewno w każdej diodzie świeci tak samo
- full green - sprawdzenie składowej zielonej czy na pewno w każdej diodzie świeci tak samo
- full blue - sprawdzenie składowej niebieskiej czy na pewno w każdej diodzie świeci tak samo
- dimming white - sprawdzenie płynności przechodzenia kolorów w diodzie - przygaszanie i rozjaśnianie białego koloru
- RGB rainbow - sprawdzanie płynności komunikacji i zmian kolorów

Aby przełączać się między trybami musimy zewrzeć krótko PIN19 z masą układu. Masa może być wzięta z pinu masy z płytki (pin o nazwie GND) lub z PIN21 (pin ten jest ustawiony przeze mnie, żeby prościej było przełączać się między trybami zwierając te dwa piny np. śrubokrętem). W obu przypadkach możesz to zwierać kabelkiem/śrubokrętem/przyciskiem/tact-switchem itp. Przy zwieraniu powinien się zaświecić niebieski LED wbudowany w ESP32 (zaprogramowany też przeze mnie do debugowania).

## Zasilanie
Nie polecam zasilać z komputera testowanych diod. Lepiej podłączyć je jakoś do ładowarki od telefonu (idealne 5V). ESP32 lepiej odłączyć od komputera w trakcie testowania diod, chociaż ja testowałem zawsze z podpiętym i wszystko było git. Jeśli masz to podłącz też lepiej rezystor 100Ω między PIN5/PIN18, a D_IN diod, ponieważ w skrajnych przypadkach może zasilić się układ właśnie z tego połączenia, a przy małej wydolności prądowej wyjścia mikrokontrolera różnie to może się skończyć.