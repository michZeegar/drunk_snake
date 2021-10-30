# Drunken Snake

## Beschreibung der Welt:

	- Spielfeld mit 15 x 15 Feldern.
	- Maximale Länge der Schlange ist 10. Diese Länge soll noch beobachtet werden können.
	- Man spielt auf einem Donut: Wenn man das Feld oben verlässt kommt man unten wieder herein. Alle anderen Fälle analog

---	
## Start:

Gestartet wird mit einer zufälligen Schlange der Länge 3 und einem zufälligen Ziel.
Das Ziel kann unter der Schlange liegen.

---
## Zustandsraum:

Zustände bestehen aus:
		1) Koordinate des Ziels
		2) Koordinate vom Kopf
		3) Alle Richtungen in welche der nächste Teil vom Körper kommt
		
Alle möglichen Kombination müssen durchnummeriert werden, oder euer Code muss mit Tupeln zurecht kommen.
Selbstkollisionen sind nicht erlaubt.

---
## Dynamik f(x,u,w):

Die Funktion f(x,u,w) kann mit einem Zustand x, einer Aktion u und dem Zufallsparameter w aufgerufen werden um einen der Nachfolger (deterministisch) zu berechnen. Die gesamte Stochastik wird in der Variable w ausgedrückt.
Da die Schlange betrunken ist, gibt es eine Tendenz eine in Blickrichtung Rechts verschobene Aktion auszuführen.

Als Beispiel: Die Schlange schaut auf dem Feld nach links, als Aktion wird "ein Feld nach unten" an f(x,u,w) übergeben. Nun gibt es zwei mögliche nachfolge Zustände
Die Aktion wird wie geplant ausgeführt, der Kopf der Schlange ist nun eins weiter unten auf dem Feld.
Die Aktion wird falsch durgeführt, die Schlange ist statt nach unten weiter in Blickrichtung gelaufen (die geplante Richtung "nach Unten" wurde aus der Sicht der Schlange nach Rechts verschoben und zeigt nun nach Links).
Der erste Fall soll in 80% der Fälle eintreten, der zweite in 20%.
Mit der Variable w könnt ihr Kontrolieren welcher Fall eintritt: 
	w = 0 bedeutet der erste und w = 1 der zweite. Mit den bekannten Wahrscheinlichkeit könnt ihr so den Erwartungswert im Code berechnen.
Ist die Aktion bereits nach Rechts zu gehen (aus Sicht der Schlange) so wird der Übergang deterministisch.
Bei Kollisionen oder beim Überschreiten der Maximallänge (größer als 10) wird wieder von vorne Angefangen (ein zufälliger Start wie oben Beschrieben wird als Nachfolge Zustand verwendet). 
Um genau zu sein: Hat die Schlange die Länge 10 und sammelt ein Ziel ein wird das Spiel zurückgesetzt.
Beim einsammeln eines Ziels wird ein neues erstellt, es kann auch unter der Schlange liegen. Das ist nur für die Visualisierung und dem Menschen unschön, nicht aber für VI.

---
## Aktionsraum:

Aktionen sind die drei Möglichen Nachbarfelder als Bewegungsrichtung.
Die Aktion welche den Kopf in den Körper bewegt steht nicht zur Verfügung.
Anders als beim bekanntem Snake gibt es keine konstante Geschwindigkeit.

### Kostenfunktion g(x,u,w):

Als Ein-Schritt Kostenfunktion wird die negative Länge der Schlange verwendet.
Evtl. muss auch das einsammeln Belohnt werden.
Wir wollen natürlich, dass die Schlange möglichst lang wird: Kostenfunktionen, welche einen Bonus für das Einsammeln multipliziert mit der Länge vergeben, wären also auch denkbar
Genaue Werte/Funktionen kann man quasi nicht vorhersagen, deswegen ist Trial-and-error angesagt bis ihr eine Funktionierende lösung habt.
Generell hängt die Kostenfunktion von allen drei Variabln ab, man muss diese aber nicht verwenden wenn sie nicht benötigt werden. Insbesondere sind die Kosten hier im Kurs deterministisch, also unabhängig von w.


---
## Visualisierung:

In eurem C++ Code liegt bereits alles vor was ihr für eine Visualisierung braucht.
Baut deswegen eine einfache GUI in Qt zusammen und nutzt diese um das Snake Spiel und eure Strategie darzustellen.
Es bietet sich an die Strategie zu berechnen und abzuspeichern, die Visualisierung kann diese dann laden und darstellen.
Evtl. müsst ihr euch gedanken machen wie man effizient die Strategie handhaben kann.
Neben der Darstellung der Schlange ist auch ein Punktestand notwendig, damit man für den Wettbewerb einen Wert hat:
Anzahl der eingesammelten Ziele seit Spielbeginn.
Durchschnittliche Länge, gemessen wenn ein Reset auftaucht.
Anzahl der Selbstkollisionen seit Spielbeginn.

---
## Asynchronous Value Iteration:

Fangt mit einem kleinen Snake-Game an und löst es erstmal Synchron, also ein Zustand nach dem anderen updaten und das "unendlich oft" (lang genug bis sich V nicht mehr ändert).
Dann habt ihr eine Vergleichslösung wenn ihr den Algorithmus parallel und verteilt implementiert.
Der Discount Faktor gamma liegt im Bereich (0,1). Beide Intervallgrenzen sind ausgeschlossen.
Der klassiker ist 0.9, aber generell gilt: Kleinere Werte beschleunigen die Konvergenz, aber zu kleine Werte können evtl. die Entscheidungen beeinflussen (zum Schlechteren).
Sobald euer Code läuft könnt ihr euch hier ein wenig rumspielen und die Strategie beeinflussen.

