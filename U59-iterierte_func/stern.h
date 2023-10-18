// Anzahl der Gleichungen
#define GL_ANZ 2

// Anzahl der Punkte
#define ANZAHL 300000

// Nummer des ersten anzuzeigenden Punktes
#define ERSTER 100

// Wahrscheinlichkeit der Gleichungssysteme: Sei x zufällig 0...99:
// Nimm die Gleichung i mit prozent[i-1] <= x < prozent[i]
int prozent[GL_ANZ] = { 91, 100 };

// 6 Koeffizienten mit je GL_ANZ Werten (pro Gleichung ein Wert)
koeff c[6][GL_ANZ] =
{
  {
    { 0.745455, 0.65, 0.85, 0.004 },
    { -0.424242, -0.5, -0.35, 0.003 }
  }, {
    { -0.459091, -0.5, -0.4, 0.0025 },
    { -0.065152, -0.07, -0.06, 0.0003 }
  }, {
    { 1.46028, 1.2, 1.7, 0.011 },
    { 3.80957, 3.5, 4.1, 0.013 }
  }, {
    { 0.406061, 0.3, 0.5, 0.0055 },
    { -0.175758, -0.2, -0.15, 0.0007 }
  }, {
    { 0.887121, 0.8, 1, 0.0035 },
    { -0.218182, -0.24, -0.18, 0.0009 }
  }, {
    { 0.691072, 0.6, 0.8, 0.0045 },
    { 6.74148, 6.5, 7, 0.0155 }
  }
};

// Farbwerte des ersten Punktes:
#define ROT 0
#define GRUEN 255
#define BLAU 0

// Farbänderungstabelle
farbinfo farbe[GL_ANZ] = {
  { 95, 105, 0, 0, 5, 0 },
  { 0, 60, 0, 255, 0, 0 }
};
