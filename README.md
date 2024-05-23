# LEDcube
Kod obsługuje jedną kolumnę LEDcube. Zawiera funkcję przerabiającą przestrzenne fizyczne położenie diody na lokalizację w ciągu szeregowo podłączonych diod. Wykorzystywana jest biblioteka FastLED, ponieważ ze wszystkich testowanych miała najwyższą wydajność.

### Sterowanie Bluetooth (Classic)
Aby (w miarę) wygodnie sterować funkcjami LEDcube bez konieczności podłączania przewodu USB, portu COM lub innego można przełączać się między trybami za pomocą połączenia Bluetooth. <br>
Pobierz na telefon aplikację <b>Serial Bluetooth</b>, podłącz LEDcube do prądu, włącz (przełącznik na boku), podłącz telefon do urządzenia BT "<b>LEDcube</b>". Włącz aplikację, podłącz aplikację do urządzenia i możesz korzystać z funkcjonalności, które oferuje LEDcube

### Funkcjonalności
Aby przełączać się między trybami możesz wysłać do LEDcube przez Bluetooth:
<li>'p' - tryb "Rainbow"
<li>'l' - tryb "Wave"
<li>'m' - tryb "Snake"
<br><br>
Żeby grać w snake korzystamy z takich znaków wysyłanych znaków:
<li>'w' - przód
<li>'a' - lewo
<li>'s' - tył
<li>'d' - prawo
<li>'q' - dół
<li>'e' - góra
<br><br>
*Grając w snake dalej można przełączać się między trybami
