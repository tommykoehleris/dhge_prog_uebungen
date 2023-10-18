// Anzahl der Gleichungen
#define GL_ANZ 2

// Anzahl der Punkte
#define ANZAHL 300000

// Nummer des ersten anzuzeigenden Punktes
#define ERSTER 100

// Wahrscheinlichkeit der Gleichungssysteme: Sei x zufällig 0...99:
// Nimm die Gleichung i mit prozent[i-1] <= x < prozent[i]
int prozent[GL_ANZ] = { 79, 100 };

// 6 Koeffizienten mit je GL_ANZ Werten (pro Gleichung ein Wert)
koeff c[6][GL_ANZ] =
{
  {
    { 0.824074, 0.6, 1, 0.008 },
    { 0.088272, 0.05, 0.12, 0.005 }
  }, {
    { 0.281482, 0.2, 0.4, 0.009 },
    { 0.520988, 0.4, 0.65, 0.007 }
  }, {
    { -1.88229, -2, -1.7, 0.007 },
    { 0.78536, 0.65, 0.9, 0.007 }
  }, {
    { -0.212346, -0.3, -0.15, 0.006 },
    { -0.463889, -0.6, -0.3, 0.009 }
  }, {
    { 0.864198, 0.7, 1, 0.01 },
    { -0.377778, -0.5, -0.25, 0.007 }
  }, {
    { -0.110607, -0.2, -0.05, 0.003 },
    { 8.0958, 7, 9, 0.011 }
  }
};

// Farbwerte des ersten Punktes:
#define ROT 255
#define GRUEN 255
#define BLAU 0

// Farbänderungstabelle
farbinfo farbe[GL_ANZ] = {
  { 0, 80, 80, 255, 60, -20 },
  { 100, 80, 80, -60, -70, 120 }
};
