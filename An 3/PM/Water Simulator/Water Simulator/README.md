In realizarea proiectului am folosit bibliotecile:
• MMA8452Q accelerometer AVR library (https://github.com/akupila/Arduino-MMA8452)
•  i2c master library

Am implementat o structura care sa contina atat datele pentru pozitia in spatiu a unui led, cat si distanta pana la planul dat de accelerometru, pinul la care este conectat led-ul, tranzistorul corespunzator.

Datorita faptului ca am calculat distanta de la un led la plan folosind formula D = (a * x + b * y + c * z) / sqrt(a * a + b * b + c * c), unde 
normala = [a,b,c] si led = [x,y,z], am vrut sa implementez o metoda mai rapida de calcul a radicalului. Am cautat pe Wikipedia o metoda de a calcula radicalul mai eficient din punct de vedere al resurselor si am decis sa folsoesc “Fast inverse square root”. 

Dupa calculul distantelor, aprind pe fiecare nivel din cub (nivel = tranzistor) led-urile ce au distanta negativa (led-ul se afla sub plan).

Mai multe detalii despre implementare gasiti si in codul sursa.
