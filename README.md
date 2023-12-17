
# Miernik wiedzy (Projekt w C++)

**Temat projektu:** Aplikacja służąca do testowania opanowanego materiału z fizyki. 

**Opis:** Projekt zakłada bazę pytań zamkniętych z różnych działów fizyki. Na bieżąco pokazuje się liczba udzielonych odpowiedzi, liczba pozostałych pytań i podobne informacje. Na końcu testu mogą wyświetlić się sugestie dotyczące konkretnych tematów, który należy jeszcze powtórzyć.  

## Harmonogram

- [x]  **Tydzień 1.** (do 23.10) – utworzenie głównej klasy dla pytań, stworzenie struktury projektu (zaplanowanie folderów, plików, itp.), stworzenie repozytorium na githubie.  
- [x]  **Tydzień 2.** (do 30.10) – dodanie bazy pytań.  
- [x]  **Tydzień 3.** (do 06.11) – początek tworzenia interfejsu graficznego w Qt.  
- [x]  **Tydzień 4.** (do 13.11) – kontynuacja tworzenia interfejsu graficznego w Qt  
- [x]  **Tydzień 5.** (do 20.11) – dodanie funkcjonalności zliczania udzielonych odpowiedzi.  
- [x]  **Tydzień 6.** (do 27.11) – dodanie funkcjonalności zliczania opanowanych pytań.  
- [x]  **Tydzień 7.** (do 04.12) – dodanie więcej pytań z większej liczby działów, dodanie możliwości wyboru działu do nauki na początku.   
- [ ]  **Tydzień 8.** (do 11.12) – dodanie funkcjonalności wyświetlania na końcu testu sugerowanych tematów do powtórki.  
- [ ]  **Tydzień 9.** (do 18.12) – ostateczne dodatki, tzn przycisk powrotu do strony głównej, przycisk do ponownego przejścia testu itp.  
- [ ]  **Tygodnie 10-13.** (do 15.01) – czas zarezerwowany na naprawę ewentualnych błędów lub dokończenie punktów, które okazałyby się bardziej czasochłonne, niż przewidziałam.  
- [ ]  **Tydzień 14.** (do 22.01) – prezentacja końcowa

## Wymagania

- Qt (u mnie 6.5.2)
- Docker (u mnie 24.0.7)

## Instalacja

1. Klonowanie repozytorium:
```bash
git clone https://github.com/ZMejer/PCPP2023-miernik-wiedzy.git
```
lub 
```bash
git clone git@github.com:ZMejer/PCPP2023-miernik-wiedzy.git
```

2. Przejście do katalogu projektu:
```bash
cd PCPP2023-miernik-wiedzy
```

3. Uruchamianie dockera:
```bash
docker compose up
```
4. Uruchamianie projektu:
```bash
cd miernik-wiedzy
cmake .
make
./miernik-wiedzy.app
```


**Temat projektu:** Aplikacja służąca do testowania opanowanego materiału z fizyki. 

**Opis:** Projekt zakłada bazę pytań zamkniętych z różnych działów fizyki. Na bieżąco pokazuje się liczba udzielonych odpowiedzi, liczba pozostałych pytań i podobne informacje. Na końcu testu mogą wyświetlić się sugestie dotyczące konkretnych tematów, który należy jeszcze powtórzyć.  

## Harmonogram

- [x]  **Tydzień 1.** (do 23.10) – utworzenie głównej klasy dla pytań, stworzenie struktury projektu (zaplanowanie folderów, plików, itp.), stworzenie repozytorium na githubie.  
- [x]  **Tydzień 2.** (do 30.10) – dodanie bazy pytań.  
- [x]  **Tydzień 3.** (do 06.11) – początek tworzenia interfejsu graficznego w Qt.  
- [x]  **Tydzień 4.** (do 13.11) – kontynuacja tworzenia interfejsu graficznego w Qt  
- [x]  **Tydzień 5.** (do 20.11) – dodanie funkcjonalności zliczania udzielonych odpowiedzi.  
- [x]  **Tydzień 6.** (do 27.11) – dodanie funkcjonalności zliczania opanowanych pytań.  
- [x]  **Tydzień 7.** (do 04.12) – dodanie więcej pytań z większej liczby działów, dodanie możliwości wyboru działu do nauki na początku.   
- [ ]  **Tydzień 8.** (do 11.12) – dodanie funkcjonalności wyświetlania na końcu testu sugerowanych tematów do powtórki.  
- [ ]  **Tydzień 9.** (do 18.12) – ostateczne dodatki, tzn przycisk powrotu do strony głównej, przycisk do ponownego przejścia testu itp.  
- [ ]  **Tygodnie 10-13.** (do 15.01) – czas zarezerwowany na naprawę ewentualnych błędów lub dokończenie punktów, które okazałyby się bardziej czasochłonne, niż przewidziałam.  
- [ ]  **Tydzień 14.** (do 22.01) – prezentacja końcowa

## Wymagania

- Qt (u mnie 6.5.2)
- Docker (u mnie 24.0.7)
- mysql-client
```bash
sudo apt-get install mysql-client
```

## Instalacja

1. Klonowanie repozytorium:
```bash
git clone https://github.com/ZMejer/PCPP2023-miernik-wiedzy.git
```
lub 
```bash
git clone git@github.com:ZMejer/PCPP2023-miernik-wiedzy.git
```

2. Przejście do katalogu projektu:
```bash
cd PCPP2023-miernik-wiedzy
```

3. Uruchamianie dockera:
```bash
docker compose up
```
4. Uruchamianie projektu:
```bash
cd miernik-wiedzy
cmake .
make
./miernik-wiedzy.app
```
