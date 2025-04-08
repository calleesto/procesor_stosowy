# Format logów:

Każde wejście w logu zaczyna się od:
=== STAN STOSU ===

Drugi wiersz:
Instrukcja [NUMER], e.g. Instrukcja 69
Numer instrukcji != Numer wskaźnika.

Trzeci wiersz:
i: 69, array: 9
Gdzie i - numer wskaźnika instrukcji, array: "coś" - zawartość tablicy na indeksie i

Czwarty wiersz:
Liczba będąca kodem ascii znaku z tablicy, e.g. "9" w ascii to 57

Piąty wiersz i następne(opcjonalne):
Wypisanie stanu stosu jak komenda &

# Inne informacje
Czasami to się "rozjeżdża", są puste linie, bo na stosie jest np. \n zapisane.
W ostatnim wpisie w niektórych logach *mogą*(nie muszą) być dziwne artefakty, spowodowane nieumyślną spacją lub enterem przy odpalaniu testów
Nie wpływają na wykonanie kodu